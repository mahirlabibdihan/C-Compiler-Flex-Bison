#include <iostream>
#include <fstream>
#include <string>
#include "../include/ErrorHandler.hpp"
#include "../include/SymbolTable.hpp"
using namespace std;

ErrorHandler::ErrorHandler(std::ofstream &err) : errout(err)
{
    error_count = 0;
}
void ErrorHandler::printError(string error, int line)
{
    error_count++;
    errout << "Error at line# " << line << ": " << error << "\n";
}
void ErrorHandler::printLexicalError(string error, int line)
{
    printError(error, line);
}

void ErrorHandler::handleLexicalError(LexicalError type, int line, string lexeme)
{
    switch (type)
    {
    case TOO_MANY_DECIMAL:
        printLexicalError("TOO_MANY_DECIMAL_POINTS " + lexeme, line);
        break;
    case ILL_NUMBER:
        printLexicalError("ILLFORMED_NUMBER " + lexeme, line);
        break;
    case INVALID_IDENTIFIER:
        printLexicalError("INVALID_ID_SUFFIX_NUM_PREFIX " + lexeme, line);
        break;
    case MULTI_CHARACTER:
        printLexicalError("MULTICHAR_CONST_CHAR " + lexeme, line);
        break;
    case UNFINISHED_CHARACTER:
        printLexicalError("UNFINISHED_CONST_CHAR " + lexeme, line);
        break;
    case EMPTY_CHARACTER:
        printLexicalError("EMPTY_CONST_CHAR " + lexeme, line);
        break;
    case UNFINISHED_STRING:
        printLexicalError("UNFINISHED_STRING " + lexeme, line);
        break;
    case UNFINISHED_COMMENT:
        printLexicalError("UNFINISHED_COMMENT " + lexeme, line);
        break;
    case UNRECOGNIZED:
        printLexicalError("UNRECOGNIZED_CHAR " + lexeme, line);
        break;
    default:
        break;
    }
}

int ErrorHandler::getErrorCount()
{
    return error_count;
}