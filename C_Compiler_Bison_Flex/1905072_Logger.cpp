#include "1905072_Logger.hpp"
#include "1905072_Helper.hpp"
#include "1905072_Symbol_Extended.hpp"
#include <iostream>
#include <fstream>
#include <map>
extern ofstream logout;
extern ofstream lexlogout;
extern int line_count;
extern Logger *logger;
extern Helper *hlpr;
extern map<string, string> operatorType;
void Logger::printLog(string token, string lexeme, int line)
{
    lexlogout << "Line no " << line << ": Token <" << token << "> Lexeme " << lexeme << " found\n"
              << endl;
}
void Logger::printLogWithToken(string token, string lexeme, string actual, int line)
{
    lexlogout << "Line no " << line << ": Token <" << token << "> Lexeme " << lexeme << " found --> <" << token << ", " << actual << ">\n"
              << endl;
}
void Logger::printLogData(LogType type, int line, string lexeme)
{
    switch (type)
    {
    case KEYWORD_LOG:
        printLog(hlpr->toUpper(lexeme), lexeme, line);
        break;
    case INTEGER_LOG:
        printLog("CONST_INT", lexeme, line);
        break;
    case FLOAT_LOG:
        printLog("CONST_FLOAT", lexeme, line);
        break;
    case CHARACTER_LOG:
        printLogWithToken("CONST_CHAR", lexeme, string(1, hlpr->getActualChar(lexeme)), line);
        break;
    case STRING_LOG:
        printLogWithToken("STRING", lexeme, hlpr->getActualString(lexeme), line);
        break;
    case OPERATOR_LOG:
        printLog(operatorType[lexeme], lexeme, line);
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

void Logger::printRule(string left_part, string right_part)
{
    logout << "Line " << line_count << ": " << left_part << " : " << right_part << "\n"
           << endl;
}
void Logger::printRule(SymbolInfo *parent, vector<SymbolInfo *> children)
{
    string left = parent->getType();
    string right = "";
    for (auto &i : children)
    {
        right += i->getType() + " ";
    }
    printRule(left, right);
}
void Logger::printCode(string code)
{
    logout << code << "\n"
           << endl;
}

void Logger::printRuleAndCode(SymbolInfo *parent, vector<SymbolInfo *> child)
{
    printRule(parent, child);
    printCode(parent->getSymbol());
}