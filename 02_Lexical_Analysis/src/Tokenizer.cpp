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

Tokenizer::Tokenizer()
{
    tokenout.open("io/token.txt");
}
void Tokenizer::printToken(std::string type, std::string symbol)
{
    tokenout << "<" << type << ", " << symbol << ">" << std::endl;
}
void Tokenizer::generateToken(TokenType type, std::string lexeme)
{
    switch (type)
    {
    case KEYWORD_TOKEN:
        printToken(Util::toUpper(lexeme), lexeme);
        break;
    case INTEGER_TOKEN:
        printToken("CONST_INT", lexeme);
        break;
    case FLOAT_TOKEN:
        printToken("CONST_FLOAT", lexeme);
        break;
    case CHARACTER_TOKEN:
        printToken("CONST_CHAR", std::string(1, Util::getActualChar(lexeme)));
        break;
    case STRING_TOKEN:
    {
        int l_count = Util::getStringLineCount(lexeme);
        std::string str = Util::getActualString(lexeme);
        printToken(std::string(l_count > 1 ? "MULTI" : "SINGLE") + " LINE STRING", str);
        break;
    }
    case OPERATOR_TOKEN:
        printToken(operatorType[lexeme], lexeme);
        break;
    case IDENTIFIER_TOKEN:
        printToken("ID", lexeme);
        break;
    default:
        break;
    }
}