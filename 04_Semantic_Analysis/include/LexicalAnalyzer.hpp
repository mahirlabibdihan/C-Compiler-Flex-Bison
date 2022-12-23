/**
 * Author: Mahir Labib Dihan
 * Last Modified: December 16, 2022
 */
#ifndef __LEXICAL_ANALYZER_H
#define __LEXICAL_ANALYZER_H 1
#include "../include/LineTracker.hpp"
#include "../include/SymbolTable.hpp"
#include "../include/ErrorHandler.hpp"
#include "../include/Logger.hpp"
#include "../include/Tokenizer.hpp"
#include <string>
class LexicalAnalyzer
{
    LineTracker *line_trkr;
    ErrorHandler *error_hndlr;
    std::ofstream &logout;
    std::ofstream &tokenout;
    // void installID(std::string yytext);

public:
    LexicalAnalyzer(ErrorHandler *error_hndlr, std::ofstream &logout, std::ofstream &tokenout);
    ~LexicalAnalyzer();
    void handleWhiteSpace(std::string yytext);
    void handleNewLine(std::string yytext);
    void handleKeyword(std::string yytext);
    void handleOperator(std::string yytext);
    void handleInteger(std::string yytext);
    void handleFloatingPoint(std::string yytext);
    void handleTooManyDecimal(std::string yytext);
    void handleIllNum(std::string yytext);
    void handleIdentifier(std::string yytext);
    void handleNonIdentifier(std::string yytext);
    void handleUnfinishedChar(std::string yytext);
    void handleEmptyChar(std::string yytext);
    void handleValidChar(std::string yytext);
    void handleMultiChar(std::string yytext);
    void handleUnfinishedString(std::string yytext);
    void handleValidString(std::string yytext);
    void handleSingleComment(std::string yytext);
    void handleUnfinishedComment(std::string yytext);
    void handleMultiComment(std::string yytext);
    void handleUnrecognized(std::string yytext);
    int getLineCount();
    int getErrorCount();
};
#endif