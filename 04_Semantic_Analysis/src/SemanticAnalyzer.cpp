/**
 * Author: Mahir Labib Dihan
 * Last modified: January 18, 2023
 */
#include <string>
#include "../include/SymbolInfo.hpp"
#include "../include/ErrorHandler.hpp"
#include "../include/SymbolTable.hpp"
#include "../include/SemanticAnalyzer.hpp"
#include "../include/Util.hpp"
using namespace std;

SemanticAnalyzer::SemanticAnalyzer(LexicalAnalyzer *lexer, SymbolTable *table, ErrorHandler *error_hndlr, ofstream &log, ofstream &error) : logout(log), errorout(error)
{
    this->lexer = lexer;
    this->table = table;
    this->error_hndlr = error_hndlr;
}
SemanticAnalyzer::~SemanticAnalyzer()
{
}

// If there is error in any expression, we will return "ERROR"
// After printing error we will set "NULL" to that expression
// And we will generate any further error due that expression
string SemanticAnalyzer::implicitTypecast(string left, string right)
{
    if (left == "NULL" || right == "NULL")
    {
        return "NULL"; // already reported , now supressing more errors
    }
    if (left == "FLOAT" && right == "INT")
    {
        return "FLOAT";
    }
    if (left == "INT" && right == "FLOAT")
    {
        return "FLOAT";
    }
    if (Util::getDataSize(left) < 1 || Util::getDataSize(right) < 1) // Checking for void or array type
    {
        return "ERROR";
    }
    if (left == right) // covers int,float
    {
        return left;
    }
    return "ERROR";
}

bool SemanticAnalyzer::checkAssignment(string left, string right)
{
    if (left == "NULL" || right == "NULL")
    {
        return true; // already error reported and converted to NULL , this is made true to supress more error
    }
    // Left can't be void, since left is a variable. And we are not inserting void variable in symbol table
    if (left == "VOID" || right == "VOID") // Void not allowed
    {
        return false;
    }
    if (left == "" || right == "") // Not an expression/variable
    {
        return false;
    }
    if (Util::getDataSize(left) < 1 || Util::getDataSize(right) < 1)
    {
        return false;
    }
    return (Util::getDataSize(left) >= Util::getDataSize(right));
}

bool SemanticAnalyzer::matchTwoFunction(Function *f1, Function *f2)
{
    if (!f1->matchReturnType(f2))
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_CONFLICT, lexer->getLineCount(), f2->getSymbol()) << std::endl;
        return false;
    }
    if (!f1->matchParamsNum(f2))
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_CONFLICT, lexer->getLineCount(), f2->getSymbol()) << std::endl;
        return false;
    }

    if (!f1->matchParamsType(f2))
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_CONFLICT, lexer->getLineCount(), f2->getSymbol()) << std::endl;
        return false;
    }
    return true;
}

void SemanticAnalyzer::returnFunction(Expression *ret)
{
    if (!functions.empty())
    {
        if (ret->getDataType() != "NULL" && ret->getDataType() != functions.top()->getReturnType())
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::RETURN_TYPE_MISMATCH, lexer->getLineCount(), functions.top()->getSymbol()) << std::endl;
        }
    }
    else
    {
        // No function to return
    }
}
void SemanticAnalyzer::endFunction()
{
    if (!functions.empty())
    {
        this->popFunction();
    }
    else
    {
        // No function to end
    }
}

void SemanticAnalyzer::declareFunctionParams()
{
    for (auto i : functions.top()->getParams())
    {
        if (i->getSymbol() == "blank")
            continue;
        Variable *var = new Variable(i->getSymbol(), Util::toUpper(i->getDataType()));
        if (!table->insert(var))
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::PARAM_REDEFINITION, lexer->getLineCount(), i->getSymbol()) << std::endl;
            delete var;
            break;
        }
        else
        {
        }
    }
}

void SemanticAnalyzer::pushFunction(string ret_type, string func_name, vector<Variable *> params)
{
    Function *func = new Function(func_name, Util::toUpper(ret_type));
    for (auto p : params)
    {
        func->addParam(new Variable(p->getSymbol(), Util::toUpper(p->getDataType())));
    }
    functions.push(func);
}
void SemanticAnalyzer::popFunction()
{
    delete functions.top();
    functions.pop();
}

