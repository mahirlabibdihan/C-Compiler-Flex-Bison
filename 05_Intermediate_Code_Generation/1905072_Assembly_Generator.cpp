#include "1905072_Assembly_Generator.h"
#include "1905072_SymbolTable.h"
#include "1905072_Comment_Generator.h"
#include <algorithm>
using namespace std;

extern SymbolTable *table;
extern int line_count;
extern int error_count;
extern ofstream codeout;

AssemblyGenerator::AssemblyGenerator(string file)
{
    this->outfile = file;
    // this->cmnt_gen = new CommentGenerator();
}
AssemblyGenerator::~AssemblyGenerator()
{
}

void AssemblyGenerator::addInDataSegment(string code)
{
    if (error_count == 0)
    {
        data_segment += code;
        writeInDataSegment();
    }
}

void AssemblyGenerator::addInCodeSegment(string code)
{
    if (error_count == 0)
    {
        if (!isForLoop)
        {
            code_segment += code;
            writeInCodeSegment(code);
        }
        else
        {
            forLoopIncDecCode += code;
        }
    }
}
void AssemblyGenerator::writeInDataSegment()
{
    codeout.close();
    codeout.open(outfile);
    codeout << header << endl;
    codeout << data_segment << endl;
    codeout << code_segment << endl;
}

void AssemblyGenerator::writeInCodeSegment(string code)
{
    codeout << code << endl;
}

void AssemblyGenerator::createFunctionScope(vector<Variable *> params)
{
    offset_history.push(offset);
    offset = 4;
    reverse(params.begin(), params.end());
    for (auto p : params)
    {
        setOffset(p, -1 * offset);
        offset += 2;
    }
    offset = 2;
}
void AssemblyGenerator::declareArray(Array *arr)
{
    if (table->getScopeIdOfSymbol(arr->getName()) == "1")
    {
        addInDataSegment(arr->getName() + " DW " + to_string(arr->getArraySize()) + " DUP(0) \n");
    }
    else
    {
        string code = "";
        // code += cmnt_gen->declareArray(arr);
        code += "\t\t; In line no " + to_string(line_count) + ": Array named " + arr->getName() + " with size " + to_string(arr->getArraySize()) + " declared";

        for (int i = 0; i < arr->getArraySize(); i++)
        {
            code += "\n\t\tPUSH BX";
        }
        code += "\n\t\t;array declared";
        setOffset(arr, offset);
        offset += arr->getArraySize() * 2;
        addInCodeSegment(code);
    }
}

void AssemblyGenerator::declareVariable(Variable *var)
{
    if (table->getScopeIdOfSymbol(var->getName()) == "1")
    {
        addInDataSegment("\t\t" + var->getName() + " DW ?\n");
    }
    else
    {
        string code = "";
        code += "\t\tPUSH BX ";
        // code += cmnt_gen->declareVariable(var);
        code += "\t; In line no " + to_string(line_count) + ": " + var->getName() + " declared";
        setOffset(var, offset);
        offset += 2;
        addInCodeSegment(code);
    }
}

void AssemblyGenerator::declareParam(Variable *var)
{
    // string code = ("\t\tPUSH BX\t; In line no " + to_string(line_count) + ": " + var->getName() + " declared");
    // // cout << offset << endl;
    // var->setOffset(offset);
    // offset += 2;
}
void AssemblyGenerator::startProcedure(Function *func)
{
    // cout << func->getName() << " " << error_count << endl;
    if (error_count > 0)
    {
        return;
    }
    string code = "";
    code += "\t" + func->getName() + " PROC\n";
    code += "\t\t; Function with name " + func->getName() + " started\n";
    if (func->getName() != "main")
    {
        code += "\t\tPUSH BP\n";
        code += "\t\tMOV BP, SP";
        code += "\t; All the offsets of a function depends on the value of BP\n";
    }
    addInCodeSegment(code);
    if (func->getName() == "main")
    {
        startMain();
    }
    curr_func = func;
}

