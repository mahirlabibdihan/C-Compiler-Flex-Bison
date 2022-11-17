#ifndef _GER__
#define _GER__
#include <string>
#include "1905072_SymbolInfo.hpp"
#include "1905072_Symbol_Extended.hpp"
using namespace std;

enum LogType
{
    KEYWORD_LOG = 0,
    INTEGER_LOG,
    FLOAT_LOG,
    CHARACTER_LOG,
    STRING_LOG,
    OPERATOR_LOG,
    IDENTIFIER_LOG,
    COMMENT_LOG
};

class Logger
{
public:
    void printLog(string token, string lexeme, int line);
    void printLogWithToken(string token, string lexeme, string actual, int line);
    void printLogData(LogType type, int line, string lexeme);
    void printRule(string left_part, string right_part);
    void printRule(SymbolInfo *parent, vector<SymbolInfo *> children);
    void printCode(string code);
    void printRuleAndCode(SymbolInfo *parent, vector<SymbolInfo *> child);
};
// NonTerminal *printRuleAndCode(vector<SymbolInfo *> child, string name, bool is_exp = false);

NonTerminal *createNonTerminal(vector<SymbolInfo *> child, string name);
Expression *createExpression(vector<SymbolInfo *> child, string name);
ParameterList *createParameterList(vector<SymbolInfo *> child, string name);
ArgumentList *createArgumentList(vector<SymbolInfo *> child, string name);
DeclarationList *createDeclarationList(vector<SymbolInfo *> child, string name);
ArrayCall *createArrayCall(vector<SymbolInfo *> child, string name);
#endif