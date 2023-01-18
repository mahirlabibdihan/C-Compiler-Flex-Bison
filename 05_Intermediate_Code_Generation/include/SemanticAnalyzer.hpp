#ifndef __SEMANTIC_ANALYZER__
#define __SEMANTIC_ANALYZER__
#include <string>
#include <vector>
#include "../include/SymbolInfo.hpp"
#include "../include/ExtendedSymbol.hpp"
#include "../include/LexicalAnalyzer.hpp"
using namespace std;

class SemanticAnalyzer
{
    Function *curr_func;
    Expression *curr_exp;
    SymbolTable *table;
    ErrorHandler *error_hndlr;
    LexicalAnalyzer *lexer;
    bool in_function;
    ofstream &logout;
    ofstream &errorout;

private:
    bool matchTwoFunction(Function *f1, Function *f2);

public:
    SemanticAnalyzer(LexicalAnalyzer *lexer, SymbolTable *table, ErrorHandler *error_hndlr, ofstream &logout, ofstream &errorout);
    ~SemanticAnalyzer();

    string callFunction(string id, vector<Expression *> args);
    string callVariable(string id);
    string callArray(string id, Expression *index);

    void declareFunctionParams();
    void defineFunction(string ret_type, string func_name, vector<Variable *> params);
    void returnFunction(Expression *);
    void endFunction();

    void declareFunction(string ret_type, string func_name, vector<Variable *> params);
    void declareVariables(string data_type, string id_names, vector<Variable *> ids);
    void declareVariable(string data_type, string var_name);
    void declareArray(string data_type, string arr_name, string arr_size);

    string assignOp(Expression *left, Expression *right);
    string logicOp(Expression *left, string op, Expression *right);
    string relOp(Expression *left, string op, Expression *right);
    string addOp(Expression *left, string op, Expression *right);
    string mulOp(Expression *left, string op, Expression *right);

    string implicitTypecast(string left, string right);
    bool isConvertible(string to, string from);
    bool checkAssignment(string left, string right);

    void setCurrentExp(Expression *);

    void handleInvalidFunctionScoping();
    void handlePrintfCall(std::string id_name);
    void endScope();
    void startScope();
    void checkArraySize(Terminal *size);
    int getLineCount();
};
#endif