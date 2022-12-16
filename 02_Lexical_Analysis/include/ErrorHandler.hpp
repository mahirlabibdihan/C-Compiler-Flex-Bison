/**
 * Author: Mahir Labib Dihan
 * Last modified: December 05, 2022
 */
#ifndef __ERROR_HANDLER_H
#define __ERROR_HANDLER_H 1
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class ErrorHandler
{
    int error_count;
    std::ofstream &errout;
    // Lexical error types
public:
    enum LexicalError
    {
        TOO_MANY_DECIMAL = 0,
        ILL_NUMBER,
        INVALID_IDENTIFIER,
        MULTI_CHARACTER,
        UNFINISHED_CHARACTER,
        EMPTY_CHARACTER,
        UNFINISHED_STRING,
        UNFINISHED_COMMENT,
        UNRECOGNIZED
    };

    ErrorHandler(std::ofstream &errout);
    void printError(string error, int line);
    void printLexicalError(string error, int line);
    void handleLexicalError(LexicalError type, int line, string lexeme = "");
    int getErrorCount();
};

#endif