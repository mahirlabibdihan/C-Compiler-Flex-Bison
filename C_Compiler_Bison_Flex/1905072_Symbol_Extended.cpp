#include "1905072_Symbol_Extended.hpp"
#include "1905072_Helper.hpp"
#include "1905072_Logger.hpp"

extern Logger *logger;
extern Helper *hlpr;
extern int line_count;
NonTerminal::NonTerminal()
{
    this->nt_type = "";
}
NonTerminal::NonTerminal(string name, string type) : SymbolInfo(name, type)
{
    this->nt_type = "";
}

NonTerminal::NonTerminal(string name, string type, string nt_type) : SymbolInfo(name, type)
{
    this->nt_type = type;
}
NonTerminal::~NonTerminal()
{
}

string NonTerminal::getNonTerminalType()
{
    return nt_type;
}

void NonTerminal::setNonTerminalType(string type)
{
    this->nt_type = type;
}

ParameterList::ParameterList()
{
}
ParameterList::ParameterList(const string &name, const string &type) : NonTerminal(name, type)
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

ArgumentList::ArgumentList()
{
}
ArgumentList::ArgumentList(const string &name, const string &type) : NonTerminal(name, type)
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

DeclarationList::DeclarationList()
{
}

DeclarationList::DeclarationList(const string &name, const string &type) : NonTerminal(name, type)
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

Expression::Expression() : NonTerminal("", "", "EXPRESSION")
{
    this->data_type = "void";
    this->tmp_var = "";
}
Expression::Expression(const string &exp_type) : NonTerminal("", "", "EXPRESSION")
{
    this->data_type = "void";
    this->tmp_var = "";
    this->exp_type = exp_type;
}
Expression::Expression(Expression *e) : NonTerminal(e->name, e->type, "EXPRESSION")
{
    this->data_type = e->data_type;
    this->tmp_var = e->tmp_var;
}
Expression::Expression(const string &name, const string &type) : NonTerminal(name, type, "EXPRESSION")
{
    this->data_type = "";
    this->tmp_var = "";
}

Expression::Expression(const string &name, const string &type, const string &data_type) : NonTerminal(name, type, "EXPRESSION")
{
    this->data_type = data_type;
    this->tmp_var = "";
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

string Expression::getTmpVar()
{
    return tmp_var;
}

void Expression::setTmpVar(string var)
{
    tmp_var = var;
}
const string &Expression::getExpType()
{
    return exp_type;
}
void Expression::setExpType(const string &type)
{
    this->exp_type = type;
}
ArrayCall::ArrayCall() : Expression("ARRAY_CALL")
{
    this->index = NULL;
}
ArrayCall::ArrayCall(Expression *index) : Expression("ARRAY_CALL")
{
    this->index = new Expression(index);
}
ArrayCall::ArrayCall(const string &name, const string &type) : Expression(name, type)
{
    this->index = NULL;
    this->exp_type = "ARRAY_CALL";
}
ArrayCall::ArrayCall(const string &name, const string &type, Expression *index) : Expression(name, type)
{
    this->index = new Expression(index);
    this->exp_type = "ARRAY_CALL";
}
ArrayCall::~ArrayCall()
{
}

Expression *ArrayCall::getIndex()
{
    return index;
}
void ArrayCall::setIndex(Expression *index)
{
    this->index = new Expression(index);
}

Terminal::Terminal(const string &t_type) : SymbolInfo("blank", "")
{
    this->t_type = t_type;
}
Terminal::Terminal(const string &name, const string &type) : SymbolInfo(name, type)
{
    this->t_type = t_type;
}
Terminal::Terminal(const string &name, const string &type, const string &t_type) : SymbolInfo(name, type)
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

Identifier::Identifier(const string &id_type) : Terminal("", "ID", "IDENTIFIER")
{
    this->id_type = id_type;
}

Identifier::Identifier(const string &id_name, const string &id_type) : Terminal(id_name, "ID", "IDENTIFIER")
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
Variable::Variable() : Identifier("VARIABLE")
{
    this->var_type = "";
}
Variable::Variable(const string &var_type) : Identifier("VARIABLE")
{
    this->var_type = var_type;
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

Array::Array(const string &arr_name) : Variable(arr_name, "", "ARRAY")
{
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

Function::Function(const string &func_name) : Identifier(func_name, "FUNCTION")
{
}
Function::~Function()
{
    // cout << name << " destructed" << line_count << endl;
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
        if (func->params[i] != this->params[i])
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
Constant::Constant(const string &data_type) : Terminal("CONSTANT")
{
    this->data_type = data_type;
}
Constant::Constant(const string &name, const string &data_type) : Terminal(name, "", "CONSTANT")
{
    this->data_type = data_type;
}
Constant::Constant(const string &name, const string &type, const string &data_type) : Terminal(name, type, "CONSTANT")
{
    this->data_type = data_type;
}
Constant::~Constant()
{
}
const string &Constant::getDataType()
{
    return data_type;
}
void Constant::setDataType(const string &data_type)
{
    this->data_type = data_type;
}

NonTerminal *createNonTerminal(vector<SymbolInfo *> child, string name)
{
    NonTerminal *node = new NonTerminal(
        hlpr->formatCode(child),
        name);
    logger->printRuleAndCode(node, child);
    return node;
}

Expression *createExpression(vector<SymbolInfo *> child, string name)
{
    Expression *node = new Expression(
        hlpr->formatCode(child),
        name);
    logger->printRuleAndCode(node, child);
    return node;
}

ParameterList *createParameterList(vector<SymbolInfo *> child, string name)
{
    ParameterList *node = new ParameterList(
        hlpr->formatCode(child),
        name);
    logger->printRuleAndCode(node, child);
    return node;
}

DeclarationList *createDeclarationList(vector<SymbolInfo *> child, string name)
{
    DeclarationList *node = new DeclarationList(
        hlpr->formatCode(child),
        name);
    logger->printRuleAndCode(node, child);
    return node;
}

ArgumentList *createArgumentList(vector<SymbolInfo *> child, string name)
{
    ArgumentList *node = new ArgumentList(
        hlpr->formatCode(child),
        name);
    logger->printRuleAndCode(node, child);
    return node;
}

ArrayCall *createArrayCall(vector<SymbolInfo *> child, string name)
{
    ArrayCall *node = new ArrayCall(
        hlpr->formatCode(child),
        name);
    logger->printRuleAndCode(node, child);
    return node;
}