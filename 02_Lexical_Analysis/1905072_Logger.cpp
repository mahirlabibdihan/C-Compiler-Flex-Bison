#include "1905072_Logger.h"
#include "1905072_Helper.h"
#include "1905072_Tokenizer.h"
#include <iostream>
#include <fstream>
extern ofstream logout;

void printLog(string token, string lexeme, int line)
{
    logout << "Line no " << line << ": Token <" << token << "> Lexeme " << lexeme << " found\n"
           << endl;
}
void printLogWithToken(string token, string lexeme, string actual, int line)
{
    logout << "Line no " << line << ": Token <" << token << "> Lexeme " << lexeme << " found --> <" << token << ", " << actual << ">\n"
           << endl;
}
void printLogData(int type, int line, string lexeme)
{
    switch (type)
    {
    case KEYWORD_LOG:
        printLog(toUpper(lexeme), lexeme, line);
        break;
    case INTEGER_LOG:
        printLog("CONST_INT", lexeme, line);
        break;
    case FLOAT_LOG:
        printLog("CONST_FLOAT", lexeme, line);
        break;
    case CHARACTER_LOG:
        printLogWithToken("CONST_CHAR", lexeme, string(1, getActualChar(lexeme)), line);
        break;
    case STRING_LOG:
        printLogWithToken("STRING", lexeme, getActualString(lexeme), line);
        break;
    case OPERATOR_LOG:
        printLog(operatorToken[lexeme], lexeme, line);
        break;
    case IDENTIFIER_LOG:
        printLog("ID", lexeme, line);
        break;
    case COMMENT_LOG:
        printLog("COMMENT", lexeme, line);
        break;
    default:
        break;
    }
}