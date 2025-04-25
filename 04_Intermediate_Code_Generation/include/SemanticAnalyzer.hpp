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
    int id_count;

public:
    SymbolTable *table;
    ErrorHandler *error_hndlr;
    LexicalAnalyzer *lexer;
    ofstream &logout;
    ofstream &errorout;
    Program *tree_root;
    stack<FunctionDefinition *> functions;
    bool matchTwoFunction(Function *f1, Function *f2);
    bool isZero(Expression *expr);
    bool isConstant(Expression *expr);
    int getConstant(Expression *expr);

    SemanticAnalyzer(LexicalAnalyzer *lexer, SymbolTable *table, ErrorHandler *error_hndlr, ofstream &logout, ofstream &errorout);
    ~SemanticAnalyzer();

    string evaluateFunctionCall(FunctionCall *func_call);
    string checkVariableCall(VariableCall *var_call);
    string checkArrayCall(ArrayCall *arr_call);

    void declareFunctionParams(vector<Variable *> params);
    void checkFunctionDefinition(FunctionDefinition *func_def);

    void checkFunctionDeclaration(FunctionDeclaration *func_dec);
    void declareVariable(Variable *var);
    void declareArray(Array *arr);

    string assignOp(AssignOp *expr);
    string logicOp(LogicOp *expr);
    string relOp(RelOp *expr);
    string addOp(AddOp *expr);
    string mulOp(MulOp *expr);

    string implicitTypecast(string left, string right);
    bool checkAssignment(string left, string right);

    void endScope();
    void startScope();

    void startProgram(Program *prog);
    string evaluateExpression(Expression *expr);
    string evaluateBinaryExpression(BinaryExpression *bin_expr);
    string evaluateUnaryExpression(UnaryExpression *unr_expr);
    string evaluateCallExpression(CallExpression *call_expr);
    string callIdentifier(IdentifierCall *id_call);
    string callVariable(VariableCall *var_call);
    string callArray(ArrayCall *arr_call);
    string callFunction(FunctionCall *func_call);

    void analyzeStatement(Statement *stmt);
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

    void declareVariables(VariableDeclaration *var_decl);
    void declareFunction(FunctionDeclaration *func_decl);
    void defineFunction(FunctionDefinition *func_def);
};
#endif