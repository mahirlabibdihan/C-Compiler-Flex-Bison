%option noyywrap
%option yylineno 

%x EMPTY_CHAR
%x SINGLE_CHAR
%x MULTI_CHAR
%x STR_STATE
%x S_COMMENT_STATE
%x D_COMMENT_STATE

%{
#include <iostream>
#include <fstream>
#include "../01_Symbol_Table/1905072_SymbolTable.h"
#include "../01_Symbol_Table/1905072_SymbolInfo.h"
#include "../01_Symbol_Table/1905072_ScopeTable.h"
#include "1905072_Lexical_Analyzer.h"
#include "y.tab.h"
using namespace std;

extern YYSTYPE yylval;
void yyerror(char *);

string res;
string res_plain;

string ans_char;
string ans_char_plain;

string comment;
%}

WHITESPACE [ \t\f\r\v]+ 
NEWLINE [\r]?\n
KEYWORDS ("break"|"case"|"char"|"continue"|"default"|"do"|"double"|"else"|"float"|"for"|"if"|"int"|"return"|"switch"|"void"|"while")

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

ADDOP [+-]
MULOP [*/%]
INCOP ("++"|"--")
RELOP ("<"|"<="|">"|">="|"=="|"!=")
ASSIGNOP [=]
LOGICOP ("&&"|"||")
NOT [!]
LPAREN [(]
RPAREN [)]
LCURL [{]
RCURL [}]
LTHIRD ("[")
RTHIRD ("]")
COMMA [,]
SEMICOLON [;]
S_QUOTE [\']
D_QUOTE [\"]
ESCAPE_SEQUENCE (\\.)
ANYTHING .|{NEWLINE}
%%

{WHITESPACE}  					{ }
{NEWLINE} 						{ }

"if" 		{return IF;}
"else" 		{return ELSE;}
"switch" 	{return SWITCH;}
"case" 		{return CASE;}
"for" 		{return FOR;}
"do" 		{return DO;}
"while" 	{return WHILE;}
"int" 		{return INT;}
"float" 	{return FLOAT;}
"char" 		{return CHAR;}
"double" 	{return DOUBLE;}
"void" 		{return VOID;}
"default" 	{return DEFAULT;}
"break" 	{return BREAK;}
"return"	{return RETURN;}
"continue" 	{return CONTINUE;}
"printf"    {return PRINTLN;}

{INTEGER}						{ addConstant("CONST_INT"); return CONST_INT; }
{FLOATING_POINT}				{ addConstant("CONST_FLOAT"); return CONST_FLOAT; }
{TOO_MANY_DECIMAL} 				{ printErrorLog("Too Many Decimal Points "+string(yytext)); }
{ILL_NUM} 						{ printErrorLog("Ill formed number "+string(yytext)); }
{IDENTIFIER}					{ addIdentifier("ID"); return ID; }
{NON_IDENTIFIER} 				{ printErrorLog("Invalid prefix on ID or invalid suffix on Number "+string(yytext)); }
{ADDOP} 						{ addOperator("ADDOP"); return ADDOP; }
{MULOP} 						{ addOperator("MULOP"); return MULOP; }
{INCOP} 						{ addOperator("INCOP"); return INCOP; }
{RELOP} 						{ addOperator("RELOP"); return DECOP; }
{ASSIGNOP} 						{ addOperator("ASSIGNOP"); return RELOP; }
{LOGICOP} 						{ addOperator("LOGICOP"); return LOGICOP; }
{NOT} 							{ addOperator("NOT"); return NOT; }
{LPAREN} 						{ addOperator("LPAREN"); return LPAREN; }
{RPAREN} 						{ addOperator("RPAREN"); return RPAREN; }
{LCURL} 						{ addOperator("LCURL"); return LCURL; }
{RCURL} 						{ addOperator("RCURL");  return RCURL; }
{LTHIRD} 						{ addOperator("LTHIRD"); return LTHIRD; }
{RTHIRD} 						{ addOperator("RTHIRD"); return RTHIRD; }
{COMMA} 						{ addOperator("COMMA"); return COMMA; }
{SEMICOLON} 					{ addOperator("SEMICOLON"); return SEMICOLON; }
{S_QUOTE}						{
									ans_char_plain.clear();
									ans_char.clear();
									BEGIN EMPTY_CHAR;
								}
<EMPTY_CHAR>{ESCAPE_SEQUENCE}	{ 
									ans_char += makeSpecialChar(yytext); 
									ans_char_plain += yytext; 
									BEGIN SINGLE_CHAR; 
								} 
<EMPTY_CHAR>{S_QUOTE}			{ 	
									printErrorLog("Empty character constant error ''");
									BEGIN INITIAL; 
								}
<EMPTY_CHAR>.					{ 
									ans_char += yytext;
									ans_char_plain += yytext; 
									BEGIN SINGLE_CHAR;
								}
<EMPTY_CHAR>{NEWLINE} 			{
									printErrorLog("Unterminated character '"+ans_char_plain);
									BEGIN INITIAL;
								}
<EMPTY_CHAR><<EOF>> 			{
									printErrorLog("Unterminated character '"+ans_char_plain);
									BEGIN INITIAL;
								}
<SINGLE_CHAR>{NEWLINE} 			{
									printErrorLog("Unterminated character '"+ans_char_plain);
									BEGIN INITIAL;
								}
<SINGLE_CHAR><<EOF>>			{
									printErrorLog("Unterminated character '"+ans_char_plain);
									BEGIN INITIAL;
								}
<MULTI_CHAR>{NEWLINE}			{
									printErrorLog("Unterminated character '"+ans_char_plain);
									BEGIN INITIAL;
								}
<MULTI_CHAR><<EOF>>				{
									printErrorLog("Unterminated character '"+ans_char_plain);
									BEGIN INITIAL;
								}
<MULTI_CHAR>{S_QUOTE}			{
									printErrorLog("Multi character constant error '"+ans_char_plain+"'"); 
									BEGIN INITIAL; 
								}
<SINGLE_CHAR>{S_QUOTE}			{ addCharacter("CONST_CHAR",ans_char_plain); BEGIN INITIAL; return CONST_CHAR; }
<SINGLE_CHAR>.					{ ans_char_plain += yytext; BEGIN MULTI_CHAR; }
<MULTI_CHAR>.					{ ans_char_plain += yytext; }
{D_QUOTE}						{
									nl_inside = 0;
									res.clear();
									res_plain.clear();
									BEGIN STR_STATE;
								}	
<STR_STATE>{ESCAPE_SEQUENCE}	{ res += makeSpecialChar(yytext), res_plain += yytext; }	
<STR_STATE>\\{NEWLINE}        	{ nl_inside++; res_plain += yytext; }
<STR_STATE>{D_QUOTE}       		{
									addString("STRING",res_plain,res);
									BEGIN(INITIAL);
									return STRING;
								}
<STR_STATE>.            		{ res += yytext; res_plain+= yytext; }
<STR_STATE>{NEWLINE} 			{ 
									printErrorLog("Unterminated String \""+res_plain, yylineno-nl_inside);
									BEGIN INITIAL;
								}
<STR_STATE><<EOF>>				{ 
									printErrorLog("Unterminated String \""+res_plain, yylineno-nl_inside);
									BEGIN INITIAL;
								}
"//"							{	
									nl_inside = 1;
									comment.clear();
									comment += yytext;
									BEGIN S_COMMENT_STATE;
								}	
"/*"							{
									nl_inside = 0;
									comment.clear();
									comment += yytext;
									BEGIN D_COMMENT_STATE;
								}	
<S_COMMENT_STATE>\\{NEWLINE}  	{ 
									nl_inside++;
									comment += yytext;
								}
<S_COMMENT_STATE>{NEWLINE}		{ 
									addComment("COMMENT",comment);
									BEGIN INITIAL;
								}
<S_COMMENT_STATE><<EOF>>      	{ 
									addComment("COMMENT",comment);
									BEGIN INITIAL;
								}
<S_COMMENT_STATE>.            	{ comment += yytext; }
<D_COMMENT_STATE>"*/"       	{ 
									comment += yytext;
									addComment("COMMENT",comment);
									BEGIN INITIAL;
								}
<D_COMMENT_STATE><<EOF>>       	{ 
									printErrorLog("Unterminated Comment "+ comment);
									BEGIN INITIAL;
								}
<D_COMMENT_STATE>{NEWLINE}   	{ nl_inside++; comment += yytext;} 
<D_COMMENT_STATE>{ANYTHING}  	{ comment += yytext; } 
. 								{ printErrorLog("Unrecognized character "+ string(yytext)); }

%%
