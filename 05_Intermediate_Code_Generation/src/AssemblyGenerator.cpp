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
    definePrintFunction();
    for (FunctionDefinition *func_def : func_defs)
    {
        defineFunction(func_def);
    }
    print("END MAIN");
}
void AssemblyGenerator::declareVariables(VariableDeclaration *var_decl)
{
    // Keep track of how many(size) local variables are created in local scope, and ADD SP, size on exiting scope
    // Is it applicable for compound statements?
    vector<Variable *> vars = var_decl->getDeclarationList();
    comment(var_decl->getCode());
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
        print("SUB SP, 2");
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
        int sz = stoi(arr_size) * 2;
        print("SUB SP, " + to_string(sz));
        new_arr->setOffset(offset_history.back());
        offset_history.back() -= sz; // Stack decrease downward
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
    // print("ADD SP, " + std::to_string(2 * curr_func->getBody()->getDeclarationList().size()));
    print("MOV SP, BP");
    print("POP BP");
    if (curr_func->getFunctionName() != "main")
    {
        print("RET " + std::to_string(2 * curr_func->getParams().size()));
    }
    else
    {
        print("MOV AX, 4CH");
        print("INT 21H");
    }
}
void AssemblyGenerator::analyzePrintStatement(PrintStatement *print_stmt)
{
    comment(print_stmt->getCode());
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
    CompoundStatement *body = func_def->getBody();
    vector<Statement *> stmt_list = body->getStatements();
    vector<VariableDeclaration *> var_decs = body->getVariableDeclarations();

    Function *new_func = new Function(func_name, ret_type);

    string ret_label = newLabel();
    func_def->setReturnLabel(ret_label);

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
        print("PUSH BP");
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

    body->setNextLabel(ret_label);
    analyzeCompoundStatement(body);
    printLabel(ret_label);
    returnFunction();

    offset_history.pop_back();
    table->exitScope();
    indent--;

    print(func_name + " ENDP");

    curr_func = NULL;
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
void AssemblyGenerator::printLabel(const string &label)
{
    asmout << label << ":" << std::endl;
}
void AssemblyGenerator::comment(const string &msg)
{
    string *lines = Util::split(msg, '\n');
    int count = Util::countTokens(msg, '\n');
    for (int i = 0; i < count; i++)
    {
        for (int j = 1; j <= indent; j++)
        {
            asmout << "\t";
        }
        asmout << "; " << lines[i] << std::endl;
    }
}

void AssemblyGenerator::comment(const string &msg, int line)
{
    comment("Line no: " + to_string(line) + " => " + msg);
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
        print("POP AX");
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
    comment(expr_stmt->getCode());
    evaluateExpression(expr_stmt->getExpression());
}
void AssemblyGenerator::analyzeCompoundStatement(CompoundStatement *compound)
{
    vector<Statement *> stmt_list = compound->getStatements();
    vector<VariableDeclaration *> var_decs = compound->getVariableDeclarations();

    int count = 0;
    for (VariableDeclaration *var_dec : var_decs)
    {
        declareVariables(var_dec);
        count += var_dec->getDeclarationList().size();
    }

    string last_label = "";
    for (int i = 0; i < stmt_list.size(); i++)
    {
        if (i < stmt_list.size() - 1)
        {
            if (last_label != "")
            {
                printLabel(last_label);
            }
            string label = newLabel();
            stmt_list[i]->setNextLabel(label);
            analyzeStatement(stmt_list[i]);
            last_label = label;
        }
        else
        {
            if (last_label != "")
            {
                printLabel(last_label);
            }
            stmt_list[i]->setNextLabel(compound->getNextLabel());
            analyzeStatement(stmt_list[i]);
        }
    }
    print("ADD SP, " + std::to_string(2 * count));
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
        else if (type == "BINARY_EXPRESSION" || type == "BINARY_BOOLEAN")
        {
            evaluateBinaryExpression(dynamic_cast<BinaryExpression *>(expr));
        }
        else if (type == "UNARY_EXPRESSION" || type == "UNARY_BOOLEAN")
        {
            evaluateUnaryExpression(dynamic_cast<UnaryExpression *>(expr));
        }
    }
}

void AssemblyGenerator::evaluateCondition(BooleanExpression *expr)
{
    if (expr != NULL)
    {
        string type = expr->getBoolType();
        if (type == "LOGICOP")
        {
            evaluateLogicOp(dynamic_cast<LogicOp *>(expr));
        }
        else if (type == "RELOP")
        {
            evaluateRelOp(dynamic_cast<RelOp *>(expr));
        }
        else if (type == "NOTOP")
        {
            evaluateNotOp(dynamic_cast<NotOp *>(expr));
        }
    }
}