void AssemblyGenerator::returnProcedure()
{
    if (error_count > 0)
    {
        return;
    }
    string code = "";
    code += "\t\tPOP AX";
    code += string("\t; Popped return value and saved it in AX") + "\n";

    code += "\n\n";

    code += "\t\tMOV SP, BP";
    code += "\t; Restoring SP at the end of function\n";

    code += "\t\tPOP BP";
    code += "\t; Restoring BP at the end of function\n";

    if (curr_func->getReturnType() == "void")
    {
        code += "\t\tRET 0\n";
    }
    else if (curr_func->getName() != "main")
    {
        code += "\t\tRET " + to_string(2 * curr_func->getNumberOfParams()) + "\n";
    }

    addInCodeSegment(code);
}

void AssemblyGenerator::endProcedure(string name)
{
    string code = "";

    if (curr_func->getReturnType() == "void")
    {
        returnProcedure();
    }

    if (name == "main")
    {
        code += "\t\t; Setting interrupt for function end\n";
        code += "\t\tMOV AH, 4CH\n";
        code += "\t\tINT 21H\n";
    }
    code += "\t" + name + " ENDP" + "\n";
    addInCodeSegment(code);
    curr_func = nullptr;
    offset = offset_history.top();
    offset_history.pop();
}

void AssemblyGenerator::writePrintFunc()
{
    string code = "";
    code = "\t;printf(n)\n";
    code +=
        "\tPRINT_NUM PROC NEAR\n\
        PUSH BP             ;Saving BP\n\
        MOV BP, SP          ;BP points to the top of the stack\n\
        MOV BX, [BP + 4]    ;The number to be printed\n\
        ;if(BX < -1) then the number is positive\n\
        CMP BX, 0\n\
        JGE POSITIVE\n\
        ;else, the number is negative\n\
        MOV AH, 2           \n\
        MOV DL, '-'         ;Print a '-' sign\n\
        INT 21H\n\
        NEG BX              ;make BX positive\n\
        POSITIVE:\n\
        MOV AX, BX\n\
        MOV CX, 0        ;Initialize character count\n\
        PUSH_WHILE:\n\
            XOR DX, DX  ;clear DX\n\
            MOV BX, 10  ;BX has the divisor //// AX has the dividend\n\
            DIV BX\n\
            ;quotient is in AX and remainder is in DX\n\
            PUSH DX     ;Division by 10 will have a remainder less than 8 bits\n\
            INC CX       ;CX++\n\
            ;if(AX == 0) then break the loop\n\
            CMP AX, 0\n\
            JE END_PUSH_WHILE\n\
            ;else continue\n\
            JMP PUSH_WHILE\n\
        END_PUSH_WHILE:\n\
        MOV AH, 2\n\
        POP_WHILE:\n\
            POP DX      ;Division by 10 will have a remaainder less than 8 bits\n\
            ADD DL, '0'\n\
            INT 21H     ;So DL will have the desired character\n\
            DEC CX       ;CX--\n\
            ;if(CX <= 0) then end loop\n\
            CMP CX, 0\n\
            JLE END_POP_WHILE\n\
            ;else continue\n\
            JMP POP_WHILE\n\
        END_POP_WHILE:\n\
        ;Print \n\
        MOV DL, 0DH\n\
        INT 21H\n\
        MOV DL, 0AH\n\
        INT 21H\n\
        POP BP          ; Restore BP\n\
        RET 2\n\
    PRINT_NUM ENDP";

    addInCodeSegment(code);
}

void AssemblyGenerator::startMain()
{
    string code = "";
    code += "\t\t; DATA SEGMENT INITIALIZATION\n";
    code += "\t\tMOV AX, @DATA\n";
    code += "\t\tMOV DS, AX\n";
    code += "\t\tMOV BP, SP";
    offset = 2;
    addInCodeSegment(code);
}

