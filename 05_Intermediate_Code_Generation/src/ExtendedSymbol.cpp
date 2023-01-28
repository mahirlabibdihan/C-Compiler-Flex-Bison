/**
 * Author: Mahir Labib Dihan
 * Last modified: January 18, 2023
 */
#include "../include/ExtendedSymbol.hpp"
#include "../include/Util.hpp"
#include "../include/Logger.hpp"
#include <iostream>

ASTNode::ASTNode(const string &ast_type, const string &name, const string &type) : SymbolInfo(name, type)
{
    this->ast_type = ast_type;
}
ASTNode::~ASTNode()
{
}
const string &ASTNode::getASTType()
{
    return ast_type;
}
void ASTNode::setASTType(const string &ast_type)
{
    this->ast_type = ast_type;
}
NonTerminal::NonTerminal(string nt_type) : ASTNode("NON_TERMINAL")
{
    this->nt_type = nt_type;
}

NonTerminal::~NonTerminal()
{
    for (SymbolInfo *ch : children)
    {
        delete ch;
    }
    children.clear();
}

string NonTerminal::getNonTerminalType()
{
    return nt_type;
}

void NonTerminal::setNonTerminalType(string type)
{
    this->nt_type = type;
}

void NonTerminal::setChildren(std::vector<SymbolInfo *> children)
{
    // while (!this->children.empty())
    // {
    //     delete this->children.back();
    //     this->children.pop_back();
    // }
    this->children = children;
}

std::vector<SymbolInfo *> NonTerminal::getChildren()
{
    return children;
}

List::List(const string &l_type) : NonTerminal("LIST")
{
    this->l_type = l_type;
}
List::~List()
{
}

const string &List::getListType()
{
    return l_type;
}
ParameterList::ParameterList() : List("PARAMETER_LIST")
{
}
ParameterList::~ParameterList()
{
    while (!list.empty())
    {
        delete list.back();
        list.pop_back();
    }
}
void ParameterList::addParam(const string &data_type)
{
    list.push_back(new Variable("blank", data_type, "PRIMITIVE"));
}

void ParameterList::addParam(const string &data_type, const string &name)
{
    list.push_back(new Variable(name, data_type, "PRIMITIVE"));
}

void ParameterList::addParam(Variable *param)
{
    list.push_back(param);
}

void ParameterList::addParams(ParameterList *params)
{
    for (auto &p : params->list)
    {
        this->addParam(p);
    }
}

vector<Variable *> ParameterList::getParams()
{
    return list;
}

ArgumentList::ArgumentList() : List("ARGUMENT_LIST")
{
}

ArgumentList::~ArgumentList()
{
    while (!list.empty())
    {
        delete list.back();
        list.pop_back();
    }
}

void ArgumentList::addArg(Expression *arg)
{
    list.push_back(arg);
}

void ArgumentList::addArgs(ArgumentList *args)
{
    for (auto &a : args->list)
    {
        this->addArg(a);
    }
}

vector<Expression *> ArgumentList::getArgs()
{
    return list;
}

DeclarationList::DeclarationList() : List("DECLARATION_LIST")
{
}

DeclarationList::~DeclarationList()
{
    while (!list.empty())
    {
        delete list.back();
        list.pop_back();
    }
}

void DeclarationList::addVariable(const string &name)
{
    list.push_back(new Variable(name, "", "PRIMITIVE"));
}

void DeclarationList::addVariable(Variable *var)
{
    list.push_back(new Variable(var->getIdName(), var->getDataType(), "PRIMITIVE"));
}

void DeclarationList::addArray(const string &name, const string &size)
{
    list.push_back(new Array(name, "", size));
}

void DeclarationList::addArray(Array *arr)
{
    list.push_back(new Array(arr->getIdName(), arr->getDataType(), arr->getArraySize()));
}

void DeclarationList::addVariables(DeclarationList *vars)
{
    for (auto &v : vars->list)
    {
        if (v->getVarType() == "ARRAY")
        {
            this->addArray((Array *)v);
        }
        else
        {
            this->addVariable(v);
        }
    }
}
vector<Variable *> DeclarationList::getDeclarations()
{
    return list;
}

Expression::Expression(const string &data_type, const string &exp_type) : NonTerminal("EXPRESSION")
{
    this->data_type = data_type;
    this->exp_type = exp_type;
}
Expression::~Expression()
{
}

const string &Expression::getDataType()
{
    return data_type;
}
void Expression::setDataType(const string &data_type)
{
    this->data_type = data_type;
}
const string &Expression::getExpType()
{
    return exp_type;
}
void Expression::setExpType(const string &type)
{
    this->exp_type = type;
}

