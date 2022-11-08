#include "1905072_Error_Handler.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

extern fstream logout;
extern int error_count;
void printErrorLog(string error, int line)
{
    logout << "Error at line no " << line << ": " << error << "\n"
           << endl;
}

void handleError(int type, int line, string lexeme)
{
    error_count++;
    switch (type)
    {
    case TOO_MANY_DECIMAL:
        printErrorLog("Too Many Decimal Points " + lexeme, line);
        break;
    case ILL_NUMBER:
        printErrorLog("Ill formed number " + lexeme, line);
        break;
    case INVALID_IDENTIFIER:
        printErrorLog("Invalid prefix on ID or invalid suffix on Number " + lexeme, line);
        break;
    case MULTI_CHARACTER:
        printErrorLog("Multi Character Constant Error " + lexeme, line);
        break;
    case UNTERMINATED_CHARACTER:
        printErrorLog("Unterminated Character " + lexeme, line);
        break;
    case EMPTY_CHARACTER:
        printErrorLog("Empty Character Constant Error " + lexeme, line);
        break;
    case UNTERMINATED_STRING:
        printErrorLog("Unterminated String " + lexeme, line);
        break;
    case UNTERMINATED_COMMENT:
        printErrorLog("Unterminated Comment " + lexeme, line);
        break;
    case UNRECOGNIZED:
        printErrorLog("Unrecognized character " + lexeme, line);
        break;
    default:
        break;
    }
}