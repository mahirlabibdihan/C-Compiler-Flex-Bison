/**
 * Author: Mahir Labib Dihan
 * Last modified: January 18, 2023
 */
#include "../include/LexicalAnalyzer.hpp"
#include "../include/Tokenizer.hpp"
#include "../include/Logger.hpp"
#include "../include/ErrorHandler.hpp"
#include "../include/SymbolTable.hpp"
#include <fstream>

LexicalAnalyzer::LexicalAnalyzer(ErrorHandler *error_hndlr, std::ofstream &log, std::ofstream &token) : logout(log), tokenout(token)
{
    this->error_hndlr = error_hndlr;
    this->line_trkr = new LineTracker(1);
}

LexicalAnalyzer::~LexicalAnalyzer()
{
    delete line_trkr;
}

void LexicalAnalyzer::handleWhiteSpace(std::string yytext)
{
    /* Do nothing */
}

void LexicalAnalyzer::handleNewLine(std::string yytext)
{
    line_trkr->handleNewLine();
}

void LexicalAnalyzer::handleKeyword(std::string yytext)
{
    tokenout << Tokenizer::generateToken(
                    Tokenizer::TokenType::KEYWORD_TOKEN,
                    yytext)
             << std::endl;
    logout << Logger::getLogData(
                  Logger::LogType::KEYWORD_LOG,
                  line_trkr->getLineNumber(), yytext)
           << std::endl;
}

void LexicalAnalyzer::handleOperator(std::string yytext)
{
    tokenout << Tokenizer::generateToken(Tokenizer::OPERATOR_TOKEN, yytext) << std::endl;
    logout << Logger::getLogData(
                  Logger::LogType::OPERATOR_LOG,
                  line_trkr->getLineNumber(), yytext)
           << std::endl;
}

void LexicalAnalyzer::handleInteger(std::string yytext)
{
    tokenout << Tokenizer::generateToken(Tokenizer::INTEGER_TOKEN, yytext) << std::endl;
    logout << Logger::getLogData(
                  Logger::LogType::INTEGER_LOG,
                  line_trkr->getLineNumber(), yytext)
           << std::endl;
}

void LexicalAnalyzer::handleFloatingPoint(std::string yytext)
{
    tokenout << Tokenizer::generateToken(Tokenizer::FLOAT_TOKEN, yytext) << std::endl;
    logout << Logger::getLogData(
                  Logger::LogType::FLOAT_LOG,
                  line_trkr->getLineNumber(), yytext)
           << std::endl;
}

void LexicalAnalyzer::handleTooManyDecimal(std::string yytext)
{
    logout << error_hndlr->handleLexicalError(
                  ErrorHandler::LexicalError::TOO_MANY_DECIMAL,
                  line_trkr->getLineNumber(), yytext)
           << std::endl;
}

void LexicalAnalyzer::handleIllNum(std::string yytext)
{
    logout << error_hndlr->handleLexicalError(
                  ErrorHandler::LexicalError::ILL_NUMBER,
                  line_trkr->getLineNumber(), yytext)
           << std::endl;
}

void LexicalAnalyzer::handleIdentifier(std::string yytext)
{
    tokenout << Tokenizer::generateToken(
                    Tokenizer::IDENTIFIER_TOKEN,
                    yytext)
             << std::endl;
    logout << Logger::getLogData(
                  Logger::LogType::IDENTIFIER_LOG,
                  line_trkr->getLineNumber(), yytext)
           << std::endl;
    // installID(yytext);
}

void LexicalAnalyzer::handleNonIdentifier(std::string yytext)
{
    logout << error_hndlr->handleLexicalError(
                  ErrorHandler::LexicalError::INVALID_IDENTIFIER,
                  line_trkr->getLineNumber(), yytext)
           << std::endl;
}

void LexicalAnalyzer::handleEmptyChar(std::string yytext)
{
    logout << error_hndlr->handleLexicalError(
                  ErrorHandler::LexicalError::EMPTY_CHARACTER,
                  line_trkr->getLineNumber(), yytext)
           << std::endl;
}

void LexicalAnalyzer::handleUnfinishedChar(std::string yytext)
{
    logout << error_hndlr->handleLexicalError(
                  ErrorHandler::LexicalError::UNFINISHED_CHARACTER,
                  line_trkr->getLineNumber(), yytext)
           << std::endl;
}

void LexicalAnalyzer::handleValidChar(std::string yytext)
{
    tokenout << Tokenizer::generateToken(Tokenizer::CHARACTER_TOKEN, yytext) << std::endl;
    logout << Logger::getLogData(
                  Logger::LogType::CHARACTER_LOG,
                  line_trkr->getLineNumber(), yytext)
           << std::endl;
}

void LexicalAnalyzer::handleMultiChar(std::string yytext)
{
    logout << error_hndlr->handleLexicalError(
                  ErrorHandler::LexicalError::MULTI_CHARACTER,
                  line_trkr->getLineNumber(), yytext)
           << std::endl;
}

void LexicalAnalyzer::handleUnfinishedString(std::string yytext)
{
    line_trkr->handleString(yytext);
    logout << error_hndlr->handleLexicalError(
                  ErrorHandler::LexicalError::UNFINISHED_STRING,
                  line_trkr->getLineNumber(), yytext)
           << std::endl;
}

void LexicalAnalyzer::handleValidString(std::string yytext)
{
    tokenout << Tokenizer::generateToken(Tokenizer::STRING_TOKEN, yytext) << std::endl;
    logout << Logger::getLogData(
                  Logger::LogType::STRING_LOG, line_trkr->getLineNumber(),
                  yytext)
           << std::endl;
    line_trkr->handleString(yytext);
}
void LexicalAnalyzer::handleSingleComment(std::string yytext)
{
    logout << Logger::getLogData(
                  Logger::LogType::SINGLE_COMMENT_LOG,
                  line_trkr->getLineNumber(), yytext)
           << std::endl;
    line_trkr->handleSingleComment(yytext);
}
void LexicalAnalyzer::handleUnfinishedComment(std::string yytext)
{
    line_trkr->handleMultiComment(yytext);
    logout << error_hndlr->handleLexicalError(
                  ErrorHandler::LexicalError::UNFINISHED_COMMENT,
                  line_trkr->getLineNumber(), yytext)
           << std::endl;
}
void LexicalAnalyzer::handleMultiComment(std::string yytext)
{
    logout << Logger::getLogData(
                  Logger::LogType::MULTI_COMMENT_LOG,
                  line_trkr->getLineNumber(), yytext)
           << std::endl;
    line_trkr->handleMultiComment(yytext);
}
void LexicalAnalyzer::handleUnrecognized(std::string yytext)
{
    logout << error_hndlr->handleLexicalError(
                  ErrorHandler::LexicalError::UNRECOGNIZED,
                  line_trkr->getLineNumber(), yytext)
           << std::endl;
}
int LexicalAnalyzer::getLineCount()
{
    return line_trkr->getLineNumber();
}
int LexicalAnalyzer::getErrorCount()
{
    return error_hndlr->getErrorCount();
}

int ErrorHandler::getErrorCount()
{
    return error_count;
}
