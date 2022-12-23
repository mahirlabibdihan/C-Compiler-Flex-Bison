#include <fstream>
#include <string>
#include <map>
#include "../include/Tokenizer.hpp"
#include "../include/Util.hpp"
#include "../include/ExtendedSymbol.hpp"
#include "../include/y.tab.h"
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

std::map<std::string, int> operatorToken = {
    {"+", ADDOP},
    {"-", ADDOP},
    {"*", MULOP},
    {"/", MULOP},
    {"%", MULOP},
    {"++", INCOP},
    {"--", DECOP},
    {"<", RELOP},
    {"<=", RELOP},
    {">", RELOP},
    {">=", RELOP},
    {"==", RELOP},
    {"!=", RELOP},
    {"=", ASSIGNOP},
    {"||", LOGICOP},
    {"&&", LOGICOP},
    {"!", NOT},
    {"(", LPAREN},
    {")", RPAREN},
    {"{", LCURL},
    {"}", RCURL},
    {"[", LTHIRD},
    {"]", RTHIRD},
    {",", COMMA},
    {";", SEMICOLON}};

std::map<std::string, int> keywordToken = {
    {"if", IF},
    {"else", ELSE},
    {"switch", SWITCH},
    {"case", CASE},
    {"for", FOR},
    {"do", DO},
    {"while", WHILE},
    {"int", INT},
    {"float", FLOAT},
    {"char", CHAR},
    {"double", DOUBLE},
    {"void", VOID},
    {"default", DEFAULT},
    {"break", BREAK},
    {"return", RETURN},
    {"continue", CONTINUE}};

std::string Tokenizer::getToken(std::string type, std::string symbol)
{
    yylval.terminal = new Terminal(symbol, type);
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
int Tokenizer::getToken(TokenType type, string lexeme)
{
    switch (type)
    {
    case KEYWORD_TOKEN:
        return keywordToken[lexeme];
        break;
    case INTEGER_TOKEN:
        return CONST_INT;
        break;
    case FLOAT_TOKEN:
        return CONST_FLOAT;
        break;
    case CHARACTER_TOKEN:
        return CONST_CHAR;
        break;
    case STRING_TOKEN:
        return STRING;
        break;
    case OPERATOR_TOKEN:
        return operatorToken[lexeme];
        break;
    case IDENTIFIER_TOKEN:
        return ID;
        break;
    default:
        break;
    }
    return -1;
}