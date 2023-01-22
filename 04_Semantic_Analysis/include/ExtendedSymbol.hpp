/**
 * Author: Mahir Labib Dihan
 * Last modified: January 18, 2023
 */

#ifndef __EXTENDED_SYMBOL_H
#define __EXTENDED_SYMBOL_H 1
#include "../include/SymbolInfo.hpp"
#include <string>
#include <vector>
using namespace std;
// Two types of Symbol
// Terminal and Nonterminal
class Terminal;
class Identifier;
class Variable;
class Function;
class NonTerminal;
class Expression;
class ArrayCall;
class ParameterList;
class ArgumentList;
class DeclarationList;

class Terminal : public SymbolInfo
{
    string t_type;

public:
    Terminal();
    Terminal(const string &t_type);
    Terminal(const string &symbol, const string &type);
    virtual ~Terminal();
    string getTerminalType();
    void setTerminalType(string);
};

class Identifier : public Terminal
{
    string id_type; // Variable, Function
public:
    Identifier(const string &id_type);
    Identifier(const string &id_name, const string &id_type);
    virtual ~Identifier();
    const string &getIdentity();
    void setIdentity(const string &);
};

class Variable : public Identifier
{
    string var_type;  // Primitive, Array
    string data_type; // int, float, char
public:
    Variable();
    Variable(const string &var_type);
    Variable(const string &var_name, const string &data_type);
    Variable(const string &var_name, const string &data_type, const string &var_type);
    virtual ~Variable();
    const string &getVarType();
    void setVarType(const string &);
    const string &getDataType();
    void setDataType(const string &);
};

class Array : public Variable
{
    string arr_size;

public:
    Array(const string &arr_name);
    Array(const string &arr_name, string arr_size);
    Array(const string &arr_name, const string &data_type, string arr_size);
    virtual ~Array();
    string getArraySize();
    void setArraySize(string);
};

class NonTerminal : public SymbolInfo
{
    // Just to maintain the stucture
    string nt_type; // Expression
    std::vector<SymbolInfo *> children;

public:
    NonTerminal();
    NonTerminal(string symbol, string type);
    virtual ~NonTerminal();
    string getNonTerminalType();
    void setNonTerminalType(string nt_type);
    void setChildren(std::vector<SymbolInfo *> children);
    std::vector<SymbolInfo *> getChildren();
};

class Expression : public NonTerminal
{
protected:
    string data_type; // int, float,
    string exp_type;  // Array call

public:
    Expression();
    Expression(const string &exp_type);
    Expression(Expression *);
    Expression(const string &name, const string &type);
    Expression(const string &name, const string &type, const string &data_type);
    virtual ~Expression();
    const string &getDataType();
    void setDataType(const string &);
    const string &getExpression();
    void setExpression(const string &);
    const string &getExpType();
    void setExpType(const string &);
};

class List : public NonTerminal
{
public:
    List();
    List(const string &name, const string &type);
    virtual ~List();
};

class ParameterList : public List
{
    vector<Variable *> list; // Need to destruct

public:
    ParameterList();
    ParameterList(const string &name, const string &type);
    virtual ~ParameterList();
    void addParam(const string &data_type);
    void addParam(const string &data_type, const string &name);
    void addParam(Variable *param);
    void addParams(ParameterList *);
    vector<Variable *> getParams();
};

class ArgumentList : public List
{
    vector<Expression *> list; // Need to destruct

public:
    ArgumentList();
    ArgumentList(const string &name, const string &type);
    virtual ~ArgumentList();
    void addArg(Expression *);
    void addArgs(ArgumentList *);
    vector<Expression *> getArgs();
};

class DeclarationList : public List
{
    vector<Variable *> list; // Need to destruct

public:
    DeclarationList();
    DeclarationList(const string &name, const string &type);
    virtual ~DeclarationList();
    void addVariable(Variable *);
    void addVariable(const string &name);
    void addArray(Array *);
    void addArray(const string &name, const string &size);
    void addVariables(DeclarationList *);
    vector<Variable *> getDeclarations();
};

class ArrayCall : public Expression
{
    string idx;

public:
    ArrayCall();
    ArrayCall(Expression *);
    ArrayCall(const string &name, const string &type);
    ArrayCall(const string &name, const string &type, const string &);
    ~ArrayCall();
    string getIndex();
    void setIndex(string);
};

class Function : public Identifier
{
    string ret_type;
    vector<Variable *> params;
    bool is_declaration;
    bool is_definition;

public:
    Function(const string &func_name);
    Function(const string &func_name, const string &ret_type);
    ~Function();
    const string &getReturnType();
    void setReturnType(const string &);
    void addParam(Variable *);
    void addParams(vector<Variable *>);
    vector<Variable *> getParams();
    int getNumberOfParams();
    bool matchParamsNum(Function *func);
    bool matchParamsType(Function *func);
    bool matchReturnType(Function *func);
    bool isDeclaredAndDefined();
    bool isDeclaredNotDefined();
    void declareFunction();
    void defineFunction();
};

#endif