void AssemblyGenerator::startCode()
{
    header = header + ".MODEL SMALL" + "\n";
    header = header + "\n" + ".STACK 100H" + "\n";
    data_segment = data_segment + "\n" + ".DATA" + "\n";
    code_segment = code_segment + "\n" + ".CODE" + "\n";
    writeInDataSegment();
}
void AssemblyGenerator::endCode()
{
    this->writePrintFunc();
    string code;
    code = code + "END MAIN" + "\n";
    addInCodeSegment(code);
}
void AssemblyGenerator::assignOp(Variable *left, Expression *right)
{
    // Expression is evaluated before, and pushed in the stack.
    // We need to pop the value of expression and assign it to left operand

    string code = "";

    code += "\t\t; At line no " + to_string(line_count) + ": Assigning " + right->getExpression() + " into " + left->getName() + "\n";
    code += "\t\tPOP AX";
    code += "\t;" + right->getExpression() + " popped from stack\n";

    if (left->getVarType() == "ARRAY")
    {
        code += "\t\tPOP BX";
        code += string("\t; Index of the array popped") + "\n";

        code += "\t\tPUSH BP";
        code += string("\t; Saving value of BP in stack, so that we can restore it's value later") + "\n";

        code += "\t\tMOV BP, BX";
        code += string("\t; Saving address of the array index in BP to access array from stack") + "\n";

        if (table->getScopeIdOfSymbol(left->getName()) == "1")
        {
            code += "\t\tMOV " + left->getName() + "[BP], AX";
            code += "\t; Value of " + right->getExpression() + " assigned into " + left->getName() + "[BP]" + "\n";
        }
        else
        {
            code += "\t\tMOV [BP], AX";
            code += "\t; Value of " + right->getExpression() + " assigned into " + left->getName() + "[BP]" + "\n";
        }

        code += "\t\tPOP BP";
        code += string("\t; Restoring value of BP") + "\n";
    }
    else
    {

        if (table->getScopeIdOfSymbol(left->getName()) == "1")
        {
            code += "\t\tMOV " + left->getName() + ", AX";
            code += "\t; Value of " + right->getExpression() + " assigned into " + left->getName() + "\n";
        }
        else
        {
            int x = -1 * getOffset(left);
            code += "\t\tMOV [BP + " + to_string(x) + "], AX";
            code += "\t; Value of " + right->getExpression() + " assigned into " + left->getName() + "\n";
        }
    }
    addInCodeSegment(code);
}

string getRelOpASM(string op)
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
        return "JnE";
    }
    else if (op == "==")
    {
        return "JE";
    }
    return "";
}

