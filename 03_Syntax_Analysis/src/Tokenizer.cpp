#include <fstream>
#include <string>
#include <map>
#include "../include/Tokenizer.hpp"
#include "../include/Util.hpp"
#include <iostream>

std::map<std::string, std::string> Tokenizer::operatorType = {
    {"+", "ADDOP"},
    {"-", "ADDOP"},
    {"*", "MULOP"},
    {"/", "MULOP"},
    {"%", "MULOP"},
    {"++", "INCOP"},
    {"--", "INCOP"},
    {"<", "RELOP"},
    {"<=", "RELOP"},
    {">", "RELOP"},
    {">=", "RELOP"},
    {"==", "RELOP"},
    {"!=", "RELOP"},
    {"=", "ASSIGNOP"},
    {"||", "LOGICOP"},
    {"&&", "LOGICOP"},
    {"&", "BITOP"},
    {"|", "BITOP"},
    {"^", "BITOP"},
    {"<<", "BITOP"},
    {">>", "BITOP"},
    {"!", "NOT"},
    {"(", "LPAREN"},
    {")", "RPAREN"},
    {"{", "LCURL"},
    {"}", "RCURL"},
    {"[", "LSQUARE"},
    {"]", "RSQUARE"},
    {",", "COMMA"},
    {";", "SEMICOLON"}};

std::string Tokenizer::getToken(std::string type, std::string symbol)
{
    return std::string() + "<" + type + ", " + symbol + ">";
}
std::string Tokenizer::generateToken(TokenType type, std::string lexeme)
{
    switch (type)
    {
    case KEYWORD_TOKEN:
        return getToken(Util::toUpper(lexeme), lexeme);
        break;
    case INTEGER_TOKEN:
        return getToken("CONST_INT", lexeme);
        break;
    case FLOAT_TOKEN:
        return getToken("CONST_FLOAT", lexeme);
        break;
    case CHARACTER_TOKEN:
        return getToken("CONST_CHAR", std::string(1, Util::getActualChar(lexeme)));
        break;
    case STRING_TOKEN:
    {
        int l_count = Util::getStringLineCount(lexeme);
        std::string str = Util::getActualString(lexeme);
        return getToken(std::string(l_count > 1 ? "MULTI" : "SINGLE") + " LINE STRING", str);
        break;
    }
    case OPERATOR_TOKEN:
        return getToken(operatorType[lexeme], lexeme);
        break;
    case IDENTIFIER_TOKEN:
        return getToken("ID", lexeme);
        break;
    default:
        break;
    }
    return getToken("", lexeme);
}