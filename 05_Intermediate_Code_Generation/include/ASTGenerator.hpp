#ifndef __AST_GENERATOR_H
#define __AST_GENERATOR_H 1
#include "../include/ExtendedSymbol.hpp"
#include <vector>
#include <string>

namespace ASTGenerator
{
    std::string getAST(Program *node, int depth = 0);
    std::string getProgram(Program *prog, int depth);
    std::string getUnit(Unit *unit, int depth);
    std::string getExpression(Expression *unit, int depth);
    std::string getStatement(Statement *stmt, int depth);
    std::string getList(List *list, int depth);
    std::string getVariableDeclaration(VariableDeclaration *var_decl, int depth);
    std::string getFunctionDeclaration(FunctionDeclaration *func_decl, int depth);
    std::string getFunctionDefinition(FunctionDefinition *func_def, int depth);
    std::string getDeclarationList(DeclarationList *decl_list, int depth);
    std::string getParameterList(ParameterList *params, int depth);
    std::string getArgumentList(ArgumentList *args, int depth);
    std::string getCallExpression(CallExpression *call_expr, int depth);
    std::string getIdentifierCall(IdentifierCall *id_call, int depth);
    std::string getVariableCall(VariableCall *var_call, int depth);
    std::string getArrayCall(ArrayCall *arr_call, int depth);
    std::string getFunctionCall(FunctionCall *func_call, int depth);
    std::string getConstantCall(ConstantCall *const_call, int depth);
    std::string getBinaryExpression(BinaryExpression *bin_expr, int depth);
    std::string getUnaryExpression(UnaryExpression *unr_expr, int depth);
    std::string getConditionalStatement(ConditionalStatement *cnd_stmt, int depth);
    std::string getIfStatement(IfStatement *cnd_stmt, int depth);
    std::string getIfElseStatement(IfElseStatement *cnd_stmt, int depth);
    std::string getLoopStatement(LoopStatement *loop_stmt, int depth);
    std::string getForLoop(ForLoop *for_loop, int depth);
    std::string getWhileLoop(WhileLoop *while_loop, int depth);
    std::string getPrintStatement(PrintStatement *print_stmt, int depth);
    std::string getReturnStatement(ReturnStatement *ret_stmt, int depth);
    std::string getCompoundStatement(CompoundStatement *stmt_list, int depth);
    std::string getExpressionStatement(ExpressionStatement *expr_stmt, int depth);
};

#endif