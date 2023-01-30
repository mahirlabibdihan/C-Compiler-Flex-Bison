#include "../include/AssemblyGenerator.hpp"
#include "../include/Util.hpp"
#include <sstream>
#include <algorithm>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <type_traits>
#include <typeinfo>

AssemblyGenerator::AssemblyGenerator(SymbolTable *table, std::ofstream &out) : asmout(out)
{
    this->table = table;
    indent = 0;
    label_count = 0;
}
void AssemblyGenerator::startProgram(Program *prog)
{
    vector<FunctionDefinition *> func_defs = prog->getFunctionDefinitions();
    vector<FunctionDeclaration *> func_decs = prog->getFunctionDeclarations();
    vector<VariableDeclaration *> var_decs = prog->getVariableDeclarations();

    print(".MODEL SMALL");
    print(".STACK 100H");
    print(".DATA");
    indent++;
    for (VariableDeclaration *var_dec : var_decs)
    {
        declareVariables(var_dec);
    }
    indent--;

    for (FunctionDeclaration *func_dec : func_decs)
    {
        declareFunction(func_dec);
    }

    print(".CODE");
    indent++;
    definePrintFunction();
    for (FunctionDefinition *func_def : func_defs)
    {
        defineFunction(func_def);
    }
    indent--;

    print("END MAIN");
}
void AssemblyGenerator::declareVariables(VariableDeclaration *var_decl)
{
    vector<Variable *> vars = var_decl->getDeclarationList();

    for (Variable *var : vars)
    {
        if (var->getVarType() == "ARRAY")
        {
            declareArray((Array *)var);
        }
        else
        {
            declareVariable(var);
        }
    }
}
void AssemblyGenerator::declareVariable(Variable *var)
{
    string data_type = var->getDataType();
    string var_name = var->getIdName();
    Variable *new_var = new Variable(var_name, data_type);
    table->insert(new_var);

    if (table->getCurrentScope()->getId() == 1)
    {
        print(var->getIdName() + " DW ?");
    }
    else
    {
        print("PUSH BX");
        new_var->setOffset(offset_history.back());
        offset_history.back() -= 2;
    }
}
void AssemblyGenerator::declareArray(Array *arr)
{
    string data_type = arr->getDataType();
    string arr_name = arr->getIdName();
    string arr_size = arr->getArraySize();
    Array *new_arr = new Array(arr_name, data_type, arr_size);
    table->insert(new_arr);

    if (table->getCurrentScope()->getId() == 1)
    {
        print(arr->getIdName() + " DW " + arr->getArraySize() + " DUP(?)");
    }
    else
    {
        for (int i = 0; i < stoi(arr_size); i++)
        {
            print("PUSH BX");
        }
        new_arr->setOffset(offset_history.back());
        offset_history.back() -= stoi(arr_size) * 2; // Stack decrease downward
    }
}
void AssemblyGenerator::declareFunctionParams(vector<Variable *> params)
{
    std::reverse(params.begin(), params.end());
    int offset = 4;
    for (auto i : params)
    {
        string param_name = i->getIdName();
        Variable *var = new Variable(param_name, i->getDataType());
        var->setOffset(offset);
        if (!table->insert(var))
        {
        }
        offset += 2;
    }
}
void AssemblyGenerator::returnFunction()
{
    if (curr_func->getReturnType() != "VOID")
    {
        print("POP AX");
    }
    print("MOV SP, BP");
    print("POP BP");

    if (curr_func->getFunctionName() != "main")
    {
        print("RET " + std::to_string(2 * curr_func->getParams().size()));
    }
}
void AssemblyGenerator::analyzePrintStatement(PrintStatement *print_stmt)
{
    callVariable(print_stmt->getVariableCall());

    print("CALL OUTPUT");
}
void AssemblyGenerator::definePrintFunction()
{
    ifstream in("print.asm");
    string line;
    while (getline(in, line))
    {
        print(line);
    }
    in.close();
}
void AssemblyGenerator::defineFunction(FunctionDefinition *func_def)
{
    string ret_type = func_def->getReturnType();
    string func_name = func_def->getFunctionName();
    vector<Variable *> params = func_def->getParams();
    vector<Statement *> stmt_list = func_def->getBody();

    Function *new_func = new Function(func_name, ret_type);

    curr_func = func_def;

    for (auto p : params)
    {
        new_func->addParam(new Variable(p->getIdName(), p->getDataType()));
    }

    table->insert(new_func);

    print(func_name + " PROC");

    indent++;
    table->enterScope();

    if (func_def->getFunctionName() == "main")
    {
        print("MOV AX, @DATA");
        print("MOV DS, AX");
        print("MOV BP, SP");

        offset_history.push_back(-2);
    }
    else
    {
        print("PUSH BP");
        print("MOV BP, SP");
        offset_history.push_back(-2);
    }

    declareFunctionParams(params);
    for (Statement *stmt : stmt_list)
    {
        analyzeStatement(stmt);
    }

    if (func_def->getFunctionName() == "main")
    {
        print("MOV AH, 4CH");
        print("INT 21H");
    }

    returnFunction();
    offset_history.pop_back();
    table->exitScope();
    indent--;

    print(func_name + " ENDP");
}
void AssemblyGenerator::declareFunction(FunctionDeclaration *func_decl)
{
    string ret_type = func_decl->getReturnType();
    string func_name = func_decl->getFunctionName();
    vector<Variable *> params = func_decl->getParams();

    Function *new_func = new Function(func_name, ret_type);

    for (auto p : params)
    {
        new_func->addParam(new Variable(p->getIdName(), p->getDataType()));
    }

    if (!table->insert(new_func))
    {
    }
}
void AssemblyGenerator::print(const string &code)
{
    string *lines = Util::split(code, '\n');
    int count = Util::countTokens(code, '\n');
    for (int i = 0; i < count; i++)
    {
        for (int j = 1; j <= indent; j++)
        {
            asmout << "\t";
        }
        asmout << lines[i] << std::endl;
    }
}
void AssemblyGenerator::analyzeStatement(Statement *stmt)
{
    if (stmt == NULL)
        return;
    string type = stmt->getStatementType();
    if (type == "CONDITIONAL_STATEMENT")
    {
        analyzeConditionalStatement((ConditionalStatement *)stmt);
    }
    if (type == "LOOP_STATEMENT")
    {
        analyzeLoopStatement((LoopStatement *)stmt);
    }
    if (type == "PRINT_STATEMENT")
    {
        analyzePrintStatement((PrintStatement *)stmt);
    }
    if (type == "RETURN_STATEMENT")
    {
        analyzeReturnStatement((ReturnStatement *)stmt);
    }
    if (type == "EXPRESSION_STATEMENT")
    {
        analyzeExpressionStatement((ExpressionStatement *)stmt);
    }
    if (type == "COMPOUND_STATEMENT")
    {
        table->enterScope();
        analyzeCompoundStatement((CompoundStatement *)stmt);
        table->exitScope();
    }
    if (type == "VARIABLE_DECLARATION")
    {
        declareVariables((VariableDeclaration *)stmt);
    }
}
void AssemblyGenerator::analyzeExpressionStatement(ExpressionStatement *expr_stmt)
{
    evaluateExpression(expr_stmt->getExpression());
}
void AssemblyGenerator::analyzeCompoundStatement(CompoundStatement *stmt_list)
{
    vector<Statement *> list = stmt_list->getStatements();
    for (Statement *stmt : list)
    {
        analyzeStatement(stmt);
    }
}
void AssemblyGenerator::evaluateExpression(Expression *expr)
{
    if (expr != NULL)
    {
        string type = expr->getExpType();
        if (type == "CALL_EXPRESSION")
        {
            evaluateCallExpression((CallExpression *)expr);
        }
        if (type == "BINARY_EXPRESSION")
        {
            evaluateBinaryExpression((BinaryExpression *)expr);
        }
        if (type == "UNARY_EXPRESSION")
        {
            return evaluateUnaryExpression((UnaryExpression *)expr);
        }
    }
}
void AssemblyGenerator::evaluateBinaryExpression(BinaryExpression *bin_expr)
{
    string type = bin_expr->getOpType();
    if (type == "ASSIGNOP")
    {
        assignOp((AssignOp *)bin_expr);
    }
    if (type == "ADDOP")
    {
        addOp((AddOp *)bin_expr);
    }
    if (type == "MULOP")
    {
        mulOp((MulOp *)bin_expr);
    }
    if (type == "RELOP")
    {
        relOp((RelOp *)bin_expr);
    }
    if (type == "LOGICOP")
    {
        logicOp((LogicOp *)bin_expr);
    }
}
void AssemblyGenerator::evaluateUnaryExpression(UnaryExpression *unr_expr)
{
    string type = unr_expr->getOpType();

    if (type == "UADDOP")
    {
        uaddOp((UAddOp *)unr_expr);
    }
    if (type == "NOTOP")
    {
        notOp((NotOp *)unr_expr);
    }
    if (type == "INCOP")
    {
        incOp((IncOp *)unr_expr);
    }
    if (type == "DECOP")
    {
        decOp((DecOp *)unr_expr);
    }
}
void AssemblyGenerator::analyzeConditionalStatement(ConditionalStatement *cnd_stmt)
{
    std::string type = cnd_stmt->getConditionType();
    if (type == "IF_STATEMENT")
    {
        analyzeIfStatement((IfStatement *)cnd_stmt);
    }
    if (type == "IFELSE_STATEMENT")
    {
        analyzeIfElseStatement((IfElseStatement *)cnd_stmt);
    }
}
void AssemblyGenerator::analyzeLoopStatement(LoopStatement *loop_stmt)
{
    string type = loop_stmt->getLoopType();
    if (type == "FOR_LOOP")
    {
        analyzeForLoop((ForLoop *)loop_stmt);
    }
    if (type == "WHILE_LOOP")
    {
        analyzeWhileLoop((WhileLoop *)loop_stmt);
    }
}
void AssemblyGenerator::analyzeIfStatement(IfStatement *if_stmt)
{
    evaluateExpression(if_stmt->getCondition());

    string true_label = newLabel();
    string end_label = newLabel();

    print("POP AX");
    print("CMP AX, 0");
    print("JE " + end_label);
    analyzeStatement(if_stmt->getIfBody());
    print(end_label + ":");
}
void AssemblyGenerator::analyzeIfElseStatement(IfElseStatement *ifelse_stmt)
{
    evaluateExpression(ifelse_stmt->getCondition());
    string else_label = newLabel();
    string end_label = newLabel();

    print("POP AX");
    print("CMP AX, 0");
    print("JE " + else_label);
    analyzeStatement(ifelse_stmt->getIfBody());
    print("JMP " + end_label);
    print(else_label + ":");
    analyzeStatement(ifelse_stmt->getElseBody());
    print(end_label + ":");
}
void AssemblyGenerator::analyzeForLoop(ForLoop *for_loop)
{
    std::string start_label = newLabel();
    std::string end_label = newLabel();

    evaluateExpression(for_loop->getInitialize());
    print(start_label + ":");
    evaluateExpression(for_loop->getCondition());
    print("POP AX");
    print("CMP AX, 0");
    print("JE " + end_label);
    analyzeStatement(for_loop->getBody());
    evaluateExpression(for_loop->getIncDec());
    print("POP AX"); // Pop increment
    print("JMP " + start_label);
    print(end_label + ":");
}
void AssemblyGenerator::analyzeWhileLoop(WhileLoop *while_loop)
{
    std::string start_label = newLabel();
    std::string end_label = newLabel();

    print(start_label + ":");
    evaluateExpression(while_loop->getCondition());
    print("POP AX");
    print("CMP AX, 0");
    print("JE " + end_label);
    analyzeStatement(while_loop->getBody());
    print("JMP " + start_label);
    print(end_label + ":");
}
void AssemblyGenerator::analyzeReturnStatement(ReturnStatement *ret_stmt)
{
    Expression *ret_expr = ret_stmt->getExpression();
    evaluateExpression(ret_expr);
    returnFunction();
}
void AssemblyGenerator::evaluateCallExpression(CallExpression *call_expr)
{
    string type = call_expr->getCallType();
    if (type == "IDENTIFIER_CALL")
    {
        callIdentifier((IdentifierCall *)call_expr);
    }
    if (type == "CONSTANT_CALL")
    {
        callConstant((ConstantCall *)call_expr);
    }
}
void AssemblyGenerator::callConstant(ConstantCall *const_call)
{
    print("PUSH " + const_call->getLiteral());
}
void AssemblyGenerator::callIdentifier(IdentifierCall *id_call)
{
    string type = id_call->getIdentity();
    if (type == "VARIABLE_CALL")
    {
        callVariable((VariableCall *)id_call);
    }
    if (type == "FUNCTION_CALL")
    {
        callFunction((FunctionCall *)id_call);
    }
}
void AssemblyGenerator::callFunction(FunctionCall *func_call)
{
    string func_name = func_call->getIdName();
    vector<Expression *> args = func_call->getArgs();
    for (Expression *e : args)
    {
        evaluateExpression(e);
    }
    Function *func = (Function *)table->find(func_name);
    print("CALL " + func_name);
    if (func->getReturnType() != "VOID")
    {
        print("PUSH AX");
    }
}
void AssemblyGenerator::uaddOp(UAddOp *expr)
{
    evaluateExpression(expr->getOperand());
    if (expr->getOperator() == "-")
    {
        print("POP BX");
        print("NEG BX");
        print("PUSH BX");
    }
}
void AssemblyGenerator::notOp(NotOp *expr)
{
    evaluateExpression(expr->getOperand());
    print("POP AX");
    print("NOT AX");
    print("PUSH AX");
}
void AssemblyGenerator::incdecOp(VariableCall *var_call, std::string op)
{
    assignVariable(var_call);

    Variable *var = (Variable *)table->find(var_call->getIdName());

    if (var->getVarType() == "ARRAY")
    {
        print("POP BX");
        if (table->getScopeIdOfSymbol(var->getIdName()) == 1)
        {
            print("PUSH " + var->getIdName() + "[BX]");           // Pushing previous value to stack
            print(op + " WORD PTR " + var->getIdName() + "[BX]"); // Increment the value
        }
        else
        {
            string offset = std::to_string(var->getOffset());
            print("MOV SI, BX");
            print("SUB SI, " + offset);
            print("NEG SI");
            print("PUSH [BP+SI]");
            print(op + " WORD PTR [BP+SI]");
        }
    }
    else
    {
        if (table->getScopeIdOfSymbol(var->getIdName()) == 1)
        {
            print("PUSH " + var->getIdName());
            print(op + " WORD PTR  " + var->getIdName());
        }
        else
        {
            string offset = std::to_string(var->getOffset());
            print("PUSH [BP + " + offset + "]");
            print(op + " WORD PTR [BP + " + offset + "]");
        }
    }
}
void AssemblyGenerator::incOp(IncOp *expr)
{
    incdecOp((VariableCall *)expr->getOperand(), "INC");
}
void AssemblyGenerator::decOp(DecOp *expr)
{
    incdecOp((VariableCall *)expr->getOperand(), "DEC");
}
void AssemblyGenerator::assignOp(AssignOp *expr)
{
    VariableCall *left_var = (VariableCall *)expr->getLeftOpr();
    assignVariable(left_var);
    evaluateExpression(expr->getRightOpr());

    Variable *left = (Variable *)table->find(left_var->getIdName());
    print("POP AX");

    if (left->getVarType() == "ARRAY")
    {
        print("POP BX");
        if (table->getScopeIdOfSymbol(left->getIdName()) == 1)
        {
            print("MOV " + left->getIdName() + "[BX], AX");
        }
        else
        {
            string offset = std::to_string(left->getOffset());
            print("MOV SI, BX");
            print("SUB SI, " + offset);
            print("NEG SI");
            print("MOV [BP+SI], AX");
        }
    }
    else
    {
        if (table->getScopeIdOfSymbol(left->getIdName()) == 1)
        {
            print("MOV " + left->getIdName() + ", AX");
        }
        else
        {
            string offset = std::to_string(left->getOffset());
            print("MOV [BP + " + offset + "], AX");
        }
    }
}
void AssemblyGenerator::logicOp(LogicOp *expr)
{
    evaluateExpression(expr->getLeftOpr());
    evaluateExpression(expr->getRightOpr());

    std::string op = expr->getOperator();

    string true_label = newLabel();
    string false_label = newLabel();
    string end_label = newLabel();

    print("POP BX");
    print("POP AX");

    if (op == "&&")
    {
        print("AND AX, BX");
    }
    else if (op == "||")
    {
        print("OR AX, BX");
    }
    print("PUSH AX");
}
std::string AssemblyGenerator::getRelOpASM(string op)
{
    if (op == ">")
    {
        return "JG";
    }
    else if (op == ">=")
    {
        return "JGE";
    }
    else if (op == "<")
    {
        return "JL";
    }
    else if (op == "<=")
    {
        return "JLE";
    }
    else if (op == "!=")
    {
        return "JNE";
    }
    else if (op == "==")
    {
        return "JE";
    }
    return "";
}
void AssemblyGenerator::relOp(RelOp *expr)
{
    evaluateExpression(expr->getLeftOpr());
    evaluateExpression(expr->getRightOpr());

    string true_label = newLabel();
    string end_label = newLabel();

    string op = getRelOpASM(expr->getOperator());
    print("POP BX");
    print("POP AX");
    print("CMP AX, BX");
    print(op + " " + true_label);
    print("PUSH 0");
    print("JMP " + end_label);
    print(true_label + ":");
    print("PUSH 1");
    print(end_label + ":");
}
void AssemblyGenerator::addOp(AddOp *expr)
{
    evaluateExpression(expr->getLeftOpr());
    evaluateExpression(expr->getRightOpr());

    string op = expr->getOperator();
    string opr = (op == "+" ? "ADD" : "SUB");

    print("POP BX");
    print("POP AX");
    print(opr + " AX, BX");
    print("PUSH AX");
}
void AssemblyGenerator::mulOp(MulOp *expr)
{
    evaluateExpression(expr->getLeftOpr());
    evaluateExpression(expr->getRightOpr());

    string op = expr->getOperator();

    print("POP BX");
    print("POP AX");
    if (op == "*")
    {
        print("CWD");
        print("IMUL BX");
        print("PUSH AX");
    }
    else
    {
        print("CWD");
        print("IDIV BX");

        if (op == "%")
        {
            print("PUSH DX");
        }
        else
        {
            print("PUSH AX");
        }
    }
}
void AssemblyGenerator::callVariable(VariableCall *var_call)
{
    string var_name = var_call->getIdName();
    Variable *var = (Variable *)table->find(var_name);

    string type = var_call->getVarType();
    if (type == "ARRAY_CALL")
    {
        return callArray((ArrayCall *)var_call);
    }
    else
    {
        if (table->getScopeIdOfSymbol(var_name) == 1)
        {
            print("PUSH " + var_name);
        }
        else
        {
            print("PUSH [BP + " + to_string(var->getOffset()) + "]");
        }
    }
}
void AssemblyGenerator::callArray(ArrayCall *arr_call)
{
    evaluateExpression(arr_call->getIndex());

    print("POP BX");
    print("SHL BX, 1");

    string arr_name = arr_call->getIdName();
    Array *arr = (Array *)table->find(arr_name);
    if (table->getScopeIdOfSymbol(arr_name) == 1)
    {
        print("MOV AX, " + arr_name + "[BX]");
    }
    else
    {
        // Offset is negative for local variables
        // index - (-offset)
        // BP - (index+offset)
        print("MOV SI, BX");
        print("SUB SI, " + std::to_string(arr->getOffset()));
        print("NEG SI");
        print("MOV AX, [BP+SI]");
    }

    print("PUSH AX");
}
void AssemblyGenerator::assignVariable(VariableCall *var_call)
{
    if (var_call->getVarType() == "ARRAY_CALL")
    {
        ArrayCall *arr_call = (ArrayCall *)var_call;
        evaluateExpression(arr_call->getIndex());
        print("POP BX");
        print("SHL BX, 1");
        print("PUSH BX");
    }
}
std::string AssemblyGenerator::newLabel()
{
    string lb = "L" + std::to_string(label_count);
    label_count++;
    return lb;
}