void AssemblyGenerator::addOp(string op, Expression *left, Expression *right)
{
    string opr = op;
    if (op == "+")
    {
        op = "ADD";
    }
    else if (op == "-")
    {
        op = "SUB";
    }
    string code = "";
    code += "\t\t; At line no " + to_string(line_count) + ": " + op + " " + left->getExpression() + " and " + right->getExpression() + "\n";

    code += "\t\tPOP BX";
    code += string("\t; ") + right->getExpression() + " popped from stack\n";

    code += "\t\tPOP AX";
    code += string("\t; ") + left->getExpression() + " popped from stack\n";

    code += "\t\t" + op + " AX, BX\n";

    code += "\t\tPUSH AX";
    code += string("\t; Pushed evaluated value of ") + left->getExpression() + opr + right->getExpression() + " in the stack\n";
    addInCodeSegment(code);
}
void AssemblyGenerator::relOp(string op, Expression *left, Expression *right)
{
    string true_label = newLabel();
    string false_label = newLabel();

    string code = "";
    code += "\t\t; At line no  " + to_string(line_count) + ": Checking if " + left->getExpression() + op + right->getExpression() + "\n";
    op = getRelOpASM(op);

    code += "\t\tPOP BX";
    code += string("\t; Popped out ") + right->getExpression() + " from stack\n";

    code += "\t\tPOP AX";
    code += string("\t; Popped out ") + left->getExpression() + " from stack\n";

    code += "\t\tCMP AX, BX";
    code += string("\t; Comparing ") + left->getExpression() + " with " + right->getExpression() + "\n";

    code += conditionalJump(op, true_label); // If true then do conditional jump
    code += "\t\tPUSH 0" + string("\t; Saving expression value to be false") + "\n";

    code += jumpInstant(false_label); // If false then do long jump
    code += declareLabel(true_label, true);
    code += "\t\t" + false_label + ":\n\n";
    addInCodeSegment(code);
}
void AssemblyGenerator::logicOp(string op, Expression *left, Expression *right)
{
    string right_check_label = newLabel();
    string end_label = newLabel();
    string result_label = newLabel();

    string code = "";

    code += "\t\t; At line no " + to_string(line_count) + ": " + left->getExpression() + op + right->getExpression() + "\n";

    code += "\t\tPOP BX";
    code += string("\t; ") + right->getExpression() + " popped from stack\n";

    code += "\t\tPOP AX";
    code += string("\t; ") + left->getExpression() + " popped from stack\n";

    code += "\t\tCMP AX, 0" + string("\t; Comparing ") + left->getExpression() + " and 0\n";
    // If operator is &&, then getting a 0 will cause result to be 0
    // and if the operator is ||, then getting a 1 will cause result
    // to be 1
    if (op == "&&")
    {
        code += "\t\t; If " + left->getExpression() + " is not 0, then check " + right->getExpression() + ". So, jump to " + right_check_label + "\n";
        code += conditionalJump("JNE", right_check_label);

        code += "\t\tPUSH 0";
        code += string("\t; Saving expression value to be false") + "\n";
    }
    else
    {
        code += "\t\t; if " + left->getExpression() + " is 0, check " + right->getExpression() + ". So, jump to " + right_check_label + "\n";
        code += conditionalJump("JE", right_check_label);

        code += "\t\tPUSH 1";
        code += string("\t; Saving expression value to be true") + "\n";
    }
    code += jumpInstant(end_label);
    code += "\t\t" + right_check_label + ":\n";
    code += "\t\tCMP BX, 0" + string("\t; Comparing ") + right->getExpression() + " and 0\n";
    // If operator is &&, then getting 0 in right will cause result to be 0
    // and if the operator is ||, then ggetting a 1 in right will cause result
    // to be 1
    if (op == "&&")
    {
        code += "\t\t; If " + right->getExpression() + " is not 0, the whole expression is true. So, jump to " + result_label + "\n";
        code += conditionalJump("JNE", result_label);
        code += "\t\tPUSH 0";
        code += string("\t; Saving expression value to be false") + "\n";
    }
    else
    {
        code += "\t\t; If " + right->getExpression() + " is 0, the whole expression is false. So, jump to " + result_label + "\n";
        code += conditionalJump("JE", result_label);
        code += "\t\tPUSH 1";
        code += string("\t; Saving expression value to be true") + "\n";
    }
    code += jumpInstant(end_label);
    if (op == "&&")
    {
        code += declareLabel(result_label, true);
        code += "\t\t" + end_label + ":\n\n";
    }
    else
    {
        code += declareLabel(result_label, false);
        code += "\t\t" + end_label + ":\n\n";
    }

    addInCodeSegment(code);
}
void AssemblyGenerator::incdecOperation(Variable *var, string op)
{
    string code = "";
    code += "\t\t; At line no " + to_string(line_count) + ": Evaluating " + var->getName() + op + "\n";
    if (var->getVarType() == "ARRAY")
    {
        code += "\t\tPOP BX";
        code += string("\t; Array index popped from stack") + "\n";

        code += "\t\tPUSH BP";
        code += string("\t; Saving value of BP in stack") + "\n";

        code += "\t\tMOV BP, BX";
        code += string("\t; Saving value of array index in BP") + "\n";

        code += "\t\tMOV AX, [BP]";
        code += string("\t; Saving value of ") + var->getName() + " in AX" + "\n";

        code += "\t\tPOP BP";
        code += string("\t; Resetting value of BP") + "\n";
    }
    else
    {
        code += "\t\tPOP AX";
        code += string("\t; Saving value of ") + var->getName() + " in AX" + "\n";

        code += "\t\tPUSH AX";
        code += string("\t; Pushing the value of ") + var->getName() + " back to stack" + "\n";
    }

    if (op == "++")
    {
        code += "\t\tINC AX" + string("\t; Incrementing ") + var->getName() + "\n";
    }
    else
    {
        code += "\t\tDEC AX" + string("\t; Decrementing ") + var->getName() + "\n";
    }

    if (table->getScopeIdOfSymbol(var->getName()) == "1")
    {
        if (var->getVarType() == "ARRAY")
        {
            code += "\t\tPUSH BP";
            code += string("\t; Saving value of BP in stack") + "\n";

            code += "\t\tMOV BP, BX";
            code += string("\t; Saving value of array index in BP") + "\n";

            code += "\t\tMOV " + var->getName() + "[BP], AX";
            code += string("\t; Saving the result in stack") + "\n";

            code += "\t\tPOP BP";
            code += string("\t; Resetting value of BP") + "\n";
        }
        else
        {
            code += "\t\tMOV " + var->getName() + ", AX";
            code += string("\t; Saving the result in stack") + "\n";
        }
    }
    else
    {
        if (var->getVarType() == "ARRAY")
        {
            code += "\t\tPUSH BP";
            code += string("\t; Saving value of BP in stack") + "\n";

            code += "\t\tMOV BP, BX";
            code += string("\t; Saving value of array index in BP") + "\n";

            code += "\t\tMOV [BP], AX";
            code += string("\t; Saving the result in stack") + "\n";

            code += "\t\tPOP BP";
            code += string("\t; Resetting value of BP") + "\n";
        }
        else
        {
            int x = -1 * getOffset(var);

            code += "\t\tMOV [BP + " + to_string(x) + "], AX";
            code += string("\t; Saving result in stack") + "\n";
        }
    }

    addInCodeSegment(code);
}
void AssemblyGenerator::decrementOperation(Variable *var)
{
    incdecOperation(var, "--");
}
void AssemblyGenerator::incrementOperation(Variable *var)
{
    incdecOperation(var, "++");
}

