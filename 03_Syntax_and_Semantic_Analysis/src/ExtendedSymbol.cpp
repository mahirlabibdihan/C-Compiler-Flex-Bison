/**
 * Author: Mahir Labib Dihan
 * Last modified: January 18, 2023
 */
#include "../include/ExtendedSymbol.hpp"
#include "../include/Util.hpp"
#include "../include/Logger.hpp"
#include <iostream>
NonTerminal::NonTerminal()
{
    this->nt_type = "";
}
NonTerminal::NonTerminal(string name, string type) : SymbolInfo(name, "NON_TERMINAL")
{
    this->nt_type = type;
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
    if (!this->children.empty())
    {
        for (SymbolInfo *s : this->children)
        {
            delete s;
        }
        this->children.clear();
    }
    this->children = children;
}

std::vector<SymbolInfo *> NonTerminal::getChildren()
{
    return children;
}

List::List(const string &name, const string &type) : NonTerminal(name, type)
{
}

List::~List()
{
}

ParameterList::ParameterList(const string &name, const string &type) : List(name, type)
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
    list.push_back(new Variable("blank", data_type));
}

void ParameterList::addParam(const string &data_type, const string &name)
{
    list.push_back(new Variable(name, data_type));
}

void ParameterList::addParam(Variable *param)
{
    list.push_back(new Variable(param->getSymbol(), param->getDataType()));
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

ArgumentList::ArgumentList(const string &name, const string &type) : List(name, type)
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
    list.push_back(new Expression(arg));
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

DeclarationList::DeclarationList(const string &name, const string &type) : List(name, type)
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
    list.push_back(new Variable(name, ""));
}

void DeclarationList::addVariable(Variable *var)
{
    list.push_back(new Variable(var->getSymbol(), var->getDataType()));
}

void DeclarationList::addArray(const string &name, const string &size)
{
    list.push_back(new Array(name, size));
}

void DeclarationList::addArray(Array *arr)
{
    list.push_back(new Array(arr->getSymbol(), arr->getArraySize()));
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

Expression::Expression(const string &exp_type) : NonTerminal()
{
    this->data_type = "void";
    this->exp_type = exp_type;
}
Expression::Expression(Expression *e) : NonTerminal(e->name, e->type)
{
    this->data_type = e->data_type;
    // this->exp_type = "";
}
Expression::Expression(const string &name, const string &type) : NonTerminal(name, type)
{
    this->data_type = "";
    // this->exp_type = "";
}

Expression::Expression(const string &name, const string &type, const string &data_type) : NonTerminal(name, type)
{
    this->data_type = data_type;
    // this->exp_type = "";
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

const string &Expression::getExpression()
{
    return this->getSymbol();
}
void Expression::setExpression(const string &exp)
{
    this->setSymbol(exp);
}

const string &Expression::getExpType()
{
    return exp_type;
}
void Expression::setExpType(const string &type)
{
    this->exp_type = type;
}

ArrayCall::ArrayCall(Expression *index) : Expression("ARRAY_CALL")
{
    idx = "";
    // this->index = new Expression(index);
}
ArrayCall::ArrayCall(const string &name, const string &type) : Expression(name, type)
{
    // this->index = NULL;
    this->exp_type = "ARRAY_CALL";
    idx = "";
}
ArrayCall::ArrayCall(const string &name, const string &type, const string &idx) : Expression(name, type)
{
    this->idx = idx;
    this->exp_type = "ARRAY_CALL";
}
ArrayCall::~ArrayCall()
{
}

string ArrayCall::getIndex()
{
    return idx;
}
void ArrayCall::setIndex(string idx)
{
    this->idx = idx;
}

Terminal::Terminal(const string &t_type) : SymbolInfo("blank", "TERMINAL")
{
    this->t_type = t_type;
}
Terminal::Terminal(const string &name, const string &t_type) : SymbolInfo(name, "TERMINAL")
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

Identifier::Identifier(const string &id_name, const string &id_type) : Terminal(id_name, "ID")
{
    this->id_type = id_type;
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

Variable::Variable(const string &var_name, const string &data_type) : Identifier(var_name, "VARIABLE")
{
    this->data_type = data_type;
    this->var_type = "PRIMITIVE";
}
Variable::Variable(const string &var_name, const string &data_type, const string &var_type) : Identifier(var_name, "VARIABLE")
{
    this->var_type = var_type;
    this->data_type = data_type;
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

Array::Array(const string &arr_name, string arr_size) : Variable(arr_name, "", "ARRAY")
{
    this->arr_size = arr_size;
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