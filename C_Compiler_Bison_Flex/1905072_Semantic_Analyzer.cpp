#include <string>
#include "1905072_SymbolInfo.hpp"
#include "1905072_Error_Handler.hpp"
#include "1905072_SymbolTable.hpp"
#include "1905072_Semantic_Analyzer.hpp"
#include "1905072_Helper.hpp"
#include "1905072_Assembly_Generator.hpp"
using namespace std;

extern int line_count;
extern bool in_function;
extern SymbolTable *table;
extern vector<string> data_segment;
extern AssemblyGenerator *asm_gen;
extern SemanticAnalyzer *sem_anlz;
extern ErrorHandler *err_hndlr;
extern Helper *hlpr;
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

// Can be merged with checkAssignment
bool SemanticAnalyzer::isConvertible(string to, string from)
{
    if (from == "NULL")
    {
        return true; // already error reported and converted to NULL , this is made true to supress more error
    }
    if (from == "void")
    {
        return false;
    }

    return hlpr->getDataSize(to) >= hlpr->getDataSize(from);
}

bool SemanticAnalyzer::checkAssignment(string left, string right)
{
    // cout << line_count << " " << left << " " << right << endl;
    if (left == "NULL" || right == "NULL")
    {
        return true; // already error reported and converted to NULL , this is made true to supress more error
    }
    // Left can't be void, since left is a variable. And we are not inserting void variable in symbol table
    if (left == "void" || right == "void") // Void not allowed
    {
        return false;
    }
    if (left == "" || right == "") // Not an expression/variable
    {
        return false;
    }

    return (hlpr->getDataSize(left) >= hlpr->getDataSize(left));
}

void matchTwoFunction(Function *f1, Function *f2)
{
    if (!f1->matchReturnType(f2))
    {
        err_hndlr->handleSemanticError(RETURN_TYPE_MISMATCH, line_count, f2->getSymbol());
    }
    if (!f1->matchParamsNum(f2))
    {
        err_hndlr->handleSemanticError(PARAM_NUMBER_MISMATCH, line_count, f2->getSymbol());
    }
    else if (!f1->matchParamsType(f2))
    {
        err_hndlr->handleSemanticError(PARAM_TYPE_MISMATCH, line_count, f2->getSymbol());
    }
}

void SemanticAnalyzer::returnFunction(Expression *ret)
{
    if (ret->getDataType() != curr_func->getReturnType())
    {
        err_hndlr->handleSemanticError(RETURN_TYPE_MISMATCH, line_count, curr_func->getSymbol());
    }
    else
    {
        // delete curr_func;
        curr_func = NULL;
    }
}
void SemanticAnalyzer::endFunction()
{
    if (curr_func != NULL)
    {
        if (curr_func->getReturnType() == "void" or curr_func->getSymbol() == "main")
        {
            // delete curr_func;
            curr_func = NULL;
        }
        else
        {
            err_hndlr->handleSemanticError(FUNCTION_NOT_RETURNED, line_count, curr_func->getSymbol());
        }
    }
}

