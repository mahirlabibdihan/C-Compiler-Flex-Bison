/**
 * Author: Mahir Labib Dihan
 * Last modified: December 14, 2022
 */
#ifndef __LOGGER_H
#define __LOGGER_H 1
#include <string>
#include <vector>
#include "../include/SymbolTable.hpp"

namespace Logger
{
    enum LogType
    {
        KEYWORD_LOG = 0,
        INTEGER_LOG,
        FLOAT_LOG,
        CHARACTER_LOG,
        STRING_LOG,
        OPERATOR_LOG,
        IDENTIFIER_LOG,
        SINGLE_COMMENT_LOG,
        MULTI_COMMENT_LOG
    };
    std::string getMsg(std::string token, std::string lexeme, int line);
    std::string getLogData(LogType type, int line, std::string lexeme);
    std::string getRule(SymbolInfo *parent, std::vector<SymbolInfo *> children);
    std::string getRule(std::string left_part, std::string right_part);
    std::string getRuleAndLine(SymbolInfo *terminal);
    std::string getRuleAndLine(SymbolInfo *parent, std::vector<SymbolInfo *> children);
};

#endif