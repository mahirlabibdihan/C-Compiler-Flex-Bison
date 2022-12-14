#include <iostream>
#include <fstream>
#include "../include/Tokenizer.hpp"
#include "../include/Logger.hpp"
#include "../include/Util.hpp"
extern std::ofstream logout;
extern std::map<std::string, std::string> operatorType;
void Logger::printLog(std::string token, std::string lexeme, int line)
{
    logout << "Line# " << line << ": Token <" << token << "> Lexeme " << lexeme << " found"
           << std::endl;
}
void Logger::printLogWithToken(std::string token, std::string lexeme, std::string actual, int line)
{
    logout << "Line# " << line << ": Token <" << token << "> Lexeme " << lexeme << " found --> <" << token << ", " << actual << ">"
           << std::endl;
}
void Logger::printLogData(Logger::LogType type, int line, std::string lexeme)
{
    switch (type)
    {
    case KEYWORD_LOG:
        printLog(Util::toUpper(lexeme), lexeme, line);
        break;
    case INTEGER_LOG:
        printLog("CONST_INT", lexeme, line);
        break;
    case FLOAT_LOG:
        printLog("CONST_FLOAT", lexeme, line);
        break;
    case CHARACTER_LOG:
        printLog("CONST_CHAR", std::string(1, Util::getActualChar(lexeme)), line);
        break;
    case STRING_LOG:
    {
        int l_count = Util::getStringLineCount(lexeme);
        std::string str = Util::getActualString(lexeme);
        printLog(std::string(l_count > 1 ? "MULTI" : "SINGLE") + " LINE STRING", lexeme, line);
        break;
    }
    case OPERATOR_LOG:
        printLog(operatorType[lexeme], lexeme, line);
        break;
    case IDENTIFIER_LOG:
        printLog("ID", lexeme, line);
        break;
    case SINGLE_COMMENT_LOG:
        printLog("SINGLE LINE COMMENT", lexeme, line);
        break;
    case MULTI_COMMENT_LOG:
        printLog("MULTI LINE COMMENT", lexeme, line);
        break;
    default:
        break;
    }
}
