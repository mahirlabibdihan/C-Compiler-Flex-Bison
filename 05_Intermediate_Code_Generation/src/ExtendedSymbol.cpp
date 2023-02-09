/**
 * Author: Mahir Labib Dihan
 * Last modified: January 18, 2023
 */
#include "../include/ExtendedSymbol.hpp"
#include "../include/Util.hpp"
#include "../include/Logger.hpp"
#include "../include/AssemblyGenerator.hpp"
#include "../include/SemanticAnalyzer.hpp"
#include <iostream>
#include <fstream>

extern std::ofstream asmout;
extern std::ofstream codeout;
extern std::ofstream parseout;
extern std::ofstream errorout;
extern AssemblyGenerator *asm_gen;
extern SemanticAnalyzer *sem_anlzr;
extern ErrorHandler *error_hndlr;
extern SymbolTable *table;
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

Expression::Expression(const string &exp_type) : NonTerminal("EXPRESSION")
{
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
VariableDeclaration::VariableDeclaration(const string &data_type, const vector<Variable *> &list) : Unit("VARIABLE_DECLARATION"), Statement("VARIABLE_DECLARATION"), NonTerminal("UNIT")
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

FunctionDeclaration::FunctionDeclaration(const string &func_name, const string &ret_type, vector<Variable *> params) : Unit("FUNCTION_DECLARATION"), Statement("FUNCTION_DECLARATION"), NonTerminal("UNIT")
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

FunctionDefinition::FunctionDefinition(const string &func_name, const string &ret_type, vector<Variable *> params, CompoundStatement *body) : Unit("FUNCTION_DEFINITION"), Statement("FUNCTION_DEFINITION"), NonTerminal("UNIT")
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
CompoundStatement *FunctionDefinition::getBody()
{
    return body;
}
void FunctionDefinition::setReturnLabel(const string &label)
{
    this->return_label = label;
}
const string &FunctionDefinition::getReturnLabel()
{
    return return_label;
}

NotOp::NotOp(Expression *right) : UnaryExpression("NOTOP", "!", right), BooleanExpression("NOTOP"), Expression("UNARY_BOOLEAN")
{
}

DecOp::DecOp(Expression *left) : UnaryExpression("DECOP", "--", left), Expression("UNARY_EXPRESSION")
{
}

IncOp::IncOp(Expression *left) : UnaryExpression("INCOP", "++", left), Expression("UNARY_EXPRESSION")
{
}

UAddOp::UAddOp(Expression *right, const string &oprt) : UnaryExpression("UADDOP", oprt, right), Expression("UNARY_EXPRESSION")
{
    this->uadd_oprt = oprt;
}

UnaryExpression::UnaryExpression(const string &op_type, const string &op_symbol, Expression *operand) : Expression("UNARY_EXPRESSION")
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
RelOp::RelOp(Expression *left, Expression *right, const string &rel_oprt) : BinaryExpression("RELOP", rel_oprt, left, right), BooleanExpression("RELOP"), Expression("BINARY_BOOLEAN")
{
    this->rel_oprt = rel_oprt;
}

AddOp::AddOp(Expression *left, Expression *right, const string &add_oprt) : BinaryExpression("ADDOP", add_oprt, left, right), Expression("BINARY_EXPRESSION")
{
    this->add_oprt = add_oprt;
}

MulOp::MulOp(Expression *left, Expression *right, const string &mul_oprt) : BinaryExpression("MULOP", mul_oprt, left, right), Expression("BINARY_EXPRESSION")
{
    this->mul_oprt = mul_oprt;
}

LogicOp::LogicOp(Expression *left, Expression *right, const string &logic_oprt) : BinaryExpression("LOGICOP", logic_oprt, left, right), BooleanExpression("LOGICOP"), Expression("BINARY_BOOLEAN")
{
    this->logic_oprt = logic_oprt;
}

AssignOp::AssignOp(VariableCall *left, Expression *right) : BinaryExpression("ASSIGNOP", "=", left, right), Expression("BINARY_EXPRESSION")
{
}

BooleanExpression::BooleanExpression(const string &bool_type) : Expression("BOOLEAN_EXPRESSION")
{
    this->bool_type = bool_type;
}
void BooleanExpression::setTrueLabel(const string &label)
{
    this->true_label = label;
}
const string &BooleanExpression::getTrueLabel()
{
    return true_label;
}
void BooleanExpression::setFalseLabel(const string &label)
{
    this->false_label = label;
}
const string &BooleanExpression::getFalseLabel()
{
    return false_label;
}
void BooleanExpression::setBoolType(const string &type)
{
    this->bool_type = type;
}
const string &BooleanExpression::getBoolType()
{
    return bool_type;
}
BinaryExpression::BinaryExpression(const string &op_type, const string &op_symbol, Expression *left, Expression *right) : Expression("BINARY_EXPRESSION")
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

CallExpression::CallExpression(const string &data_type, const string &call_type) : Expression("CALL_EXPRESSION")
{
    this->data_type = data_type;
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

ConditionalStatement::ConditionalStatement(string c_type, Expression *condition) : Statement("CONDITIONAL_STATEMENT"), NonTerminal("STATEMENT")
{
    this->condition = dynamic_cast<BooleanExpression *>(condition);
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
IfStatement::IfStatement(Expression *condition, Statement *body) : ConditionalStatement("IF_STATEMENT", condition), NonTerminal("STATEMENT")
{
    this->if_body = body;
}
Statement *IfStatement::getIfBody()
{
    return if_body;
}

IfElseStatement::IfElseStatement(Expression *condition, Statement *if_body, Statement *else_body) : ConditionalStatement("IFELSE_STATEMENT", condition), NonTerminal("STATEMENT")
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

LoopStatement::LoopStatement(Expression *condition, Statement *body, const string &l_type) : Statement("LOOP_STATEMENT"), NonTerminal("STATEMENT")
{
    this->condition = dynamic_cast<BooleanExpression *>(condition);
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
ForLoop::ForLoop(Expression *initialize, Expression *condition, Expression *inc_dec, Statement *body) : LoopStatement(condition, body, "FOR_LOOP"), NonTerminal("STATEMENT")
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

WhileLoop::WhileLoop(Expression *condition, Statement *body) : LoopStatement(condition, body, "WHILE_LOOP"), NonTerminal("STATEMENT")
{
}

PrintStatement::PrintStatement(VariableCall *var_call) : Statement("PRINT_STATEMENT"), NonTerminal("STATEMENT")
{
    this->var_call = var_call;
}
VariableCall *PrintStatement::getVariableCall()
{
    return var_call;
}

ReturnStatement::ReturnStatement(Expression *expr) : Statement("RETURN_STATEMENT"), NonTerminal("STATEMENT")
{
    this->expr = expr;
}
Expression *ReturnStatement::getExpression()
{
    return expr;
}

ExpressionStatement::ExpressionStatement(Expression *expr) : Statement("EXPRESSION_STATEMENT"), NonTerminal("STATEMENT")
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

void Statement::setNextLabel(const string &label)
{
    this->next_label = label;
}

const string &Statement::getNextLabel()
{
    return next_label;
}
CompoundStatement::CompoundStatement() : Statement("COMPOUND_STATEMENT"), NonTerminal("STATEMENT")
{
}

void CompoundStatement::addStatement(Statement *stmt)
{
    this->stmt_list.push_back(stmt);
}
const vector<Statement *> &CompoundStatement::getStatements()
{
    return this->stmt_list;
}
void CompoundStatement::addVariableDeclaration(VariableDeclaration *var_dec)
{
    var_decs.push_back(var_dec);
}
const vector<VariableDeclaration *> &CompoundStatement::getVariableDeclarations()
{
    return var_decs;
}

const string &Statement::getStatementType()
{
    return stmt_type;
}

// Semantic Analysis
void Program::checkSemantics()
{
    for (VariableDeclaration *var_dec : var_decs)
    {
        var_dec->checkSemantics();
    }
    for (FunctionDeclaration *func_dec : func_decs)
    {
        func_dec->checkSemantics();
    }
    for (FunctionDefinition *func_def : func_defs)
    {
        func_def->checkSemantics();
    }
}
void VariableDeclaration::checkSemantics()
{
    for (Variable *var : decl_list)
    {
        if (var->getDataType() == "VOID")
        {
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::VOID_VARIABLE, this->getStartLine(), var->getIdName()) << std::endl;
        }
        else
        {
            var->setStartLine(this->getStartLine());
            if (var->getVarType() == "ARRAY")
            {
                sem_anlzr->declareArray((Array *)var);
            }
            else
            {
                sem_anlzr->declareVariable(var);
            }
        }
    }
}
void FunctionDeclaration::checkSemantics()
{
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
            errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::DIFF_DECLARATION, this->getStartLine(), func_name) << std::endl;
        }
        else
        {
            Function *func = (Function *)id;
            if (sem_anlzr->matchTwoFunction(func, new_func))
            {
                // Same declaration
            }
            else
            {
                errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::TYPE_CONFLICT, this->getStartLine(), func_name) << std::endl;
            }
        }
        delete new_func;
    }
    else
    {
        /** Function inserted successfully **/
    }
}

