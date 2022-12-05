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
    logout << "Error at line " << line << ": " << error << "\n";
}
void ErrorHandler::printLexicalError(string error, int line)
{
    lexical_error_count++;
    printError("lexical error, " + error, line);
}

void ErrorHandler::handleLexicalError(LexicalError type, int line, string lexeme)
{
    switch (type)
    {
    case TOO_MANY_DECIMAL:
        printLexicalError("Too Many Decimal Points " + lexeme, line);
        break;
    case ILL_NUMBER:
        printLexicalError("Ill formed number " + lexeme, line);
        break;
    case INVALID_IDENTIFIER:
        printLexicalError("Invalid prefix on ID or invalid suffix on Number " + lexeme, line);
        break;
    case MULTI_CHARACTER:
        printLexicalError("Multi Character Constant Error " + lexeme, line);
        break;
    case UNTERMINATED_CHARACTER:
        printLexicalError("Unterminated Character " + lexeme, line);
        break;
    case EMPTY_CHARACTER:
        printLexicalError("Empty Character Constant Error " + lexeme, line);
        break;
    case UNTERMINATED_STRING:
        printLexicalError("Unterminated String " + lexeme, line);
        break;
    case UNTERMINATED_COMMENT:
        printLexicalError("Unterminated Comment " + lexeme, line);
        break;
    case UNRECOGNIZED:
        printLexicalError("Unrecognized character " + lexeme, line);
        break;
    default:
        break;
    }
}