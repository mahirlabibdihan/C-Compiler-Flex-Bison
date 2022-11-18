#include "1905072_Assembly_Generator.hpp"
#include "1905072_SymbolTable.hpp"
#include <algorithm>
#include <string>
using namespace std;

extern SymbolTable *table;
extern int line_count;
extern int error_count;
extern ofstream codeout;

// declared variable, temporary variable, constant

AssemblyGenerator::AssemblyGenerator(string file)
{
    this->outfile = file;
    curr_tmp = tmp_count = 0;
    label_count = 0;
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

void AssemblyGenerator::addInDeclaredVariable(string code)
{
    if (declared_var_segment.empty())
    {
        declared_var_segment += "\t\t; Declared variables\n";
    }
    declared_var_segment += code;
    writeInDataSegment();
}
void AssemblyGenerator::addInTemporaryVariable(string code)
{
    if (tmp_var_segment.empty())
    {
        tmp_var_segment += "\t\t; Temporary variables\n";
    }
    tmp_var_segment += code;
    writeInDataSegment();
}

void AssemblyGenerator::addInCodeSegment(string code)
{
    if (error_count == 0)
    {
        if (!stopPrinting)
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
    if (error_count == 0)
    {
        codeout << header << endl;
        codeout << data_segment << endl;
        codeout << declared_var_segment << endl;
        codeout << tmp_var_segment << endl;
        codeout << code_segment << endl;
        codeout.flush();
    }
}

void AssemblyGenerator::writeInCodeSegment(string code)
{
    if (error_count == 0)
    {
        codeout << code;
        codeout.flush();
    }
}

void AssemblyGenerator::createFunctionScope()
{
    // offset_history.push(offset);
    int offset = 4;

    vector<Variable *> params = curr_func->getParams();
    reverse(params.begin(), params.end());

    string code;
    for (auto p : params)
    {
        addInDeclaredVariable("\t\t" + getVariableName(p) + " DW ?\n");

        code += "\t\tMOV AX, [BP + " + to_string(offset) + "]\n";
        code += "\t\tMOV " + getVariableName(p) + ", AX\n";

        offset += 2;
    }
    // offset = 2;
    addInCodeSegment(code);
    /** NEWLY ADDED **/
}
void AssemblyGenerator::declareArray(Array *arr)
{
    addInDeclaredVariable("\t\t; " + arr->getDataType() + " " + arr->getSymbol() + "[" + arr->getArraySize() + "]" + ";\n");
    addInDeclaredVariable("\t\t" + getVariableName(arr) + " DW " + arr->getArraySize() + " DUP(0) \n");
}

void AssemblyGenerator::declareVariable(Variable *var)
{
    addInDeclaredVariable("\t\t; " + var->getDataType() + " " + var->getSymbol() + ";\n");
    addInDeclaredVariable("\t\t" + getVariableName(var) + " DW ?\n");
}

void AssemblyGenerator::startFunction(Function *func)
{
    if (error_count > 0)
    {
        return;
    }
    string code = "\n";
    code += "\t" + func->getSymbol() + " PROC\n";
    code += "\t\t; Function with name " + func->getSymbol() + " started\n";
    if (func->getSymbol() != "main")
    {
        code += "\t\tPUSH BP\n";
        code += "\t\tMOV BP, SP\n";
        code += "\t\t; All the offsets of a function depends on the value of BP\n";
    }
    addInCodeSegment(code);
    if (func->getSymbol() == "main")
    {
        startMain();
    }
    curr_func = func;
}

void AssemblyGenerator::returnFunction(Expression *ret)
{
    if (error_count > 0)
    {
        return;
    }
    string code = "\n";

    if (curr_func->getSymbol() != "main")
    {
        code += "\t\t; Restoring BP at the end of function\n";
        code += "\t\tPOP BP\n";
    }

    code += "\n";

    if (ret == NULL)
    {
        code += "\t\t; return ;\n";
        if (curr_func->getReturnType() == "void")
        {
            code += "\t\tRET\n";
        }
    }
    else
    {
        code += "\t\t; return " + ret->getSymbol() + ";\n";
        if (curr_func->getSymbol() != "main")
        {
            code += "\t\tPOP BX\n"; // return address in BX
            code += "\t\tPUSH " + ret->getTmpVar() + "\n";
            code += "\t\tPUSH BX\n";
            code += "\t\tRET\n";
        }
    }
    addInCodeSegment(code);
}

void AssemblyGenerator::endFunction(string name)
{
    string code = "";

    if (curr_func->getReturnType() == "void")
    {
        returnFunction();
    }

    if (name == "main")
    {
        // code += "\t\t; Setting interrupt for function end\n";
        code += "\t\tMOV AH, 4CH\n";
        code += "\t\tINT 21H\n";
    }
    code += "\t" + name + " ENDP" + "\n\n";
    addInCodeSegment(code);
    curr_func = nullptr;
    // offset = offset_history.top();
    // offset_history.pop();
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
    PRINT_NUM ENDP\n";

    addInCodeSegment(code);
}

void AssemblyGenerator::startMain()
{
    string code = "";
    code += "\t\t; DATA SEGMENT INITIALIZATION\n";
    code += "\t\tMOV AX, @DATA\n";
    code += "\t\tMOV DS, AX\n";
    // offset = 2;
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

string AssemblyGenerator::addOp(Expression *left, string op, Expression *right)
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
    string code = "\n";
    code += "\t\t; " + left->getSymbol() + opr + right->getSymbol() + "\n";
    code += "\t\tMOV AX, " + left->getTmpVar() + "\n";
    code += "\t\tMOV BX, " + right->getTmpVar() + "\n";
    string tmp = newTemp();
    code += "\t\t" + op + " AX, BX\n";
    code += "\t\tMOV " + tmp + ", AX\n";
    addInCodeSegment(code);
    return tmp;
}
string AssemblyGenerator::relOp(Expression *left, string op, Expression *right)
{
    // string true_label = newLabel();
    string end_label = newLabel();

    string code = "\n";
    string opr = op;
    // code += "\t\t; At line no  " + to_string(line_count) + ": Checking if " + left->getExpression() + op + right->getExpression() + "\n";
    op = getRelOpASM(op);

    string tmp = newTemp();

    code += "\t\t; " + left->getSymbol() + opr + right->getSymbol() + "\n";
    // AX = Left, BX = Right and Compare
    code += "\t\tMOV AX, " + left->getTmpVar() + "\n";
    code += "\t\tMOV BX, " + right->getTmpVar() + "\n";
    code += "\t\tCMP AX, BX\n";
    code += "\t\tMOV " + tmp + ", 1\n";           // Default value as 1
    code += "\t\t" + op + " " + end_label + "\n"; // Jump to end_label if true
    code += "\t\tMOV " + tmp + ", 0\n";
    code += "\t\t" + end_label + ":\n";

    addInCodeSegment(code);
    return tmp;
}
string AssemblyGenerator::logicOp(Expression *left, string op, Expression *right)
{

    string code = "\n";

    code += "\t\t; " + left->getSymbol() + op + right->getSymbol() + "\n";
    code += "\t\tMOV AX, " + left->getTmpVar() + "\n";
    code += "\t\tMOV BX, " + right->getTmpVar() + "\n";

    string false_label = newLabel();
    string true_label = newLabel();
    string end_label = newLabel();

    string tmp = newTemp();
    if (op == "&&")
    {
        code += "\t\tCMP AX, 0\n";
        code += "\t\tJE " + false_label + "\n";
        code += "\t\tCMP BX, 0\n";
        code += "\t\tJE " + false_label + "\n";
        // True
        code += "\t\tMOV " + tmp + ", 1\n";
        code += "\t\tJMP " + end_label + "\n";
        // False
        code += "\t\t" + false_label + ":\n";
        code += "\t\tMOV " + tmp + ", 0\n";

        code += "\t\t" + end_label + ":\n";
    }
    else if (op == "||")
    {
        code += "\t\tCMP AX, 0\n";
        code += "\t\tJNE " + true_label + "\n";
        code += "\t\tCMP BX, 0\n";
        code += "\t\tJNE " + true_label + "\n";
        // False
        code += "\t\tMOV " + tmp + ", 0\n";
        code += "\t\tJMP " + end_label + "\n";
        // True
        code += "\t\t" + true_label + ":\n";
        code += "\t\tMOV " + tmp + ", 1\n";
        code += "\t\t" + end_label + ":\n";
    }

    addInCodeSegment(code);
    return tmp;
}

void AssemblyGenerator::moveIndex(ArrayCall *var)
{
    string code = "\n";
    code += "\t\t; " + var->getSymbol() + "\n";
    code += "\t\tMOV BX, " + var->getIndex() + "\n";
    code += "\t\tSHL BX, 1\n";
    addInCodeSegment(code);
}

string AssemblyGenerator::arrayToFactor(Expression *var)
{
    string tmp = newTemp();
    string code = "\n";
    code += "\t\t; Converting array to factor\n";
    code += "\t\tMOV AX, " + var->getTmpVar() + "\n";
    code += "\t\tMOV " + tmp + ", AX\n";
    addInCodeSegment(code);
    return tmp;
}

// left operand must be lvalue
string AssemblyGenerator::assignOp(Expression *left, Expression *right)
{
    string code = "\n";

    code += "\t\t; " + left->getSymbol() + "=" + right->getSymbol() + "\n";
    code += "\t\tMOV AX, " + right->getTmpVar() + "\n";
    if (left->getExpType() == "ARRAY_CALL")
    {
        moveIndex((ArrayCall *)left); // Moving index to BX
    }
    code += "\t\tMOV " + left->getTmpVar() + ", AX\n";
    addInCodeSegment(code);
    return left->getTmpVar();
}

// left operand must be lvalue
void AssemblyGenerator::decrementOperation(Expression *var)
{
    string code;
    if (var->getExpType() == "ARRAY_CALL")
    {
        moveIndex((ArrayCall *)var); // Moving index to BX
    }
    code += "\t\t; " + var->getSymbol() + "--\n";
    code += "\t\tMOV AX, " + var->getTmpVar() + "\n";
    code += "\t\tDEC AX\n";
    code += "\t\tMOV " + var->getTmpVar() + ", AX\n";
    addInCodeSegment(code);
}

// left operand must be lvalue
void AssemblyGenerator::incrementOperation(Expression *var)
{
    string code = "\n";
    if (var->getExpType() == "ARRAY_CALL")
    {
        moveIndex((ArrayCall *)var); // Moving index to BX
    }

    code += "\t\t; " + var->getSymbol() + "++\n";
    code += "\t\tMOV AX, " + var->getTmpVar() + "\n";
    code += "\t\tINC AX\n";
    code += "\t\tMOV " + var->getTmpVar() + ", AX\n";
    addInCodeSegment(code);
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

string AssemblyGenerator::mulOp(Expression *left, string op, Expression *right)
{
    string operation = getMulopOperator(op);
    string code = "\n";

    string tmp = newTemp();

    code += "\t\t; " + left->getSymbol() + op + right->getSymbol() + "\n";
    code += "\t\tMOV AX, " + left->getTmpVar() + "\n";
    code += "\t\tMOV BX, " + right->getTmpVar() + "\n";

    if (op == "*")
    {
        // AX = AX * BX
        code += "\t\tIMUL BX\n";
        // code += string("\t; Multiplying ") + left->getExpression() + " and " + right->getExpression() + "\n";
    }
    else
    {
        code += "\t\tXOR DX, DX\n";
        // code += string("\t; Setting value of DX to 0") + "\n";

        code += "\t\tIDIV BX\n";
        // code += string("\t; Dividing ") + left->getExpression() + " by " + right->getExpression() + "\n";

        // AX = AX / BX and DX = AX % BX
        if (op == "%")
        {
            code += "\t\tMOV AX, DX\n";
            // code += string("\t; Saving remainder after division from DX to AX") + "\n";
        }
    }
    code += "\t\tMOV " + tmp + ", AX\n";
    // code += string("\t; Saving result of ") + left->getExpression() + op + right->getExpression() + " in stack" + "\n";

    addInCodeSegment(code);
    return tmp;
}

string AssemblyGenerator::unaryOperation(string uniop, Expression *sym)
{
    string tmp = sym->getTmpVar();
    if (uniop == "-")
    {
        tmp = newTemp();
        string code = "\n";

        code += "\t\t; -" + sym->getSymbol() + "\n";
        code += "\t\tMOV AX, " + sym->getTmpVar() + "\n";
        code += "\t\tNEG AX\n";
        code += "\t\tMOV " + tmp + ", AX\n";

        addInCodeSegment(code);
    }
    return tmp;
}

string AssemblyGenerator::notOperation(Expression *sym)
{
    string false_label = newLabel();
    string end_label = newLabel();
    string code = "";

    // code += "\t\t; At line no " + to_string(line_count) + ": Evaluating !" + sym->getExpression() + "\n";

    string tmp = newTemp();
    code += "\t\tMOV AX, " + sym->getTmpVar() + "\n";
    code += "\t\tNOT AX\n";
    code += "\t\tMOV " + tmp + ", AX";

    addInCodeSegment(code);

    return tmp;
}
string AssemblyGenerator::callVariable(string var_name)
{
    return getVariableName(var_name);
}

string AssemblyGenerator::callFunction(Function *func, vector<Expression *> args)
{
    string code = "\n";

    code += "\t\t; " + func->getSymbol() + "(";
    for (auto &i : args)
    {
        code += i->getSymbol() + ",";
    }
    if (code.back() == ',')
        code.pop_back();

    code += ")\n";
    // Push the arguments in stack
    for (auto &i : args)
    {
        code += "\t\tPUSH " + i->getTmpVar() + "\n";
    }

    code += "\t\tCALL " + func->getSymbol() + "\n";
    // code += "\t; Function with name " + func->getSymbol() + " called" + "\n";

    string tmp = newTemp(); // Temporary variable for return value

    if (func->getReturnType() != "void")
    {
        code += "\t\tPOP AX\n";
        code += "\t\tMOV " + tmp + ", AX\n";
        // return value saved in tmp
    }

    // Pop the arguments from stack
    for (auto &i : args)
    {
        code += "\t\tPOP BX\n";
    }

    addInCodeSegment(code);
    return tmp;
}

// string AssemblyGenerator::evaluateArrayIndex(Expression *index)
// {
//     string code = "\n";
//     string tmp = newTemp();

//     code += "\t\t; [" + index->getSymbol() + "]\n";
//     code += "\t\tMOV BX, " + index->getTmpVar() + "\n";
//     code += "\t\tSHL BX, 1\n";
//     code += "\t\tMOV " + tmp + ", BX\n";
//     addInCodeSegment(code);
//     return tmp;
// }

// string AssemblyGenerator::callConstant(Constant *cons)
// {
//     string tmp = cons->getSymbol();
//     return tmp;
// }

string AssemblyGenerator::newLabel()
{
    string lb = "L" + to_string(label_count);
    label_count++;
    return lb;
}

string AssemblyGenerator::newTemp()
{
    string tmp = "T" + to_string(curr_tmp);
    if (curr_tmp == tmp_count)
    {
        curr_tmp++;
        tmp_count++;
        addInTemporaryVariable("\t\t" + tmp + " DW ?\n");
    }
    else
    {
        curr_tmp++;
    }
    return tmp;
}

string AssemblyGenerator::getVariableName(Variable *var)
{
    string scope = table->getScopeIdOfSymbol(var->getSymbol());
    for (auto &c : scope)
    {
        if (c == '.')
        {
            c = '_';
        }
    }
    return var->getSymbol() + "_" + scope;
}

string AssemblyGenerator::getVariableName(string var_name)
{
    string scope = table->getScopeIdOfSymbol(var_name);
    for (auto &c : scope)
    {
        if (c == '.')
        {
            c = '_';
        }
    }
    return var_name + "_" + scope;
}

void AssemblyGenerator::printId(Variable *id)
{
    string code = "\n";

    code += "\t\t; println(" + id->getSymbol() + ");\n";
    code += "\t\tPUSH " + getVariableName(id) + "\n";
    // code += "\t; Passing " + getVariableName(id) + " to PRINT_NUM for printing it" + "\n";
    code += "\t\tCALL PRINT_NUM\n";
    addInCodeSegment(code);
}

void AssemblyGenerator::forLoopStart()
{
    string startLabel = newLabel();
    forLoopStartLabel.push(startLabel);
    isInForLoop = true;
    string code = "\n";
    // code += "\t\t; At line no " + to_string(line_count) + ": Starting for loop" + "\n";
    code += "\t\t; For loop start label\n";
    code += "\t\t" + startLabel + ":";
    addInCodeSegment(code);
}

void AssemblyGenerator::forLoopConditionCheck(Expression *exp)
{
    if (isInForLoop)
    {
        string end_label = newLabel();
        forLoopEndLabel.push(end_label);

        string code = "\n";
        code += "\t\t; for( ;" + exp->getSymbol() + "; )\n";
        code += "\t\tMOV AX, " + exp->getTmpVar() + "\n";
        code += "\t\tCMP AX, 0\n";
        code += "\t\tJE " + end_label + "\n";

        addInCodeSegment(code);
        stopPrinting = true; // We are making it true, so that the expression is evaluated after the for loop statement is executed
        isInForLoop = false;
    }
}

void AssemblyGenerator::gotoNextStepInForLoop()
{
    // Just store this expression for later printing
    string code = "\n";

    if (!forLoopStartLabel.empty())
    {
        code += "\t\t; Jump back to for loop\n";
        code += "\t\tJMP " + forLoopStartLabel.top();
        forLoopStartLabel.pop();
    }
    if (!forLoopEndLabel.empty())
    {
        code += "\t\t; End label of for loop\n";
        code += "\t\t" + forLoopEndLabel.top() + ":" + "\n";
        forLoopEndLabel.pop();
    }

    forLoopExpressionCode = forLoopIncDecCode + code;
    forLoopDelayedCode.push(forLoopExpressionCode);
    forLoopIncDecCode.clear();
    forLoopExpressionCode.clear();
    stopPrinting = false;
}

void AssemblyGenerator::endForLoop()
{
    if (!forLoopDelayedCode.empty())
    {

        addInCodeSegment(forLoopDelayedCode.top());
        forLoopDelayedCode.pop();

        string code = "\n";
        code += "\t\t; For Loop ended\n";
        addInCodeSegment(code);
    }
    // forLoopIncDecCode.clear();
    // forLoopExpressionCode.clear();
}

void AssemblyGenerator::createIfBlock(Expression *exp)
{
    // string true_label = newLabel();
    string end_label = newLabel();
    ifBlockEndLabel.push(end_label);

    string code = "\n";

    code += "\t\t; if(" + exp->getSymbol() + ")\n";
    code += "\t\tMOV AX, " + exp->getTmpVar() + "\n";
    code += "\t\tCMP AX, 0\n";
    code += "\t\tJE " + end_label + "\n";

    addInCodeSegment(code);
}

void AssemblyGenerator::endIfBlock()
{
    if (!ifBlockEndLabel.empty())
    {
        string code = "";
        code += "\t\t; End label for if statement\n";
        code += "\t\t" + ifBlockEndLabel.top() + ":" + "\n";
        ifBlockEndLabel.pop();
        code += "\t\t; If block ended\n";
        addInCodeSegment(code);
    }
}

void AssemblyGenerator::createElseBlock()
{
    string end_label = newLabel();
    elseBlockEndLabel.push(end_label);

    if (!ifBlockEndLabel.empty())
    {
        string code = "";
        // code += "\t\t; If expression was true and statement is evaluated then jump to end label\n";
        code += "\t\tJMP " + end_label + "\n";

        // code += "\t\t; Label for else block\n";
        code += "\t\t" + ifBlockEndLabel.top() + ":" + "\n";
        ifBlockEndLabel.pop();
        addInCodeSegment(code);
    }
}

void AssemblyGenerator::endIfElseBlock()
{
    if (!elseBlockEndLabel.empty())
    {
        string code = "";
        code += "\t\t; End label for if else statement\n";
        code += "\t\t" + elseBlockEndLabel.top() + ":" + "\n";
        elseBlockEndLabel.pop();
        code += "\t\t; If-Else block ended\n";
        addInCodeSegment(code);
    }
}

void AssemblyGenerator::whileLoopStart()
{
    string startLabel = newLabel();
    whileLoopStartLabel.push(startLabel);
    string code = "\n";
    // code += "\t\t; At line no " + to_string(line_count) + ": Starting while loop" + "\n";

    code += "\t\t; while\n";
    code += "\t\t" + startLabel + ":";

    // code += "\t; While loop start label\n";
    addInCodeSegment(code);
}

void AssemblyGenerator::whileLoopConditionCheck(Expression *exp)
{
    // string true_label = newLabel();
    string end_label = newLabel();
    whileLoopEndLabel.push(end_label);
    string code = "\n";

    code += "\t\twhile(" + exp->getSymbol() + ")\n";
    code += "\t\tMOV AX, " + exp->getTmpVar() + "\n";
    code += "\t\tCMP AX, 0\n";
    // code += string("\t; Checking if the condition is true or false") + "\n";
    code += "\t\tJE " + end_label + "\n";

    addInCodeSegment(code);
}

void AssemblyGenerator::endWhileLoop()
{
    string code = "\n";
    if (!whileLoopStartLabel.empty())
    {
        code += "\t\tJMP " + whileLoopStartLabel.top();
        code += "\t; Jump back to while loop\n";
        whileLoopStartLabel.pop();
    }
    if (!whileLoopEndLabel.empty())
    {
        code += "\t\t; End label of while loop\n";
        code += "\t\t" + whileLoopEndLabel.top() + ":" + "\n";
        whileLoopEndLabel.pop();
    }
    code += "\t\t; While Loop ended\n";
    addInCodeSegment(code);
}

string AssemblyGenerator::callArray(string arr_name, Expression *index)
{
    return getVariableName(arr_name) + "[BX]";
}

void AssemblyGenerator::addComment(string comment)
{
    addInCodeSegment("\t\t; " + comment + "\n");
}

void AssemblyGenerator::resetTmpVar()
{
    curr_tmp = 0;
}