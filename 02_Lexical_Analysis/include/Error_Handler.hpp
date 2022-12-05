/**
 * Author: Mahir Labib Dihan
 * Last modified: December 05, 2022
 */
#ifndef __ERROR_HANDLER_H
#define __ERROR_HANDLER_H 1
#include <iostream>
#include <string>
using namespace std;

namespace ErrorHandler
{
    // Lexical errors
    enum LexicalError
    {
        TOO_MANY_DECIMAL = 0,
        ILL_NUMBER,
        INVALID_IDENTIFIER,
        MULTI_CHARACTER,
        UNTERMINATED_CHARACTER,
        EMPTY_CHARACTER,
        UNTERMINATED_STRING,
        UNTERMINATED_COMMENT,
        UNRECOGNIZED
    };
    void printError(string error, int line);
    void printLexicalError(string error, int line);
    void handleLexicalError(LexicalError type, int line, string lexeme = "");
};

#endif