#include <string>
#include "../include/SymbolInfo.hpp"
#include "../include/ErrorHandler.hpp"
#include "../include/SymbolTable.hpp"
#include "../include/SemanticAnalyzer.hpp"
#include "../include/Util.hpp"
using namespace std;

extern bool in_function;
SemanticAnalyzer::SemanticAnalyzer(LexicalAnalyzer *lexer, SymbolTable *table, ErrorHandler *error_hndlr)
{
    this->lexer = lexer;
    this->table = table;
    this->error_hndlr = error_hndlr;
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

    // Add conversion in syntax tree
    return Util::getDataSize(to) >= Util::getDataSize(from);
}

bool SemanticAnalyzer::checkAssignment(string left, string right)
{
    // cout << lexer->getLineCount() << " " << left << " " << right << endl;
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

    return (Util::getDataSize(left) >= Util::getDataSize(left));
}

void SemanticAnalyzer::matchTwoFunction(Function *f1, Function *f2)
{
    if (!f1->matchReturnType(f2))
    {
        error_hndlr->handleSemanticError(ErrorHandler::SemanticError::RETURN_TYPE_MISMATCH, lexer->getLineCount(), f2->getSymbol());
    }
    if (!f1->matchParamsNum(f2))
    {
        error_hndlr->handleSemanticError(ErrorHandler::SemanticError::PARAM_NUMBER_MISMATCH, lexer->getLineCount(), f2->getSymbol());
    }
    else if (!f1->matchParamsType(f2))
    {
        error_hndlr->handleSemanticError(ErrorHandler::SemanticError::PARAM_TYPE_MISMATCH, lexer->getLineCount(), f2->getSymbol());
    }
}