string getMulopOperator(string mulop)
{
    if (mulop == "%")
    {
        return "MODULUS";
    }
    else if (mulop == "*")
    {
        return "MULTIPLICATION";
    }
    else
    {
        return "DIVISION";
    }
    return "";
}

void AssemblyGenerator::mulOp(string op, Expression *left, Expression *right)
{
    string operation = getMulopOperator(op);
    string code = "";

    code += "\t\t; " + operation + " operation between " + left->getExpression() + " and " + right->getExpression() + "\n";

    code += "\t\tPOP BX";
    code += string("\t; ") + right->getExpression() + " popped from stack" + "\n";

    code += "\t\tPOP AX";
    code += string("\t; ") + left->getExpression() + " popped from stack" + "\n";

    if (op == "*")
    {
        // DX:AX = AX * BX
        code += "\t\tIMUL BX" + string("\t; Multiplying ") + left->getExpression() + " and " + right->getExpression() + "\n";
    }
    else
    {
        code += "\t\tXOR DX, DX";
        code += string("\t; Setting value of DX to 0") + "\n";

        code += "\t\tIDIV BX";
        code += string("\t; Dividing ") + left->getExpression() + " by " + right->getExpression() + "\n";

        // AX = DX:AX / BX and DX = DX:AX % BX
        if (op == "%")
        {
            code += "\t\tMOV AX, DX";
            code += string("\t; Saving remainder after division from DX to AX") + "\n";
        }
    }
    code += "\t\tPUSH AX";
    code += string("\t; Saving result of ") + left->getExpression() + op + right->getExpression() + " in stack" + "\n";

    addInCodeSegment(code);
}

void AssemblyGenerator::unaryOperation(string uniop, Expression *sym)
{
    if (uniop == "-")
    {
        string code = "";

        code += "\t\t; At line no " + to_string(line_count) + ": Negating " + sym->getExpression() + "\n";

        code += "\t\tPOP AX";
        code += string("\t; ") + sym->getExpression() + " popped from stack" + "\n";

        code += "\t\tNEG AX";
        code += string("\t; Negating ") + sym->getExpression() + "\n";

        code += "\t\tPUSH AX";
        code += string("\t; Saving result of -") + sym->getExpression() + " in stack" + "\n";

        addInCodeSegment(code);
    }
}

