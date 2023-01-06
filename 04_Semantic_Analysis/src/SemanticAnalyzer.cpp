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

string SemanticAnalyzer::implicitTypecast(string left, string right)
{
    // cout << left << "," << right << endl;
    if (left == "NULL" || right == "NULL")
    {
        return "NULL"; // already reported , now supressing more errors
    }
    if (left == "VOID" || right == "VOID")
    {
        return "ERROR";
    }
    if (left == "FLOAT" && right == "FLOAT")
    {
        return "FLOAT";
    }
    if (left == "FLOAT" && right == "INT")
    {
        return "FLOAT";
    }
    if (left == "INT" && right == "FLOAT")
    {
        return "FLOAT";
    }
    if (left == "INT" && right == "INT")
    {
        return "INT";
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
    if (from == "VOID")
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
    if (left == "VOID" || right == "VOID") // Void not allowed
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
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_CONFLICT, lexer->getLineCount(), f2->getSymbol()) << std::endl;
        return;
    }
    if (!f1->matchParamsNum(f2))
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_CONFLICT, lexer->getLineCount(), f2->getSymbol()) << std::endl;
    }
    else if (!f1->matchParamsType(f2))
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_CONFLICT, lexer->getLineCount(), f2->getSymbol()) << std::endl;
    }
}

void SemanticAnalyzer::returnFunction(Expression *ret)
{
    if (ret->getDataType() != curr_func->getReturnType())
    {
        // errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::RETURN_TYPE_MISMATCH, lexer->getLineCount(), curr_func->getSymbol()) << std::endl;
        curr_func = NULL;
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
        if (curr_func->getReturnType() == "VOID" or curr_func->getSymbol() == "main")
        {
            curr_func = NULL;
        }
        else
        {
            // errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::FUNCTION_NOT_RETURNED, lexer->getLineCount(), curr_func->getSymbol()) << std::endl;
            curr_func = NULL;
        }
    }
}

void SemanticAnalyzer::declareFunctionParams()
{
    for (auto i : curr_func->getParams())
    {
        if (i->getSymbol() == "blank")
            continue;
        Variable *var = new Variable(i->getSymbol(), Util::toUpper(i->getDataType()));
        if (!table->insert(var))
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::PARAM_REDEFINITION, lexer->getLineCount(), i->getSymbol()) << std::endl;
        }
    }
}

void SemanticAnalyzer::defineFunction(string ret_type, string id_name, vector<Variable *> params)
{
    in_function = true;
    Function *new_func = new Function(id_name);
    new_func->setReturnType(Util::toUpper(ret_type));
    for (auto p : params)
    {
        new_func->addParam(new Variable(p->getSymbol(), Util::toUpper(p->getDataType())));
    }

    if (!table->insert(new_func))
    {
        Identifier *id = (Identifier *)table->find(new_func->getSymbol());
        if (id->getIdentity() != "FUNCTION") // Already declared as non-function type or Defined as function
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::DIFF_DECLARATION, lexer->getLineCount(), new_func->getSymbol()) << std::endl;
        }
        else
        {
            Function *func = (Function *)id;
            if (func->isDeclaredAndDefined())
            {
            }
            else
            {
                func->defineFunction();
            }
            matchTwoFunction(func, new_func);
        }
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
    curr_func = new_func;
}

void SemanticAnalyzer::declareFunction(string ret_type, string id_name, vector<Variable *> params)
{
    Function *new_func = new Function(id_name);

    new_func->setReturnType(Util::toUpper(ret_type));
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
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::UNDECLARED_FUNCTION, lexer->getLineCount(), id_name) << std::endl;
        return "NULL";
    }

    if (id->getIdentity() != "FUNCTION")
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::NOT_FUNCTION, lexer->getLineCount(), id_name) << std::endl;
        return "NULL";
    }

    Function *func = (Function *)id;
    // cout << func->isDeclaredAndDefined() << endl;
    if (func->isDeclaredNotDefined())
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::UNDEFINED_FUNCTION, lexer->getLineCount(), id_name) << std::endl;
    }
    else if (func->getNumberOfParams() < args.size())
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
            // std::cerr << lexer->getLineCount() << " " << params[i]->getDataType() << " " << args[i]->getDataType() << std::endl;
            if (params[i]->getDataType() != args[i]->getDataType())
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
    }
    else
    {
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
    }
    else
    {
        // table->printAllScope();
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
            // errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_MISMATCH, lexer->getLineCount(), var_name + " is an array") << std::endl;
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
    // cout << left << endl;
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
                return "INT";
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
    errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::NESTED_FUNCTION, lexer->getLineCount()) << std::endl;
}

void SemanticAnalyzer::handlePrintfCall(std::string id_name)
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
    if (in_function)
    {
        this->declareFunctionParams();
        in_function = false;
    }
}
void SemanticAnalyzer::checkArraySize(Terminal *size)
{
    // std::cout << size->getSymbol() << " " << size->getTerminalType() << std::endl;
    if (size->getTerminalType() == "CONST_FLOAT")
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INVALID_ARRAY_SIZE, lexer->getLineCount(), size->getSymbol()) << std::endl;
    }
}