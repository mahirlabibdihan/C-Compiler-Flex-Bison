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
    bool isZero(Expression *expr);

public:
    SemanticAnalyzer(LexicalAnalyzer *lexer, SymbolTable *table, ErrorHandler *error_hndlr, ofstream &logout, ofstream &errorout);
    ~SemanticAnalyzer();

    string evaluateFunctionCall(FunctionCall *func_call);
    string checkVariableCall(VariableCall *var_call);
    string checkArrayCall(ArrayCall *arr_call);

    void declareFunctionParams(vector<Variable *> params);
    void checkFunctionDefinition(FunctionDefinition *func_def);
    // void returnFunction(Expression *);
    // void endFunction();

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
    string evaluateExpression(Expression *expr); // Unary, Binary, Call
    string evaluateBinaryExpression(BinaryExpression *bin_expr);
    string evaluateUnaryExpression(UnaryExpression *unr_expr);
    string evaluateCallExpression(CallExpression *call_expr);
    string callIdentifier(IdentifierCall *id_call);
    string callVariable(VariableCall *var_call);
    string callArray(ArrayCall *arr_call);
    string callFunction(FunctionCall *func_call);
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

    void declareVariables(VariableDeclaration *var_decl);
    void declareFunction(FunctionDeclaration *func_decl);
    void defineFunction(FunctionDefinition *func_def);
    // void analyzeDeclarationList(DeclarationList *decl_list);
    // void analyzeParameterList(ParameterList *params);
    // void analyzeArgumentList(ArgumentList *args);
};
#endif