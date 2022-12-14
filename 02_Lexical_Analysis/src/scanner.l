%option noyywrap
%option yylineno 

%{
#include <fstream>
#include "../include/ErrorHandler.hpp"
#include "../include/Tokenizer.hpp"
#include "../include/Logger.hpp"
#include "../include/SymbolTable.hpp"
#include "../include/Util.hpp"
#include "../include/LineTracker.hpp"

extern std::ofstream logout;
extern std::ofstream tokenout;
extern int error_count;
extern SymbolTable *table;
extern LineTracker *line_trkr;
void installID(std::string);
%}

WHITESPACE [ \t\f\r\v]+ 
NEWLINE [\r]?\n
KEYWORDS (break|case|char|continue|default|do|double|else|float|for|if|int|return|switch|void|while)
OPERATOR ("+"|"-"|"*"|"/"|"%"|"++"|"--"|"<"|"<="|">"|">="|"=="|"!="|=|"&&"|"||"|"!"|"("|")"|"["|"]"|","|";")

LCURL [{]
RCURL [}]
ESCAPE_SEQUENCE (\\.)

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
%%

{WHITESPACE}  					{ /* Do nothing */ }
{NEWLINE} 						{ line_trkr->handleNewLine(); }
{KEYWORDS}						{ 
									Tokenizer::generateToken(
										Tokenizer::TokenType::KEYWORD_TOKEN, 
										yytext
									); 
									Logger::printLogData(
										Logger::LogType::KEYWORD_LOG,
										line_trkr->getLineNumber(),yytext
									); 
								}
{LCURL} 						{ 
									Tokenizer::generateToken(Tokenizer::OPERATOR_TOKEN,yytext); 
									Logger::printLogData(
										Logger::LogType::OPERATOR_LOG,
										line_trkr->getLineNumber(),yytext
									);
									table->enterScope();
								}
{RCURL} 						{ 
									Tokenizer::generateToken(Tokenizer::OPERATOR_TOKEN,yytext); 
									Logger::printLogData(
										Logger::LogType::OPERATOR_LOG,
										line_trkr->getLineNumber(),yytext
									);
									table->exitScope();
								}
{OPERATOR}						{ 
									Tokenizer::generateToken(Tokenizer::OPERATOR_TOKEN,yytext); 
									Logger::printLogData(
										Logger::LogType::OPERATOR_LOG,
										line_trkr->getLineNumber(),yytext
									);
								}
{INTEGER}						{ 
									Tokenizer::generateToken(Tokenizer::INTEGER_TOKEN, yytext); 	
									Logger::printLogData(
										Logger::LogType::INTEGER_LOG,
										line_trkr->getLineNumber(),yytext
									);
								}
{FLOATING_POINT}				{ 
									Tokenizer::generateToken(Tokenizer::FLOAT_TOKEN, yytext); 
									Logger::printLogData(
										Logger::LogType::FLOAT_LOG,
										line_trkr->getLineNumber(),yytext
									);
								}
{VALID_STRING}					{ 	
									Tokenizer::generateToken(Tokenizer::STRING_TOKEN, yytext); 
									Logger::printLogData(
										Logger::LogType::STRING_LOG,line_trkr->getLineNumber(),
										yytext
									);
									line_trkr->handleString(yytext);
								}
{UNTERMINATED_STRING} 			{ 
									line_trkr->handleString(yytext);
									ErrorHandler::handleLexicalError(
										ErrorHandler::LexicalError::UNTERMINATED_STRING, 
										line_trkr->getLineNumber(), yytext
									); 
								}
{SINGLE_COMMENT}				{ 
									Logger::printLogData(
										Logger::LogType::SINGLE_COMMENT_LOG,
										line_trkr->getLineNumber(),yytext
									);  
									line_trkr->handleSingleComment(yytext);
								}  
{MULTI_COMMENT} 				{ 
									Logger::printLogData(
										Logger::LogType::MULTI_COMMENT_LOG,
										line_trkr->getLineNumber(),yytext
									); 
									line_trkr->handleMultiComment(yytext);	
								}
{INCOMPLETE_MULTI_COMMENT} 		{ 	
									line_trkr->handleMultiComment(yytext);
									ErrorHandler::handleLexicalError(
										ErrorHandler::LexicalError::UNTERMINATED_COMMENT,
										line_trkr->getLineNumber(),yytext
									); 	
								}
{TOO_MANY_DECIMAL} 				{ 
									ErrorHandler::handleLexicalError(
										ErrorHandler::LexicalError::TOO_MANY_DECIMAL,
										line_trkr->getLineNumber(),yytext
									); 
								}
{ILL_NUM} 						{ 
									ErrorHandler::handleLexicalError(
										ErrorHandler::LexicalError::ILL_NUMBER,
										line_trkr->getLineNumber(),yytext
									); 
								}
{VALID_CHAR} 					{ 
									Tokenizer::generateToken(Tokenizer::CHARACTER_TOKEN, yytext);
									Logger::printLogData(
										Logger::LogType::CHARACTER_LOG,
										line_trkr->getLineNumber(),yytext
									);
								}
{MULTI_CHAR} 					{ 
									ErrorHandler::handleLexicalError(
										ErrorHandler::LexicalError::MULTI_CHARACTER,
										line_trkr->getLineNumber(),yytext
									); 
								}
{UNTERMINATED_CHAR} 			{ 
									ErrorHandler::handleLexicalError(
										ErrorHandler::LexicalError::UNTERMINATED_CHARACTER,
										line_trkr->getLineNumber(),yytext
									); 
								}
{EMPTY_CHAR} 					{ 
									ErrorHandler::handleLexicalError(
										ErrorHandler::LexicalError::EMPTY_CHARACTER,
										line_trkr->getLineNumber(),yytext
									); 
								}
{IDENTIFIER}					{ 
									Tokenizer::generateToken(
										Tokenizer::IDENTIFIER_TOKEN, 
										yytext
									);
									Logger::printLogData(
										Logger::LogType::IDENTIFIER_LOG,
										line_trkr->getLineNumber(),yytext
									);
									installID(yytext);
									
								}
{NON_IDENTIFIER} 				{ 
									ErrorHandler::handleLexicalError(
										ErrorHandler::LexicalError::INVALID_IDENTIFIER, 
										line_trkr->getLineNumber(), yytext
									); 
								}
. 								{ 
									ErrorHandler::handleLexicalError(
										ErrorHandler::LexicalError::UNRECOGNIZED, 
										line_trkr->getLineNumber(), yytext); 
								}
%%
void installID(std::string text){
	if (table->insert(text, "ID"))
	{
		table->printAllScope();
	}
	else
	{
		logout<<"\t"<<yytext<<" already exisits in the current ScopeTable"<<std::endl;
	}
}