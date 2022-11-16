#include <string>
#include "1905072_SymbolInfo.h"
#include "1905072_Error_Handler.h"
#include "1905072_SymbolTable.h"
#include "1905072_Semantic_Analyzer.h"
#include "1905072_Helper.h"
#include "1905072_Assembly_Generator.h"
using namespace std;

extern int line_count;
extern bool in_function;
extern SymbolTable *table;
extern vector<string> data_segment;
extern AssemblyGenerator *asm_gen;
extern AssemblyGenerator *sem_anlz;

SemanticAnalyzer::SemanticAnalyzer()
{
}
SemanticAnalyzer::~SemanticAnalyzer()
{
}

string SemanticAnalyzer::implicitTypecast(string left, string right)
{
    // cout << left << "," << right << endl;
    if (left == "NULL" || right == "NULL")
    {
        return "NULL"; // already reported , now supressing more errors
    }
    if (left == "void" || right == "void")
    {
        return "ERROR";
    }
    if (left == "float" && right == "float")
    {
        return "float";
    }
    if (left == "float" && right == "int")
    {
        return "float";
    }
    if (left == "int" && right == "float")
    {
        return "float";
    }
    if (left == "int" && right == "int")
    {
        return "int";
    }
    return "ERROR";
}

bool SemanticAnalyzer::checkAssignment(string left, string right)
{
    // cout << line_count << " " << left << " " << right << endl;
    if (left == "NULL" || right == "NULL")
    {
        return true; // already error reported and converted to NULL , this is made true to supress more error
    }
    if (left == "void" || right == "void") // Void not allowed
    {
        return false;
    }
    if (left == "" || right == "") // Not an expression/variable
    {
        return false;
    }
    if (left == "int" && right == "int")
    {
        return true;
    }
    if (left == "float")
    {
        return true;
    }
    return false;
}

void matchTwoFunction(Function *f1, Function *f2)
{
    if (!f1->matchReturnType(f2))
    {
        handleError(RETURN_TYPE_MISMATCH, line_count, f2->getName());
    }
    if (!f1->matchParamsNum(f2))
    {
        handleError(PARAM_NUMBER_MISMATCH, line_count, f2->getName());
    }
    else if (!f1->matchParamsType(f2))
    {
        handleError(PARAM_TYPE_MISMATCH, line_count, f2->getName());
    }
}

void SemanticAnalyzer::returnFunction(Expression *ret)
{
    if (ret->getDataType() != curr_func->getReturnType())
    {
        handleError(RETURN_TYPE_MISMATCH, line_count, curr_func->getName());
    }
    else
    {
        curr_func = NULL;
    }
}
void SemanticAnalyzer::endFunction()
{
    if (curr_func != NULL)
    {
        if (curr_func->getReturnType() == "void" or curr_func->getName() == "main")
        {
            curr_func = NULL;
        }
        else
        {
            handleError(FUNCTION_NOT_RETURNED, line_count, curr_func->getName());
        }
    }
}
void SemanticAnalyzer::defineFunction(string ret_type, string id_name, vector<Variable *> params)
{
    in_function = true;
    Function *new_func = new Function(id_name);
    new_func->setReturnType(ret_type);
    for (auto p : params)
    {
        new_func->addParam(new Variable(p->getName(), p->getDataType()));
    }

    if (!table->insert(new_func))
    {
        Identifier *id = (Identifier *)table->search(new_func->getName());
        if (id->getIdType() != "FUNCTION" or new_func->isDeclaredAndDefined()) // Already declared as non-function type or Defined as function
        {
            handleError(MULTIPLE_DECLARATION, line_count, new_func->getName());
        }
        else
        {
            Function *func = (Function *)id;
            func->defineFunction();
            matchTwoFunction(func, new_func);

            curr_func = func;
            asm_gen->startFunction(func);
        }
    }
    else
    {
        for (auto &i : params)
        {
            if (i->getName() == "blank")
            {
                handleError(MISSING_PARAM_NAME, line_count, new_func->getName());
            }
        }

        curr_func = new_func;
        new_func->defineFunction();
        asm_gen->startFunction(new_func);
    }
}