void SemanticAnalyzer::defineFunction(string ret_type, string id_name, vector<Variable *> params)
{
    if (!functions.empty())
    {
        handleInvalidFunctionScoping();
    }

    // Creating a Function to insert into table
    Function *new_func = new Function(id_name, Util::toUpper(ret_type));
    for (auto p : params)
    {
        new_func->addParam(new Variable(p->getSymbol(), Util::toUpper(p->getDataType())));
    }

    if (!table->insert(new_func)) // Couldn't insert
    {
        Identifier *id = (Identifier *)table->find(new_func->getSymbol());
        if (id->getIdentity() != "FUNCTION") // Already declared as non-function type
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::DIFF_DECLARATION, lexer->getLineCount(), new_func->getSymbol()) << std::endl;
        }
        else // or Defined as function
        {
            Function *func = (Function *)id;
            if (func->isDeclaredAndDefined())
            {
                if (matchTwoFunction(func, new_func))
                {
                    errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::MULTIPLE_DEFINITION, lexer->getLineCount(), new_func->getSymbol()) << std::endl;
                }
            }
            else // declared but not defined
            {
                if (matchTwoFunction(func, new_func))
                {
                    func->defineFunction();
                }
            }
        }
        delete new_func;
    }
    else
    {
        for (auto &i : params)
        {
            if (i->getSymbol() == "blank")
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::MISSING_PARAM_NAME, lexer->getLineCount(), new_func->getSymbol()) << std::endl;
            }
        }
        new_func->defineFunction();
    }

    // Creating a track of current function
    this->pushFunction(ret_type, id_name, params);
}

void SemanticAnalyzer::declareFunction(string ret_type, string id_name, vector<Variable *> params)
{
    if (!functions.empty())
    {
        handleInvalidFunctionScoping();
    }
    Function *new_func = new Function(id_name, Util::toUpper(ret_type));

    for (auto p : params)
    {
        new_func->addParam(new Variable(p->getSymbol(), Util::toUpper(p->getDataType())));
    }

    if (!table->insert(new_func))
    {
        Identifier *id = (Identifier *)table->find(id_name);
        if (id->getIdentity() != "FUNCTION") // Already declared as non-function type or Defined as function
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::DIFF_DECLARATION, lexer->getLineCount(), id_name) << std::endl;
        }
        else
        {
            Function *func = (Function *)id;
            matchTwoFunction(func, new_func);
        }
        delete new_func;
    }
    else
    {
        /** Function inserted successfully **/
    }
}

string SemanticAnalyzer::callFunction(string id_name, vector<Expression *> args)
{
    Identifier *id = (Identifier *)table->find(id_name);
    if (id == NULL)
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::UNDECLARED_FUNCTION, lexer->getLineCount(), id_name) << std::endl;
        return "NULL";
    }

    if (id->getIdentity() != "FUNCTION")
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::NOT_FUNCTION, lexer->getLineCount(), id_name) << std::endl;
        return "NULL";
    }

    Function *func = (Function *)id;

    if (func->getNumberOfParams() < args.size())
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TOO_MANY_ARGUMENTS, lexer->getLineCount(), id_name) << std::endl;
    }
    else if (func->getNumberOfParams() > args.size())
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TOO_FEW_ARGUMENTS, lexer->getLineCount(), id_name) << std::endl;
    }
    else
    {
        vector<Variable *> params = func->getParams();
        for (int i = 0; i < params.size(); i++)
        {
            if (args[i]->getDataType() != "NULL" && params[i]->getDataType() != args[i]->getDataType())
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::ARGUMENT_TYPE_MISMATCH, lexer->getLineCount(), std::to_string(i + 1) + " of '" + id_name + "'") << std::endl;
            }
        }
    }
    return func->getReturnType();
}

