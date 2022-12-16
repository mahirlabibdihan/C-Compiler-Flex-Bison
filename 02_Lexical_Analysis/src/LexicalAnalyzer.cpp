#include "../include/LexicalAnalyzer.hpp"
#include "../include/Tokenizer.hpp"
#include "../include/Logger.hpp"
#include "../include/ErrorHandler.hpp"
#include "../include/SymbolTable.hpp"
#include <fstream>

LexicalAnalyzer::LexicalAnalyzer(SymbolTable *table, ErrorHandler *error_hndlr, Logger *logger, std::ofstream &log) : logout(log)
{
    this->table = table;
    this->error_hndlr = error_hndlr;
    this->logger = logger;
    this->tokenizer = new Tokenizer();
    this->line_trkr = new LineTracker(1);
}

LexicalAnalyzer::~LexicalAnalyzer()
{
    delete line_trkr;
    delete tokenizer;
}
void LexicalAnalyzer::installID(std::string yytext)
{
    if (table->insert(yytext, "ID"))
    {
        table->printAllScope();
    }
    else
    {
        logout << "\t" << yytext << " already exisits in the current ScopeTable" << std::endl;
    }
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
    tokenizer->generateToken(
        Tokenizer::TokenType::KEYWORD_TOKEN,
        yytext);
    logger->printLogData(
        Logger::LogType::KEYWORD_LOG,
        line_trkr->getLineNumber(), yytext);
}

void LexicalAnalyzer::handleOperator(std::string yytext)
{
    if (yytext == "{")
    {
        table->enterScope();
    }
    else if (yytext == "}")
    {
        if (table->getCurrentScope()->getParentScope() != nullptr)
        {
            table->exitScope();
        }
    }

    tokenizer->generateToken(Tokenizer::OPERATOR_TOKEN, yytext);
    logger->printLogData(
        Logger::LogType::OPERATOR_LOG,
        line_trkr->getLineNumber(), yytext);
}

void LexicalAnalyzer::handleInteger(std::string yytext)
{
    tokenizer->generateToken(Tokenizer::INTEGER_TOKEN, yytext);
    logger->printLogData(
        Logger::LogType::INTEGER_LOG,
        line_trkr->getLineNumber(), yytext);
}

void LexicalAnalyzer::handleFloatingPoint(std::string yytext)
{
    tokenizer->generateToken(Tokenizer::FLOAT_TOKEN, yytext);
    logger->printLogData(
        Logger::LogType::FLOAT_LOG,
        line_trkr->getLineNumber(), yytext);
}

void LexicalAnalyzer::handleTooManyDecimal(std::string yytext)
{
    error_hndlr->handleLexicalError(
        ErrorHandler::LexicalError::TOO_MANY_DECIMAL,
        line_trkr->getLineNumber(), yytext);
}

void LexicalAnalyzer::handleIllNum(std::string yytext)
{
    error_hndlr->handleLexicalError(
        ErrorHandler::LexicalError::ILL_NUMBER,
        line_trkr->getLineNumber(), yytext);
}

void LexicalAnalyzer::handleIdentifier(std::string yytext)
{
    tokenizer->generateToken(
        Tokenizer::IDENTIFIER_TOKEN,
        yytext);
    logger->printLogData(
        Logger::LogType::IDENTIFIER_LOG,
        line_trkr->getLineNumber(), yytext);
    installID(yytext);
}

void LexicalAnalyzer::handleNonIdentifier(std::string yytext)
{
    error_hndlr->handleLexicalError(
        ErrorHandler::LexicalError::INVALID_IDENTIFIER,
        line_trkr->getLineNumber(), yytext);
}

void LexicalAnalyzer::handleEmptyChar(std::string yytext)
{
    error_hndlr->handleLexicalError(
        ErrorHandler::LexicalError::EMPTY_CHARACTER,
        line_trkr->getLineNumber(), yytext);
}

void LexicalAnalyzer::handleUnfinishedChar(std::string yytext)
{
    error_hndlr->handleLexicalError(
        ErrorHandler::LexicalError::UNFINISHED_CHARACTER,
        line_trkr->getLineNumber(), yytext);
}

void LexicalAnalyzer::handleValidChar(std::string yytext)
{
    tokenizer->generateToken(Tokenizer::CHARACTER_TOKEN, yytext);
    logger->printLogData(
        Logger::LogType::CHARACTER_LOG,
        line_trkr->getLineNumber(), yytext);
}

void LexicalAnalyzer::handleMultiChar(std::string yytext)
{
    error_hndlr->handleLexicalError(
        ErrorHandler::LexicalError::MULTI_CHARACTER,
        line_trkr->getLineNumber(), yytext);
}

void LexicalAnalyzer::handleUnfinishedString(std::string yytext)
{
    line_trkr->handleString(yytext);
    error_hndlr->handleLexicalError(
        ErrorHandler::LexicalError::UNFINISHED_STRING,
        line_trkr->getLineNumber(), yytext);
}

void LexicalAnalyzer::handleValidString(std::string yytext)
{
    tokenizer->generateToken(Tokenizer::STRING_TOKEN, yytext);
    logger->printLogData(
        Logger::LogType::STRING_LOG, line_trkr->getLineNumber(),
        yytext);
    line_trkr->handleString(yytext);
}
void LexicalAnalyzer::handleSingleComment(std::string yytext)
{
    logger->printLogData(
        Logger::LogType::SINGLE_COMMENT_LOG,
        line_trkr->getLineNumber(), yytext);
    line_trkr->handleSingleComment(yytext);
}
void LexicalAnalyzer::handleUnfinishedComment(std::string yytext)
{
    line_trkr->handleMultiComment(yytext);
    error_hndlr->handleLexicalError(
        ErrorHandler::LexicalError::UNFINISHED_COMMENT,
        line_trkr->getLineNumber(), yytext);
}
void LexicalAnalyzer::handleMultiComment(std::string yytext)
{
    logger->printLogData(
        Logger::LogType::MULTI_COMMENT_LOG,
        line_trkr->getLineNumber(), yytext);
    line_trkr->handleMultiComment(yytext);
}
void LexicalAnalyzer::handleUnrecognized(std::string yytext)
{
    error_hndlr->handleLexicalError(
        ErrorHandler::LexicalError::UNRECOGNIZED,
        line_trkr->getLineNumber(), yytext);
}
int LexicalAnalyzer::getLineCount()
{
    return line_trkr->getLineNumber();
}
int LexicalAnalyzer::getErrorCount()
{
    return error_hndlr->getErrorCount();
}