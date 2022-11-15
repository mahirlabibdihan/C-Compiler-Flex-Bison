#ifndef __TOKEN__
#define __TOKEN__
#include <string>
#include <vector>
#include "1905072_SymbolInfo.h"
using namespace std;

class Token : public SymbolInfo
{
    string token_type; // Identifier, Constant, Keyword, Constant

public:
    Token(string token_type);
    Token(string name, string token_type);
    Token(string name, string type, string token_type);
    ~Token();
    string getTokenType();
    void setTokenType(string type);
};

class Identifier : public Token
{
    string id_type; // Variable, Function
public:
    Identifier(const string &id_type);
    Identifier(const string &id_name, const string &id_type);
    ~Identifier();
    const string &getIdType();
    void setIdType(const string &);
};

class Variable : public Identifier
{
    string var_type;  // Primitive, Array
    string data_type; // int, float, char
public:
    Variable(const string &var_type);
    Variable(const string &var_name, const string &data_type);
    Variable(const string &var_name, const string &data_type, const string &var_type);
    ~Variable();
    const string &getVarType();
    void setVarType(const string &);
    const string &getDataType();
    void setDataType(const string &);
};

class Array : public Variable
{
    int arr_size;

public:
    Array(const string &arr_name);
    Array(const string &arr_name, const int &arr_size);
    Array(const string &arr_name, const string &data_type, const int &arr_size);
    ~Array();
    const int &getArraySize();
    void setArraySize(const int &);
};

class Function : public Identifier
{
    string ret_type;
    vector<string> param_types;
    bool is_declaration;
    bool is_definition;

public:
    Function(const string &func_name);
    ~Function();
    const string &getReturnType();
    void setReturnType(const string &);
    void addParam(const string &);
    void addParams(const vector<string> &);
    int getNumberOfParams();
    bool isValidArgs(vector<string> args);
    bool matchParamsNum(Function *func);
    bool matchParamsType(Function *func);
    bool matchReturnType(Function *func);
    bool isDeclaredAndDefined();
    bool isDeclaredNotDefined();
    void declareFunction();
    void defineFunction();
};

class Operator : public Token
{
    string opr_type;
};

class Constant : public Token
{
    string data_type;

public:
    Constant(const string &);
    Constant(const string &, const string &);
    Constant(const string &, const string &, const string &);
    ~Constant();
    const string &getDataType();
    void setDataType(const string &);
};

class Keyword : public Token
{
};
#endif