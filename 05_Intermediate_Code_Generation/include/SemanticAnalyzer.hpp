/**
 * Author: Mahir Labib Dihan
 * Last modified: January 18, 2023
 */
#ifndef __SEMANTIC_ANALYZER_H
#define __SEMANTIC_ANALYZER_H 1
#include <string>
#include <vector>
#include <stack>
#include "../include/SymbolInfo.hpp"
#include "../include/ExtendedSymbol.hpp"
#include "../include/LexicalAnalyzer.hpp"
using namespace std;

class SemanticAnalyzer
{
    SymbolTable *table;
    ErrorHandler *error_hndlr;
    LexicalAnalyzer *lexer;
    ofstream &logout;
    ofstream &errorout;
    Program *tree_root;

private:
    bool matchTwoFunction(Function *f1, Function *f2);

public:
    SemanticAnalyzer(LexicalAnalyzer *lexer, SymbolTable *table, ErrorHandler *error_hndlr, ofstream &logout, ofstream &errorout);
    ~SemanticAnalyzer();

    string callFunction(string id, vector<Expression *> args);
    string callVariable(string id);
    string callArray(string id, Expression *index);

    void declareFunctionParams(vector<Variable *> params);
    void defineFunction(string ret_type, string func_name, vector<Variable *> params);
    // void returnFunction(Expression *);
    // void endFunction();

    void declareFunction(string ret_type, string func_name, vector<Variable *> params);
    void declareVariables(string data_type, vector<Variable *> ids);
    void declareVariable(string data_type, string var_name);
    void declareArray(string data_type, string arr_name, string arr_size);

    string assignOp(const string &left, const string &right);
    string logicOp(const string &left, const string &op, const string &right);
    string relOp(const string &left, const string &op, const string &right);
    string addOp(const string &left, const string &op, const string &right);
    string mulOp(const string &left, const string &op, const string &right);

    string implicitTypecast(string left, string right);
    bool checkAssignment(string left, string right);

    // void handleInvalidFunctionScoping();
    void handlePrintlnCall(std::string id_name);
    void endScope();
    void startScope();
    int getLineCount();

    void setASTRoot(Program *root);
    Program *getASTRoot();
    // void pushFunction(string ret_type, string func_name, vector<Variable *> params);
    // void popFunction();

    void startProgram(Program *prog);
    void analyzeUnit(Unit *unit);
    string analyzeExpression(Expression *expr); // Unary, Binary, Call
    string analyzeBinaryExpression(BinaryExpression *bin_expr);
    string analyzeUnaryExpression(UnaryExpression *unr_expr);
    string analyzeCallExpression(CallExpression *call_expr);
    string analyzeIdentifierCall(IdentifierCall *id_call);
    string analyzeVariableCall(VariableCall *var_call);
    string analyzeArrayCall(ArrayCall *arr_call);
    string analyzeFunctionCall(FunctionCall *func_call);
    // string analyzeConstantCall(ConstantCall *const_call);

    void analyzeStatement(Statement *stmt); // Conditional, Loop, Return, Print, Expression
    void analyzeConditionalStatement(ConditionalStatement *stmt);
    void analyzeLoopStatement(LoopStatement *stmt);
    void analyzeIfStatement(IfStatement *if_stmt);
    void analyzeIfElseStatement(IfElseStatement *ifelse_stmt);
    void analyzeForLoop(ForLoop *for_loop);
    void analyzeWhileLoop(WhileLoop *while_loop);
    void analyzeReturnStatement(ReturnStatement *ret_stmt);
    void analyzePrintStatement(PrintStatement *print_stmt);
    void analyzeCompoundStatement(CompoundStatement *stmt_list);
    void analyzeExpressionStatement(ExpressionStatement *expr_stmt);

    void analyzeVariableDeclaration(VariableDeclaration *var_decl);
    void analyzeFunctionDeclaration(FunctionDeclaration *func_decl);
    void analyzeFunctionDefinition(FunctionDefinition *func_def);
    // void analyzeDeclarationList(DeclarationList *decl_list);
    // void analyzeParameterList(ParameterList *params);
    // void analyzeArgumentList(ArgumentList *args);
};
#endif