void AssemblyGenerator::notOperation(Expression *sym)
{
    string false_label = newLabel();
    string end_label = newLabel();
    string code = "";

    code += "\t\t; At line no " + to_string(line_count) + ": Evaluating !" + sym->getExpression() + "\n";

    code += "\t\tPOP AX";
    code += string("\t; Popped ") + sym->getExpression() + " from stack" + "\n";

    code += "\t\tCMP AX,0";
    code += string("\t; Comparing ") + sym->getExpression() + " with 0" + "\n";

    code += "\t\tJNE " + false_label + "\t; Go to label " + false_label + " if BX is not 0" + "\n";
    code += "\t\tPUSH 1" + string("\t; Pushing 1 in stack if BX is 0") + "\n";
    code += jumpInstant(end_label);
    code += declareLabel(false_label, false);
    code += "\t\t" + end_label + ":\n\n";
    addInCodeSegment(code);
}
void AssemblyGenerator::callVariable(Variable *var)
{
    string code = "";
    if (table->getScopeIdOfSymbol(var->getName()) == "1")
    {
        code += "\t\tPUSH " + var->getName() + "; Pushing global variable to stack for expression evaluation";
    }
    else
    {
        int x = -1 * getOffset(var);
        code += "\t\tPUSH [BP + " + to_string(x) + "]\t; " + var->getName() + " pushed for expression evaluation" + "\n";
    }
    addInCodeSegment(code);
}

void AssemblyGenerator::callFunction(Function *func)
{
    string code = "";
    code += "\t\tCALL " + func->getName() + "\t; Function with name " + func->getName() + " called" + "\n";
    code += "\t\tPUSH AX" + string("\t; Return value of function named ") + func->getName() + " pushed in stack" + "\n";
    addInCodeSegment(code);
}

void AssemblyGenerator::callConstant(Constant *cons)
{
    if (cons->getDataType() == "int")
    {
        string code = "";
        code += "\t\tPUSH " + cons->getName() + "\t; Pushing constant value in stack";
        addInCodeSegment(code);
    }
}

string AssemblyGenerator::newLabel()
{
    string lb = "L" + to_string(label_count);
    label_count++;
    return lb;
}

void AssemblyGenerator::returnFunction()
{
    string code = "";
    // code += "\t\tPOP AX" + string("\t; Popped return value and saved it in AX") + "\n";
    addInCodeSegment(code);
    // endProcedure(curr_func->getName());
}

void AssemblyGenerator::writeENDPForFunc(string name)
{
    string code = "";
    if (name == "main")
    {
        code += "\t\t; Setting interrupt for function end\n";
        code += "\t\tMOV AH, 4CH\n\t\tINT 21H\n";
    }
    code += "\t" + name + " ENDP" + "\n";
    addInCodeSegment(code);
}

void AssemblyGenerator::printId(Identifier *id)
{
    string code = "";
    code += "\n";
    if (table->getScopeIdOfSymbol(id->getName()) == "1")
    {
        code += "\t\tPUSH " + id->getName();
        code += "\t; Passing " + id->getName() + " to PRINT_NUM for printing it" + "\n";
    }
    else
    {
        int x = -1 * getOffset(id);
        code += "\t\tPUSH [BP + " + to_string(x) + "]" + "\t; Passing " + id->getName() + " to PRINT_NUM for printing it" + "\n";
    }
    code += "\t\tCALL PRINT_NUM\n";
    addInCodeSegment(code);
}

void AssemblyGenerator::popArrayFromStack(string reg, Variable *var)
{
    // If after "variable: Id" or "variable: Array" rule matches and next rule doesn't match with INCOP or DECOP,
    // and goes to "factor : variable" rule then we no longer need the index of the previously accessed array
    if (var->getVarType() == "ARRAY")
    {
        addInCodeSegment("\t\tPOP BX" + string("\t; Array index popped because it is no longer required"));
    }
}

void AssemblyGenerator::handleExtraExpressionPush(string name)
{
    // There is always an extra push after every expression
    // So, we need to pop it out after we get a semicolon after an expression
    string code = "";
    code += "\t\tPOP AX" + string("\t; Popped out ") + name + "\n";
    addInCodeSegment(code);
}

void AssemblyGenerator::forLoopStart()
{
    string startLabel = newLabel();
    forLoopStartLabel.push(startLabel);
    string code = "";
    code += "\t\t; At line no " + to_string(line_count) + ": Starting for loop" + "\n";
    code += "\t\t" + startLabel + ":\t; For loop start label" + "\n";
    addInCodeSegment(code);
}

