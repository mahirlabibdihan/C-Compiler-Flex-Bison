#include "1905072_Tokenizer.h"
#include "1905072_Node.h"
#include "1905072_Helper.h"
#include "../01_Symbol_Table/1905072_SymbolInfo.h"
#include <fstream>

#include "y.tab.h"
extern ofstream tokenout;
extern YYSTYPE yylval;
map<string, string> operatorType = {
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
    {"--", INCOP},
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
void printToken(string type)
{
    tokenout << "<" << type << "> ";
    // yylval = new SymbolInfo(symbol, (char *)"RELOP");
    // yylval.symbol = new SymbolInfo(symbol, type);
}
void printToken(string type, string symbol)
{
    tokenout << "<" << type << "," << symbol << "> ";
    yylval.symbol = new SymbolInfo(symbol, type);
    // yylval = (YYSTYPE) new SymbolInfo(symbol, type);
}
void generateToken(int type, string lexeme)
{
    switch (type)
    {
    case KEYWORD_TOKEN:
        printToken(toUpper(lexeme));
        break;
    case INTEGER_TOKEN:
        printToken("CONST_INT", lexeme);
        break;
    case FLOAT_TOKEN:
        printToken("CONST_FLOAT", lexeme);
        break;
    case CHARACTER_TOKEN:
        printToken("CONST_CHAR", string(1, getActualChar(lexeme)));
        break;
    case STRING_TOKEN:
        printToken("CONST_CHAR", getActualString(lexeme));
        break;
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