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

extern AssemblyGenerator *asm_gen;
std::map<std::string, std::string> AssemblyGenerator::RelOpASM = {
    {">", "JG"},
    {">=", "JGE"},
    {"<", "JL"},
    {"<=", "JLE"},
    {"!=", "JNE"},
    {"==", "JE"}};

AssemblyGenerator::AssemblyGenerator(std::ofstream &out) : asmout(out)
{
    indent = 0;
    label_count = 0;
}

void AssemblyGenerator::declareVariable(Variable *var)
{
    if (var->isGlobal())
    {
        print(var->getUniqueName() + " DW (0000H)");
    }
    else
    {
        print("SUB SP, 2");
        var->setOffset(offset_history);
        offset_history -= 2;
    }
}
void AssemblyGenerator::declareArray(Array *arr)
{
    string arr_size = arr->getArraySize();

    if (arr->isGlobal())
    {
        print(arr->getUniqueName() + " DW " + arr_size + " DUP(0000H)");
    }
    else
    {
        int sz = stoi(arr_size) * 2;
        print("SUB SP, " + to_string(sz));
        arr->setOffset(offset_history);
        offset_history -= sz; // Stack decrease downward
    }
}
void AssemblyGenerator::declareFunctionParams(vector<Variable *> params)
{
    std::reverse(params.begin(), params.end());
    int offset = 4;
    for (auto p : params)
    {
        p->setOffset(offset);
        offset += 2;
    }
}
void AssemblyGenerator::returnFunction()
{
    // print("ADD SP, " + std::to_string(-asm_gen->offset_history - 2));
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

void AssemblyGenerator::jumpBoolean(BooleanExpression *expr)
{
    if (expr != NULL)
    {
        string type = expr->getBoolType();
        if (type == "LOGICOP")
        {
            jumpLogicOp(dynamic_cast<LogicOp *>(expr));
        }
        else if (type == "RELOP")
        {
            jumpRelOp(dynamic_cast<RelOp *>(expr));
        }
        else if (type == "NOTOP")
        {
            jumpNotOp(dynamic_cast<NotOp *>(expr));
        }
    }
}

void AssemblyGenerator::jumpLogicOp(LogicOp *expr)
{
    std::string op = expr->getOperator();

    if (op == "&&")
    {
        jumpAndOp(expr);
    }
    else if (op == "||")
    {
        jumpOrOp(expr);
    }
}

void AssemblyGenerator::jumpAndOp(LogicOp *expr)
{
    BooleanExpression *left = dynamic_cast<BooleanExpression *>(expr->getLeftOpr());
    BooleanExpression *right = dynamic_cast<BooleanExpression *>(expr->getRightOpr());

    left->setTrueLabel(newLabel());
    left->setFalseLabel(expr->getFalseLabel());
    right->setTrueLabel(expr->getTrueLabel());
    right->setFalseLabel(expr->getFalseLabel());

    jumpBoolean(left);
    printLabel(left->getTrueLabel());
    jumpBoolean(right);
}

void AssemblyGenerator::jumpOrOp(LogicOp *expr)
{
    BooleanExpression *left = dynamic_cast<BooleanExpression *>(expr->getLeftOpr());
    BooleanExpression *right = dynamic_cast<BooleanExpression *>(expr->getRightOpr());

    left->setTrueLabel(expr->getTrueLabel());
    left->setFalseLabel(newLabel());
    right->setTrueLabel(expr->getTrueLabel());
    right->setFalseLabel(expr->getFalseLabel());

    jumpBoolean(left);
    printLabel(left->getFalseLabel());
    jumpBoolean(right);
}

void AssemblyGenerator::jumpNotOp(NotOp *expr)
{
    BooleanExpression *right = dynamic_cast<BooleanExpression *>(expr->getOperand());

    right->setTrueLabel(expr->getFalseLabel());
    right->setFalseLabel(expr->getTrueLabel());

    jumpBoolean(right);
}

void AssemblyGenerator::jumpRelOp(RelOp *expr)
{
    expr->getLeftOpr()->toAssembly();
    expr->getRightOpr()->toAssembly();

    string op = this->RelOpASM[expr->getOperator()];
    // print("POP DX");
    // print("POP AX");
    asm_gen->assignRegister(expr->getRightOpr(), "DX");
    asm_gen->assignRegister(expr->getLeftOpr(), "AX");
    print("CMP AX, DX");

    print(op + " " + expr->getTrueLabel());
    print("JMP " + expr->getFalseLabel());
}

string getOffset(int offset)
{
    string off = to_string(offset);
    if (off.front() != '-')
    {
        off = "+" + off;
    }
    return off;
}
void AssemblyGenerator::incdecOp(VariableCall *var_call, std::string op)
{
    assignVariable(var_call);
    Variable *var = (Variable *)var_call->getIdentifier();
    if (var->getVarType() == "ARRAY")
    {
        print("POP BX");
        if (var->isGlobal())
        {
            print("PUSH " + var->getUniqueName() + "[BX]");  // Pushing previous value to stack
            print(op + " " + var->getUniqueName() + "[BX]"); // Increment the value
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
        if (var->isGlobal())
        {
            print("PUSH " + var->getUniqueName());
            print(op + " " + var->getUniqueName());
        }
        else
        {
            string offset = getOffset(var->getOffset());
            print("PUSH [BP" + offset + "]");
            print(op + " WORD PTR [BP" + offset + "]");
        }
    }
}

void AssemblyGenerator::assignVariable(VariableCall *var_call)
{
    if (var_call->getVarType() == "ARRAY_CALL")
    {
        ArrayCall *arr_call = (ArrayCall *)var_call;
        arr_call->getIndex()->toAssembly();
        assignRegister(arr_call->getIndex(), "BX");
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

    // for (FunctionDeclaration *func_dec : func_decs)
    // {
    //     func_dec->toAssembly();
    // }

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
    asm_gen->comment(this->getCode(), this->start_line);
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
}
void FunctionDefinition::toAssembly()
{
    string ret_label = asm_gen->newLabel();
    this->setReturnLabel(ret_label);

    asm_gen->curr_func = this;
    asm_gen->print((func_name == "main" ? func_name : func->getUniqueName()) + " PROC");
    asm_gen->indent++;

    if (func_name == "main")
    {
        asm_gen->print("MOV AX, @DATA");
        asm_gen->print("MOV DS, AX");
        asm_gen->print("PUSH BP");
        asm_gen->print("MOV BP, SP");
        asm_gen->offset_history = -2;
    }
    else
    {
        asm_gen->print("PUSH BP");
        asm_gen->print("MOV BP, SP");
        asm_gen->offset_history = -2;
    }

    asm_gen->declareFunctionParams(params);
    body->setNextLabel(ret_label);
    body->toAssembly();
    asm_gen->printLabel(ret_label);
    asm_gen->returnFunction();

    asm_gen->offset_history = 0;
    asm_gen->indent--;
    asm_gen->print((func_name == "main" ? func_name : func->getUniqueName()) + " ENDP");
    asm_gen->curr_func = NULL;
}

// Expression
void ArrayCall::toAssembly()
{
    asm_gen->comment(this->getCode());
    idx->toAssembly();
    asm_gen->assignRegister(idx, "BX");
    asm_gen->print("SHL BX, 1");
    Array *arr = (Array *)id;
    if (arr->isGlobal())
    {
        asm_gen->print("MOV AX, " + this->id->getUniqueName() + "[BX]");
    }
    else
    {
        // Offset is negative for local variables
        // index - (-offset)
        // BP - (index+offset)
        string offset = std::to_string(arr->getOffset());
        asm_gen->print("MOV SI, BX");
        asm_gen->print("SUB SI, " + offset);
        asm_gen->print("NEG SI");
        asm_gen->print("MOV AX, [BP+SI]");
    }

    asm_gen->print("PUSH AX");
}
string getVariable(VariableCall *var_call)
{
    Variable *var = (Variable *)var_call->getIdentifier();

    if (var->isGlobal())
    {
        return var_call->getIdentifier()->getUniqueName();
    }
    else
    {
        return "[BP" + getOffset(var->getOffset()) + "]";
    }
}
void VariableCall::toAssembly()
{
    Variable *var = (Variable *)id;

    if (type == "ARRAY_CALL")
    {
        return this->toAssembly();
    }
    else
    {
        /*
        if (var->isGlobal())
        {
            asm_gen->print("PUSH " + id_name);
        }
        else
        {
            asm_gen->print("PUSH [BP" + getOffset(var->getOffset()) + "]");
        }
        */
    }
}
string DecToHex(string dec)
{
    int decimal_value = stoi(dec);
    stringstream ss;
    ss << hex << decimal_value << 'h';
    string res(ss.str());
    return res;
}
void ConstantCall::toAssembly()
{
    // asm_gen->print("MOV AX, " + literal);
    // asm_gen->print("PUSH AX");
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
    // asm_gen->print("POP AX");
    asm_gen->assignRegister(operand, "AX");
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
        // asm_gen->print("POP AX");
        asm_gen->assignRegister(operand, "AX");
        asm_gen->print("NEG AX");
        asm_gen->print("PUSH AX");
    }
}
void RelOp::toAssembly()
{
    left_opr->toAssembly();
    right_opr->toAssembly();

    string true_label = asm_gen->newLabel();
    string end_label = asm_gen->newLabel();

    string op = asm_gen->RelOpASM[op_symbol];
    // asm_gen->print("POP DX");
    // asm_gen->print("POP AX");
    asm_gen->assignRegister(right_opr, "DX");
    asm_gen->assignRegister(left_opr, "AX");
    asm_gen->print("CMP AX, DX");
    asm_gen->print(op + " " + true_label);
    asm_gen->print("PUSH 0");
    asm_gen->print("JMP " + end_label);
    asm_gen->printLabel(true_label);
    asm_gen->print("PUSH 1");
    asm_gen->printLabel(end_label);
}

void AssemblyGenerator::assignRegister(Expression *expr, string dst_reg)
{
    if (expr->getExpType() == "CALL_EXPRESSION")
    {
        CallExpression *call_expr = dynamic_cast<CallExpression *>(expr);
        if (call_expr->getCallType() == "CONSTANT_CALL")
        {
            ConstantCall *const_call = dynamic_cast<ConstantCall *>(call_expr);
            asm_gen->print("MOV " + dst_reg + ", " + const_call->getLiteral());
            return;
        }
        else if (call_expr->getCallType() == "IDENTIFIER_CALL")
        {
            IdentifierCall *id_call = dynamic_cast<IdentifierCall *>(call_expr);
            if (id_call->getIdentity() == "VARIABLE_CALL")
            {
                VariableCall *var_call = dynamic_cast<VariableCall *>(id_call);
                if (var_call->getVarType() == "PRIMITIVE_CALL")
                {
                    asm_gen->print("MOV " + dst_reg + ", " + getVariable(var_call));
                    return;
                }
            }
        }
    }
    asm_gen->print("POP " + dst_reg);
}
void AddOp::toAssembly()
{
    if (Expression::isVariableCall(this->getLeftOpr()) && Expression::isVariableCall(this->getRightOpr()) && this->getOperator() == "-")
    {
        if (Expression::getVariable(dynamic_cast<VariableCall *>(this->getLeftOpr())) == Expression::getVariable(dynamic_cast<VariableCall *>(this->getRightOpr())))
        {
            this->setLeftOpr(new ConstantCall("0", "INT"));
            this->setRightOpr(new ConstantCall("0", "INT"));
        }
    }
    string opr = (op_symbol == "+" ? "ADD" : "SUB");

    left_opr->toAssembly();
    if (Expression::isConstant(right_opr) && Expression::getConstant(right_opr) == 0)
    {
        asm_gen->comment("Skipping " + op_symbol + ", since right operand is 0");
        asm_gen->pushExpression(left_opr);
        return;
    }

    right_opr->toAssembly();

    asm_gen->assignRegister(right_opr, "DX");
    asm_gen->assignRegister(left_opr, "AX");
    // asm_gen->print("POP DX");
    // asm_gen->print("POP AX");
    asm_gen->print(opr + " AX, DX");
    asm_gen->print("PUSH AX");
}

bool AssemblyGenerator::isZero(Expression *expr)
{
    if (expr->getExpType() == "CALL_EXPRESSION")
    {
        CallExpression *call_expr = dynamic_cast<CallExpression *>(expr);
        if (call_expr->getCallType() == "CONSTANT_CALL")
        {
            ConstantCall *const_call = dynamic_cast<ConstantCall *>(call_expr);
            return const_call->getLiteral() == "0";
        }
    }
    return false;
}
bool AssemblyGenerator::isOne(Expression *expr)
{
    if (expr->getExpType() == "CALL_EXPRESSION")
    {
        CallExpression *call_expr = dynamic_cast<CallExpression *>(expr);
        if (call_expr->getCallType() == "CONSTANT_CALL")
        {
            ConstantCall *const_call = dynamic_cast<ConstantCall *>(call_expr);
            return const_call->getLiteral() == "1";
        }
    }
    return false;
}
bool AssemblyGenerator::isConstant(Expression *expr)
{
    if (expr->getExpType() == "CALL_EXPRESSION")
    {
        CallExpression *call_expr = dynamic_cast<CallExpression *>(expr);
        if (call_expr->getCallType() == "CONSTANT_CALL")
        {
            return true;
        }
    }
    return false;
}

string AssemblyGenerator::getConstant(Expression *expr)
{
    ConstantCall *const_call = dynamic_cast<ConstantCall *>(expr);
    return const_call->getLiteral();
}

void AssemblyGenerator::pushExpression(Expression *expr)
{
    if (asm_gen->isConstant(expr))
    {
        asm_gen->print("MOV AX, " + asm_gen->getConstant(expr));
        asm_gen->print("PUSH AX");
    }
    else if (expr->getExpType() == "CALL_EXPRESSION")
    {
        CallExpression *call_expr = dynamic_cast<CallExpression *>(expr);

        IdentifierCall *id_call = dynamic_cast<IdentifierCall *>(call_expr);
        if (id_call->getIdentity() == "VARIABLE_CALL")
        {
            VariableCall *var_call = dynamic_cast<VariableCall *>(id_call);
            if (var_call->getVarType() == "PRIMITIVE_CALL")
            {
                asm_gen->print("PUSH " + getVariable(var_call));
                return;
            }
        }
    }
}

void MulOp::toAssembly()
{
    if (Expression::isVariableCall(this->getLeftOpr()) && Expression::isVariableCall(this->getRightOpr()))
    {
        if (Expression::getVariable(dynamic_cast<VariableCall *>(this->getLeftOpr())) == Expression::getVariable(dynamic_cast<VariableCall *>(this->getRightOpr())))
        {
            if (this->getOperator() == "/")
            {
                this->setLeftOpr(new ConstantCall("1", "INT"));
                this->setRightOpr(new ConstantCall("1", "INT"));
            }
            else if (this->getOperator() == "%")
            {
                this->setLeftOpr(new ConstantCall("0", "INT"));
                this->setRightOpr(new ConstantCall("0", "INT"));
                this->setOperator("*");
            }
        }
    }
    string op = op_symbol;

    if (Expression::isConstant(right_opr) && Expression::getConstant(right_opr) == 0)
    {
        asm_gen->comment("Skipping " + op + ", since right operand is 0");
        asm_gen->print("PUSH 0");
        return;
    }
    left_opr->toAssembly();

    if (asm_gen->isOne(right_opr) && (op == "*" || op == "/"))
    {
        asm_gen->comment("Skipping " + op + ", since right operand is 1");
        asm_gen->pushExpression(left_opr);
        return;
    }
    if (asm_gen->isConstant(right_opr) && asm_gen->getConstant(right_opr) == "2")
    {
        (new AddOp(this->getLeftOpr(), this->getLeftOpr(), "+"))->toAssembly();
        return;
    }
    right_opr->toAssembly();
    asm_gen->assignRegister(right_opr, "CX");
    asm_gen->assignRegister(left_opr, "AX");
    // asm_gen->print("POP CX");
    // asm_gen->print("POP AX");
    if (op == "*")
    {
        asm_gen->print("CWD");
        asm_gen->print("IMUL CX");
        asm_gen->print("PUSH AX");
    }
    else
    {
        asm_gen->print("CWD");
        asm_gen->print("IDIV CX");

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

    std::string op = op_symbol;
    string false_label = asm_gen->newLabel();
    string true_label = asm_gen->newLabel();
    string end_label = asm_gen->newLabel();

    if (op == "&&")
    {
        left_opr->toAssembly();
        asm_gen->print("POP AX");
        asm_gen->print("CMP AX, 0");
        asm_gen->print("JE " + false_label);

        right_opr->toAssembly();
        asm_gen->print("POP AX");
        asm_gen->print("CMP AX, 0");
        asm_gen->print("JE " + false_label);

        asm_gen->print("PUSH 1");
        asm_gen->print("JMP " + end_label);
        asm_gen->printLabel(false_label);
        asm_gen->print("PUSH 0");
        asm_gen->printLabel(end_label);
    }
    else if (op == "||")
    {
        left_opr->toAssembly();
        asm_gen->print("POP AX");
        asm_gen->print("CMP AX, 0");
        asm_gen->print("JNE " + true_label);

        right_opr->toAssembly();
        asm_gen->print("POP AX");
        asm_gen->print("CMP AX, 0");
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

    Variable *left = (Variable *)left_var->getIdentifier();
    // asm_gen->print("POP AX");
    asm_gen->assignRegister(right_opr, "AX");
    if (left->getVarType() == "ARRAY")
    {
        asm_gen->print("POP BX");
        if (left->isGlobal())
        {
            asm_gen->print("MOV " + left->getUniqueName() + "[BX], AX");
        }
        else
        {
            //
            string offset = std::to_string(left->getOffset());
            asm_gen->print("MOV SI, BX");
            asm_gen->print("SUB SI, " + offset);
            asm_gen->print("NEG SI");
            asm_gen->print("MOV [BP+SI], AX");
        }
    }
    else
    {
        if (left->isGlobal())
        {
            asm_gen->print("MOV " + left->getUniqueName() + ", AX");
        }
        else
        {
            string offset = getOffset(left->getOffset());
            asm_gen->print("MOV [BP" + offset + "], AX");
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

    asm_gen->comment("If Statement", this->start_line);
    asm_gen->comment(condition->getCode());
    asm_gen->jumpBoolean(condition);
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

    asm_gen->comment("If-Else Statement", this->start_line);
    asm_gen->comment(condition->getCode());
    asm_gen->jumpBoolean(condition);
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

    asm_gen->comment("For Loop", this->start_line);
    asm_gen->comment(initialize->getCode());
    initialize->toAssembly();
    asm_gen->printLabel(start_label);
    asm_gen->comment(condition->getCode());
    asm_gen->jumpBoolean(condition);
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

    asm_gen->comment("While Loop", this->start_line);
    asm_gen->printLabel(start_label);
    asm_gen->comment(condition->getCode());
    asm_gen->jumpBoolean(condition);
    asm_gen->printLabel(true_label);
    body->toAssembly();
    asm_gen->print("JMP " + start_label);
}
void PrintStatement::toAssembly()
{
    asm_gen->comment(this->getCode(), this->start_line);
    this->getVariableCall()->toAssembly();
    // asm_gen->print("POP AX");
    asm_gen->assignRegister(this->getVariableCall(), "AX");
    asm_gen->print("CALL print_output");
    asm_gen->print("CALL new_line");
}
void ReturnStatement::toAssembly()
{
    asm_gen->comment(this->getCode(), this->start_line);
    expr->toAssembly();
    asm_gen->assignRegister(this->getExpression(), "AX");
    if (asm_gen->curr_func->getReturnType() != "VOID" && asm_gen->curr_func->getFunctionName() != "main")
    {
        asm_gen->print("MOV [BP+" + std::to_string(2 * asm_gen->curr_func->getParams().size() + 4) + "], AX");
    }
    asm_gen->print("JMP " + asm_gen->curr_func->getReturnLabel());
}
void AssemblyGenerator::popExpression(Expression *expr)
{
    if (expr->getExpType() == "CALL_EXPRESSION")
    {
        CallExpression *call_expr = dynamic_cast<CallExpression *>(expr);
        if (call_expr->getCallType() == "CONSTANT_CALL")
        {
            ConstantCall *const_call = dynamic_cast<ConstantCall *>(call_expr);
            return;
        }
        else if (call_expr->getCallType() == "IDENTIFIER_CALL")
        {
            IdentifierCall *id_call = dynamic_cast<IdentifierCall *>(call_expr);
            if (id_call->getIdentity() == "VARIABLE_CALL")
            {
                VariableCall *var_call = dynamic_cast<VariableCall *>(id_call);
                if (var_call->getVarType() == "PRIMITIVE_CALL")
                {
                    return;
                }
            }
            else if (id_call->getIdentity() == "FUNCTION_CALL")
            {
                FunctionCall *func_call = dynamic_cast<FunctionCall *>(id_call);
                if (((Function *)func_call->getIdentifier())->getReturnType() == "VOID")
                {
                    return;
                }
            }
        }
    }
    asm_gen->print("POP AX");
}
void ExpressionStatement::toAssembly()
{
    asm_gen->comment(this->getCode(), this->start_line);
    expr->toAssembly();
    asm_gen->popExpression(this->expr);
}
void CompoundStatement::toAssembly()
{
    int allocated = 0;
    for (VariableDeclaration *var_dec : var_decs)
    {
        var_dec->toAssembly();
        for (Variable *var : var_dec->getDeclarationList())
        {
            if (var->getVarType() == "ARRAY")
            {
                allocated += 2 * stoi(((Array *)var)->getArraySize());
            }
            else
            {
                allocated += 2;
            }
        }
    }

    string last_label = allocated > 0 ? asm_gen->newLabel() : "";
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
        if (stmt_list[i]->getStatementType() == "RETURN_STATEMENT")
        {
            break;
        }
    }
    if (allocated > 0)
    {
        asm_gen->comment("Deallocating Variables");
        asm_gen->print("ADD SP, " + std::to_string(allocated));
        asm_gen->offset_history += allocated;
    }
}
void FunctionCall::toAssembly()
{
    // Push reference for return type
    // Return type will be stored here
    if (((Function *)id)->getReturnType() != "VOID")
    {
        asm_gen->print("SUB SP, 2");
    }
    asm_gen->comment(this->getCode());
    for (Expression *e : args)
    {
        e->toAssembly();
        asm_gen->pushExpression(e);
    }
    asm_gen->print("CALL " + this->getIdentifier()->getUniqueName());
}
