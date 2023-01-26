#include "../include/ASTGenerator.hpp"
#include <iostream>
std::string getIndent(int depth)
{
    std::string indent;
    for (int i = 0; i < depth; i++)
    {
        indent += " ";
    }
    return indent;
}
std::string ASTGenerator::getAST(Program *node, int depth)
{
    std::string tree = "";
    tree += getProgram((Program *)node, depth);
    return tree;
}
std::string ASTGenerator::getProgram(Program *prog, int depth)
{
    std::string tree = "";
    // tree += getIndent(depth);
    vector<FunctionDefinition *> func_defs = prog->getFunctionDefinitions();
    vector<FunctionDeclaration *> func_decs = prog->getFunctionDeclarations();
    vector<VariableDeclaration *> var_decs = prog->getVariableDeclarations();

    for (VariableDeclaration *var_dec : var_decs)
    {
        tree += getIndent(depth);
        tree += "VARIABLE_DECLARATION\n";
        tree += getVariableDeclaration(var_dec, depth + 1);
    }
    for (FunctionDeclaration *func_dec : func_decs)
    {
        tree += getIndent(depth);
        tree += "FUNCTION_DECLARATION\n";
        tree += getFunctionDeclaration(func_dec, depth + 1);
    }
    for (FunctionDefinition *func_def : func_defs)
    {
        tree += getIndent(depth);
        tree += "FUNCTION_DEFINITION\n";
        tree += getFunctionDefinition(func_def, depth + 1);
    }
    return tree;
}
std::string ASTGenerator::getUnit(Unit *unit, int depth)
{
    std::string tree = "";
    tree += getIndent(depth);
    string type = unit->getUnitType();
    tree += type + "\n";
    if (type == "VARIABLE_DECLARATION")
    {
        tree += getVariableDeclaration((VariableDeclaration *)unit, depth + 1);
    }
    if (type == "FUNCTION_DECLARATION")
    {
        tree += getFunctionDeclaration((FunctionDeclaration *)unit, depth + 1);
    }
    if (type == "FUNCTION_DEFINITION")
    {
        tree += getFunctionDefinition((FunctionDefinition *)unit, depth + 1);
    }
    return tree;
}
std::string ASTGenerator::getExpression(Expression *expr, int depth)
{

    std::string tree = "";
    if (expr == NULL)
        return tree;
    // tree += getIndent(depth);
    string type = expr->getExpType();
    if (type == "CALL_EXPRESSION")
    {
        tree += getCallExpression((CallExpression *)expr, depth);
    }
    if (type == "BINARY_EXPRESSION")
    {
        tree += getBinaryExpression((BinaryExpression *)expr, depth);
    }
    if (type == "UNARY_EXPRESSION")
    {
        tree += getUnaryExpression((UnaryExpression *)expr, depth);
    }
    return tree;
}
std::string ASTGenerator::getStatement(Statement *stmt, int depth)
{
    std::string tree = "";
    if (stmt == NULL)
        return tree;
    // tree += getIndent(depth);
    string type = stmt->getStatementType();
    if (type == "CONDITIONAL_STATEMENT")
    {
        tree += getConditionalStatement((ConditionalStatement *)stmt, depth);
    }
    if (type == "LOOP_STATEMENT")
    {
        tree += getLoopStatement((LoopStatement *)stmt, depth);
    }
    if (type == "PRINT_STATEMENT")
    {
        tree += getIndent(depth);
        tree += type + "\n";
        tree += getPrintStatement((PrintStatement *)stmt, depth);
    }
    if (type == "RETURN_STATEMENT")
    {
        tree += getIndent(depth);
        tree += type + "\n";
        tree += getReturnStatement((ReturnStatement *)stmt, depth);
    }
    if (type == "EXPRESSION_STATEMENT")
    {
        tree += getIndent(depth);
        tree += type + "\n";
        tree += getExpressionStatement((ExpressionStatement *)stmt, depth);
    }
    if (type == "COMPOUND_STATEMENT")
    {
        tree += getCompoundStatement((CompoundStatement *)stmt, depth);
    }
    if (type == "VARIABLE_DECLARATION")
    {
        tree += getIndent(depth);
        tree += type + "\n";
        tree += getVariableDeclaration((VariableDeclaration *)stmt, depth + 1);
    }
    if (type == "FUNCTION_DEFINITION")
    {
        tree += getIndent(depth);
        tree += type + "\n";
        tree += getFunctionDefinition((FunctionDefinition *)stmt, depth + 1);
    }
    if (type == "FUNCTION_DECLARATION")
    {
        tree += getIndent(depth);
        tree += type + "\n";
        tree += getFunctionDeclaration((FunctionDeclaration *)stmt, depth + 1);
    }
    return tree;
}
std::string ASTGenerator::getList(List *list, int depth)
{
    std::string tree = "";
    // tree += getIndent(depth);
    string type = list->getListType();
    return tree;
}
std::string ASTGenerator::getVariableDeclaration(VariableDeclaration *var_decl, int depth)
{
    std::string tree = "";
    tree += getIndent(depth);
    for (Variable *var : var_decl->getDeclarationList())
    {
        tree += getIndent(depth);
        if (var->getVarType() == "ARRAY")
        {
            tree += var->getDataType() + " " + var->getIdName() + "[" + ((Array *)var)->getArraySize() + "]" + "\n";
        }
        else
        {
            tree += var->getDataType() + " " + var->getIdName() + "\n";
        }
    }
    return tree;
}
std::string ASTGenerator::getFunctionDeclaration(FunctionDeclaration *func_decl, int depth)
{
    std::string tree = "";
    tree += getIndent(depth);
    tree += func_decl->getReturnType() + "\n";
    tree += getIndent(depth);
    tree += func_decl->getFunctionName() + "\n";
    tree += getIndent(depth);
    tree += "PARAMETER_LIST\n";
    for (Variable *p : func_decl->getParams())
    {
        tree += getIndent(depth + 1);
        tree += p->getDataType() + " " + p->getIdName() + "\n";
    }
    return tree;
}
std::string ASTGenerator::getFunctionDefinition(FunctionDefinition *func_def, int depth)
{
    std::string tree = "";
    tree += getIndent(depth);
    tree += func_def->getReturnType() + "\n";
    tree += getIndent(depth);
    tree += func_def->getFunctionName() + "\n";
    tree += getIndent(depth);
    tree += "PARAMETER_LIST\n";
    for (Variable *p : func_def->getParams())
    {
        tree += getIndent(depth + 1);
        tree += p->getDataType() + " " + p->getIdName() + "\n";
    }
    tree += getIndent(depth);
    tree += "FUNCTION_BODY\n";
    for (Statement *stmt : func_def->getBody())
    {
        tree += getStatement(stmt, depth + 1);
    }
    return tree;
}
std::string ASTGenerator::getDeclarationList(DeclarationList *decl_list, int depth)
{
    std::string tree = "";
    vector<Variable *> var_list = decl_list->getDeclarations();
    for (Variable *var : var_list)
    {
        tree += getIndent(depth);
        tree += var->getIdName() + "\n";
    }
    // if (var_list.empty())
    //     tree += "\n";
    return tree;
}
std::string ASTGenerator::getParameterList(ParameterList *params, int depth)
{
    std::string tree = "";
    vector<Variable *> list = params->getParams();
    for (Variable *p : list)
    {
        tree += getIndent(depth);
        tree += p->getDataType() + " " + p->getIdName() + "\n";
    }
    // if (list.empty())
    //     tree += "\n";
    return tree;
}
std::string ASTGenerator::getArgumentList(ArgumentList *args, int depth)
{
    std::string tree = "";
    // tree += getIndent(depth);
    vector<Expression *> list = args->getArgs();
    for (Expression *e : list)
    {
        tree += getExpression(e, depth + 1);
    }
    // tree += "\n";
    return tree;
}
std::string ASTGenerator::getCallExpression(CallExpression *call_expr, int depth)
{
    std::string tree = "";
    // tree += getIndent(depth);
    string type = call_expr->getCallType();
    if (type == "IDENTIFIER_CALL")
    {
        tree += getIdentifierCall((IdentifierCall *)call_expr, depth);
    }
    if (type == "CONSTANT_CALL")
    {
        tree += getIndent(depth);
        tree += type + "\n";
        tree += getConstantCall((ConstantCall *)call_expr, depth);
    }
    return tree;
}
std::string ASTGenerator::getIdentifierCall(IdentifierCall *id_call, int depth)
{
    std::string tree = "";
    // tree += getIndent(depth);
    string type = id_call->getIdentity();
    if (type == "VARIABLE_CALL")
    {
        tree += getVariableCall((VariableCall *)id_call, depth);
    }
    if (type == "FUNCTION_CALL")
    {
        tree += getIndent(depth);
        tree += type + "\n";
        tree += getFunctionCall((FunctionCall *)id_call, depth + 1);
    }
    return tree;
}
std::string ASTGenerator::getVariableCall(VariableCall *var_call, int depth)
{
    std::string tree = "";
    tree += getIndent(depth);
    string type = var_call->getVarType();
    tree += type + "\n";
    if (type == "PRIMITIVE_CALL")
    {
        tree += getIndent(depth) + " " + var_call->getIdName() + "\n";
    }
    if (type == "ARRAY_CALL")
    {
        tree += getArrayCall((ArrayCall *)var_call, depth + 1);
    }
    return tree;
}
std::string ASTGenerator::getArrayCall(ArrayCall *arr_call, int depth)
{
    std::string tree = "";
    tree += getIndent(depth);
    tree += arr_call->getIdName() + "\n";
    tree += getExpression(arr_call->getIndex(), depth);
    return tree;
}
std::string ASTGenerator::getConstantCall(ConstantCall *const_call, int depth)
{
    std::string tree = "";
    tree += getIndent(depth);
    string type = const_call->getDataType();
    tree += " " + const_call->getLiteral() + "\n";

    return tree;
}
std::string ASTGenerator::getFunctionCall(FunctionCall *func_call, int depth)
{
    std::string tree = "";
    tree += getIndent(depth);
    tree += func_call->getIdName() + "\n";
    for (Expression *e : func_call->getArgs())
    {
        tree += getExpression(e, depth + 1);
    }
    return tree;
}
std::string ASTGenerator::getBinaryExpression(BinaryExpression *bin_expr, int depth)
{
    std::string tree = "";
    tree += getIndent(depth);
    tree += bin_expr->getOpType() + "\n";
    tree += getExpression(bin_expr->getLeftOpr(), depth + 1);
    tree += getExpression(bin_expr->getRightOpr(), depth + 1);
    return tree;
}
std::string ASTGenerator::getUnaryExpression(UnaryExpression *unr_expr, int depth)
{
    std::string tree = "";
    tree += getIndent(depth);
    tree += unr_expr->getOpType() + "\n";
    tree += getExpression(unr_expr->getOperand(), depth + 1);
    return tree;
}
std::string ASTGenerator::getConditionalStatement(ConditionalStatement *cnd_stmt, int depth)
{
    std::string tree = "";
    tree += getIndent(depth);
    std::string type = cnd_stmt->getConditionType();
    tree += type + "\n";
    if (type == "IF_STATEMENT")
    {
        tree += getIfStatement((IfStatement *)cnd_stmt, depth + 1);
    }
    if (type == "IFELSE_STATEMENT")
    {
        tree += getIfElseStatement((IfElseStatement *)cnd_stmt, depth + 1);
    }
    return tree;
}
std::string ASTGenerator::getIfStatement(IfStatement *cnd_stmt, int depth)
{
    std::string tree = "";
    // tree += getIndent(depth);
    tree += getExpression(cnd_stmt->getCondition(), depth);
    tree += getStatement(cnd_stmt->getIfBody(), depth);
    return tree;
}
std::string ASTGenerator::getIfElseStatement(IfElseStatement *cnd_stmt, int depth)
{
    std::string tree = "";
    // tree += getIndent(depth);
    tree += getExpression(cnd_stmt->getCondition(), depth);
    tree += getStatement(cnd_stmt->getIfBody(), depth);
    tree += getStatement(cnd_stmt->getElseBody(), depth);
    return tree;
}
std::string ASTGenerator::getLoopStatement(LoopStatement *loop_stmt, int depth)
{
    std::string tree = "";
    tree += getIndent(depth);
    string type = loop_stmt->getLoopType();
    tree += type + "\n";
    if (type == "FOR_LOOP")
    {
        tree += getForLoop((ForLoop *)loop_stmt, depth + 1);
    }
    if (type == "WHILE_LOOP")
    {
        tree += getWhileLoop((WhileLoop *)loop_stmt, depth + 1);
    }
    return tree;
}
std::string ASTGenerator::getForLoop(ForLoop *for_loop, int depth)
{
    std::string tree = "";
    // tree += getIndent(depth);
    tree += getExpression(for_loop->getInitialize(), depth);
    // tree += getIndent(depth);
    tree += getExpression(for_loop->getCondition(), depth);
    // tree += getIndent(depth);
    tree += getExpression(for_loop->getIncDec(), depth);
    // tree += getIndent(depth);
    tree += getStatement(for_loop->getBody(), depth);
    return tree;
}
std::string ASTGenerator::getWhileLoop(WhileLoop *while_loop, int depth)
{
    std::string tree = "";
    // tree += getIndent(depth);
    tree += getExpression(while_loop->getCondition(), depth);
    // tree += getIndent(depth);
    tree += getStatement(while_loop->getBody(), depth);
    return tree;
}
std::string ASTGenerator::getPrintStatement(PrintStatement *print_stmt, int depth)
{
    std::string tree = "";
    // tree += getIndent(depth);
    tree += getVariableCall(print_stmt->getVariableCall(), depth + 1);
    return tree;
}
std::string ASTGenerator::getReturnStatement(ReturnStatement *ret_stmt, int depth)
{
    std::string tree = "";
    // tree += getIndent(depth);
    tree += getExpression(ret_stmt->getExpression(), depth + 1);
    return tree;
}
std::string ASTGenerator::getCompoundStatement(CompoundStatement *stmt_list, int depth)
{
    std::string tree = "";
    // tree += getIndent(depth);
    vector<Statement *> list = stmt_list->getStatements();

    for (Statement *stmt : list)
    {
        tree += getStatement(stmt, depth);
    }
    return tree;
}
std::string ASTGenerator::getExpressionStatement(ExpressionStatement *expr_stmt, int depth)
{
    std::string tree = "";
    // tree += getIndent(depth);
    tree += getExpression(expr_stmt->getExpression(), depth + 1);
    return tree;
}