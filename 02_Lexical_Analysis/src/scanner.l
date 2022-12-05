%option noyywrap
%option yylineno 

%{
#include <fstream>
#include "../include/Error_Handler.hpp"
#include "../include/Tokenizer.hpp"
#include "../include/Logger.hpp"
#include "../include/SymbolTable.hpp"

extern std::ofstream logout;
extern std::ofstream tokenout;
extern int line_count;
extern int error_count;
extern SymbolTable *table;

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
									Tokenizer::generateToken(Tokenizer::TokenType::KEYWORD_TOKEN, yytext); 
									Logger::printLogData(Logger::LogType::KEYWORD_LOG,yylineno,yytext); 
								}
{INTEGER}						{ 
									Tokenizer::generateToken(Tokenizer::INTEGER_TOKEN, yytext); 	
									Logger::printLogData(Logger::LogType::INTEGER_LOG,yylineno,yytext);
								}
{FLOATING_POINT}				{ 
									Tokenizer::generateToken(Tokenizer::FLOAT_TOKEN, yytext); 
									Logger::printLogData(Logger::LogType::FLOAT_LOG,yylineno,yytext);
								}
{VALID_STRING}					{ 
									Tokenizer::generateToken(Tokenizer::STRING_TOKEN, yytext); 
									Logger::printLogData(Logger::LogType::STRING_LOG,yylineno,yytext);
									line_count = yylineno; 
								}
{UNTERMINATED_STRING} 			{ 
									ErrorHandler::handleLexicalError(ErrorHandler::LexicalError::UNTERMINATED_STRING, yylineno, yytext); 
									line_count = yylineno; 
								}
{SINGLE_COMMENT}				{ 
									Logger::printLogData(Logger::LogType::SINGLE_COMMENT_LOG,yylineno,yytext); 
									line_count = yylineno; 
								}  
{MULTI_COMMENT} 				{ 
									Logger::printLogData(Logger::LogType::MULTI_COMMENT_LOG,yylineno,yytext); 
									line_count = yylineno; 
								}
{INCOMPLETE_MULTI_COMMENT} 		{ 	
									ErrorHandler::handleLexicalError(ErrorHandler::LexicalError::UNTERMINATED_COMMENT,yylineno,yytext); 
									line_count = yylineno; 
								}
{TOO_MANY_DECIMAL} 				{ ErrorHandler::handleLexicalError(ErrorHandler::LexicalError::TOO_MANY_DECIMAL,yylineno,yytext); }
{ILL_NUM} 						{ ErrorHandler::handleLexicalError(ErrorHandler::LexicalError::ILL_NUMBER,yylineno,yytext); }
{VALID_CHAR} 					{ 
									Tokenizer::generateToken(Tokenizer::CHARACTER_TOKEN, yytext);
									Logger::printLogData(Logger::LogType::CHARACTER_LOG,yylineno,yytext);
								}
{MULTI_CHAR} 					{ ErrorHandler::handleLexicalError(ErrorHandler::LexicalError::MULTI_CHARACTER,yylineno,yytext); }
{UNTERMINATED_CHAR} 			{ 
									ErrorHandler::handleLexicalError(ErrorHandler::LexicalError::UNTERMINATED_CHARACTER,yylineno,yytext); 
									line_count = yylineno; 
								}
{EMPTY_CHAR} 					{ ErrorHandler::handleLexicalError(ErrorHandler::LexicalError::EMPTY_CHARACTER,yylineno,yytext); }
{LCURL} 						{ 
									Tokenizer::generateToken(Tokenizer::OPERATOR_TOKEN,yytext); 
									Logger::printLogData(Logger::LogType::OPERATOR_LOG,yylineno,yytext);
									table->enterScope();
								}
{RCURL} 						{ 
									Tokenizer::generateToken(Tokenizer::OPERATOR_TOKEN,yytext); 
									Logger::printLogData(Logger::LogType::OPERATOR_LOG,yylineno,yytext);
									table->exitScope();
								}
{OPERATOR}						{ 
									Tokenizer::generateToken(Tokenizer::OPERATOR_TOKEN,yytext); 
									Logger::printLogData(Logger::LogType::OPERATOR_LOG,yylineno,yytext);}
{IDENTIFIER}					{ 
									Tokenizer::generateToken(Tokenizer::IDENTIFIER_TOKEN, yytext);
									Logger::printLogData(Logger::LogType::IDENTIFIER_LOG,yylineno,yytext);
									if (table->insert(yytext, "ID"))
									{
										table->printAllScope();
									}
									else
									{
										logout<<yytext<<" already exisits in the current ScopeTable"<<std::endl;
									}
								}
{NON_IDENTIFIER} 				{ ErrorHandler::handleLexicalError(ErrorHandler::LexicalError::INVALID_IDENTIFIER, yylineno, yytext); }
. 								{ ErrorHandler::handleLexicalError(ErrorHandler::LexicalError::UNRECOGNIZED, yylineno, yytext); }

%%