void AssemblyGenerator::evaluateAndOp(LogicOp *expr)
{
    BooleanExpression *left = dynamic_cast<BooleanExpression *>(expr->getLeftOpr());
    BooleanExpression *right = dynamic_cast<BooleanExpression *>(expr->getRightOpr());
    left->setTrueLabel(newLabel());
    left->setFalseLabel(expr->getFalseLabel());
    right->setTrueLabel(expr->getTrueLabel());
    right->setFalseLabel(expr->getFalseLabel());

    evaluateExpression(expr->getLeftOpr());
    print("POP AX");

    print("CMP AX, 0");
    print("JNE " + left->getTrueLabel());
    print("JMP " + left->getFalseLabel()); // False

    printLabel(left->getTrueLabel());

    evaluateExpression(expr->getRightOpr());
    print("POP AX");

    print("CMP AX, 0");
    print("JNE " + right->getTrueLabel());  // True
    print("JMP " + right->getFalseLabel()); // False
}

void AssemblyGenerator::evaluateOrOp(LogicOp *expr)
{
    BooleanExpression *left = dynamic_cast<BooleanExpression *>(expr->getLeftOpr());
    BooleanExpression *right = dynamic_cast<BooleanExpression *>(expr->getRightOpr());

    left->setTrueLabel(expr->getTrueLabel());
    left->setFalseLabel(newLabel());
    right->setTrueLabel(expr->getTrueLabel());
    right->setFalseLabel(expr->getFalseLabel());

    evaluateExpression(expr->getLeftOpr());
    print("POP AX");

    print("CMP AX, 0");
    print("JNE " + left->getTrueLabel());
    print("JMP " + left->getFalseLabel()); // False

    printLabel(left->getFalseLabel());

    evaluateExpression(expr->getRightOpr());
    print("POP AX");

    print("CMP AX, 0");
    print("JNE " + right->getTrueLabel());  // True
    print("JMP " + right->getFalseLabel()); // False
}
void AssemblyGenerator::evaluateLogicOp(LogicOp *expr)
{
    std::string op = expr->getOperator();

    if (op == "&&")
    {
        evaluateAndOp(expr);
    }
    else if (op == "||")
    {
        evaluateOrOp(expr);
    }
}
void AssemblyGenerator::evaluateRelOp(RelOp *expr)
{
    evaluateExpression(expr->getLeftOpr());
    evaluateExpression(expr->getRightOpr());

    string op = getRelOpASM(expr->getOperator());
    print("POP DX");
    print("POP AX");
    print("CMP AX, DX");

    print(op + " " + expr->getTrueLabel());
    print("JMP " + expr->getFalseLabel());
}
void AssemblyGenerator::evaluateNotOp(NotOp *expr)
{
    evaluateExpression(expr->getOperand());
    print("POP AX");

    print("CMP AX, 0");
    print("JNE " + expr->getFalseLabel());
    print("JMP " + expr->getTrueLabel());
}

void AssemblyGenerator::evaluateBinaryExpression(BinaryExpression *bin_expr)
{
    string type = bin_expr->getOpType();
    if (type == "ASSIGNOP")
    {
        assignOp((AssignOp *)bin_expr);
    }
    else if (type == "ADDOP")
    {
        addOp((AddOp *)bin_expr);
    }
    else if (type == "MULOP")
    {
        mulOp((MulOp *)bin_expr);
    }
    else if (type == "RELOP")
    {
        relOp((RelOp *)bin_expr);
    }
    else if (type == "LOGICOP")
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
    string true_label = newLabel();
    string false_label = if_stmt->getNextLabel();

    BooleanExpression *cond = dynamic_cast<BooleanExpression *>(if_stmt->getCondition());
    cond->setTrueLabel(true_label);
    cond->setFalseLabel(false_label);

    Statement *if_body = if_stmt->getIfBody();
    if_body->setNextLabel(if_stmt->getNextLabel());

    comment(if_stmt->getCondition()->getCode());

    evaluateCondition(cond);
    printLabel(true_label);
    analyzeStatement(if_body);
}
void AssemblyGenerator::analyzeIfElseStatement(IfElseStatement *ifelse_stmt)
{
    string true_label = newLabel();
    string false_label = newLabel();

    BooleanExpression *cond = dynamic_cast<BooleanExpression *>(ifelse_stmt->getCondition());
    cond->setTrueLabel(true_label);
    cond->setFalseLabel(false_label);

    Statement *if_body = ifelse_stmt->getIfBody();
    if_body->setNextLabel(ifelse_stmt->getNextLabel());

    Statement *else_body = ifelse_stmt->getElseBody();
    else_body->setNextLabel(ifelse_stmt->getNextLabel());

    comment(ifelse_stmt->getCondition()->getCode());

    evaluateCondition(cond);
    printLabel(true_label);
    analyzeStatement(if_body);
    print("JMP " + ifelse_stmt->getNextLabel());
    printLabel(false_label);
    analyzeStatement(else_body);
}

