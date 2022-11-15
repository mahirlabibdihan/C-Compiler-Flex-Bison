#include "1905072_Tokenizer.h"
#include "1905072_Helper.h"
#include "1905072_SymbolInfo.h"
#include "1905072_Token.h"
#include "1905072_Expression.h"

#include "y.tab.h"
#include <fstream>
extern ofstream tokenout;
extern YYSTYPE yylval;
map<string, string> operatorType = {
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

map<string, int> operatorToken = {
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

map<string, int> keywordToken = {
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
void printToken(string type, string token_type)
{
    tokenout << "<" << type << "> ";
    tokenout.flush();
    yylval.segment = new Segment(toLower(type), type);
}
void printToken(string type, string symbol, string token_type)
{
    tokenout << "<" << type << "," << symbol << "> ";
    tokenout.flush();
    yylval.segment = new Segment(symbol, type);
}
void generateToken(int type, string lexeme)
{
    switch (type)
    {
    case KEYWORD_TOKEN:
        printToken(toUpper(lexeme), "KEYWORD");
        break;
    case INTEGER_TOKEN:
        printToken("CONST_INT", lexeme, "CONSTANT");
        break;
    case FLOAT_TOKEN:
        printToken("CONST_FLOAT", lexeme, "CONSTANT");
        break;
    case CHARACTER_TOKEN:
        printToken("CONST_CHAR", string(1, getActualChar(lexeme)), "CONSTANT");
        break;
    case STRING_TOKEN:
        printToken("STRING", getActualString(lexeme), "CONSTANT");
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

int getToken(int type, string lexeme)
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
        // printToken("CONST_CHAR," + getActualChar(lexeme));
        return CONST_CHAR;
        break;
    case STRING_TOKEN:
        // printToken("STRING," + getActualString(lexeme));
        return STRING;
        break;
    case OPERATOR_TOKEN:
        // printToken(operatorToken[lexeme] + "," + lexeme);
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