ArrayCall::~ArrayCall()
{
}

Terminal::Terminal(const string &name, const string &type, const string &t_type) : ASTNode("TERMINAL", name, type)
{
    this->t_type = t_type;
}
Terminal::~Terminal()
{
}

string Terminal::getTerminalType()
{
    return t_type;
}
void Terminal::setTerminalType(string type)
{
    this->t_type = type;
}

Identifier::Identifier(const string &id_name, const string &id_type) : Terminal(id_name, "ID", "IDENTIFIER")
{
    this->id_type = id_type;
    this->id_name = id_name;
}

Identifier::~Identifier()
{
}
const string &Identifier::getIdentity()
{
    return id_type;
}

void Identifier::setIdentity(const string &id_type)
{
    this->id_type = id_type;
}

const string &Identifier::getIdName()
{
    return id_name;
}
Variable::Variable(const string &var_name, const string &data_type, const string &var_type) : Identifier(var_name, "VARIABLE")
{
    this->var_type = var_type;
    this->data_type = data_type;
    this->offset = 0;
}
Variable::~Variable()
{
}
const string &Variable::getVarType()
{
    return var_type;
}
void Variable::setVarType(const string &var_type)
{
    this->var_type = var_type;
}
const string &Variable::getDataType()
{
    return data_type;
}
void Variable::setDataType(const string &data_type)
{
    this->data_type = data_type;
}
void Variable::setOffset(int offset)
{
    this->offset = offset;
}
int Variable::getOffset()
{
    return offset;
}
Array::Array(const string &arr_name, const string &data_type, string arr_size) : Variable(arr_name, data_type, "ARRAY")
{
    this->arr_size = arr_size;
}
Array::~Array()
{
}
string Array::getArraySize()
{
    return arr_size;
}
void Array::setArraySize(string arr_size)
{
    this->arr_size = arr_size;
}
Function::Function(const string &func_name, const string &ret_type) : Identifier(func_name, "FUNCTION")
{
    is_definition = false;
    is_declaration = false;
    this->ret_type = ret_type;
}
Function::~Function()
{
    for (Variable *v : params)
    {
        delete v;
    }
}
const string &Function::getReturnType()
{
    return ret_type;
}
void Function::setReturnType(const string &type)
{
    this->ret_type = type;
}
void Function::addParam(Variable *param)
{
    params.push_back(param);
}
void Function::addParams(vector<Variable *> params)
{
    for (auto param : params)
    {
        addParam(param);
    }
}
vector<Variable *> Function::getParams()
{
    return params;
}
int Function::getNumberOfParams()
{
    return params.size();
}

bool Function::isDeclaredAndDefined()
{
    return is_definition;
}
bool Function::isDeclaredNotDefined()
{
    return is_declaration && !is_definition;
}
bool Function::matchParamsNum(Function *func)
{
    return func->params.size() == this->params.size();
}
bool Function::matchParamsType(Function *func)
{
    for (int i = 0; i < params.size(); i++)
    {
        if (func->params[i]->getDataType() != this->params[i]->getDataType())
        {
            return false;
        }
    }
    return true;
}
bool Function::matchReturnType(Function *func)
{
    return func->ret_type == this->ret_type;
}
void Function::declareFunction()
{
    is_declaration = true;
}
void Function::defineFunction()
{
    is_definition = true;
}

Program::Program() : NonTerminal("PROGRAM")
{
}

void Program::addFunctionDefinition(FunctionDefinition *func_def)
{
    this->func_defs.push_back(func_def);
}
void Program::addFunctionDeclaration(FunctionDeclaration *func_dec)
{
    this->func_decs.push_back(func_dec);
}
void Program::addVariableDeclaration(VariableDeclaration *var_dec)
{
    this->var_decs.push_back(var_dec);
}
void Program::addUnit(Unit *unit)
{
    if (unit != NULL)
    {
        string type = unit->getUnitType();
        if (type == "FUNCTION_DEFINITION")
        {
            this->addFunctionDefinition((FunctionDefinition *)unit);
        }
        if (type == "FUNCTION_DECLARATION")
        {
            this->addFunctionDeclaration((FunctionDeclaration *)unit);
        }
        if (type == "VARIABLE_DECLARATION")
        {
            this->addVariableDeclaration((VariableDeclaration *)unit);
        }
    }
}
const vector<FunctionDefinition *> &Program::getFunctionDefinitions()
{
    return func_defs;
}
const vector<FunctionDeclaration *> &Program::getFunctionDeclarations()
{
    return func_decs;
}
const vector<VariableDeclaration *> &Program::getVariableDeclarations()
{
    return var_decs;
}

