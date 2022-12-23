#include "../include/Tokenizer.hpp"
#include "../include/Logger.hpp"
#include "../include/Util.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
std::string Logger::getMsg(std::string token, std::string lexeme, int line)
{
    return "Line# " + std::to_string(line) + ": Token <" + token + "> Lexeme " + lexeme + " found";
}
std::string Logger::getLogData(Logger::LogType type, int line, std::string lexeme)
{
    switch (type)
    {
    case KEYWORD_LOG:
        return getMsg(Util::toUpper(lexeme), lexeme, line);
        break;
    case INTEGER_LOG:
        return getMsg("CONST_INT", lexeme, line);
        break;
    case FLOAT_LOG:
        return getMsg("CONST_FLOAT", lexeme, line);
        break;
    case CHARACTER_LOG:
        return getMsg("CONST_CHAR", std::string(1, Util::getActualChar(lexeme)), line);
        break;
    case STRING_LOG:
    {
        int l_count = Util::getStringLineCount(lexeme);
        std::string str = Util::getActualString(lexeme);
        return getMsg(std::string(l_count > 1 ? "MULTI" : "SINGLE") + " LINE STRING", lexeme, line);
        break;
    }
    case OPERATOR_LOG:
        return getMsg(Tokenizer::operatorType[lexeme], lexeme, line);
        break;
    case IDENTIFIER_LOG:
        return getMsg("ID", lexeme, line);
        break;
    case SINGLE_COMMENT_LOG:
        return getMsg("SINGLE LINE COMMENT", lexeme, line);
        break;
    case MULTI_COMMENT_LOG:
        return getMsg("MULTI LINE COMMENT", lexeme, line);
        break;
    default:
        break;
    }
    return getMsg("UNKNOWN", lexeme, line);
}
std::string Logger::getRuleAndLine(std::string left_part, std::string right_part)
{
    return left_part + " : " + right_part;
}
std::string Logger::getRuleAndLine(SymbolInfo *parent, std::vector<SymbolInfo *> children)
{
    std::string left = parent->getType();
    std::string right = "";
    for (auto &i : children)
    {
        right += i->getType() + " ";
    }
    return getRuleAndLine(left, right);
}