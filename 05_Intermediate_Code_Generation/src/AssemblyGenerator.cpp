#include <type_traits>
#include <typeinfo>
#include "../include/ExtendedSymbol.hpp"
#include "../include/Logger.hpp"
#include "../include/SemanticAnalyzer.hpp"
#include "../include/AssemblyGenerator.hpp"
#include "../include/Util.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
// #ifdef _WIN32
// #include <Windows.h>
// #else
// #include <unistd.h>
// #endif

std::map<std::string, std::string> AssemblyGenerator::RelOpASM = {
    {">", "JG"},
    {">=", "JGE"},
    {"<", "JL"},
    {"<=", "JLE"},
    {"!=", "JNE"},
    {"==", "JE"}};

extern AssemblyGenerator *asm_gen;

AssemblyGenerator::AssemblyGenerator(SymbolTable *table, std::ofstream &out) : asmout(out)
{
    this->table = table;
    indent = 0;
    label_count = 0;
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

    expr->getLeftOpr()->toAssembly();
    print("POP AX");

    print("CMP AX, 0");
    print("JNE " + left->getTrueLabel());
    print("JMP " + left->getFalseLabel()); // False

    printLabel(left->getTrueLabel());

    expr->getRightOpr()->toAssembly();
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

    expr->getLeftOpr()->toAssembly();
    print("POP AX");

    print("CMP AX, 0");
    print("JNE " + left->getTrueLabel());
    print("JMP " + left->getFalseLabel()); // False

    printLabel(left->getFalseLabel());

    expr->getRightOpr()->toAssembly();
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
    expr->getLeftOpr()->toAssembly();
    expr->getRightOpr()->toAssembly();

    string op = this->RelOpASM[expr->getOperator()];
    print("POP DX");
    print("POP AX");
    print("CMP AX, DX");

    print(op + " " + expr->getTrueLabel());
    print("JMP " + expr->getFalseLabel());
}
void AssemblyGenerator::evaluateNotOp(NotOp *expr)
{
    expr->getOperand()->toAssembly();
    print("POP AX");

    print("CMP AX, 0");
    print("JNE " + expr->getFalseLabel());
    print("JMP " + expr->getTrueLabel());
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

void AssemblyGenerator::assignVariable(VariableCall *var_call)
{
    if (var_call->getVarType() == "ARRAY_CALL")
    {
        ArrayCall *arr_call = (ArrayCall *)var_call;
        arr_call->getIndex()->toAssembly();
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

/**********************************************************************************/
/**********************************************************************************/
// Unit
void Program::toAssembly()
{
    asm_gen->print(".MODEL SMALL");
    asm_gen->print(".STACK 1000H");
    asm_gen->print(".DATA");
    asm_gen->indent++;
    asm_gen->print("CR EQU 0DH");
    asm_gen->print("LF EQU 0AH");
    asm_gen->print("number DB \"00000$\"");
    for (VariableDeclaration *var_dec : var_decs)
    {
        var_dec->toAssembly();
    }
    asm_gen->indent--;

    for (FunctionDeclaration *func_dec : func_decs)
    {
        func_dec->toAssembly();
    }

    asm_gen->print(".CODE");
    for (FunctionDefinition *func_def : func_defs)
    {
        func_def->toAssembly();
    }
    asm_gen->definePrintFunction();
    asm_gen->print("END MAIN");
}
void VariableDeclaration::toAssembly()
{
    asm_gen->comment(this->getCode());
    for (Variable *var : decl_list)
    {
        if (var->getVarType() == "ARRAY")
        {
            asm_gen->declareArray((Array *)var);
        }
        else
        {
            asm_gen->declareVariable(var);
        }
    }
}
void FunctionDeclaration::toAssembly()
{
    Function *new_func = new Function(func_name, ret_type);

    for (auto p : params)
    {
        new_func->addParam(new Variable(p->getIdName(), p->getDataType()));
    }

    if (!asm_gen->table->insert(new_func))
    {
    }
}
void FunctionDefinition::toAssembly()
{
    Function *new_func = new Function(func_name, ret_type);
    string ret_label = asm_gen->newLabel();
    this->setReturnLabel(ret_label);

    asm_gen->curr_func = this;

    for (auto p : params)
    {
        new_func->addParam(new Variable(p->getIdName(), p->getDataType()));
    }

    asm_gen->table->insert(new_func);
    asm_gen->print(func_name + " PROC");
    asm_gen->indent++;
    asm_gen->table->enterScope();

    if (func_name == "main")
    {
        asm_gen->print("MOV AX, @DATA");
        asm_gen->print("MOV DS, AX");
        asm_gen->print("PUSH BP");
        asm_gen->print("MOV BP, SP");
        asm_gen->offset_history.push_back(-2);
    }
    else
    {
        asm_gen->print("PUSH BP");
        asm_gen->print("MOV BP, SP");
        asm_gen->offset_history.push_back(-2);
    }

    asm_gen->declareFunctionParams(params);
    body->setNextLabel(ret_label);
    body->toAssembly();
    asm_gen->printLabel(ret_label);
    asm_gen->returnFunction();

    asm_gen->offset_history.pop_back();
    asm_gen->table->exitScope();
    asm_gen->indent--;
    asm_gen->print(func_name + " ENDP");
    asm_gen->curr_func = NULL;
}

// Expression
void ArrayCall::toAssembly()
{
    idx->toAssembly();
    asm_gen->print("POP BX");
    asm_gen->print("SHL BX, 1");
    Array *arr = (Array *)asm_gen->table->find(id_name);
    if (asm_gen->table->getScopeIdOfSymbol(id_name) == 1)
    {
        asm_gen->print("MOV AX, " + id_name + "[BX]");
    }
    else
    {
        // Offset is negative for local variables
        // index - (-offset)
        // BP - (index+offset)
        asm_gen->print("MOV SI, BX");
        asm_gen->print("SUB SI, " + std::to_string(arr->getOffset()));
        asm_gen->print("NEG SI");
        asm_gen->print("MOV AX, [BP+SI]");
    }

    asm_gen->print("PUSH AX");
}
void VariableCall::toAssembly()
{
    Variable *var = (Variable *)asm_gen->table->find(id_name);

    if (type == "ARRAY_CALL")
    {
        return this->toAssembly();
    }
    else
    {
        if (asm_gen->table->getScopeIdOfSymbol(id_name) == 1)
        {
            asm_gen->print("PUSH " + id_name);
        }
        else
        {
            asm_gen->print("PUSH [BP + " + to_string(var->getOffset()) + "]");
        }
    }
}
void ConstantCall::toAssembly()
{
    asm_gen->print("PUSH " + literal);
}
void DecOp::toAssembly()
{
    asm_gen->incdecOp((VariableCall *)this->getOperand(), "DEC");
}
void IncOp::toAssembly()
{
    asm_gen->incdecOp((VariableCall *)this->getOperand(), "INC");
}
void NotOp::toAssembly()
{
    operand->toAssembly();
    string true_label = asm_gen->newLabel();
    string end_label = asm_gen->newLabel();
    asm_gen->print("POP AX");
    asm_gen->print("CMP AX, 0");
    asm_gen->print("JE " + true_label);
    asm_gen->print("PUSH 0");
    asm_gen->print("JMP " + end_label);
    asm_gen->printLabel(true_label);
    asm_gen->print("PUSH 1");
    asm_gen->printLabel(end_label);
}
void UAddOp::toAssembly()
{
    operand->toAssembly();
    if (op_symbol == "-")
    {
        asm_gen->print("POP BX");
        asm_gen->print("NEG BX");
        asm_gen->print("PUSH BX");
    }
}
void RelOp::toAssembly()
{
    left_opr->toAssembly();
    right_opr->toAssembly();

    string true_label = asm_gen->newLabel();
    string end_label = asm_gen->newLabel();

    string op = asm_gen->RelOpASM[op_symbol];
    asm_gen->print("POP BX");
    asm_gen->print("POP AX");
    asm_gen->print("CMP AX, BX");
    asm_gen->print(op + " " + true_label);
    asm_gen->print("PUSH 0");
    asm_gen->print("JMP " + end_label);
    asm_gen->printLabel(true_label);
    asm_gen->print("PUSH 1");
    asm_gen->printLabel(end_label);
}
void AddOp::toAssembly()
{
    string opr = (op_symbol == "+" ? "ADD" : "SUB");

    // For constant and variable, MOV AX, [BP-4] MOV BX, 5
    left_opr->toAssembly();
    right_opr->toAssembly();
    asm_gen->print("POP BX");
    asm_gen->print("POP AX");

    asm_gen->print(opr + " AX, BX");
    asm_gen->print("PUSH AX");
}
void MulOp::toAssembly()
{
    left_opr->toAssembly();
    right_opr->toAssembly();

    string op = op_symbol;

    asm_gen->print("POP BX");
    asm_gen->print("POP AX");
    if (op == "*")
    {
        asm_gen->print("CWD");
        asm_gen->print("IMUL BX");
        asm_gen->print("PUSH AX");
    }
    else
    {
        asm_gen->print("CWD");
        asm_gen->print("IDIV BX");

        if (op == "%")
        {
            asm_gen->print("PUSH DX");
        }
        else
        {
            asm_gen->print("PUSH AX");
        }
    }
}
void LogicOp::toAssembly()
{
    left_opr->toAssembly();
    right_opr->toAssembly();

    std::string op = op_symbol;
    string false_label = asm_gen->newLabel();
    string true_label = asm_gen->newLabel();
    string end_label = asm_gen->newLabel();

    asm_gen->print("POP BX");
    asm_gen->print("POP AX");

    if (op == "&&")
    {
        asm_gen->print("CMP AX, 0");
        asm_gen->print("JE " + false_label);
        asm_gen->print("JE " + false_label);
        asm_gen->print("CMP BX, 0");
        asm_gen->print("PUSH 1");
        asm_gen->print("JMP " + end_label);
        asm_gen->printLabel(false_label);
        asm_gen->print("PUSH 0");
        asm_gen->printLabel(end_label);
    }
    else if (op == "||")
    {
        asm_gen->print("CMP AX, 0");
        asm_gen->print("JNE " + true_label);
        asm_gen->print("CMP BX, 0");
        asm_gen->print("JNE " + true_label);
        asm_gen->print("PUSH 0");
        asm_gen->print("JMP " + end_label);
        asm_gen->printLabel(true_label);
        asm_gen->print("PUSH 1");
        asm_gen->printLabel(end_label);
    }
}
void AssignOp::toAssembly()
{
    VariableCall *left_var = (VariableCall *)left_opr;
    asm_gen->assignVariable(left_var);
    right_opr->toAssembly();

    Variable *left = (Variable *)asm_gen->table->find(left_var->getIdName());
    asm_gen->print("POP AX");

    if (left->getVarType() == "ARRAY")
    {
        asm_gen->print("POP BX");
        if (asm_gen->table->getScopeIdOfSymbol(left->getIdName()) == 1)
        {
            asm_gen->print("MOV " + left->getIdName() + "[BX], AX");
        }
        else
        {
            string offset = std::to_string(left->getOffset());
            asm_gen->print("MOV SI, BX");
            asm_gen->print("SUB SI, " + offset);
            asm_gen->print("NEG SI");
            asm_gen->print("MOV [BP+SI], AX");
        }
    }
    else
    {
        if (asm_gen->table->getScopeIdOfSymbol(left->getIdName()) == 1)
        {
            asm_gen->print("MOV " + left->getIdName() + ", AX");
        }
        else
        {
            string offset = std::to_string(left->getOffset());
            asm_gen->print("MOV [BP + " + offset + "], AX");
        }
    }
    asm_gen->print("PUSH AX");
}

// Statement
void IfStatement::toAssembly()
{
    string true_label = asm_gen->newLabel();
    string false_label = this->getNextLabel();

    condition->setTrueLabel(true_label);
    condition->setFalseLabel(false_label);
    if_body->setNextLabel(this->getNextLabel());

    asm_gen->comment(condition->getCode());
    asm_gen->evaluateCondition(condition);
    asm_gen->printLabel(true_label);
    if_body->toAssembly();
}
void IfElseStatement::toAssembly()
{
    string true_label = asm_gen->newLabel();
    string false_label = asm_gen->newLabel();

    condition->setTrueLabel(true_label);
    condition->setFalseLabel(false_label);

    if_body->setNextLabel(this->getNextLabel());
    else_body->setNextLabel(this->getNextLabel());

    asm_gen->comment(condition->getCode());
    asm_gen->evaluateCondition(condition);
    asm_gen->printLabel(true_label);
    if_body->toAssembly();
    asm_gen->print("JMP " + this->getNextLabel());
    asm_gen->printLabel(false_label);
    else_body->toAssembly();
}
void ForLoop::toAssembly()
{
    std::string start_label = asm_gen->newLabel();
    std::string true_label = asm_gen->newLabel();
    std::string false_label = this->getNextLabel();
    std::string incdec_label = asm_gen->newLabel();

    condition->setTrueLabel(true_label);
    condition->setFalseLabel(false_label);
    body->setNextLabel(incdec_label);

    asm_gen->comment(initialize->getCode());
    initialize->toAssembly();
    asm_gen->printLabel(start_label);
    asm_gen->comment(condition->getCode());
    asm_gen->evaluateCondition(condition);
    asm_gen->printLabel(incdec_label);
    asm_gen->comment(inc_dec->getCode());
    inc_dec->toAssembly();
    asm_gen->print("JMP " + start_label);
    asm_gen->printLabel(true_label);
    body->toAssembly();
    asm_gen->print("JMP " + incdec_label);
}
void WhileLoop::toAssembly()
{
    std::string start_label = asm_gen->newLabel();
    std::string true_label = asm_gen->newLabel();
    std::string false_label = this->getNextLabel();

    condition->setTrueLabel(true_label);
    condition->setFalseLabel(false_label);
    body->setNextLabel(start_label);

    asm_gen->printLabel(start_label);
    asm_gen->comment(condition->getCode());
    asm_gen->evaluateCondition(condition);
    asm_gen->printLabel(true_label);
    body->toAssembly();
    asm_gen->print("JMP " + start_label);
}
void PrintStatement::toAssembly()
{
    asm_gen->comment(this->getCode());
    this->getVariableCall()->toAssembly();
    asm_gen->print("POP AX");
    asm_gen->print("CALL print_output");
    asm_gen->print("CALL new_line");
}
void ReturnStatement::toAssembly()
{
    asm_gen->comment(this->getCode());
    expr->toAssembly();
    asm_gen->print("POP AX");
    if (asm_gen->curr_func->getReturnType() != "VOID" && asm_gen->curr_func->getFunctionName() != "main")
    {
        asm_gen->print("MOV [BP+" + std::to_string(2 * asm_gen->curr_func->getParams().size() + 4) + "], AX");
    }
    asm_gen->print("JMP " + asm_gen->curr_func->getReturnLabel());
}
void ExpressionStatement::toAssembly()
{
    asm_gen->comment(this->getCode());
    expr->toAssembly();
    asm_gen->print("POP AX");
}
void CompoundStatement::toAssembly()
{
    if (asm_gen->curr_func == NULL)
    {
        asm_gen->table->enterScope();
    }

    int count = 0;
    for (VariableDeclaration *var_dec : var_decs)
    {
        var_dec->toAssembly();
        count += var_dec->getDeclarationList().size();
    }

    string last_label = count > 0 ? asm_gen->newLabel() : "";
    for (int i = 0; i < stmt_list.size(); i++)
    {
        if (i < stmt_list.size() - 1)
        {
            if (last_label != "")
            {
                asm_gen->printLabel(last_label);
            }
            string label = asm_gen->newLabel();
            stmt_list[i]->setNextLabel(label);
            stmt_list[i]->toAssembly();
            last_label = label;
        }
        else
        {
            if (last_label != "")
            {
                asm_gen->printLabel(last_label);
            }
            stmt_list[i]->setNextLabel(this->getNextLabel());
            stmt_list[i]->toAssembly();
        }
    }
    if (count > 0)
    {
        asm_gen->print("ADD SP, " + std::to_string(2 * count));
    }

    if (asm_gen->curr_func == NULL)
    {
        asm_gen->table->enterScope();
    }
}
void FunctionCall::toAssembly()
{
    Function *func = (Function *)asm_gen->table->find(id_name);
    // Push reference for return type
    // Return type will be stored here
    if (func->getReturnType() != "VOID")
    {
        asm_gen->print("SUB SP, 2");
    }
    asm_gen->comment(this->getCode());
    for (Expression *e : args)
    {
        e->toAssembly();
    }
    asm_gen->print("CALL " + id_name);
}
