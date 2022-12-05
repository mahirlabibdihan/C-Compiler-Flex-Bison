#include <fstream>
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
    {"[", "LTHIRD"},
    {"]", "RTHIRD"},
    {",", "COMMA"},
    {";", "SEMICOLON"}};

void Tokenizer::printToken(std::string type, std::string token_type)
{
    tokenout << "<" << type << "> ";
    tokenout.flush();
}
void Tokenizer::printToken(std::string type, std::string symbol, std::string token_type)
{
    tokenout << "<" << type << "," << symbol << "> ";
    tokenout.flush();
}
void Tokenizer::generateToken(TokenType type, std::string lexeme)
{
    switch (type)
    {
    case KEYWORD_TOKEN:
        printToken(Util::toUpper(lexeme), "KEYWORD");
        break;
    case INTEGER_TOKEN:
        printToken("CONST_INT", lexeme, "CONSTANT");
        break;
    case FLOAT_TOKEN:
        printToken("CONST_FLOAT", lexeme, "CONSTANT");
        break;
    case CHARACTER_TOKEN:
        printToken("CONST_CHAR", std::string(1, Util::getActualChar(lexeme)), "CONSTANT");
        break;
    case STRING_TOKEN:
        printToken("STRING", Util::getActualString(lexeme), "CONSTANT");
        break;
    case OPERATOR_TOKEN:
        printToken(operatorType[lexeme], lexeme, "OPERATOR");
        break;
    case IDENTIFIER_TOKEN:
        printToken("ID", lexeme, "IDENTIFIER");
        break;
    default:
        break;
    }
}