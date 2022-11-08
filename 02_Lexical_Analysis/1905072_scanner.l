%option noyywrap
%option yylineno 

%{
#include <fstream>
#include "1905072_Error_Handler.h"
#include "1905072_Tokenizer.h"
#include "1905072_Logger.h"
#include "../01_Symbol_Table/1905072_SymbolTable.h"
using namespace std;
ofstream logout;
ofstream tokenout;
int line_count;
int error_count;
SymbolTable *table;
unsigned long sdbmHash(string str)
{
    unsigned long hash = 0;
    for (auto ch : str)
    {
        int c = ch;
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

void ScopeTable::print()
{
    logout << "ScopeTable # " << id << endl;
    for (int i = 0; i < n_buckets; i++)
    {
        SymbolInfo *cur = hash_table[i];
        if (cur == nullptr)
        {
            continue;
        }
        logout << " " << i << " --> ";

        while (cur != nullptr)
        {
            logout << "< " << cur->getName() << " : " << cur->getType() << "> ";
            cur = cur->getNext();
        }
        logout << endl;
    }
    logout << endl;
}
%}

WHITESPACE [ \t\f\r\v]+ 
NEWLINE [\r]?\n
KEYWORDS (break|case|char|continue|default|do|double|else|float|for|if|int|return|switch|void|while)

DIGIT [0-9]
DIGITS {DIGIT}+
INTEGER {DIGITS}
EXPONENT ([Ee][+-]?{INTEGER})
FLOATING_POINT {INTEGER}?(\.)?{INTEGER}{EXPONENT}?
TOO_MANY_DECIMAL {INTEGER}?(\.{DIGIT}*)+{EXPONENT}?
ILL_NUM {FLOATING_POINT}+

LETTER [a-zA-Z]
ALPHABET {LETTER}|_
ALPHANUMERIC {ALPHABET}|{DIGIT}
IDENTIFIER {ALPHABET}({ALPHANUMERIC})*
NON_IDENTIFIER {INTEGER}({ALPHANUMERIC})*


CHAR_CONST ({ESCAPE_SEQUENCE}|[^\\'(\r\n)])
VALID_CHAR ('{CHAR_CONST}')
EMPTY_CHAR ''
MULTI_CHAR ('{CHAR_CONST}{2,}')
UNTERMINATED_CHAR '({CHAR_CONST}|\\)*


STRING_CONST ({ESCAPE_SEQUENCE}|[^\\"(\r\n)])
ALL_STRING_CONST ({STRING_CONST}|\\)
VALID_STRING \"{STRING_CONST}*((\\{NEWLINE})?{STRING_CONST}*)*\"
UNTERMINATED_STRING \"{ALL_STRING_CONST}*((\\{NEWLINE})?{ALL_STRING_CONST}*)*

NOT_NEWLINE [^\r\n]

SINGLE_COMMENT "//"{NOT_NEWLINE}*((\\{NEWLINE})?{NOT_NEWLINE}*)*

INCOMPLETE_MULTI_COMMENT "/*"([^"*"]|(["*"]+[^"*/"]))*
MULTI_COMMENT {INCOMPLETE_MULTI_COMMENT}("*")*"*/"

LCURL [{]
RCURL [}]
OPERATOR ("+"|"-"|"*"|"/"|"%"|"++"|"--"|"<"|"<="|">"|">="|"=="|"!="|=|"&&"|"||"|"!"|"("|")"|"{"|"}"|"["|"]"|","|";")
ESCAPE_SEQUENCE (\\.)
%%

{WHITESPACE}  					{ /* Do nothing */ }
{NEWLINE} 						{ line_count = yylineno; }
{KEYWORDS}						{ 
									generateToken(KEYWORD_TOKEN, yytext); 
									printLogData(KEYWORD_LOG,line_count,yytext); 
								}
{INTEGER}						{ 
									generateToken(INTEGER_TOKEN, yytext); 	
									printLogData(INTEGER_LOG,line_count,yytext);
									if (table->insert(SymbolInfo(yytext, "CONST_INT")))
									{
										table->printAllScope();
									}
								}
{FLOATING_POINT}				{ 
									generateToken(FLOAT_TOKEN, yytext); 
									printLogData(FLOAT_LOG,line_count,yytext);
									if (table->insert(SymbolInfo(yytext, "CONST_FLOAT")))
									{
										table->printAllScope();
									}
								}
{VALID_STRING}					{ 
									generateToken(CHARACTER_TOKEN, yytext); 
									printLogData(STRING_LOG,line_count,yytext);
									line_count = yylineno; 
								}
{UNTERMINATED_STRING} 			{ 
									handleError(UNTERMINATED_STRING, line_count, yytext); 
									line_count = yylineno; 
								}
{SINGLE_COMMENT}				{ 
									printLogData(COMMENT_LOG,line_count,yytext); 
									line_count = yylineno; }  
{MULTI_COMMENT} 				{ 
									printLogData(COMMENT_LOG,line_count,yytext); 
									line_count = yylineno; }
{INCOMPLETE_MULTI_COMMENT} 		{ 	
									handleError(UNTERMINATED_COMMENT,line_count,yytext); 
									line_count = yylineno; 
								}
{TOO_MANY_DECIMAL} 				{ handleError(TOO_MANY_DECIMAL,line_count,yytext); }
{ILL_NUM} 						{ handleError(ILL_NUMBER,line_count,yytext); }
{VALID_CHAR} 					{ 
									generateToken(CHARACTER_TOKEN, yytext);
									printLogData(CHARACTER_LOG,line_count,yytext);
									if (table->insert(SymbolInfo(yytext, "CONST_CHAR")))
									{
										table->printAllScope();
									}
								}
{MULTI_CHAR} 					{ handleError(MULTI_CHARACTER,line_count,yytext); }
{UNTERMINATED_CHAR} 			{ handleError(UNTERMINATED_CHARACTER,line_count,yytext); line_count = yylineno; }
{EMPTY_CHAR} 					{ handleError(EMPTY_CHARACTER,line_count,yytext); }
{LCURL} 						{ 
									generateToken(OPERATOR_TOKEN,yytext); 
									printLogData(OPERATOR_LOG,line_count,yytext);
									table->enterScope();
								}
{RCURL} 						{ 
									generateToken(OPERATOR_TOKEN,yytext); 
									printLogData(OPERATOR_LOG,line_count,yytext);
									table->exitScope();
								}
{OPERATOR}						{ 
									generateToken(OPERATOR_TOKEN,yytext); 
									printLogData(OPERATOR_LOG,line_count,yytext);}
{IDENTIFIER}					{ 
									generateToken(IDENTIFIER_TOKEN, yytext);
									printLogData(IDENTIFIER_LOG,line_count,yytext);
									if (table->insert(SymbolInfo(yytext, "ID")))
									{
										table->printAllScope();
									}
								}
{NON_IDENTIFIER} 				{ handleError(INVALID_IDENTIFIER, line_count, yytext); }
. 								{ handleError(UNRECOGNIZED, line_count, yytext); }

%%
int main(int argc,char *argv[]){
	if (argc != 2)
    {
        printf("Please provide input file name and try again\n");
        return 0;
    }

    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL)
    {
        printf("Cannot open specified file\n");
        return 0;
    }

    tokenout.open("1905072_token.txt");
    logout.open("1905072_log.txt");

	table = new SymbolTable(7,sdbmHash);
    yyin = fin;
    line_count = yylineno = 1;
	error_count = 0;
    yylex();
    fclose(yyin);

    table->printAllScope();

    logout << "Total lines: " << yylineno << endl;
    logout << "Total errors: " << error_count;

    tokenout.close();
    logout.close();

    return EXIT_SUCCESS;
}