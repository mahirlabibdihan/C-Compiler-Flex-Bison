%option noyywrap
%option yylineno 

%{
#include <fstream>
#include "1905072_Error_Handler.hpp"
#include "1905072_Symbol_Extended.hpp"
#include "1905072_Logger.hpp"
#include "1905072_SymbolTable.hpp"
#include "1905072_Tokenizer.hpp"
#include "y.tab.h"
using namespace std;

extern int line_count;
extern SymbolTable* table;
extern Tokenizer* tknzr;
extern Logger* logger;
extern ErrorHandler* err_hndlr;
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
									tknzr->generateToken(KEYWORD_TOKEN, yytext); 
									logger->printLogData(KEYWORD_LOG,line_count,yytext); 
									return tknzr->getToken(KEYWORD_TOKEN, yytext);
								}
"println"						{ 
									// tknzr->generateToken(KEYWORD_TOKEN, yytext); 
									logger->printLogData(KEYWORD_LOG,line_count,yytext); 
									yylval.terminal = new Terminal(yytext, "PRINTLN");
									return PRINTLN;
								}
{INTEGER}						{ 
									tknzr->generateToken(INTEGER_TOKEN, yytext); 	
									logger->printLogData(INTEGER_LOG,line_count,yytext);
									// if (table->insert(SymbolInfo(yytext, "CONST_INT")))
									// {
									// 	table->printAllScope();
									// }
									return tknzr->getToken(INTEGER_TOKEN, yytext);
								}
{FLOATING_POINT}				{ 
									tknzr->generateToken(FLOAT_TOKEN, yytext); 
									logger->printLogData(FLOAT_LOG,line_count,yytext);
									// if (table->insert(SymbolInfo(yytext, "CONST_FLOAT")))
									// {
									// 	table->printAllScope();
									// }
									return tknzr->getToken(FLOAT_TOKEN, yytext);
								}
{VALID_STRING}					{ 
									tknzr->generateToken(CHARACTER_TOKEN, yytext); 
									logger->printLogData(STRING_LOG,line_count,yytext);
									line_count = yylineno; 
									return tknzr->getToken(CHARACTER_TOKEN, yytext); 
								}
{UNTERMINATED_STRING} 			{ 
									err_hndlr->handleLexicalError(UNTERMINATED_STRING, line_count, yytext); 
									line_count = yylineno; 
								}
{SINGLE_COMMENT}				{ 
									logger->printLogData(COMMENT_LOG,line_count,yytext); 
									line_count = yylineno; 
								}  
{MULTI_COMMENT} 				{ 
									logger->printLogData(COMMENT_LOG,line_count,yytext); 
									line_count = yylineno; 
								}
{INCOMPLETE_MULTI_COMMENT} 		{ 	
									err_hndlr->handleLexicalError(UNTERMINATED_COMMENT,line_count,yytext); 
									line_count = yylineno; 
								}
{TOO_MANY_DECIMAL} 				{ err_hndlr->handleLexicalError(TOO_MANY_DECIMAL,line_count,yytext); }
{ILL_NUM} 						{ err_hndlr->handleLexicalError(ILL_NUMBER,line_count,yytext); }
{VALID_CHAR} 					{ 
									tknzr->generateToken(CHARACTER_TOKEN, yytext);
									logger->printLogData(CHARACTER_LOG,line_count,yytext);
									// if (table->insert(SymbolInfo(yytext, "CONST_CHAR")))
									// {
									// 	table->printAllScope();
									// }
									return tknzr->getToken(CHARACTER_TOKEN, yytext);
								}
{MULTI_CHAR} 					{ err_hndlr->handleLexicalError(MULTI_CHARACTER,line_count,yytext); }
{UNTERMINATED_CHAR} 			{ err_hndlr->handleLexicalError(UNTERMINATED_CHARACTER,line_count,yytext); line_count = yylineno; }
{EMPTY_CHAR} 					{ err_hndlr->handleLexicalError(EMPTY_CHARACTER,line_count,yytext); }
{LCURL} 						{ 
									tknzr->generateToken(OPERATOR_TOKEN,yytext); 
									logger->printLogData(OPERATOR_LOG,line_count,yytext);
									// cout<<"Entered new scope "<<line_count<<endl;
									// table->enterScope();
									return tknzr->getToken(OPERATOR_TOKEN,yytext); 
								}
{RCURL} 						{ 
									tknzr->generateToken(OPERATOR_TOKEN,yytext); 
									logger->printLogData(OPERATOR_LOG,line_count,yytext);
									// table->printAllScope();
									// table->exitScope();
									return tknzr->getToken(OPERATOR_TOKEN,yytext); 
								}
{OPERATOR}						{ 
									tknzr->generateToken(OPERATOR_TOKEN,yytext); 
									logger->printLogData(OPERATOR_LOG,line_count,yytext);
									return tknzr->getToken(OPERATOR_TOKEN,yytext); 
								}
{IDENTIFIER}					{ 
									tknzr->generateToken(IDENTIFIER_TOKEN, yytext);
									logger->printLogData(IDENTIFIER_LOG,line_count,yytext);
									// if (table->insert(SymbolInfo(yytext, "ID")))
									// {
									// 	table->printAllScope();
									// }
									return tknzr->getToken(IDENTIFIER_TOKEN, yytext);
								}
{NON_IDENTIFIER} 				{ err_hndlr->handleLexicalError(INVALID_IDENTIFIER, line_count, yytext); }
. 								{ err_hndlr->handleLexicalError(UNRECOGNIZED, line_count, yytext); }
<<EOF>> {
    return 0;
}
%%