Unit::Unit(const string &u_type) : NonTerminal("UNIT")
{
    this->u_type = u_type;
}

const string &Unit::getUnitType()
{
    return u_type;
}
VariableDeclaration::VariableDeclaration(const string &data_type, const vector<Variable *> &list) : Unit("VARIABLE_DECLARATION"), Statement("VARIABLE_DECLARATION")
{
    for (Variable *var : list)
    {
        var->setDataType(data_type);
    }
    this->decl_list = list;
}

const vector<Variable *> &VariableDeclaration::getDeclarationList()
{
    return decl_list;
}

FunctionDeclaration::FunctionDeclaration(const string &func_name, const string &ret_type, vector<Variable *> params) : Unit("FUNCTION_DECLARATION"), Statement("FUNCTION_DECLARATION")
{
    this->ret_type = ret_type;
    this->func_name = func_name;
    this->params = params;
}
const string &FunctionDeclaration::getReturnType()
{
    return ret_type;
}
const string &FunctionDeclaration::getFunctionName()
{
    return func_name;
}
const vector<Variable *> &FunctionDeclaration::getParams()
{
    return params;
}
FunctionDefinition::FunctionDefinition(const string &func_name, const string &ret_type, vector<Variable *> params, vector<Statement *> body) : Unit("FUNCTION_DEFINITION"), Statement("FUNCTION_DEFINITION")
{
    this->ret_type = ret_type;
    this->func_name = func_name;
    this->params = params;
    this->body = body;
}
const string &FunctionDefinition::getFunctionName()
{
    return func_name;
}
const string &FunctionDefinition::getReturnType()
{
    return ret_type;
}
const vector<Variable *> &FunctionDefinition::getParams()
{
    return params;
}
const vector<Statement *> &FunctionDefinition::getBody()
{
    return body;
}
NotOp::NotOp(Expression *right) : UnaryExpression("NOTOP", "!", right)
{
}

DecOp::DecOp(Expression *left) : UnaryExpression("DECOP", "--", left)
{
}

IncOp::IncOp(Expression *left) : UnaryExpression("INCOP", "++", left)
{
}

UAddOp::UAddOp(Expression *right, const string &oprt) : UnaryExpression("UADDOP", oprt, right)
{
    this->uadd_oprt = oprt;
}
UnaryExpression::UnaryExpression(const string &op_type, const string &op_symbol, Expression *operand) : Expression("", "UNARY_EXPRESSION")
{
    this->op_type = op_type;
    this->operand = operand;
    this->op_symbol = op_symbol;
}
const string &UnaryExpression::getOpType()
{
    return op_type;
}
Expression *UnaryExpression::getOperand()
{
    return operand;
}
const string &UnaryExpression::getOperator()
{
    return op_symbol;
}
RelOp::RelOp(Expression *left, Expression *right, const string &rel_oprt) : BinaryExpression("RELOP", rel_oprt, left, right)
{
    this->rel_oprt = rel_oprt;
}

AddOp::AddOp(Expression *left, Expression *right, const string &add_oprt) : BinaryExpression("ADDOP", add_oprt, left, right)
{
    this->add_oprt = add_oprt;
}

MulOp::MulOp(Expression *left, Expression *right, const string &mul_oprt) : BinaryExpression("MULOP", mul_oprt, left, right)
{
    this->mul_oprt = mul_oprt;
}

LogicOp::LogicOp(Expression *left, Expression *right, const string &logic_oprt) : BinaryExpression("LOGICOP", logic_oprt, left, right)
{
    this->logic_oprt = logic_oprt;
}

AssignOp::AssignOp(VariableCall *left, Expression *right) : BinaryExpression("ASSIGNOP", "=", left, right)
{
}

