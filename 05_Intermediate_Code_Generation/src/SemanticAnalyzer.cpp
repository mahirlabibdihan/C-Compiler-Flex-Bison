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

void SemanticAnalyzer::declareFunctionParams(vector<Variable *> params)
{
    for (auto i : params)
    {
        if (i->getSymbol() == "blank")
            continue;
        Variable *var = new Variable(i->getSymbol(), i->getDataType());
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

void SemanticAnalyzer::defineFunction(string ret_type, string id_name, vector<Variable *> params)
{
    // Creating a Function to insert into table
    Function *new_func = new Function(id_name, ret_type);
    for (auto p : params)
    {
        new_func->addParam(new Variable(p->getSymbol(), p->getDataType()));
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
    // this->pushFunction(ret_type, id_name, params);
}

void SemanticAnalyzer::declareFunction(string ret_type, string id_name, vector<Variable *> params)
{
    Function *new_func = new Function(id_name, ret_type);

    for (auto p : params)
    {
        new_func->addParam(new Variable(p->getSymbol(), p->getDataType()));
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
    Variable *var = new Variable(var_name, data_type);

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
    Array *arr = new Array(arr_name, data_type, arr_size);
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
void SemanticAnalyzer::declareVariables(string data_type, vector<Variable *> vars)
{
    if (data_type == "void")
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::VOID_VARIABLE, lexer->getLineCount()) << std::endl;
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

string SemanticAnalyzer::assignOp(const string &left, const string &right)
{
    if (!checkAssignment(left, right))
    {
        if (left == "VOID" || right == "VOID")
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::VOID_FUNCTION_EXP, lexer->getLineCount(), "of types '" + left + "' and '" + right + "' to 'operator='") << std::endl;
            return "NULL";
        }
        else
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INVALID_CONVERSION, lexer->getLineCount(), "from '" + right + "' to '" + left + "'") << std::endl;
            return "NULL";
        }
    }
    else
    {
        if (left == "INT" && right == "FLOAT")
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::DATA_LOSS, lexer->getLineCount(), right + " to " + left) << std::endl;
        }
        return left;
    }
}

