%option noyywrap

%{
#include "../include/LexicalAnalyzer.hpp"
extern LexicalAnalyzer *lexer;
%}

WHITESPACE [ \t\f\r\v]+ 
NEWLINE ([\r]?\n)
KEYWORD (break|case|char|continue|default|do|double|else|float|for|if|int|return|switch|void|while)
OPERATOR ("+"|"-"|"*"|"/"|"%"|"++"|"--"|">>"|"<<"|"^"|"|"|"&"|"<"|"<="|">"|">="|"=="|"!="|=|"&&"|"||"|"!"|"("|")"|"["|"]"|","|";"|"{"|"}")

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

%{
    /*ESCAPE_SEQUENCE (\\['\"nt\\afrbv0])*/
%}

ESCAPE_SEQUENCE (\\.)
EMPTY_CHAR ''
CHAR_CONST ({ESCAPE_SEQUENCE}|[^(\')(\\)(\r\n)])
VALID_CHAR ('{CHAR_CONST}')
MULTI_CHAR ('{CHAR_CONST}{2,}')
UNFINISHED_CHAR '({CHAR_CONST})*(\\)?

STRING_CONST ({ESCAPE_SEQUENCE}|[^(\")(\\)(\r\n)])
UNFINISHED_STRING (\"((\\{NEWLINE})?({STRING_CONST})*)*)(\\)?
VALID_STRING {UNFINISHED_STRING}\"

SINGLE_COMMENT "//"((\\{NEWLINE})?.*)*

UNFINISHED_COMMENT ("/*"([^\/]|([^(\*)(\/)][\/]+))*)
MULTI_COMMENT {UNFINISHED_COMMENT}"*/"
%%
{WHITESPACE}  			{ lexer->handleWhiteSpace(yytext); }
{NEWLINE} 				{ lexer->handleNewLine(yytext); }
{KEYWORD}				{ lexer->handleKeyword(yytext); }
{OPERATOR}				{ lexer->handleOperator(yytext); }
{INTEGER}				{ lexer->handleInteger(yytext); }
{FLOATING_POINT}		{ lexer->handleFloatingPoint(yytext); }
{TOO_MANY_DECIMAL} 		{ lexer->handleTooManyDecimal(yytext); }
{ILL_NUM} 				{ lexer->handleIllNum(yytext); }
{IDENTIFIER}			{ lexer->handleIdentifier(yytext); }
{NON_IDENTIFIER} 		{ lexer->handleNonIdentifier(yytext); }
{EMPTY_CHAR} 			{ lexer->handleEmptyChar(yytext); }
{UNFINISHED_CHAR} 		{ lexer->handleUnfinishedChar(yytext); }
{VALID_CHAR} 			{ lexer->handleValidChar(yytext); }
{MULTI_CHAR} 			{ lexer->handleMultiChar(yytext); }
{UNFINISHED_STRING} 	{ lexer->handleUnfinishedString(yytext); }
{VALID_STRING}			{ lexer->handleValidString(yytext); }
{SINGLE_COMMENT}		{ lexer->handleSingleComment(yytext); }  
{UNFINISHED_COMMENT} 	{ lexer->handleUnfinishedComment(yytext); }
{MULTI_COMMENT} 		{ lexer->handleMultiComment(yytext); }
. 						{ lexer->handleUnrecognized(yytext); }
%%
void run(FILE* fin)
{
    yyin = fin;
    yylex();
}