#include <iostream>
#include <fstream>
#include <string>
#include "../include/ErrorHandler.hpp"
#include "../include/SymbolTable.hpp"
using namespace std;

ErrorHandler::ErrorHandler()
{
    error_count = 0;
}
std::string ErrorHandler::getError(string error, int line)
{
    error_count++;
    return "Error at line# " + std::to_string(line) + ": " + error;
}
std::string ErrorHandler::getLexicalError(string error, int line)
{
    return getError(error, line);
}

std::string ErrorHandler::handleLexicalError(LexicalError type, int line, string lexeme)
{
    switch (type)
    {
    case TOO_MANY_DECIMAL:
        return getLexicalError("TOO_MANY_DECIMAL_POINTS " + lexeme, line);
        break;
    case ILL_NUMBER:
        return getLexicalError("ILLFORMED_NUMBER " + lexeme, line);
        break;
    case INVALID_IDENTIFIER:
        return getLexicalError("INVALID_ID_SUFFIX_NUM_PREFIX " + lexeme, line);
        break;
    case MULTI_CHARACTER:
        return getLexicalError("MULTICHAR_CONST_CHAR " + lexeme, line);
        break;
    case UNFINISHED_CHARACTER:
        return getLexicalError("UNFINISHED_CONST_CHAR " + lexeme, line);
        break;
    case EMPTY_CHARACTER:
        return getLexicalError("EMPTY_CONST_CHAR " + lexeme, line);
        break;
    case UNFINISHED_STRING:
        return getLexicalError("UNFINISHED_STRING " + lexeme, line);
        break;
    case UNFINISHED_COMMENT:
        return getLexicalError("UNFINISHED_COMMENT " + lexeme, line);
        break;
    case UNRECOGNIZED:
        return getLexicalError("UNRECOGNIZED_CHAR " + lexeme, line);
        break;
    default:
        break;
    }
    return getLexicalError("Unknown Lexical Error", line);
}

int ErrorHandler::getErrorCount()
{
    return error_count;
}