void SemanticAnalyzer::declareFunction(string ret_type, string id_name, vector<Variable *> params)
{
    Function *new_func = new Function(id_name);

    new_func->setReturnType(ret_type);
    for (auto p : params)
    {
        new_func->addParam(p);
    }

    if (!table->insert(new_func))
    {
        Identifier *id = (Identifier *)table->search(id_name);
        if (id->getIdType() != "FUNCTION") // Already declared as non-function type or Defined as function
        {
            handleError(MULTIPLE_DECLARATION, line_count, id_name);
        }
        else
        {
            Function *func = (Function *)id;
            matchTwoFunction(func, new_func);
            asm_gen->startFunction(func);
        }
    }
    else
    {
        /** Function inserted successfully **/
    }
}

string SemanticAnalyzer::callFunction(string id_name, vector<Expression *> args)
{
    // cout << id_name << endl;
    Identifier *id = (Identifier *)table->search(id_name);
    if (id == NULL)
    {
        handleError(UNDECLARED_FUNCTION, line_count, id_name);
        return "NULL";
    }

    if (id->getIdType() != "FUNCTION")
    {
        handleError(NOT_FUNCTION, line_count, id_name);
        return "NULL";
    }

    Function *func = (Function *)id;
    // cout << func->isDeclaredAndDefined() << endl;
    if (func->isDeclaredNotDefined())
    {
        handleError(UNDEFINED_FUNCTION, line_count, id_name);
    }
    else if (func->getNumberOfParams() < args.size())
    {
        handleError(TOO_MANY_ARGUMENTS, line_count, id_name);
    }
    else if (func->getNumberOfParams() > args.size())
    {
        handleError(TOO_FEW_ARGUMENTS, line_count, id_name);
    }
    else
    {
        bool matched = func->isValidArgs(args);
        if (!matched)
        {
            handleError(ARGUMENT_TYPE_MISMATCH, line_count, id_name);
        }
        else
        {
        }
    }
    return func->getReturnType();
}

void SemanticAnalyzer::declareVariable(string data_type, string var_name)
{
    Variable *var = new Variable(var_name, data_type);

    if (!table->insert(var)) // already present in current scope
    {
        handleError(MULTIPLE_DECLARATION, line_count, var_name);
    }
    else
    {
        asm_gen->declareVariable(var);
    }
}
void SemanticAnalyzer::declareArray(string data_type, string arr_name, string arr_size)
{
    Array *arr = new Array(arr_name, data_type, arr_size);

    if (!table->insert(arr)) // already present in current scope
    {
        handleError(MULTIPLE_DECLARATION, line_count, arr_name);
    }
    else
    {
        table->printAllScope();
        asm_gen->declareArray(arr);
    }
}
void SemanticAnalyzer::declareVariables(string data_type, string id_names, vector<Variable *> vars)
{
    if (data_type == "void")
    {
        handleError(VOID_VARIABLE, line_count, id_names);
    }
    else
    {
        for (auto &var : vars)
        {
            if (var->getVarType() == "ARRAY")
            {
                Array *arr = (Array *)var;
                declareArray(data_type, arr->getName(), arr->getArraySize());
            }
            else
            {
                declareVariable(data_type, var->getName());
            }
        }
    }
}

string SemanticAnalyzer::callVariable(string var_name)
{
    Identifier *id = (Identifier *)table->search(var_name);

    if (id == NULL)
    {
        handleError(UNDECLARED_VARIABLE, line_count, var_name);
        return "NULL";
    }
    else
    {
        if (id->getIdType() != "VARIABLE")
        {
            handleError(TYPE_MISMATCH, line_count, var_name + " is not a variable"); // should i change this to indexing
            return "NULL";
        }

        Variable *var = (Variable *)id;
        if (var->getVarType() == "ARRAY")
        {
            handleError(TYPE_MISMATCH, line_count, var_name + " is an array"); // should i change this to indexing
            return "NULL";
        }
        return var->getDataType();
    }
}

string SemanticAnalyzer::callArray(string arr_name, Expression *index)
{

    Identifier *id = (Identifier *)table->search(arr_name);

    if (id == NULL)
    {
        handleError(UNDECLARED_VARIABLE, line_count, arr_name);
        return "NULL";
    }
    else
    {
        if (id->getIdType() != "VARIABLE")
        {
            handleError(TYPE_MISMATCH, line_count, arr_name + " is not a variable");
            return "NULL";
        }

        Variable *var = (Variable *)id;
        if (var->getVarType() != "ARRAY")
        {
            handleError(TYPE_MISMATCH, line_count, arr_name + " is not an array"); // should i change this to indexing
            return "NULL";
        }
        if (index->getDataType() != "int")
        {
            handleError(INVALID_ARRAY_INDEX, line_count, index->getCode());
        }
        // asm_gen->callArray(var);
        return var->getDataType();
    }
}