void AssemblyGenerator::forLoopConditionCheck()
{
    string true_label = newLabel();
    string end_label = newLabel();
    forLoopEndLabel.push(end_label);
    string code = "";
    // We have already popped AX from stack after getting expression_statement. This AX contains
    // the result of the condition inside for loop
    code += "\t\tCMP AX, 0" + string("\t; Checking if the condition is true or false") + "\n";
    // If AX != 0, then statement will compile, otherwise go to end label
    code += conditionalJump("JNE", true_label);
    code += "\t\t; If false then jump to the end label of for loop\n";
    code += jumpInstant(end_label);
    code += "\t\t" + true_label + ":" + "\n";
    addInCodeSegment(code);
    isForLoop = true; // We are making it true, so that the expression is evaluated after the for loop statement is executed
}

void AssemblyGenerator::gotoNextStepInForLoop(string var)
{
    string code = "";
    code += "\t\tPOP AX" + string("\t; Popped ") + var + " from stack" + "\n";
    if (!forLoopStartLabel.empty())
    {
        code += "\t\tJMP " + forLoopStartLabel.top() + "\t; Jump back to for loop" + "\n";
        forLoopStartLabel.pop();
    }
    if (!forLoopEndLabel.empty())
    {
        code += "\t\t; End label of for loop\n";
        code += "\t\t" + forLoopEndLabel.top() + ":" + "\n";
        forLoopEndLabel.pop();
    }
    forLoopExpressionCode = forLoopIncDecCode + code;
    forLoop.push(forLoopExpressionCode);
    forLoopIncDecCode = "";
    forLoopExpressionCode = "";
    isForLoop = false;
    // addInCodeSegment(code);
}

void AssemblyGenerator::endForLoop()
{
    if (!forLoop.empty())
    {
        addInCodeSegment(forLoop.top());
        forLoop.pop();
    }
    forLoopIncDecCode = "";
    forLoopExpressionCode = "";
}

Segment *AssemblyGenerator::createIfBlock()
{
    string true_label = newLabel();
    string false_label = newLabel();
    Segment *sym = new Segment(false_label, "TEMP");

    string code = "";
    code += "\t\t; At line no " + to_string(line_count) + ": Evaluationg if statement" + "\n";

    code += "\t\tPOP AX";
    code += string("\t; Popped expression value from stack") + "\n";

    code += "\t\tCMP AX, 0";
    code += string("\t; Checking whether expression is true or false") + "\n";

    code += conditionalJump("JNE", true_label);
    code += "\t\t; If expression is false then jump to the end of if block\n";

    code += jumpInstant(false_label);
    code += "\t\t" + true_label + ":" + "\n";
    addInCodeSegment(code);
    return sym;
}

void AssemblyGenerator::endIfBlock(string label)
{
    string code = "";
    code += "\t\t; End label for if statement\n";
    code += "\t\t" + label + ":" + "\n";
    addInCodeSegment(code);
}

void AssemblyGenerator::createElseBlock(string label)
{
    string end_label = newLabel();
    elseBlockEndLabel.push(end_label);
    string code = "";
    code += "\t\t; If expression was true and statement is evaluated then jump to end label\n";
    code += jumpInstant(end_label);
    code += "\t\t; Label for else block\n";
    code += "\t\t" + label + ":" + "\n";
    addInCodeSegment(code);
}

void AssemblyGenerator::endIfElseBlock()
{
    string code = "";
    if (!elseBlockEndLabel.empty())
    {
        code += "\t\t; End label for if else statement\n";
        code += "\t\t" + elseBlockEndLabel.top() + ":" + "\n";
        elseBlockEndLabel.pop();
        addInCodeSegment(code);
    }
}

string AssemblyGenerator::declareLabel(string label, bool condition)
{
    string code = "";
    code += "\t\t" + label + ":" + "\n";
    if (condition)
    {
        code += "\t\tPUSH 1\t; Saving expression value to be true\n";
    }
    else
    {
        code += "\t\tPUSH 0\t; Saving expression value to be false\n";
    }
    return code;
}

string AssemblyGenerator::conditionalJump(string condition, string label)
{
    return "\t\t" + condition + " " + label + "\n";
}

string AssemblyGenerator::jumpInstant(string label)
{
    return "\t\tJMP " + label + "\n";
}

