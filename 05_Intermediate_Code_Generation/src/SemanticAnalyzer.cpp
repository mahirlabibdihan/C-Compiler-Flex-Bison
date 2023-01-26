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
string SemanticAnalyzer::assignOp(AssignOp *expr)
{
    string left = evaluateExpression(expr->getLeftOpr());
    string right = evaluateExpression(expr->getRightOpr());
    if (!checkAssignment(left, right))
    {
        if (left == "VOID" || right == "VOID")
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::VOID_FUNCTION_EXP, expr->getStartLine()) << std::endl;
            return "NULL";
        }
        else
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INVALID_CONVERSION, expr->getStartLine(), "from '" + right + "' to '" + left + "'") << std::endl;
            return "NULL";
        }
    }
    else
    {
        if (left == "INT" && right == "FLOAT")
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::DATA_LOSS, expr->getStartLine(), right + " to " + left) << std::endl;
        }
        return left;
    }
}
string SemanticAnalyzer::logicOp(LogicOp *expr)
{
    string left = evaluateExpression(expr->getLeftOpr());
    string right = evaluateExpression(expr->getRightOpr());
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
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::VOID_FUNCTION_EXP, expr->getStartLine()) << std::endl;
            }
            else
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INCOMPATIBLE_OPERAND, expr->getStartLine()) << std::endl;
            }
            return "NULL";
        }
    }
    else
    {
        return "NULL";
    }
}
string SemanticAnalyzer::relOp(RelOp *expr)
{
    string left = evaluateExpression(expr->getLeftOpr());
    string right = evaluateExpression(expr->getRightOpr());
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
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::VOID_FUNCTION_EXP, expr->getStartLine()) << std::endl;
            }
            else
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INCOMPATIBLE_OPERAND, expr->getStartLine()) << std::endl;
            }
            return "NULL";
        }
    }
    else
    {
        return "NULL";
    }
}
string SemanticAnalyzer::addOp(AddOp *expr)
{
    string left = evaluateExpression(expr->getLeftOpr());
    string right = evaluateExpression(expr->getRightOpr());
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
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::VOID_FUNCTION_EXP, expr->getStartLine()) << std::endl;
            }
            else
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INCOMPATIBLE_OPERAND, expr->getStartLine()) << std::endl;
            }
            return "NULL";
        }
    }
    else
    {
        return "NULL";
    }
}
string SemanticAnalyzer::mulOp(MulOp *expr)
{
    string left = evaluateExpression(expr->getLeftOpr());
    string right = evaluateExpression(expr->getRightOpr());
    string op = expr->getOperator();
    string type = implicitTypecast(left, right);

    if (op == "%") // both operand should be integer
    {
        if (type != "INT")
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::NONINT_MOD, expr->getStartLine()) << std::endl;
            return "NULL";
        }
    }
    else if (type != "NULL")
    {
        if (type == "ERROR")
        {
            if (left == "VOID" || right == "VOID")
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::VOID_FUNCTION_EXP, expr->getStartLine()) << std::endl;
            }
            else
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INCOMPATIBLE_OPERAND, expr->getStartLine()) << std::endl;
            }
            return "NULL";
        }
    }
    else
    {
        return "NULL";
    }

    if ((op == "/" || op == "%") && isZero(expr->getRightOpr()))
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::MOD_BY_ZERO, expr->getStartLine()) << std::endl;
        return "NULL";
    }
    return type;
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
void SemanticAnalyzer::startProgram(Program *prog)
{
    vector<FunctionDefinition *> func_defs = prog->getFunctionDefinitions();
    vector<FunctionDeclaration *> func_decs = prog->getFunctionDeclarations();
    vector<VariableDeclaration *> var_decs = prog->getVariableDeclarations();

    for (VariableDeclaration *var_dec : var_decs)
    {
        declareVariables(var_dec);
    }
    for (FunctionDeclaration *func_dec : func_decs)
    {
        declareFunction(func_dec);
    }
    for (FunctionDefinition *func_def : func_defs)
    {
        defineFunction(func_def);
    }
}