// analyzeBooleanExpression - LogicOp, RelOp, NotOp
void AssemblyGenerator::analyzeForLoop(ForLoop *for_loop)
{
    std::string start_label = newLabel();
    std::string true_label = newLabel();
    std::string false_label = for_loop->getNextLabel();
    std::string incdec_label = newLabel();

    BooleanExpression *cond = dynamic_cast<BooleanExpression *>(for_loop->getCondition());
    cond->setTrueLabel(true_label);
    cond->setFalseLabel(false_label);

    Statement *body = for_loop->getBody();
    body->setNextLabel(incdec_label);

    Expression *incdec = for_loop->getIncDec();

    comment(for_loop->getInitialize()->getCode());
    evaluateExpression(for_loop->getInitialize());

    printLabel(start_label);
    comment(for_loop->getCondition()->getCode());
    evaluateCondition(cond);

    printLabel(incdec_label);
    comment(for_loop->getIncDec()->getCode());
    evaluateExpression(incdec);
    print("JMP " + start_label);

    printLabel(true_label);
    analyzeStatement(body);
    print("JMP " + incdec_label);
}
void AssemblyGenerator::analyzeWhileLoop(WhileLoop *while_loop)
{
    std::string start_label = newLabel();
    std::string true_label = newLabel();
    std::string false_label = while_loop->getNextLabel();

    BooleanExpression *cond = dynamic_cast<BooleanExpression *>(while_loop->getCondition());
    cond->setTrueLabel(true_label);
    cond->setFalseLabel(false_label);

    Statement *body = while_loop->getBody();
    body->setNextLabel(start_label);

    printLabel(start_label);
    comment(while_loop->getCondition()->getCode());
    evaluateCondition(cond);
    printLabel(true_label);
    analyzeStatement(body);
    print("JMP " + start_label);
}
void AssemblyGenerator::analyzeReturnStatement(ReturnStatement *ret_stmt)
{
    Expression *ret_expr = ret_stmt->getExpression();
    comment(ret_stmt->getCode());
    evaluateExpression(ret_expr);
    print("POP AX");
    if (curr_func->getReturnType() != "VOID" && curr_func->getFunctionName() != "main")
    {
        print("MOV [BP+" + std::to_string(2 * curr_func->getParams().size() + 4) + "], AX");
    }
    print("JMP " + curr_func->getReturnLabel());
}
void AssemblyGenerator::evaluateCallExpression(CallExpression *call_expr)
{
    // MOV AX, constant/variable
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

    Function *func = (Function *)table->find(func_name);
    // Push reference for return type
    // Return type will be stored here
    if (func->getReturnType() != "VOID")
    {
        print("SUB SP, 2");
    }

    comment(func_call->getCode());
    for (Expression *e : args)
    {
        evaluateExpression(e);
    }
    print("CALL " + func_name);
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

    string true_label = newLabel();
    string end_label = newLabel();
    print("POP AX");
    print("CMP AX, 0");
    print("JE " + true_label);
    print("PUSH 0");
    print("JMP " + end_label);
    printLabel(true_label);
    print("PUSH 1");
    printLabel(end_label);
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

// If right side of assignment is boolean expression
// E -> V = E
// E -> V = B ->

// Assign AX to left variable
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
    print("PUSH AX");
}
void AssemblyGenerator::logicOp(LogicOp *expr)
{
    evaluateExpression(expr->getLeftOpr());
    evaluateExpression(expr->getRightOpr());

    std::string op = expr->getOperator();
    string false_label = newLabel();
    string true_label = newLabel();
    string end_label = newLabel();

    print("POP BX");
    print("POP AX");

    if (op == "&&")
    {
        print("CMP AX, 0");
        print("JE " + false_label);
        print("CMP BX, 0");
        print("JE " + false_label);
        print("PUSH 1");
        print("JMP " + end_label);
        printLabel(false_label);
        print("PUSH 0");
        printLabel(end_label);
    }
    else if (op == "||")
    {
        print("CMP AX, 0");
        print("JNE " + true_label);
        print("CMP BX, 0");
        print("JNE " + true_label);
        print("PUSH 0");
        print("JMP " + end_label);
        printLabel(true_label);
        print("PUSH 1");
        printLabel(end_label);
    }
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

// Short circuit:
// Condition in if,while,for
// Relop - Both operand need to be evaluated
// LogicOp - At least one operand need to be evaluated
// So boolean expression will be stored in AX
// Constant, Variable, Array, Boolean expression(LogicOp, RelOp, NotOp) will be stored in AX
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
    printLabel(true_label);
    print("PUSH 1");
    printLabel(end_label);
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
    label_count++;
    string lb = "L" + std::to_string(label_count);
    return lb;
}

bool AssemblyGenerator::isBooleanExpression(Expression *expr)
{
    if (expr != NULL)
    {
        string type = expr->getExpType();
        if (type == "BINARY_EXPRESSION")
        {
            BinaryExpression *bin_expr = dynamic_cast<BinaryExpression *>(expr);
            string type = bin_expr->getOpType();
            if (type == "RELOP")
            {
                return true;
            }
            if (type == "LOGICOP")
            {
                return true;
            }
        }
        if (type == "UNARY_EXPRESSION")
        {
            evaluateUnaryExpression(dynamic_cast<UnaryExpression *>(expr));
        }
    }
    return false;
}
// If left operand is call expression, evaluate right first. Evaluation result based on right operand.

// If left operand is not call expression, evaluate left first. Evaluation result will be stored in stack top.

// If right operand is evaluated first.
// If right operand is call expression, result is stored in AX
// If not result is stored in stack top

// In case of ADD, SUB always MOV AX, DX after right operand evaluation

// In case of MUL, DIV - MOV CX, AX