void SemanticAnalyzer::declareVariable(string data_type, string var_name)
{
    Variable *var = new Variable(var_name, Util::toUpper(data_type));

    if (!table->insert(var)) // already present in current scope
    {
        Identifier *old_id = (Identifier *)table->find(var_name);
        if (old_id->getIdentity() == "FUNCTION")
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::DIFF_DECLARATION, lexer->getLineCount(), var_name) << std::endl;
        }
        else
        {
            Variable *old_var = (Variable *)old_id;
            if (old_var->getVarType() == "ARRAY")
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_CONFLICT, lexer->getLineCount(), var_name) << std::endl;
            }
            else if (old_var->getDataType() != var->getDataType())
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_CONFLICT, lexer->getLineCount(), var_name) << std::endl;
            }
            else
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::MULTIPLE_DECLARATION, lexer->getLineCount(), var_name) << std::endl;
            }
        }
        delete var;
    }
    else
    {
        /** Variable inserted successfully **/
    }
}
void SemanticAnalyzer::declareArray(string data_type, string arr_name, string arr_size)
{
    Array *arr = new Array(arr_name, Util::toUpper(data_type), arr_size);
    if (!table->insert(arr)) // already present in current scope
    {
        Identifier *old_id = (Identifier *)table->find(arr_name);
        if (old_id->getIdentity() == "FUNCTION")
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::DIFF_DECLARATION, lexer->getLineCount(), arr_name) << std::endl;
        }
        else
        {
            Variable *old_var = (Variable *)old_id;
            if (old_var->getVarType() != "ARRAY")
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_CONFLICT, lexer->getLineCount(), arr_name) << std::endl;
            }
            else
            {
                Array *old_arr = (Array *)old_var;
                if (old_arr->getDataType() != arr->getDataType())
                {
                    errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_CONFLICT, lexer->getLineCount(), arr_name) << std::endl;
                }
                else if (old_arr->getArraySize() != arr->getArraySize())
                {
                    errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_CONFLICT, lexer->getLineCount(), arr_name) << std::endl;
                }
                else
                {
                    errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::MULTIPLE_DECLARATION, lexer->getLineCount(), arr_name) << std::endl;
                }
            }
        }
        delete arr;
    }
    else
    {
        /** Array inserted successfully **/
    }
}
void SemanticAnalyzer::declareVariables(string data_type, string id_names, vector<Variable *> vars)
{
    if (data_type == "void")
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::VOID_VARIABLE, lexer->getLineCount(), id_names) << std::endl;
    }
    else
    {
        for (auto &var : vars)
        {
            if (var->getVarType() == "ARRAY")
            {
                Array *arr = (Array *)var;
                declareArray(Util::toUpper(data_type), arr->getSymbol(), arr->getArraySize());
            }
            else
            {
                declareVariable(Util::toUpper(data_type), var->getSymbol());
            }
        }
    }
}

string SemanticAnalyzer::callVariable(string var_name)
{
    Identifier *id = (Identifier *)table->find(var_name);

    if (id == NULL)
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::UNDECLARED_VARIABLE, lexer->getLineCount(), var_name) << std::endl;
        return "NULL";
    }
    else
    {
        if (id->getIdentity() != "VARIABLE")
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_MISMATCH, lexer->getLineCount(), var_name + " is not a variable") << std::endl;
            return "NULL";
        }

        Variable *var = (Variable *)id;
        if (var->getVarType() == "ARRAY")
        {
            return "ARRAY_" + var->getDataType();
        }

        return var->getDataType();
    }
}

string SemanticAnalyzer::callArray(string arr_name, Expression *index)
{
    Identifier *id = (Identifier *)table->find(arr_name);

    if (id == NULL)
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::UNDECLARED_VARIABLE, lexer->getLineCount(), arr_name) << std::endl;
        return "NULL";
    }
    else
    {
        if (id->getIdentity() != "VARIABLE")
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_MISMATCH, lexer->getLineCount(), arr_name + " is not a variable") << std::endl;
            return "NULL";
        }

        Variable *var = (Variable *)id;
        if (var->getVarType() != "ARRAY")
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::NOT_ARRAY, lexer->getLineCount(), arr_name) << std::endl;
            return "NULL";
        }
        if (index->getDataType() != "INT")
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INVALID_ARRAY_INDEX, lexer->getLineCount(), index->getSymbol()) << std::endl;
        }
        return var->getDataType();
    }
}