string SemanticAnalyzer::logicOp(const string &left, const string &op, const string &right)
{
    string type = implicitTypecast(left, right);

    if (type != "NULL")
    {
        if (type != "ERROR")
        {
            return "INT";
        }
        else
        {
            if (left == "VOID" || right == "VOID")
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::VOID_FUNCTION_EXP, lexer->getLineCount(), "of types '" + left + "' and '" + right + "' to 'operator" + op + "'") << std::endl;
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

string SemanticAnalyzer::relOp(const string &left, const string &op, const string &right)
{
    string type = implicitTypecast(left, right);

    if (type != "NULL")
    {
        if (type != "ERROR")
        {
            return "INT";
        }
        else
        {
            if (left == "VOID" || right == "VOID")
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::VOID_FUNCTION_EXP, lexer->getLineCount(), "of types '" + left + "' and '" + right + "' to 'operator" + op + "'") << std::endl;
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

string SemanticAnalyzer::addOp(const string &left, const string &op, const string &right)
{
    string type = implicitTypecast(left, right);

    if (type != "NULL")
    {
        if (type != "ERROR")
        {
            return type;
        }
        else
        {
            if (left == "VOID" || right == "VOID")
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::VOID_FUNCTION_EXP, lexer->getLineCount(), "of types '" + left + "' and '" + right + "' to 'operator" + op + "'") << std::endl;
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

string SemanticAnalyzer::mulOp(const string &left, const string &op, const string &right)
{
    string type = implicitTypecast(left, right);

    if (op == "%") // both operand should be integer
    {
        if (type != "INT")
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::NONINT_MOD, lexer->getLineCount(), "of types '" + left + "' and '" + right + "' to 'operator" + op + "'") << std::endl;
            return "NULL";
        }
        else
        {
            return type;
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
            if (left == "VOID" || right == "VOID")
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::VOID_FUNCTION_EXP, lexer->getLineCount(), "of types '" + left + "' and '" + right + "' to 'operator" + op + "'") << std::endl;
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
}

// void SemanticAnalyzer::setASTRoot(Program *root)
// {
//     this->tree_root = root;
// }

// Program *SemanticAnalyzer::getASTRoot()
// {
//     return this->tree_root;
// }

void SemanticAnalyzer::startProgram(Program *prog)
{
    vector<Unit *> units = prog->getUnits();
    for (Unit *unit : units)
    {
        this->analyzeUnit(unit);
    }
}
void SemanticAnalyzer::analyzeUnit(Unit *unit)
{
    string type = unit->getUnitType();
    if (type == "VARIABLE_DECLARATION")
    {
        analyzeVariableDeclaration((VariableDeclaration *)unit);
    }
    if (type == "FUNCTION_DECLARATION")
    {
        analyzeFunctionDeclaration((FunctionDeclaration *)unit);
    }
    if (type == "FUNCTION_DEFINITION")
    {
        analyzeFunctionDefinition((FunctionDefinition *)unit);
    }
}
string SemanticAnalyzer::analyzeExpression(Expression *expr)
{
    if (expr == NULL)
        return "NULL";

    string type = expr->getExpType();
    if (type == "CALL_EXPRESSION")
    {
        return analyzeCallExpression((CallExpression *)expr);
    }
    if (type == "BINARY_EXPRESSION")
    {
        return analyzeBinaryExpression((BinaryExpression *)expr);
    }
    if (type == "UNARY_EXPRESSION")
    {
        return analyzeUnaryExpression((UnaryExpression *)expr);
    }
} // Unary, Binary, Call

bool isZero(Expression *expr)
{
    if (expr->getExpType() == "CALL_EXPRESSION")
    {
        CallExpression *call_expr = (CallExpression *)expr;
        if (call_expr->getCallType() == "CONSTANT_CALL")
        {
            ConstantCall *const_call = (ConstantCall *)call_expr;
            if (const_call->getLiteral() == "0")
            {
                return true;
            }
        }
    }
    return false;
}
string SemanticAnalyzer::analyzeBinaryExpression(BinaryExpression *bin_expr)
{
    string type = bin_expr->getOpType();
    string left = analyzeExpression(bin_expr->getLeftOpr());
    string right = analyzeExpression(bin_expr->getRightOpr());
    if (type == "ASSIGNOP")
    {
        return assignOp(left, right);
    }
    if (type == "ADDOP")
    {
        return addOp(left, ((AddOp *)bin_expr)->getOperator(), right);
    }
    if (type == "MULOP")
    {
        string data_type = mulOp(left, ((MulOp *)bin_expr)->getOperator(), right);
        if ((bin_expr->getOperator() == "/" || bin_expr->getOperator() == "%") && isZero(bin_expr->getRightOpr()))
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::MOD_BY_ZERO, bin_expr->getStartLine()) << std::endl;
            return "NULL";
        }
        return data_type;
    }
    if (type == "RELOP")
    {
        return relOp(left, ((RelOp *)bin_expr)->getOperator(), right);
    }
    if (type == "LOGICOP")
    {
        return logicOp(left, ((LogicOp *)bin_expr)->getOperator(), right);
    }
}
string SemanticAnalyzer::analyzeUnaryExpression(UnaryExpression *unr_expr)
{
    string type = unr_expr->getOpType();
    string opr = analyzeExpression(unr_expr->getOperand());

    if (type == "UADDOP")
    {
        return opr;
    }
    if (type == "NOTOP")
    {
        return "INT";
    }
    if (type == "INCOP")
    {
        return opr;
    }
    if (type == "DECOP")
    {
        return opr;
    }
}
string SemanticAnalyzer::analyzeCallExpression(CallExpression *call_expr)
{
    string type = call_expr->getCallType();
    if (type == "IDENTIFIER_CALL")
    {
        return analyzeIdentifierCall((IdentifierCall *)call_expr);
    }
    if (type == "CONSTANT_CALL")
    {
        return call_expr->getDataType();
    }
}
string SemanticAnalyzer::analyzeIdentifierCall(IdentifierCall *id_call)
{
    string type = id_call->getIdType();
    if (type == "VARIABLE_CALL")
    {
        return analyzeVariableCall((VariableCall *)id_call);
    }
    if (type == "FUNCTION_CALL")
    {
        return analyzeFunctionCall((FunctionCall *)id_call);
    }
}
string SemanticAnalyzer::analyzeVariableCall(VariableCall *var_call)
{
    string type = var_call->getVarType();
    if (type == "PRIMITIVE_CALL")
    {
        string var_name = var_call->getIdName();
        return callVariable(var_name);
    }
    if (type == "ARRAY_CALL")
    {
        return analyzeArrayCall((ArrayCall *)var_call);
    }
}
string SemanticAnalyzer::analyzeArrayCall(ArrayCall *arr_call)
{
    string arr_name = arr_call->getIdName();
    Expression *index = arr_call->getIndex();
    index->setDataType(analyzeExpression(index));
    return callArray(arr_name, index);
}
string SemanticAnalyzer::analyzeFunctionCall(FunctionCall *func_call)
{
    string func_name = func_call->getIdName(); // Check validity
    vector<Expression *> args = func_call->getArgs();
    for (Expression *e : args)
    {
        e->setDataType(analyzeExpression(e));
    }
    return callFunction(func_name, args);
}
// string SemanticAnalyzer::analyzeConstantCall(ConstantCall *const_call)
// {
//     string type = const_call->getDataType();
//     if (type == "INT")
//     {
//         return type;
//     }
// }
void SemanticAnalyzer::analyzeConditionalStatement(ConditionalStatement *cnd_stmt)
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
void SemanticAnalyzer::analyzeLoopStatement(LoopStatement *loop_stmt)
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
void SemanticAnalyzer::analyzeStatement(Statement *stmt)
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
    }
    if (type == "COMPOUND_STATEMENT")
    {
        analyzeCompoundStatement((CompoundStatement *)stmt);
    }
    if (type == "VARIABLE_DECLARATION")
    {
        analyzeVariableDeclaration((VariableDeclaration *)stmt);
    }
    if (type == "FUNCTION_DEFINITION")
    {
        analyzeFunctionDefinition((FunctionDefinition *)stmt);
    }
    if (type == "FUNCTION_DECLARATION")
    {
        analyzeFunctionDeclaration((FunctionDeclaration *)stmt);
    }
} // Conditional, Loop, Return, Print, Expression
void SemanticAnalyzer::analyzeIfStatement(IfStatement *if_stmt)
{
    analyzeExpression(if_stmt->getCondition());
    analyzeStatement(if_stmt->getIfBody());
}
void SemanticAnalyzer::analyzeIfElseStatement(IfElseStatement *ifelse_stmt)
{
    analyzeExpression(ifelse_stmt->getCondition());
    analyzeStatement(ifelse_stmt->getIfBody());
    analyzeStatement(ifelse_stmt->getElseBody());
}
void SemanticAnalyzer::analyzeForLoop(ForLoop *for_loop)
{
    analyzeExpression(for_loop->getInitialize());
    analyzeExpression(for_loop->getCondition());
    analyzeExpression(for_loop->getIncDec());
    analyzeStatement(for_loop->getBody());
}
void SemanticAnalyzer::analyzeWhileLoop(WhileLoop *while_loop)
{
    analyzeExpression(while_loop->getCondition());
    analyzeStatement(while_loop->getBody());
}
void SemanticAnalyzer::analyzeReturnStatement(ReturnStatement *ret_stmt)
{
    Expression *expr = ret_stmt->getExpression();
    expr->setDataType(analyzeExpression(expr));
}
void SemanticAnalyzer::analyzePrintStatement(PrintStatement *print_stmt)
{
    analyzeVariableCall(print_stmt->getVariableCall());
}

void SemanticAnalyzer::analyzeCompoundStatement(CompoundStatement *stmt_list)
{
    vector<Statement *> list = stmt_list->getStatements();
    for (Statement *stmt : list)
    {
        analyzeStatement(stmt);
    }
}

void SemanticAnalyzer::analyzeExpressionStatement(ExpressionStatement *expr_stmt)
{
    analyzeExpression(expr_stmt->getExpression());
}

void SemanticAnalyzer::analyzeVariableDeclaration(VariableDeclaration *var_decl)
{
    string data_type = var_decl->getDataType();
    vector<Variable *> vars = var_decl->getDeclarationList();
    declareVariables(data_type, vars);
}
void SemanticAnalyzer::analyzeFunctionDeclaration(FunctionDeclaration *func_decl)
{
    string ret_type = func_decl->getReturnType();
    string func_name = func_decl->getFunctionName();
    vector<Variable *> params = func_decl->getParams();
    declareFunction(ret_type, func_name, params);
}
void SemanticAnalyzer::analyzeFunctionDefinition(FunctionDefinition *func_def)
{
    string ret_type = func_def->getReturnType();
    string func_name = func_def->getFunctionName();
    vector<Variable *> params = func_def->getParams();
    vector<Statement *> stmt_list = func_def->getBody();
    defineFunction(ret_type, func_name, params);

    this->startScope();
    declareFunctionParams(params);
    for (Statement *stmt : stmt_list)
    {
        if (stmt != NULL && stmt->getStatementType() == "RETURN_STATEMENT")
        {
            Expression *ret_expr = ((ReturnStatement *)stmt)->getExpression();
            string data_type = analyzeExpression(ret_expr);
            if (data_type != "NULL" && ret_type != data_type)
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::RETURN_TYPE_MISMATCH, stmt->getStartLine(), func_name) << std::endl;
            }
        }
        else
        {
            analyzeStatement(stmt);
        }
    }
    this->endScope();
}
