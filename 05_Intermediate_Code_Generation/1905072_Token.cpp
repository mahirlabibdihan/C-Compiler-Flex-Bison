#include "1905072_Token.h"
#include "1905072_Helper.h"
Token::Token(string token_type) : SymbolInfo("blank", "")
{
    this->token_type = token_type;
}
Token::Token(string name, string token_type) : SymbolInfo(name, "")
{
    this->token_type = token_type;
}
Token::Token(string name, string type, string token_type) : SymbolInfo(name, type)
{
    this->token_type = token_type;
}
Token::~Token()
{
}
string Token::getTokenType()
{
    return token_type;
}
void Token::setTokenType(string type)
{
    this->token_type = type;
}

Identifier::Identifier(const string &id_type) : Token("", "ID", "IDENTIFIER")
{
    this->id_type = id_type;
}

Identifier::Identifier(const string &id_name, const string &id_type) : Token(id_name, "ID", "IDENTIFIER")
{
    this->id_type = id_type;
}

Identifier::~Identifier()
{
}
const string &Identifier::getIdType()
{
    return id_type;
}

void Identifier::setIdType(const string &id_type)
{
    this->id_type = id_type;
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
Array::Array(const string &arr_name, const int &arr_size) : Variable(arr_name, "", "ARRAY")
{
    this->arr_size = arr_size;
}
Array::Array(const string &arr_name, const string &data_type, const int &arr_size) : Variable(arr_name, data_type, "ARRAY")
{
    this->arr_size = arr_size;
}
Array::~Array()
{
}
const int &Array::getArraySize()
{
    return arr_size;
}
void Array::setArraySize(const int &arr_size)
{
    this->arr_size = arr_size;
}

Function::Function(const string &func_name) : Identifier(func_name, "FUNCTION")
{
}
Function::~Function()
{
}
const string &Function::getReturnType()
{
    return ret_type;
}
void Function::setReturnType(const string &type)
{
    this->ret_type = type;
}
void Function::addParam(const string &param)
{
    param_types.push_back(param);
}
void Function::addParams(const vector<string> &params)
{
    for (auto param : params)
    {
        addParam(param);
    }
}
int Function::getNumberOfParams()
{
    return param_types.size();
}
bool Function::isValidArgs(vector<string> args)
{
    for (int i = 0; i < param_types.size(); i++)
    {
        if (!isConvertible(param_types[i], args[i]))
        {
            return false;
        }
    }
    return true;
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
    return func->param_types.size() == this->param_types.size();
}
bool Function::matchParamsType(Function *func)
{
    for (int i = 0; i < param_types.size(); i++)
    {
        if (func->param_types[i] != this->param_types[i])
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
Constant::Constant(const string &data_type) : Token("CONSTANT")
{
    this->data_type = data_type;
}
Constant::Constant(const string &name, const string &data_type) : Token(name, "", "CONSTANT")
{
    this->data_type = data_type;
}
Constant::Constant(const string &name, const string &type, const string &data_type) : Token(name, type, "CONSTANT")
{
    this->data_type = data_type;
}
const string &Constant::getDataType()
{
    return data_type;
}
void Constant::setDataType(const string &data_type)
{
    this->data_type = data_type;
}
