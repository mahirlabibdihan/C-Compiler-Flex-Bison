#include "1905072_Logger.h"
#include "1905072_Helper.h"
#include "1905072_Symbol_Extended.h"
#include <iostream>
#include <fstream>
extern ofstream logout;
extern int line_count;
void printLog(string token, string lexeme, int line)
{
    logout << "Line no " << line << ": Token <" << token << "> Lexeme " << lexeme << " found\n"
           << endl;
}
void printLogWithToken(string token, string lexeme, string actual, int line)
{
    logout << "Line no " << line << ": Token <" << token << "> Lexeme " << lexeme << " found --> <" << token << ", " << actual << ">\n"
           << endl;
}
void printLogData(int type, int line, string lexeme)
{
    // switch (type)
    // {
    // case KEYWORD_LOG:
    //     printLog(toUpper(lexeme), lexeme, line);
    //     break;
    // case INTEGER_LOG:
    //     printLog("CONST_INT", lexeme, line);
    //     break;
    // case FLOAT_LOG:
    //     printLog("CONST_FLOAT", lexeme, line);
    //     break;
    // case CHARACTER_LOG:
    //     printLogWithToken("CONST_CHAR", lexeme, string(1, getActualChar(lexeme)), line);
    //     break;
    // case STRING_LOG:
    //     printLogWithToken("STRING", lexeme, getActualString(lexeme), line);
    //     break;
    // case OPERATOR_LOG:
    //     printLog(operatorToken[lexeme], lexeme, line);
    //     break;
    // case IDENTIFIER_LOG:
    //     printLog("ID", lexeme, line);
    //     break;
    // case COMMENT_LOG:
    //     printLog("COMMENT", lexeme, line);
    //     break;
    // default:
    //     break;
    // }
}

void printRule(string left_part, string right_part)
{
    logout << "Line " << line_count << ": " << left_part << " : " << right_part << "\n"
           << endl;
}
void printRule(SymbolInfo *parent, vector<SymbolInfo *> children)
{
    string left = parent->getType();
    string right = "";
    for (auto &i : children)
    {
        right += i->getType() + " ";
    }
    printRule(left, right);
}
void printCode(string code)
{
    logout << code << "\n"
           << endl;
}

NonTerminal *printRuleAndCode(vector<SymbolInfo *> child, string name, bool is_exp)
{
    if (is_exp)
    {
        Expression *node = new Expression(
            formatCode(child),
            name);
        printRule(node, child);
        printCode(node->getSymbol());
        return node;
    }
    else
    {
        NonTerminal *node = new NonTerminal(
            formatCode(child),
            name);
        printRule(node, child);
        printCode(node->getSymbol());
        return node;
    }
}

NonTerminal *createNonTerminal(vector<SymbolInfo *> child, string name)
{
    NonTerminal *node = new NonTerminal(
        formatCode(child),
        name);
    printRule(node, child);
    printCode(node->getSymbol());
    return node;
}

Expression *createExpression(vector<SymbolInfo *> child, string name)
{
    Expression *node = new Expression(
        formatCode(child),
        name);
    printRule(node, child);
    printCode(node->getSymbol());
    return node;
}

ParameterList *createParameterList(vector<SymbolInfo *> child, string name)
{
    ParameterList *node = new ParameterList(
        formatCode(child),
        name);
    printRule(node, child);
    printCode(node->getSymbol());
    return node;
}

DeclarationList *createDeclarationList(vector<SymbolInfo *> child, string name)
{
    DeclarationList *node = new DeclarationList(
        formatCode(child),
        name);
    printRule(node, child);
    printCode(node->getSymbol());
    return node;
}

ArgumentList *createArgumentList(vector<SymbolInfo *> child, string name)
{
    ArgumentList *node = new ArgumentList(
        formatCode(child),
        name);
    printRule(node, child);
    printCode(node->getSymbol());
    return node;
}

ArrayCall *createArrayCall(vector<SymbolInfo *> child, string name)
{
    ArrayCall *node = new ArrayCall(
        formatCode(child),
        name);
    printRule(node, child);
    printCode(node->getSymbol());
    return node;
}