void AssemblyGenerator::whileLoopStart()
{
    string startLabel = newLabel();
    whileLoopStartLabel.push(startLabel);
    string code = "";
    code += "\t\t; At line no " + to_string(line_count) + ": Starting while loop" + "\n";
    code += "\t\t" + startLabel;
    code += ":\t; While loop start label\n";
    addInCodeSegment(code);
}

void AssemblyGenerator::whileLoopConditionCheck(string var)
{
    string true_label = newLabel();
    string end_label = newLabel();
    whileLoopEndLabel.push(end_label);
    string code = "";
    code += "\t\tPOP AX";
    code += string("\t; Popped ") + var + " from stack" + "\n";

    code += "\t\tCMP AX, 0";
    code += string("\t; Checking if the condition is true or false") + "\n";
    // If AX != 0, then statement will compile, otherwise go to end label
    code += conditionalJump("JNE", true_label);
    code += "\t\t; If false then jump to the end label of while loop\n";
    code += jumpInstant(end_label);
    code += "\t\t" + true_label + ":" + "\n";
    // Under true label there will be all the statements
    addInCodeSegment(code);
}

void AssemblyGenerator::endWhileLoop()
{
    string code = "";
    if (!whileLoopStartLabel.empty())
    {
        code += "\t\tJMP " + whileLoopStartLabel.top() + "\t; Jump back to while loop" + "\n";
        whileLoopStartLabel.pop();
    }
    if (!whileLoopEndLabel.empty())
    {
        code += "\t\t; End label of while loop\n";
        code += "\t\t" + whileLoopEndLabel.top() + ":" + "\n";
        whileLoopEndLabel.pop();
    }
    addInCodeSegment(code);
}

void AssemblyGenerator::setOffset(SymbolInfo *s, int offset)
{
    this->id_offset[s->getName() + "_" + table->getScopeIdOfSymbol(s->getName())] = offset;
}

int AssemblyGenerator::getOffset(SymbolInfo *s)
{
    // cout << s->getName() + "_" + table->getScopeIdOfSymbol(s->getName()) << endl;
    return this->id_offset[s->getName() + "_" + table->getScopeIdOfSymbol(s->getName())];
}

void AssemblyGenerator::callArray(Array *arr, string index)
{
    string code = "";

    code += "\t\t; At line no " + to_string(line_count) + ": getting value of " + arr->getName() + "[" + index + "]\n";

    code += "\t\tPOP BX";
    code += string("\t; Getting index of the array") + "\n";

    code += "\t\tSHL BX, 1";
    code += string("\t; Multiplying index by 2 to match size of a word") + "\n";

    if (table->getScopeIdOfSymbol(arr->getName()) == "1")
    {
        code += "\t\tPUSH BP";
        code += string("\t; Saving value of BP in stack, so that we can restore it's value later") + "\n";

        code += "\t\tMOV BP, BX";
        code += string("\t; Saving address of the array index in BP to access array from stack") + "\n";

        code += "\t\tMOV AX, " + arr->getName() + "[BP]";
        code += string("\t; Getting the value of the array from index BP") + "\n";
    }
    else
    {
        code += "\t\tADD BX, " + to_string(getOffset(arr));

        code += "\t; Adding the offset of the array to get the offset of array element\n";

        code += "\t\tPUSH BP";
        code += string("\t; Saving value of BP in stack, so that we can restore it's value later") + "\n";

        code += "\t\tSUB BP, BX";
        code += string("\t; Adding BP to BX to get the address of the array") + "\n";

        // code += "\t\tMOV BP, BX";
        // code += string("\t; Saving address of the array index in BP to access array from stack") + "\n";

        code += "\t\tMOV AX, [BP]";
        code += string("\t; Getting the value of the array at address BP") + "\n";
    }
    code += "\t\tPOP BP";
    code += string("\t; Restoring value of BP") + "\n";
    // Pushing the index and value of the array element on the stack
    // This will allow the ASSIGNOP and INCOP to use it later
    code += "\t\tPUSH AX";
    code += string("\t; Pushing the value of the array element at index ") + index + "\n";

    code += "\t\tPUSH BX";
    code += string("\t; Pushing the index of the array") + "\n";
    addInCodeSegment(code);
}