void SemanticAnalyzer::declareFunctionParams()
{
    for (auto i : curr_func->getParams())
    {
        if (i->getSymbol() == "blank")
            continue;
        Variable *var = new Variable(i->getSymbol(), i->getDataType());
        if (!table->insert(var))
        {
            err_hndlr->handleSemanticError(MULTIPLE_DECLARATION, line_count, i->getSymbol());
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
        new_func->addParam(new Variable(p->getSymbol(), p->getDataType()));
    }

    if (!table->insert(new_func))
    {
        Identifier *id = (Identifier *)table->search(new_func->getSymbol());
        if (id->getIdentity() != "FUNCTION" or new_func->isDeclaredAndDefined()) // Already declared as non-function type or Defined as function
        {
            err_hndlr->handleSemanticError(MULTIPLE_DECLARATION, line_count, new_func->getSymbol());
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
            if (i->getSymbol() == "blank")
            {
                err_hndlr->handleSemanticError(MISSING_PARAM_NAME, line_count, new_func->getSymbol());
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
        new_func->addParam(new Variable(p->getSymbol(), p->getDataType()));
    }

    if (!table->insert(new_func))
    {
        Identifier *id = (Identifier *)table->search(id_name);
        if (id->getIdentity() != "FUNCTION") // Already declared as non-function type or Defined as function
        {
            err_hndlr->handleSemanticError(MULTIPLE_DECLARATION, line_count, id_name);
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
        err_hndlr->handleSemanticError(UNDECLARED_FUNCTION, line_count, id_name);
        return "NULL";
    }

    if (id->getIdentity() != "FUNCTION")
    {
        err_hndlr->handleSemanticError(NOT_FUNCTION, line_count, id_name);
        return "NULL";
    }

    Function *func = (Function *)id;
    // cout << func->isDeclaredAndDefined() << endl;
    if (func->isDeclaredNotDefined())
    {
        err_hndlr->handleSemanticError(UNDEFINED_FUNCTION, line_count, id_name);
    }
    else if (func->getNumberOfParams() < args.size())
    {
        err_hndlr->handleSemanticError(TOO_MANY_ARGUMENTS, line_count, id_name);
    }
    else if (func->getNumberOfParams() > args.size())
    {
        err_hndlr->handleSemanticError(TOO_FEW_ARGUMENTS, line_count, id_name);
    }
    else
    {
        vector<Variable *> params = func->getParams();
        for (int i = 0; i < params.size(); i++)
        {
            if (!isConvertible(params[i]->getDataType(), args[i]->getDataType()))
            {
                err_hndlr->handleSemanticError(ARGUMENT_TYPE_MISMATCH, line_count, id_name);
                break;
            }
        }
    }
    return func->getReturnType();
}

void SemanticAnalyzer::declareVariable(string data_type, string var_name)
{
    Variable *var = new Variable(var_name, data_type);

    if (!table->insert(var)) // already present in current scope
    {
        err_hndlr->handleSemanticError(MULTIPLE_DECLARATION, line_count, var_name);
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
        err_hndlr->handleSemanticError(MULTIPLE_DECLARATION, line_count, arr_name);
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
        err_hndlr->handleSemanticError(VOID_VARIABLE, line_count, id_names);
    }
    else
    {
        for (auto &var : vars)
        {
            if (var->getVarType() == "ARRAY")
            {
                Array *arr = (Array *)var;
                declareArray(data_type, arr->getSymbol(), arr->getArraySize());
            }
            else
            {
                declareVariable(data_type, var->getSymbol());
            }
        }
    }
}

string SemanticAnalyzer::callVariable(string var_name)
{
    Identifier *id = (Identifier *)table->search(var_name);

    if (id == NULL)
    {
        err_hndlr->handleSemanticError(UNDECLARED_VARIABLE, line_count, var_name);
        return "NULL";
    }
    else
    {
        if (id->getIdentity() != "VARIABLE")
        {
            err_hndlr->handleSemanticError(TYPE_MISMATCH, line_count, var_name + " is not a variable"); // should i change this to indexing
            return "NULL";
        }

        Variable *var = (Variable *)id;
        if (var->getVarType() == "ARRAY")
        {
            err_hndlr->handleSemanticError(TYPE_MISMATCH, line_count, var_name + " is an array"); // should i change this to indexing
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
        err_hndlr->handleSemanticError(UNDECLARED_VARIABLE, line_count, arr_name);
        return "NULL";
    }
    else
    {
        if (id->getIdentity() != "VARIABLE")
        {
            err_hndlr->handleSemanticError(TYPE_MISMATCH, line_count, arr_name + " is not a variable");
            return "NULL";
        }

        Variable *var = (Variable *)id;
        if (var->getVarType() != "ARRAY")
        {
            err_hndlr->handleSemanticError(TYPE_MISMATCH, line_count, arr_name + " is not an array"); // should i change this to indexing
            return "NULL";
        }
        if (index->getDataType() != "int")
        {
            err_hndlr->handleSemanticError(INVALID_ARRAY_INDEX, line_count, index->getSymbol());
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
            err_hndlr->handleSemanticError(INVALID_OPERAND, line_count, "of types '" + left->getDataType() + "' and '" + right->getDataType() + "' to 'operator='");
            return "NULL";
        }
        else
        {
            err_hndlr->handleSemanticError(INVALID_CONVERSION, line_count, "from '" + right->getDataType() + "' to '" + left->getDataType() + "'");
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
                err_hndlr->handleSemanticError(INVALID_OPERAND, line_count, "of types '" + left->getDataType() + "' and '" + right->getDataType() + "' to 'operator" + op + "'");
            }
            else
            {
                err_hndlr->handleSemanticError(INCOMPATIBLE_OPERAND, line_count);
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
                err_hndlr->handleSemanticError(INVALID_OPERAND, line_count, "of types '" + left->getDataType() + "' and '" + right->getDataType() + "' to 'operator" + op + "'");
            }
            else
            {
                err_hndlr->handleSemanticError(INCOMPATIBLE_OPERAND, line_count);
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
                err_hndlr->handleSemanticError(INVALID_OPERAND, line_count, "of types '" + left->getDataType() + "' and '" + right->getDataType() + "' to 'operator" + op + "'");
            }
            else
            {
                err_hndlr->handleSemanticError(INCOMPATIBLE_OPERAND, line_count);
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
            err_hndlr->handleSemanticError(MOD_BY_ZERO, line_count, right->getExpression() + "%" + right->getExpression());
            return "NULL";
        }
        else
        {
            if (type != "int")
            {
                err_hndlr->handleSemanticError(INVALID_OPERAND, line_count, "of types '" + left->getDataType() + "' and '" + right->getDataType() + "' to 'operator" + op + "'");
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
                err_hndlr->handleSemanticError(INVALID_OPERAND, line_count, "of types '" + left->getDataType() + "' and '" + right->getDataType() + "' to 'operator" + op + "'");
            }
            else
            {
                err_hndlr->handleSemanticError(INCOMPATIBLE_OPERAND, line_count);
            }
            return "NULL";
        }
    }
    else
    {
        return "NULL";
    }
}

void SemanticAnalyzer::setCurrentExp(Expression *exp)
{
    this->curr_exp = exp;
}