string SemanticAnalyzer::assignOp(Expression *left, Expression *right)
{
    // cout << left << endl;
    if (!checkAssignment(left->getDataType(), right->getDataType()))
    {
        if (left->getDataType() == "void" || right->getDataType() == "void")
        {
            handleError(INVALID_OPERAND, line_count, "of types '" + left->getDataType() + "' and '" + right->getDataType() + "' to 'operator='");
            return "NULL";
        }
        else
        {
            handleError(INVALID_CONVERSION, line_count, "from '" + right->getDataType() + "' to '" + left->getDataType() + "'");
            return "NULL";
        }
    }
    else
    {
        return left->getDataType();
    }
}

string SemanticAnalyzer::logicOp(Expression *left, string op, Expression *right)
{
    string type = implicitTypecast(left->getDataType(), right->getDataType());

    if (type != "NULL")
    {
        if (type != "ERROR")
        {
            // asm_gen->logicOp(op, left, right);
            return "int";
        }
        else
        {
            if (left->getDataType() == "void" || right->getDataType() == "void")
            {
                handleError(INVALID_OPERAND, line_count, "of types '" + left->getDataType() + "' and '" + right->getDataType() + "' to 'operator" + op + "'");
            }
            else
            {
                handleError(INCOMPATIBLE_OPERAND, line_count);
            }
            return "NULL";
        }
    }
    else
    {
        return "NULL";
    }
}

string SemanticAnalyzer::relOp(Expression *left, string op, Expression *right)
{
    string type = implicitTypecast(left->getDataType(), right->getDataType());

    if (type != "NULL")
    {
        if (type != "ERROR")
        {
            // asm_gen->relOp(op, left, right);
            return "int";
        }
        else
        {
            if (left->getDataType() == "void" || right->getDataType() == "void")
            {
                handleError(INVALID_OPERAND, line_count, "of types '" + left->getDataType() + "' and '" + right->getDataType() + "' to 'operator" + op + "'");
            }
            else
            {
                handleError(INCOMPATIBLE_OPERAND, line_count);
            }
            return "NULL";
        }
    }
    else
    {
        return "NULL";
    }
}

string SemanticAnalyzer::addOp(Expression *left, string op, Expression *right)
{
    string type = implicitTypecast(left->getDataType(), right->getDataType());

    if (type != "NULL")
    {
        if (type != "ERROR")
        {
            return type;
        }
        else
        {
            if (left->getDataType() == "void" || right->getDataType() == "void")
            {
                handleError(INVALID_OPERAND, line_count, "of types '" + left->getDataType() + "' and '" + right->getDataType() + "' to 'operator" + op + "'");
            }
            else
            {
                handleError(INCOMPATIBLE_OPERAND, line_count);
            }
            return "NULL";
        }
    }
    else
    {
        return "NULL";
    }
}

string SemanticAnalyzer::mulOp(Expression *left, string op, Expression *right)
{
    string type = implicitTypecast(left->getDataType(), right->getDataType());

    if (op == "%") // both operand should be integer
    {
        if (right->getExpression() == "0")
        {
            handleError(MOD_BY_ZERO, line_count, right->getExpression() + "%" + right->getExpression());
            return "NULL";
        }
        else
        {
            if (type != "int")
            {
                handleError(INVALID_OPERAND, line_count, "of types '" + left->getDataType() + "' and '" + right->getDataType() + "' to 'operator" + op + "'");
                return "NULL";
            }
            else
            {
                // asm_gen->mulOp(op, left, right);
                return "int";
            }
        }
    }
    else if (type != "NULL")
    {
        if (type != "ERROR")
        {
            // asm_gen->mulOp(op, left, right);
            return type;
        }
        else
        {
            if (left->getDataType() == "void" || right->getDataType() == "void")
            {
                handleError(INVALID_OPERAND, line_count, "of types '" + left->getDataType() + "' and '" + right->getDataType() + "' to 'operator" + op + "'");
            }
            else
            {
                handleError(INCOMPATIBLE_OPERAND, line_count);
            }
            return "NULL";
        }
    }
    else
    {
        return "NULL";
    }
}