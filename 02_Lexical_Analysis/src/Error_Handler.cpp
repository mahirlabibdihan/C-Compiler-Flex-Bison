#include <iostream>
#include <fstream>
#include <string>
#include "../include/Error_Handler.hpp"
#include "../include/SymbolTable.hpp"
using namespace std;

extern ofstream logout;
extern int error_count;
extern int lexical_error_count;
extern int line_count;
extern SymbolTable *table;

void ErrorHandler::printError(string error, int line)
{
    error_count++;
    logout << "Error at line# " << line << ": " << error << "\n";
}
void ErrorHandler::printLexicalError(string error, int line)
{
    lexical_error_count++;
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
    case UNTERMINATED_CHARACTER:
        printLexicalError("UNFINISHED_CONST_CHAR " + lexeme, line);
        break;
    case EMPTY_CHARACTER:
        printLexicalError("EMPTY_CONST_CHAR " + lexeme, line);
        break;
    case UNTERMINATED_STRING:
        printLexicalError("UNFINISHED_STRING " + lexeme, line);
        break;
    case UNTERMINATED_COMMENT:
        printLexicalError("UNFINISHED_COMMENT " + lexeme, line);
        break;
    case UNRECOGNIZED:
        printLexicalError("UNRECOGNIZED_CHAR " + lexeme, line);
        break;
    default:
        break;
    }
}