string SemanticAnalyzer::assignOp(Expression *left, Expression *right)
{
    if (!checkAssignment(left->getDataType(), right->getDataType()))
    {
        if (left->getDataType() == "VOID" || right->getDataType() == "VOID")
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::VOID_FUNCTION_EXP, lexer->getLineCount(), "of types '" + left->getDataType() + "' and '" + right->getDataType() + "' to 'operator='") << std::endl;
            return "NULL";
        }
        else
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INVALID_CONVERSION, lexer->getLineCount(), "from '" + right->getDataType() + "' to '" + left->getDataType() + "'") << std::endl;
            return "NULL";
        }
    }
    else
    {
        if (left->getDataType() == "INT" && right->getDataType() == "FLOAT")
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::DATA_LOSS, lexer->getLineCount(), right->getDataType() + " to " + left->getDataType()) << std::endl;
        }
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
            return "INT";
        }
        else
        {
            if (left->getDataType() == "VOID" || right->getDataType() == "VOID")
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::VOID_FUNCTION_EXP, lexer->getLineCount(), "of types '" + left->getDataType() + "' and '" + right->getDataType() + "' to 'operator" + op + "'") << std::endl;
            }
            else
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INCOMPATIBLE_OPERAND, lexer->getLineCount()) << std::endl;
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
            return "INT";
        }
        else
        {
            if (left->getDataType() == "VOID" || right->getDataType() == "VOID")
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::VOID_FUNCTION_EXP, lexer->getLineCount(), "of types '" + left->getDataType() + "' and '" + right->getDataType() + "' to 'operator" + op + "'") << std::endl;
            }
            else
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INCOMPATIBLE_OPERAND, lexer->getLineCount()) << std::endl;
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
            if (left->getDataType() == "VOID" || right->getDataType() == "VOID")
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::VOID_FUNCTION_EXP, lexer->getLineCount(), "of types '" + left->getDataType() + "' and '" + right->getDataType() + "' to 'operator" + op + "'") << std::endl;
            }
            else
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INCOMPATIBLE_OPERAND, lexer->getLineCount()) << std::endl;
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
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::MOD_BY_ZERO, lexer->getLineCount(), right->getExpression() + "%" + right->getExpression()) << std::endl;
            return "NULL";
        }
        else
        {
            if (type != "INT")
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::NONINT_MOD, lexer->getLineCount(), "of types '" + left->getDataType() + "' and '" + right->getDataType() + "' to 'operator" + op + "'") << std::endl;
                return "NULL";
            }
            else
            {
                return type;
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
            if (left->getDataType() == "VOID" || right->getDataType() == "VOID")
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::VOID_FUNCTION_EXP, lexer->getLineCount(), "of types '" + left->getDataType() + "' and '" + right->getDataType() + "' to 'operator" + op + "'") << std::endl;
            }
            else
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INCOMPATIBLE_OPERAND, lexer->getLineCount()) << std::endl;
            }
            return "NULL";
        }
    }
    else
    {
        return "NULL";
    }
}

int SemanticAnalyzer::getLineCount()
{
    return lexer->getLineCount();
}

void SemanticAnalyzer::handleInvalidFunctionScoping()
{
    errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::NESTED_FUNCTION, lexer->getLineCount(), functions.top()->getSymbol()) << std::endl;
}

void SemanticAnalyzer::handlePrintlnCall(std::string id_name)
{
    Identifier *id = (Identifier *)table->find(id_name);
    if (id == NULL)
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::UNDECLARED_VARIABLE, lexer->getLineCount(), id_name) << std::endl;
    }
    else if (id->getIdentity() == "FUNCTION")
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::UNDECLARED_VARIABLE, lexer->getLineCount(), id_name) << std::endl;
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
    if (!functions.empty())
    {
        this->declareFunctionParams();
    }
}

void SemanticAnalyzer::setParseTreeRoot(NonTerminal *root)
{
    this->tree_root = root;
}

NonTerminal *SemanticAnalyzer::getParseTreeRoot()
{
    return this->tree_root;
}
