#include "1905072_Tokenizer.h"
#include "1905072_Helper.h"
#include <fstream>
extern ofstream tokenout;
map<string, string> operatorToken = {
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
    {"&&", "LOGICOP"},
    {"!", "NOT"},
    {"(", "LPAREN"},
    {")", "RPAREN"},
    {"{", "RCURL"},
    {"}", "RCURL"},
    {"[", "LTHIRD"},
    {"]", "RTHIRD"},
    {",", "COMMA"},
    {";", "SEMICOLON"}};

void printToken(string token)
{
    tokenout << "<" << token << "> ";
}
void generateToken(int type, string lexeme)
{
    switch (type)
    {
    case KEYWORD_TOKEN:
        printToken(toUpper(lexeme));
        break;
    case INTEGER_TOKEN:
        printToken("CONST_INT," + lexeme);
        break;
    case FLOAT_TOKEN:
        printToken("CONST_FLOAT," + lexeme);
        break;
    case CHARACTER_TOKEN:
        printToken("CONST_CHAR," + getActualChar(lexeme));
        break;
    case STRING_TOKEN:
        printToken("CONST_CHAR," + getActualString(lexeme));
        break;
    case OPERATOR_TOKEN:
        printToken(operatorToken[lexeme] + "," + lexeme);
        break;
    case IDENTIFIER_TOKEN:
        printToken("ID," + lexeme);
        break;
    default:
        break;
    }
}