string SemanticAnalyzer::evaluateExpression(Expression *expr)
{
    if (expr != NULL)
    {
        string type = expr->getExpType();
        if (type == "CALL_EXPRESSION")
        {
            return evaluateCallExpression((CallExpression *)expr);
        }
        if (type == "BINARY_EXPRESSION")
        {
            return evaluateBinaryExpression((BinaryExpression *)expr);
        }
        if (type == "UNARY_EXPRESSION")
        {
            return evaluateUnaryExpression((UnaryExpression *)expr);
        }
    }

    return "NULL";
} // Unary, Binary, Call
bool SemanticAnalyzer::isZero(Expression *expr)
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
string SemanticAnalyzer::evaluateBinaryExpression(BinaryExpression *bin_expr)
{
    string type = bin_expr->getOpType();
    if (type == "ASSIGNOP")
    {
        return assignOp((AssignOp *)bin_expr);
    }
    if (type == "ADDOP")
    {
        return addOp((AddOp *)bin_expr);
    }
    if (type == "MULOP")
    {
        return mulOp((MulOp *)bin_expr);
    }
    if (type == "RELOP")
    {
        return relOp((RelOp *)bin_expr);
    }
    if (type == "LOGICOP")
    {
        return logicOp((LogicOp *)bin_expr);
    }
    return "NULL";
}
string SemanticAnalyzer::evaluateUnaryExpression(UnaryExpression *unr_expr)
{
    string type = unr_expr->getOpType();
    string data_type = evaluateExpression(unr_expr->getOperand());

    if (type == "UADDOP")
    {
        return data_type;
    }
    if (type == "NOTOP")
    {
        return "INT";
    }
    if (type == "INCOP")
    {
        return data_type;
    }
    if (type == "DECOP")
    {
        return data_type;
    }
    return "NULL";
}
string SemanticAnalyzer::evaluateCallExpression(CallExpression *call_expr)
{
    string type = call_expr->getCallType();
    if (type == "IDENTIFIER_CALL")
    {
        return callIdentifier((IdentifierCall *)call_expr);
    }
    if (type == "CONSTANT_CALL")
    {
        return call_expr->getDataType();
    }
    return "NULL";
}
string SemanticAnalyzer::callIdentifier(IdentifierCall *id_call)
{
    string type = id_call->getIdentity();
    if (type == "VARIABLE_CALL")
    {
        return callVariable((VariableCall *)id_call);
    }
    if (type == "FUNCTION_CALL")
    {
        return callFunction((FunctionCall *)id_call);
    }
    return "NULL";
}
string SemanticAnalyzer::checkVariableCall(VariableCall *var)
{
    string var_name = var->getIdName();
    Identifier *id = (Identifier *)table->find(var_name);

    if (id == NULL)
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::UNDECLARED_VARIABLE, var->getStartLine(), var_name) << std::endl;
        return "NULL";
    }
    else
    {
        if (id->getIdentity() != "VARIABLE")
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_MISMATCH, var->getStartLine(), var_name + " is not a variable") << std::endl;
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
string SemanticAnalyzer::callVariable(VariableCall *var_call)
{
    string type = var_call->getVarType();
    if (type == "PRIMITIVE_CALL")
    {
        return checkVariableCall(var_call);
    }
    if (type == "ARRAY_CALL")
    {
        return callArray((ArrayCall *)var_call);
    }
    return "NULL";
}
string SemanticAnalyzer::checkArrayCall(ArrayCall *arr_call)
{
    string arr_name = arr_call->getIdName();
    Expression *index = arr_call->getIndex();

    Identifier *id = (Identifier *)table->find(arr_name);

    if (id == NULL)
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::UNDECLARED_VARIABLE, arr_call->getStartLine(), arr_name) << std::endl;
        return "NULL";
    }
    else
    {
        if (id->getIdentity() != "VARIABLE")
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_MISMATCH, arr_call->getStartLine(), arr_name + " is not a variable") << std::endl;
            return "NULL";
        }

        Variable *var = (Variable *)id;
        if (var->getVarType() != "ARRAY")
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::NOT_ARRAY, arr_call->getStartLine(), arr_name) << std::endl;
            return "NULL";
        }
        if (index->getDataType() != "INT")
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::INVALID_ARRAY_INDEX, arr_call->getStartLine()) << std::endl;
        }
        return var->getDataType();
    }
}
string SemanticAnalyzer::callArray(ArrayCall *arr_call)
{
    Expression *index = arr_call->getIndex();
    index->setDataType(evaluateExpression(index));
    return checkArrayCall(arr_call);
}
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
        this->startScope();
        analyzeCompoundStatement((CompoundStatement *)stmt);
        this->endScope();
    }
    if (type == "VARIABLE_DECLARATION")
    {
        declareVariables((VariableDeclaration *)stmt);
    }
    if (type == "FUNCTION_DEFINITION")
    {
        defineFunction((FunctionDefinition *)stmt);
    }
    if (type == "FUNCTION_DECLARATION")
    {
        declareFunction((FunctionDeclaration *)stmt);
    }
} // Conditional, Loop, Return, Print, Expression
void SemanticAnalyzer::analyzeIfStatement(IfStatement *if_stmt)
{
    evaluateExpression(if_stmt->getCondition());
    analyzeStatement(if_stmt->getIfBody());
}
void SemanticAnalyzer::analyzeIfElseStatement(IfElseStatement *ifelse_stmt)
{
    evaluateExpression(ifelse_stmt->getCondition());
    analyzeStatement(ifelse_stmt->getIfBody());
    analyzeStatement(ifelse_stmt->getElseBody());
}
void SemanticAnalyzer::analyzeForLoop(ForLoop *for_loop)
{
    evaluateExpression(for_loop->getInitialize());
    evaluateExpression(for_loop->getCondition());
    evaluateExpression(for_loop->getIncDec());
    analyzeStatement(for_loop->getBody());
}
void SemanticAnalyzer::analyzeWhileLoop(WhileLoop *while_loop)
{
    evaluateExpression(while_loop->getCondition());
    analyzeStatement(while_loop->getBody());
}
void SemanticAnalyzer::analyzeReturnStatement(ReturnStatement *ret_stmt)
{
    Expression *ret_expr = ret_stmt->getExpression();
    string data_type = evaluateExpression(ret_expr);
    string ret_type = functions.top()->getReturnType();
    string func_name = functions.top()->getFunctionName();
    if (ret_expr == NULL)
    {
        if (ret_type != "VOID")
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::RETURN_TYPE_MISMATCH, ret_stmt->getStartLine(), func_name) << std::endl;
        }
    }
    else if (data_type != "NULL" && ret_type != data_type)
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::RETURN_TYPE_MISMATCH, ret_stmt->getStartLine(), func_name) << std::endl;
    }
}
void SemanticAnalyzer::analyzePrintStatement(PrintStatement *print_stmt)
{
    callVariable(print_stmt->getVariableCall());
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
    evaluateExpression(expr_stmt->getExpression());
}
string SemanticAnalyzer::evaluateFunctionCall(FunctionCall *func_call)
{
    string func_name = func_call->getIdName();
    vector<Expression *> args = func_call->getArgs();

    Identifier *id = (Identifier *)table->find(func_name);
    if (id == NULL)
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::UNDECLARED_FUNCTION, func_call->getStartLine(), func_name) << std::endl;
        return "NULL";
    }

    if (id->getIdentity() != "FUNCTION")
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::NOT_FUNCTION, func_call->getStartLine(), func_name) << std::endl;
        return "NULL";
    }

    Function *func = (Function *)id;

    if (func->getNumberOfParams() < args.size())
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TOO_MANY_ARGUMENTS, func_call->getStartLine(), func_name) << std::endl;
    }
    else if (func->getNumberOfParams() > args.size())
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TOO_FEW_ARGUMENTS, func_call->getStartLine(), func_name) << std::endl;
    }
    else
    {
        vector<Variable *> params = func->getParams();
        for (int i = 0; i < params.size(); i++)
        {
            if (args[i]->getDataType() != "NULL" && params[i]->getDataType() != args[i]->getDataType())
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::ARGUMENT_TYPE_MISMATCH, func_call->getStartLine(), std::to_string(i + 1) + " of '" + func_name + "'") << std::endl;
            }
        }
    }
    return func->getReturnType();
}
string SemanticAnalyzer::callFunction(FunctionCall *func_call)
{
    string func_name = func_call->getIdName();
    vector<Expression *> args = func_call->getArgs();
    for (Expression *e : args)
    {
        e->setDataType(evaluateExpression(e));
    }
    return evaluateFunctionCall(func_call);
}
void SemanticAnalyzer::declareArray(Array *arr)
{
    // Start line not set in arr
    string data_type = arr->getDataType();
    string arr_name = arr->getIdName();
    string arr_size = arr->getArraySize();

    Array *new_arr = new Array(arr_name, data_type, arr_size);
    if (!table->insert(new_arr)) // already present in current scope
    {
        Identifier *old_id = (Identifier *)table->find(arr_name);
        if (old_id->getIdentity() != new_arr->getIdentity())
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::DIFF_DECLARATION, arr->getStartLine(), arr_name) << std::endl;
        }
        else
        {
            Variable *old_var = (Variable *)old_id;
            if (old_var->getVarType() != new_arr->getVarType())
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_CONFLICT, arr->getStartLine(), arr_name) << std::endl;
            }
            else
            {
                Array *old_arr = (Array *)old_var;
                if (old_arr->getDataType() != new_arr->getDataType())
                {
                    errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_CONFLICT, arr->getStartLine(), arr_name) << std::endl;
                }
                else if (old_arr->getArraySize() != arr->getArraySize())
                {
                    errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_CONFLICT, arr->getStartLine(), arr_name) << std::endl;
                }
                else
                {
                    errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::MULTIPLE_DECLARATION, arr->getStartLine(), arr_name) << std::endl;
                }
            }
        }
        delete new_arr;
    }
    else
    {
        /** Array inserted successfully **/
    }
}
void SemanticAnalyzer::declareVariable(Variable *var)
{
    // Start line not set in var
    string data_type = var->getDataType();
    string var_name = var->getIdName();

    Variable *new_var = new Variable(var_name, data_type);

    if (!table->insert(new_var)) // Already present in current scope
    {
        Identifier *old_id = (Identifier *)table->find(var_name);
        if (old_id->getIdentity() != new_var->getIdentity())
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::DIFF_DECLARATION, var->getStartLine(), var_name) << std::endl;
        }
        else
        {
            Variable *old_var = (Variable *)old_id;
            if (old_var->getVarType() != new_var->getVarType())
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_CONFLICT, var->getStartLine(), var_name) << std::endl;
            }
            else if (old_var->getDataType() != new_var->getDataType())
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_CONFLICT, var->getStartLine(), var_name) << std::endl;
            }
            else // Same declaration
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::MULTIPLE_DECLARATION, var->getStartLine(), var_name) << std::endl;
            }
        }
        delete new_var;
    }
    else
    {
        /** Variable inserted successfully **/
    }
}
void SemanticAnalyzer::declareVariables(VariableDeclaration *var_decl)
{
    vector<Variable *> vars = var_decl->getDeclarationList();

    for (Variable *var : vars)
    {
        if (var->getDataType() == "VOID")
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::VOID_VARIABLE, var_decl->getStartLine(), var->getIdName()) << std::endl;
        }
        else
        {
            var->setStartLine(var_decl->getStartLine());
            if (var->getVarType() == "ARRAY")
            {
                declareArray((Array *)var);
            }
            else
            {
                declareVariable(var);
            }
        }
    }
}
bool SemanticAnalyzer::matchTwoFunction(Function *f1, Function *f2)
{
    return f1->matchReturnType(f2) && f1->matchParamsNum(f2) && f1->matchParamsType(f2);
}
void SemanticAnalyzer::checkFunctionDeclaration(FunctionDeclaration *func_dec)
{
    string ret_type = func_dec->getReturnType();
    string func_name = func_dec->getFunctionName();
    vector<Variable *> params = func_dec->getParams();

    Function *new_func = new Function(func_name, ret_type);

    for (auto p : params)
    {
        new_func->addParam(new Variable(p->getIdName(), p->getDataType()));
    }

    if (!table->insert(new_func))
    {
        Identifier *id = (Identifier *)table->find(func_name);
        if (id->getIdentity() != "FUNCTION") // Already declared as non-function type or Defined as function
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::DIFF_DECLARATION, lexer->getLineCount(), func_name) << std::endl;
        }
        else
        {
            Function *func = (Function *)id;
            if (matchTwoFunction(func, new_func))
            {
                // Same declaration
            }
            else
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_CONFLICT, func_dec->getStartLine(), func_name) << std::endl;
            }
        }
        delete new_func;
    }
    else
    {
        /** Function inserted successfully **/
    }
}
void SemanticAnalyzer::declareFunction(FunctionDeclaration *func_decl)
{
    checkFunctionDeclaration(func_decl);
}
void SemanticAnalyzer::checkFunctionDefinition(FunctionDefinition *func_def)
{
    // Creating a Function to insert into table
    string ret_type = func_def->getReturnType();
    string func_name = func_def->getFunctionName();
    vector<Variable *> params = func_def->getParams();

    Function *new_func = new Function(func_name, ret_type);
    for (auto p : params)
    {
        new_func->addParam(new Variable(p->getIdName(), p->getDataType()));
    }

    if (!table->insert(new_func)) // Couldn't insert
    {
        Identifier *id = (Identifier *)table->find(func_name);
        if (id->getIdentity() != "FUNCTION") // Already declared as non-function type
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::DIFF_DECLARATION, func_def->getStartLine(), func_name) << std::endl;
        }
        else // or Defined as function
        {
            Function *func = (Function *)id;
            if (func->isDeclaredAndDefined())
            {
                if (matchTwoFunction(func, new_func))
                {
                    errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::MULTIPLE_DEFINITION, func_def->getStartLine(), func_name) << std::endl;
                }
                else
                {
                    errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_CONFLICT, func_def->getStartLine(), func_name) << std::endl;
                }
            }
            else // declared but not defined
            {
                if (matchTwoFunction(func, new_func))
                {
                    func->defineFunction();
                }
                else
                {
                    errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_CONFLICT, func_def->getStartLine(), func_name) << std::endl;
                }
            }
        }
        delete new_func;
    }
    else
    {
        for (auto &i : params)
        {
            if (i->getIdName() == "blank")
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::MISSING_PARAM_NAME, func_def->getStartLine(), func_name) << std::endl;
            }
        }
        new_func->defineFunction();
    }
}
void SemanticAnalyzer::declareFunctionParams(vector<Variable *> params)
{
    for (auto i : params)
    {
        string param_name = i->getIdName();
        if (param_name == "blank")
            continue;
        Variable *var = new Variable(param_name, i->getDataType());
        if (!table->insert(var))
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::PARAM_REDEFINITION, i->getStartLine(), param_name) << std::endl;
            delete var;
            return;
        }
        else
        {
            /* Parameter declared */
        }
    }
}
void SemanticAnalyzer::defineFunction(FunctionDefinition *func_def)
{
    if (!functions.empty())
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::NESTED_FUNCTION, lexer->getLineCount(), functions.top()->getFunctionName()) << std::endl;
    }

    string ret_type = func_def->getReturnType();
    string func_name = func_def->getFunctionName();
    vector<Variable *> params = func_def->getParams();
    vector<Statement *> stmt_list = func_def->getBody();
    checkFunctionDefinition(func_def);

    this->startScope();
    functions.push(func_def);

    declareFunctionParams(params);
    for (Statement *stmt : stmt_list)
    {
        analyzeStatement(stmt);
    }

    functions.pop();
    this->endScope();
}