BinaryExpression::BinaryExpression(const string &op_type, const string &op_symbol, Expression *left, Expression *right) : Expression("", "BINARY_EXPRESSION")
{
    this->op_type = op_type;
    this->left_opr = left;
    this->right_opr = right;
    this->op_symbol = op_symbol;
}
Expression *BinaryExpression::getLeftOpr()
{
    return left_opr;
}
Expression *BinaryExpression::getRightOpr()
{
    return right_opr;
}
const string &BinaryExpression::getOpType()
{
    return op_type;
}
const string &BinaryExpression::getOperator()
{
    return op_symbol;
}
CallExpression::CallExpression(const string &data_type, const string &call_type) : Expression(data_type, "CALL_EXPRESSION")
{
    this->call_type = call_type;
}
const string &CallExpression::getCallType()
{
    return call_type;
}
IdentifierCall::IdentifierCall(const string &id_name, const string &id_type) : CallExpression("", "IDENTIFIER_CALL")
{
    this->id_name = id_name;
    this->id_type = id_type;
}
const string &IdentifierCall::getIdName()
{
    return id_name;
}
const string &IdentifierCall::getIdentity()
{
    return id_type;
}
FunctionCall::FunctionCall(const string &func_name, const vector<Expression *> &args) : IdentifierCall(func_name, "FUNCTION_CALL")
{
    this->args = args;
}
const vector<Expression *> &FunctionCall::getArgs()
{
    return args;
}
VariableCall::VariableCall(const string &var_name, const string &var_type) : IdentifierCall(var_name, "VARIABLE_CALL")
{
    this->var_type = var_type;
}
const string &VariableCall::getVarType()
{
    return var_type;
}
ArrayCall::ArrayCall(const string &var_name, Expression *idx) : VariableCall(var_name, "ARRAY_CALL")
{
    this->idx = idx;
}
Expression *ArrayCall::getIndex()
{
    return idx;
}
ConstantCall::ConstantCall(const string &literal, const string &data_type) : CallExpression(data_type, "CONSTANT_CALL")
{
    this->literal = literal;
    this->data_type = data_type;
}
const string &ConstantCall::getLiteral()
{
    return literal;
}

IntegerCall::IntegerCall(const string &literal) : ConstantCall(literal, "INT")
{
}

FloatCall::FloatCall(const string &literal) : ConstantCall(literal, "FLOAT")
{
}

ConditionalStatement::ConditionalStatement(string c_type, Expression *condition) : Statement("CONDITIONAL_STATEMENT")
{
    this->condition = condition;
    this->c_type = c_type;
}

Expression *ConditionalStatement::getCondition()
{
    return condition;
}
const string &ConditionalStatement::getConditionType()
{
    return c_type;
}
IfStatement::IfStatement(Expression *condition, Statement *body) : ConditionalStatement("IF_STATEMENT", condition)
{
    this->if_body = body;
}
Statement *IfStatement::getIfBody()
{
    return if_body;
}
IfElseStatement::IfElseStatement(Expression *condition, Statement *if_body, Statement *else_body) : ConditionalStatement("IFELSE_STATEMENT", condition)
{
    this->if_body = if_body;
    this->else_body = else_body;
}
Statement *IfElseStatement::getIfBody()
{
    return if_body;
}
Statement *IfElseStatement::getElseBody()
{
    return else_body;
}
LoopStatement::LoopStatement(Expression *condition, Statement *body, const string &l_type) : Statement("LOOP_STATEMENT")
{
    this->condition = condition;
    this->body = body;
    this->l_type = l_type;
}
Expression *LoopStatement::getCondition()
{
    return condition;
}
Statement *LoopStatement::getBody()
{
    return body;
}
const string &LoopStatement::getLoopType()
{
    return l_type;
}
ForLoop::ForLoop(Expression *initialize, Expression *condition, Expression *inc_dec, Statement *body) : LoopStatement(condition, body, "FOR_LOOP")
{
    this->initialize = initialize;
    this->inc_dec = inc_dec;
}
Expression *ForLoop::getInitialize()
{
    return initialize;
}
Expression *ForLoop::getIncDec()
{
    return inc_dec;
}
WhileLoop::WhileLoop(Expression *condition, Statement *body) : LoopStatement(condition, body, "WHILE_LOOP")
{
}

PrintStatement::PrintStatement(VariableCall *var_call) : Statement("PRINT_STATEMENT")
{
    this->var_call = var_call;
}
VariableCall *PrintStatement::getVariableCall()
{
    return var_call;
}
ReturnStatement::ReturnStatement(Expression *expr) : Statement("RETURN_STATEMENT")
{
    this->expr = expr;
}
Expression *ReturnStatement::getExpression()
{
    return expr;
}
ExpressionStatement::ExpressionStatement(Expression *expr) : Statement("EXPRESSION_STATEMENT")
{
    this->expr = expr;
}

Expression *ExpressionStatement::getExpression()
{
    return expr;
}

Statement::Statement(const string &stmt_type) : NonTerminal("STATEMENT")
{
    this->stmt_type = stmt_type;
}

CompoundStatement::CompoundStatement() : Statement("COMPOUND_STATEMENT")
{
}

void CompoundStatement::addStatement(Statement *stmt)
{
    this->list.push_back(stmt);
}

const vector<Statement *> &CompoundStatement::getStatements()
{
    return this->list;
}
const string &Statement::getStatementType()
{
    return stmt_type;
}