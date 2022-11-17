#include "1905072_Logger.hpp"
#include "1905072_Helper.hpp"
#include "1905072_Symbol_Extended.hpp"
#include <iostream>
#include <fstream>
extern ofstream logout;
extern int line_count;
extern Logger *logger;
void Logger::printLog(string token, string lexeme, int line)
{
    logout << "Line no " << line << ": Token <" << token << "> Lexeme " << lexeme << " found\n"
           << endl;
}
void Logger::printLogWithToken(string token, string lexeme, string actual, int line)
{
    logout << "Line no " << line << ": Token <" << token << "> Lexeme " << lexeme << " found --> <" << token << ", " << actual << ">\n"
           << endl;
}
void Logger::printLogData(LogType type, int line, string lexeme)
{
    // switch (type)
    // {
    // case KEYWORD:
    //     printLog(toUpper(lexeme), lexeme, line);
    //     break;
    // case INTEGER:
    //     printLog("CONST_INT", lexeme, line);
    //     break;
    // case FLOAT:
    //     printLog("CONST_FLOAT", lexeme, line);
    //     break;
    // case CHARACTER:
    //     printLogWithToken("CONST_CHAR", lexeme, string(1, getActualChar(lexeme)), line);
    //     break;
    // case STRING:
    //     printLogWithToken("STRING", lexeme, getActualString(lexeme), line);
    //     break;
    // case OPERATOR:
    //     printLog(operatorToken[lexeme], lexeme, line);
    //     break;
    // case IDENTIFIER:
    //     printLog("ID", lexeme, line);
    //     break;
    // case COMMENT:
    //     printLog("COMMENT", lexeme, line);
    //     break;
    // default:
    //     break;
    // }
}

void Logger::printRule(string left_part, string right_part)
{
    logout << "Line " << line_count << ": " << left_part << " : " << right_part << "\n"
           << endl;
}
void Logger::printRule(SymbolInfo *parent, vector<SymbolInfo *> children)
{
    string left = parent->getType();
    string right = "";
    for (auto &i : children)
    {
        right += i->getType() + " ";
    }
    printRule(left, right);
}
void Logger::printCode(string code)
{
    logout << code << "\n"
           << endl;
}

void Logger::printRuleAndCode(SymbolInfo *parent, vector<SymbolInfo *> child)
{
    printRule(parent, child);
    printCode(parent->getSymbol());
}

NonTerminal *createNonTerminal(vector<SymbolInfo *> child, string name)
{
    NonTerminal *node = new NonTerminal(
        formatCode(child),
        name);
    logger->printRuleAndCode(node, child);
    return node;
}

Expression *createExpression(vector<SymbolInfo *> child, string name)
{
    Expression *node = new Expression(
        formatCode(child),
        name);
    logger->printRuleAndCode(node, child);
    return node;
}

ParameterList *createParameterList(vector<SymbolInfo *> child, string name)
{
    ParameterList *node = new ParameterList(
        formatCode(child),
        name);
    logger->printRuleAndCode(node, child);
    return node;
}

DeclarationList *createDeclarationList(vector<SymbolInfo *> child, string name)
{
    DeclarationList *node = new DeclarationList(
        formatCode(child),
        name);
    logger->printRuleAndCode(node, child);
    return node;
}

ArgumentList *createArgumentList(vector<SymbolInfo *> child, string name)
{
    ArgumentList *node = new ArgumentList(
        formatCode(child),
        name);
    logger->printRuleAndCode(node, child);
    return node;
}

ArrayCall *createArrayCall(vector<SymbolInfo *> child, string name)
{
    ArrayCall *node = new ArrayCall(
        formatCode(child),
        name);
    logger->printRuleAndCode(node, child);
    return node;
}