void FunctionDefinition::checkSemantics()
{
    if (!sem_anlzr->functions.empty())
    {
        errorout << error_hndlr->handleSemanticError(ErrorHandler::SemanticError::NESTED_FUNCTION, this->getStartLine(), sem_anlzr->functions.top()->getFunctionName()) << std::endl;
    }

    sem_anlzr->checkFunctionDefinition(this);
    sem_anlzr->startScope();
    sem_anlzr->functions.push(this);
    sem_anlzr->declareFunctionParams(params);
    body->checkSemantics();
    sem_anlzr->functions.pop();
    sem_anlzr->endScope();
}

// Expression
string ArrayCall::checkSemantics()
{
    idx->setDataType(idx->checkSemantics());
    sem_anlzr->checkArrayCall(this);
}
string VariableCall::checkSemantics()
{
    if (var_type == "PRIMITIVE_CALL")
    {
        return sem_anlzr->checkVariableCall(this);
    }
    return "NULL";
}
string ConstantCall::checkSemantics()
{
    return data_type;
}
string AssignOp::checkSemantics()
{
    sem_anlzr->assignOp(this);
}
string AddOp::checkSemantics()
{
    sem_anlzr->addOp(this);
}
string MulOp::checkSemantics()
{
    sem_anlzr->mulOp(this);
}
string RelOp::checkSemantics()
{
    sem_anlzr->relOp(this);
}
string LogicOp::checkSemantics()
{
    sem_anlzr->logicOp(this);
}
string UAddOp::checkSemantics()
{
    return data_type;
}
string NotOp::checkSemantics()
{
    return "INT";
}
string DecOp::checkSemantics()
{
    return data_type;
}
string IncOp::checkSemantics()
{
    return data_type;
}
string FunctionCall::checkSemantics()
{
    sem_anlzr->evaluateFunctionCall(this);
}
// Statement
void IfStatement::checkSemantics()
{
    sem_anlzr->analyzeIfStatement(this);
}
void IfElseStatement::checkSemantics()
{
    sem_anlzr->analyzeIfElseStatement(this);
}
void ForLoop::checkSemantics()
{
    sem_anlzr->analyzeForLoop(this);
}
void WhileLoop::checkSemantics()
{
    sem_anlzr->analyzeWhileLoop(this);
}
void PrintStatement::checkSemantics()
{
    sem_anlzr->analyzePrintStatement(this);
}
void ReturnStatement::checkSemantics()
{
    sem_anlzr->analyzeReturnStatement(this);
}
void ExpressionStatement::checkSemantics()
{
    expr->checkSemantics();
}
void CompoundStatement::checkSemantics()
{
    sem_anlzr->startScope();
    sem_anlzr->analyzeCompoundStatement(this);
    sem_anlzr->endScope();
}
