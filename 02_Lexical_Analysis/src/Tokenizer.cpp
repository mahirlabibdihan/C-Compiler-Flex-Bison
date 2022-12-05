#include <fstream>
#include <string>
#include <map>
#include "../include/Tokenizer.hpp"
#include "../include/Util.hpp"

extern std::ofstream tokenout;

std::map<std::string, std::string> operatorType = {
    {"+", "ADDOP"},
    {"-", "ADDOP"},
    {"*", "MULOP"},
    {"/", "MULOP"},
    {"%", "MULOP"},
    {"++", "INCOP"},
    {"--", "DECOP"},
    {"<", "RELOP"},
    {"<=", "RELOP"},
    {">", "RELOP"},
    {">=", "RELOP"},
    {"==", "RELOP"},
    {"!=", "RELOP"},
    {"=", "ASSIGNOP"},
    {"||", "LOGICOP"},
    {"&&", "LOGICOP"},
    {"!", "NOT"},
    {"(", "LPAREN"},
    {")", "RPAREN"},
    {"{", "LCURL"},
    {"}", "RCURL"},
    {"[", "LSQUARE"},
    {"]", "RSQUARE"},
    {",", "COMMA"},
    {";", "SEMICOLON"}};

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
        bool is_multi = false;
        std::string str = Util::getActualString(lexeme, is_multi);
        if (is_multi)
        {
            printToken("MULTI LINE STRING", str);
        }
        else
        {
            printToken("SINGLE LINE STRING", str);
        }
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