void SemanticAnalyzer::returnFunction(Expression *ret)
{
    if (ret->getDataType() != curr_func->getReturnType())
    {
        error_hndlr->handleSemanticError(ErrorHandler::SemanticError::RETURN_TYPE_MISMATCH, lexer->getLineCount(), curr_func->getSymbol());
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
            curr_func = NULL;
        }
        else
        {
            error_hndlr->handleSemanticError(ErrorHandler::SemanticError::FUNCTION_NOT_RETURNED, lexer->getLineCount(), curr_func->getSymbol());
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
            error_hndlr->handleSemanticError(ErrorHandler::SemanticError::MULTIPLE_DECLARATION, lexer->getLineCount(), i->getSymbol());
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
        Identifier *id = (Identifier *)table->find(new_func->getSymbol());
        if (id->getIdentity() != "FUNCTION" or new_func->isDeclaredAndDefined()) // Already declared as non-function type or Defined as function
        {
            error_hndlr->handleSemanticError(ErrorHandler::SemanticError::MULTIPLE_DECLARATION, lexer->getLineCount(), new_func->getSymbol());
        }
        else
        {
            Function *func = (Function *)id;
            func->defineFunction();
            matchTwoFunction(func, new_func);
            curr_func = func;
        }
    }
    else
    {
        for (auto &i : params)
        {
            if (i->getSymbol() == "blank")
            {
                error_hndlr->handleSemanticError(ErrorHandler::SemanticError::MISSING_PARAM_NAME, lexer->getLineCount(), new_func->getSymbol());
            }
        }

        curr_func = new_func;
        new_func->defineFunction();
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
        Identifier *id = (Identifier *)table->find(id_name);
        if (id->getIdentity() != "FUNCTION") // Already declared as non-function type or Defined as function
        {
            error_hndlr->handleSemanticError(ErrorHandler::SemanticError::MULTIPLE_DECLARATION, lexer->getLineCount(), id_name);
        }
        else
        {
            Function *func = (Function *)id;
            matchTwoFunction(func, new_func);
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
    Identifier *id = (Identifier *)table->find(id_name);
    if (id == NULL)
    {
        error_hndlr->handleSemanticError(ErrorHandler::SemanticError::UNDECLARED_FUNCTION, lexer->getLineCount(), id_name);
        return "NULL";
    }

    if (id->getIdentity() != "FUNCTION")
    {
        error_hndlr->handleSemanticError(ErrorHandler::SemanticError::NOT_FUNCTION, lexer->getLineCount(), id_name);
        return "NULL";
    }

    Function *func = (Function *)id;
    // cout << func->isDeclaredAndDefined() << endl;
    if (func->isDeclaredNotDefined())
    {
        error_hndlr->handleSemanticError(ErrorHandler::SemanticError::UNDEFINED_FUNCTION, lexer->getLineCount(), id_name);
    }
    else if (func->getNumberOfParams() < args.size())
    {
        error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TOO_MANY_ARGUMENTS, lexer->getLineCount(), id_name);
    }
    else if (func->getNumberOfParams() > args.size())
    {
        error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TOO_FEW_ARGUMENTS, lexer->getLineCount(), id_name);
    }
    else
    {
        vector<Variable *> params = func->getParams();
        for (int i = 0; i < params.size(); i++)
        {
            if (!isConvertible(params[i]->getDataType(), args[i]->getDataType()))
            {
                error_hndlr->handleSemanticError(ErrorHandler::SemanticError::ARGUMENT_TYPE_MISMATCH, lexer->getLineCount(), id_name);
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
        error_hndlr->handleSemanticError(ErrorHandler::SemanticError::MULTIPLE_DECLARATION, lexer->getLineCount(), var_name);
    }
    else
    {
    }
}
void SemanticAnalyzer::declareArray(string data_type, string arr_name, string arr_size)
{
    Array *arr = new Array(arr_name, data_type, arr_size);

    if (!table->insert(arr)) // already present in current scope
    {
        error_hndlr->handleSemanticError(ErrorHandler::SemanticError::MULTIPLE_DECLARATION, lexer->getLineCount(), arr_name);
    }
    else
    {
        table->printAllScope();
    }
}
void SemanticAnalyzer::declareVariables(string data_type, string id_names, vector<Variable *> vars)
{
    if (data_type == "void")
    {
        error_hndlr->handleSemanticError(ErrorHandler::SemanticError::VOID_VARIABLE, lexer->getLineCount(), id_names);
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
    Identifier *id = (Identifier *)table->find(var_name);

    if (id == NULL)
    {
        error_hndlr->handleSemanticError(ErrorHandler::SemanticError::UNDECLARED_VARIABLE, lexer->getLineCount(), var_name);
        return "NULL";
    }
    else
    {
        if (id->getIdentity() != "VARIABLE")
        {
            error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_MISMATCH, lexer->getLineCount(), var_name + " is not a variable"); // should i change this to indexing
            return "NULL";
        }

        Variable *var = (Variable *)id;
        if (var->getVarType() == "ARRAY")
        {
            error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_MISMATCH, lexer->getLineCount(), var_name + " is an array"); // should i change this to indexing
            return "NULL";
        }
        return var->getDataType();
    }
}

string SemanticAnalyzer::callArray(string arr_name, Expression *index)
{

    Identifier *id = (Identifier *)table->find(arr_name);

    if (id == NULL)
    {
        error_hndlr->handleSemanticError(ErrorHandler::SemanticError::UNDECLARED_VARIABLE, lexer->getLineCount(), arr_name);
        return "NULL";
    }
    else
    {
        if (id->getIdentity() != "VARIABLE")
        {
            error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_MISMATCH, lexer->getLineCount(), arr_name + " is not a variable");
            return "NULL";
        }

        Variable *var = (Variable *)id;
        if (var->getVarType() != "ARRAY")
        {
            error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_MISMATCH, lexer->getLineCount(), arr_name + " is not an array");
            return "NULL";
        }
        if (index->getDataType() != "int")
        {
            error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INVALID_ARRAY_INDEX, lexer->getLineCount(), index->getSymbol());
        }
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
            error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INVALID_OPERAND, lexer->getLineCount(), "of types '" + left->getDataType() + "' and '" + right->getDataType() + "' to 'operator='");
            return "NULL";
        }
        else
        {
            error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INVALID_CONVERSION, lexer->getLineCount(), "from '" + right->getDataType() + "' to '" + left->getDataType() + "'");
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
            return "int";
        }
        else
        {
            if (left->getDataType() == "void" || right->getDataType() == "void")
            {
                error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INVALID_OPERAND, lexer->getLineCount(), "of types '" + left->getDataType() + "' and '" + right->getDataType() + "' to 'operator" + op + "'");
            }
            else
            {
                error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INCOMPATIBLE_OPERAND, lexer->getLineCount());
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
            return "int";
        }
        else
        {
            if (left->getDataType() == "void" || right->getDataType() == "void")
            {
                error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INVALID_OPERAND, lexer->getLineCount(), "of types '" + left->getDataType() + "' and '" + right->getDataType() + "' to 'operator" + op + "'");
            }
            else
            {
                error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INCOMPATIBLE_OPERAND, lexer->getLineCount());
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
                error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INVALID_OPERAND, lexer->getLineCount(), "of types '" + left->getDataType() + "' and '" + right->getDataType() + "' to 'operator" + op + "'");
            }
            else
            {
                error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INCOMPATIBLE_OPERAND, lexer->getLineCount());
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
            error_hndlr->handleSemanticError(ErrorHandler::SemanticError::MOD_BY_ZERO, lexer->getLineCount(), right->getExpression() + "%" + right->getExpression());
            return "NULL";
        }
        else
        {
            if (type != "int")
            {
                error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INVALID_OPERAND, lexer->getLineCount(), "of types '" + left->getDataType() + "' and '" + right->getDataType() + "' to 'operator" + op + "'");
                return "NULL";
            }
            else
            {
                return "int";
            }
        }
    }
    else if (type != "NULL")
    {
        if (type != "ERROR")
        {
            return type;
        }
        else
        {
            if (left->getDataType() == "void" || right->getDataType() == "void")
            {
                error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INVALID_OPERAND, lexer->getLineCount(), "of types '" + left->getDataType() + "' and '" + right->getDataType() + "' to 'operator" + op + "'");
            }
            else
            {
                error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INCOMPATIBLE_OPERAND, lexer->getLineCount());
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

int SemanticAnalyzer::getLineCount()
{
    return lexer->getLineCount();
}

void SemanticAnalyzer::handleInvalidFunctionScoping()
{
    error_hndlr->handleSemanticError(ErrorHandler::SemanticError::NESTED_FUNCTION, lexer->getLineCount());
}

void SemanticAnalyzer::handlePrintfCall(std::string id_name)
{
    Identifier *id = (Identifier *)table->find(id_name);
    if (id == NULL)
    {
        error_hndlr->handleSemanticError(ErrorHandler::SemanticError::UNDECLARED_VARIABLE, lexer->getLineCount(), id_name);
    }
    else if (id->getIdentity() == "FUNCTION")
    {
        error_hndlr->handleSemanticError(ErrorHandler::SemanticError::UNDECLARED_VARIABLE, lexer->getLineCount(), id_name);
    }
    else
    {
        Variable *var = (Variable *)id;
    }
}

void SemanticAnalyzer::endScope()
{
    table->printAllScope();
    table->exitScope();
}

void SemanticAnalyzer::startScope()
{
    table->enterScope();
    if (in_function)
    {
        this->declareFunctionParams();
        in_function = false;
    }
}
void SemanticAnalyzer::checkArraySize(Expression *size)
{
    if (size->getDataType() == "float")
    {
        error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INVALID_ARRAY_SIZE, lexer->getLineCount(), size->getSymbol());
    }
}