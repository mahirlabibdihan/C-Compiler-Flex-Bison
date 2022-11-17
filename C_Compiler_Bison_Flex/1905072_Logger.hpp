#ifndef __LOGGER__
#define __LOGGER__
#include <string>
#include "1905072_SymbolInfo.hpp"
#include "1905072_Symbol_Extended.hpp"
using namespace std;
#define KEYWORD_LOG 0
#define INTEGER_LOG 1
#define FLOAT_LOG 2
#define CHARACTER_LOG 3
#define STRING_LOG 4
#define OPERATOR_LOG 5
#define IDENTIFIER_LOG 6
#define COMMENT_LOG 7

void printLog(string token, string lexeme, int line);
void printLogWithToken(string token, string lexeme, string actual, int line);
void printLogData(int type, int line, string lexeme);
void printRule(string left_part, string right_part);
void printRule(SymbolInfo *parent, vector<SymbolInfo *> children);
// void printRule(SymbolInfo *parent, vector<Segment *> children);
void printCode(string code);
// SymbolInfo *printRuleAndCode(vector<SymbolInfo *> child, string name);
NonTerminal *printRuleAndCode(vector<SymbolInfo *> child, string name, bool is_exp = false);

NonTerminal *createNonTerminal(vector<SymbolInfo *> child, string name);
Expression *createExpression(vector<SymbolInfo *> child, string name);
ParameterList *createParameterList(vector<SymbolInfo *> child, string name);
ArgumentList *createArgumentList(vector<SymbolInfo *> child, string name);
DeclarationList *createDeclarationList(vector<SymbolInfo *> child, string name);
ArrayCall *createArrayCall(vector<SymbolInfo *> child, string name);
#endif