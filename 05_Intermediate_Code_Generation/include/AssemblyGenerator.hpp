#ifndef __ASSEMBLY_GENERATOR_H
#define __ASSEMBLY_GENERATOR_H 1
#include "../include/ExtendedSymbol.hpp"
#include "../include/SymbolTable.hpp"
#include <fstream>
#include <stack>
class AssemblyGenerator
{
    SymbolTable *table;
    std::ofstream &asmout;
    int indent;
    std::vector<int> offset_history;
    FunctionDefinition *curr_func;
    int label_count;

public:
    AssemblyGenerator(SymbolTable *table, std::ofstream &asmout);
    void startProgram(Program *prog);

    void declareVariable(Variable *var);
    void declareArray(Array *arr);

    void declareVariables(VariableDeclaration *var_decl);
    void declareFunction(FunctionDeclaration *func_decl);
    void defineFunction(FunctionDefinition *func_def);
    void returnFunction();
    void definePrintFunction();

    void declareFunctionParams(std::vector<Variable *> params);
    void print(const string &code);

    // Statements
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

    // Expressions
    void evaluateExpression(Expression *expr);
    void evaluateBinaryExpression(BinaryExpression *bin_expr);
    void evaluateUnaryExpression(UnaryExpression *unr_expr);
    void evaluateCallExpression(CallExpression *call_expr);

    void assignOp(AssignOp *expr);
    void logicOp(LogicOp *expr);
    std::string getRelOpASM(string op);
    void relOp(RelOp *expr);
    void addOp(AddOp *expr);
    void mulOp(MulOp *expr);
    void uaddOp(UAddOp *expr);
    void notOp(NotOp *expr);
    void incOp(IncOp *expr);
    void decOp(DecOp *expr);
    void incdecOp(VariableCall *expr, std::string op);
    void callConstant(ConstantCall *const_call);
    void callIdentifier(IdentifierCall *id_call);
    void callVariable(VariableCall *var_call);
    void callArray(ArrayCall *arr_call);
    void callFunction(FunctionCall *func_call);

    void assignVariable(VariableCall *var_call);

    std::string newLabel();
};
#endif