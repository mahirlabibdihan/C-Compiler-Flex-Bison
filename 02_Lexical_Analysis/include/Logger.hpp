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

    void printLog(std::string token, std::string lexeme, int line);
    void printLogData(LogType type, int line, std::string lexeme);
};

#endif