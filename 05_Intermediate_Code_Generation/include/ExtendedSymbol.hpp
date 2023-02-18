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
class Array;
class Function;

class NonTerminal;

// Non Terminal
class Expression;
class Unit;
class List;
class Statement;
class Program;

// Expression
class CallExpression;
class BinaryExpression;
class UnaryExpression;

// Call Expression
class ConstantCall;
class IntegerCall;
class IdentifierCall;
class VariableCall;
class ArrayCall;
class FunctionCall;

// Binary Expression
class AssignOp;
class AddOp;
class MulOp;
class LogicOp;
class RelOp;

// Unary Expression
class IncOp;
class DecOp;
class NotOp;

// Unit
class VariableDeclaration;
class FunctionDeclaration;
class FunctionDefinition;

// List
class ParameterList;
class ArgumentList;
class DeclarationList;

// Statement
class ConditionalStatement;
class IfStatement;
class IfElseStatement;
class LoopStatement;
class WhileLoop;
class ForLoop;

class CompoundStatement;

class BooleanExpression;
class ASTNode : public SymbolInfo
{
protected:
    std::string ast_type;

public:
    ASTNode(const string &ast_type, const string &name = "", const string &type = "");
    virtual ~ASTNode();
    const string &getASTType();
    void setASTType(const string &ast_type);
};

class Terminal : public ASTNode
{
    string t_type;

public:
    Terminal(const string &name, const string &type, const string &t_type);
    virtual ~Terminal();
    string getTerminalType();
    void setTerminalType(string);
};

class Identifier : public Terminal
{
    string id_type; // Variable, Function
    string id_name;
    string unique_name;

public:
    Identifier(const string &id_name, const string &id_type);
    virtual ~Identifier();
    const string &getIdentity();
    void setIdentity(const string &);
    void setIdName(const string &);
    const string &getIdName();
    void setUniqueName(const string &);
    const string &getUniqueName();
};

class Variable : public Identifier
{
    string var_type;  // Primitive, Array
    string data_type; // int, float, char
    int offset;
    bool is_global;

public:
    Variable(const string &var_name, const string &data_type, const string &var_type = "PRIMITIVE");
    virtual ~Variable();
    const string &getVarType();
    void setVarType(const string &);
    const string &getDataType();
    void setDataType(const string &);
    void setOffset(int offset);
    int getOffset();
    bool isGlobal();
    void makeGlobal();
};

class Array : public Variable
{
    string arr_size;

public:
    Array(const string &arr_name, const string &data_type, string arr_size);
    virtual ~Array();
    string getArraySize();
    void setArraySize(string);
};

class Function : public Identifier
{
    string ret_type;
    vector<Variable *> params;
    bool is_declaration;
    bool is_definition;

public:
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

class NonTerminal : public ASTNode
{
    // Just to maintain the stucture
    string nt_type; // Expression
    std::vector<SymbolInfo *> children;

public:
    NonTerminal(string nt_type);
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
    string exp_type;  // CallExpression, BinaryExpression, UnaryExpression

public:
    Expression(const string &exp_type);
    virtual ~Expression();
    const string &getDataType();
    void setDataType(const string &);
    const string &getExpType();
    void setExpType(const string &);
    virtual string getCode() = 0;
    virtual void toCode() = 0;
    virtual void toAssembly() = 0;
    virtual string checkSemantics() = 0;

    static bool isVariableCall(Expression *);
    static bool isArrayCall(Expression *);
    static bool isConstant(Expression *);
    static int getConstant(Expression *);
    static string getVariable(VariableCall *);
};

class List : public NonTerminal
{
    string l_type; // CompoundStatement, ParameterList, ArgumentList, DeclarationList

public:
    List(const string &l_type);
    virtual ~List();
    const string &getListType();
};

class Statement : virtual public NonTerminal
{
    string stmt_type; // ConditionalStatement, LoopStatement, CompoundStatement
    string next_label;

public:
    Statement(const string &stmt_type);
    const string &getStatementType();
    void setNextLabel(const string &label);
    const string &getNextLabel();
    virtual string getCode() = 0;
    virtual void toCode() = 0;
    virtual void toAssembly() = 0;
    virtual void checkSemantics() = 0;
};

class CompoundStatement : public Statement
{
    vector<VariableDeclaration *> var_decs;
    vector<Statement *> stmt_list; // Need to destruct

public:
    CompoundStatement(); // **
    void addStatement(Statement *stmt);
    const vector<Statement *> &getStatements();
    void addVariableDeclaration(VariableDeclaration *var_dec);
    const vector<VariableDeclaration *> &getVariableDeclarations();
    string getCode();
    void toCode();
    void toAssembly();
    void checkSemantics();
};

class ParameterList : public List
{
    vector<Variable *> list; // Need to destruct

public:
    ParameterList(); // **
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
    ArgumentList(); // **
    virtual ~ArgumentList();
    void addArg(Expression *);
    void addArgs(ArgumentList *);
    vector<Expression *> getArgs();
};

class DeclarationList : public List
{
    vector<Variable *> list; // Need to destruct

public:
    DeclarationList(); // **
    virtual ~DeclarationList();
    void addVariable(Variable *);
    void addVariable(const string &name);
    void addArray(Array *);
    void addArray(const string &name, const string &size);
    void addVariables(DeclarationList *);
    vector<Variable *> getDeclarations();
};

class ConditionalStatement : public Statement
{
protected:
    BooleanExpression *condition;
    string c_type; // IF, IF_ELSE

public:
    ConditionalStatement(string c_type, Expression *condition);
    Expression *getCondition();
    const string &getConditionType();
};

class IfStatement : public ConditionalStatement
{
    Statement *if_body;

public:
    IfStatement(Expression *condition, Statement *body); // **
    Statement *getIfBody();
    string getCode();
    void toCode();
    void toAssembly();
    void checkSemantics();
};

class IfElseStatement : public ConditionalStatement
{
    Statement *if_body;
    Statement *else_body;

public:
    IfElseStatement(Expression *condition, Statement *if_body, Statement *else_body);
    Statement *getIfBody();
    Statement *getElseBody();
    string getCode();
    void toCode();
    void toAssembly();
    void checkSemantics();
};

class LoopStatement : public Statement
{
protected:
    BooleanExpression *condition;
    Statement *body;
    string l_type;

public:
    LoopStatement(Expression *condition, Statement *body, const string &l_type);
    Expression *getCondition();
    Statement *getBody();
    const string &getLoopType();
};

class ForLoop : public LoopStatement
{
    Expression *initialize;
    Expression *inc_dec;

public:
    ForLoop(Expression *initialize, Expression *condition, Expression *inc_dec, Statement *body); // **
    Expression *getInitialize();
    Expression *getIncDec();
    string getCode();
    void toCode();
    void toAssembly();
    void checkSemantics();
};

class WhileLoop : public LoopStatement
{
public:
    WhileLoop(Expression *condition, Statement *body); // **
    string getCode();
    void toCode();
    void toAssembly();
    void checkSemantics();
};

class PrintStatement : public Statement
{
    VariableCall *var_call;

public:
    PrintStatement(VariableCall *var_call); // **
    VariableCall *getVariableCall();
    string getCode();
    void toCode();
    void toAssembly();
    void checkSemantics();
};

class ReturnStatement : public Statement
{
    Expression *expr;

public:
    ReturnStatement(Expression *expr); // **
    Expression *getExpression();
    string getCode();
    void toCode();
    void toAssembly();
    void checkSemantics();
};

class ExpressionStatement : public Statement
{
    Expression *expr;

public:
    ExpressionStatement(Expression *expr); // **
    Expression *getExpression();
    string getCode();
    void toCode();
    void toAssembly();
    void checkSemantics();
};

class CallExpression : public Expression
{
    string call_type;

public:
    CallExpression(const string &data_type, const string &call_type);
    const string &getCallType();
};

class IdentifierCall : public CallExpression
{
protected:
    string id_name;
    string id_type;
    Identifier *id;

public:
    IdentifierCall(const string &id_name, const string &id_type);
    const string &getIdName();
    const string &getIdentity();
    void setIdentifier(Identifier *id);
    Identifier *getIdentifier();
};

class FunctionCall : public IdentifierCall
{
    vector<Expression *> args;

public:
    FunctionCall(const string &func_name, const vector<Expression *> &args); // **
    const vector<Expression *> &getArgs();
    string getCode();
    void toCode();
    void toAssembly();
    string checkSemantics();
};

class VariableCall : public IdentifierCall
{
    string var_type;

public:
    VariableCall(const string &var_name, const string &var_type = "PRIMITIVE_CALL"); // **
    const string &getVarType();

    string getCode();
    void toCode();
    void toAssembly();
    string checkSemantics();
};

class ArrayCall : public VariableCall
{
    Expression *idx;

public:
    ArrayCall(const string &var_name, Expression *idx); // **
    ~ArrayCall();
    Expression *getIndex();
    void setIndex(Expression *);
    string getCode();
    void toCode();
    void toAssembly();
    string checkSemantics();
};

class ConstantCall : public CallExpression
{
protected:
    string literal;

public:
    ConstantCall(const string &literal, const string &data_type);
    const string &getLiteral();
    string getCode();
    void toCode();
    void toAssembly();
    string checkSemantics();
};

class IntegerCall : public ConstantCall
{
public:
    IntegerCall(const string &literal); // **
};

class FloatCall : public ConstantCall
{
public:
    FloatCall(const string &literal); // **
};

class BinaryExpression : virtual public Expression
{
protected:
    Expression *left_opr;
    Expression *right_opr;
    string op_type;
    string op_symbol;

public:
    BinaryExpression(const string &op_type, const string &op_symbol, Expression *left, Expression *right);
    Expression *getLeftOpr();
    Expression *getRightOpr();
    void setLeftOpr(Expression *);
    void setRightOpr(Expression *);
    const string &getOpType();
    const string &getOperator();
    void setOperator(string);
    string getCode();
    void toCode();
};

class AssignOp : public BinaryExpression
{

public:
    AssignOp(VariableCall *left, Expression *right); // **
    void toAssembly();
    string checkSemantics();
};

class AddOp : public BinaryExpression
{
    string add_oprt;

public:
    AddOp(Expression *left, Expression *right, const string &add_oprt);
    void toAssembly();
    string checkSemantics();
};

class MulOp : public BinaryExpression
{
    string mul_oprt;

public:
    MulOp(Expression *left, Expression *right, const string &mul_oprt);
    void toAssembly();
    string checkSemantics();
};

class BooleanExpression : virtual public Expression
{
    string true_label;
    string false_label;
    string bool_type;

public:
    BooleanExpression(const string &);
    void setTrueLabel(const string &label);
    const string &getTrueLabel();
    void setFalseLabel(const string &label);
    const string &getFalseLabel();
    void setBoolType(const string &type);
    const string &getBoolType();
};

class LogicOp : public BinaryExpression, public BooleanExpression
{
    string logic_oprt;

public:
    LogicOp(Expression *left, Expression *right, const string &logic_oprt);
    void toAssembly();
    string checkSemantics();
};

class RelOp : public BinaryExpression, public BooleanExpression
{
    string rel_oprt;

public:
    RelOp(Expression *left, Expression *right, const string &rel_oprt);
    void toAssembly();
    string checkSemantics();
};

class UnaryExpression : virtual public Expression
{
protected:
    Expression *operand;
    string op_type;
    string op_symbol;

public:
    UnaryExpression(const string &op_type, const string &op_symbol, Expression *operand);
    const string &getOpType();
    Expression *getOperand();
    const string &getOperator();
};

class UAddOp : public UnaryExpression
{
    string uadd_oprt;

public:
    UAddOp(Expression *right, const string &oprt);
    string getCode();
    void toCode();
    void toAssembly();
    string checkSemantics();
};

class IncOp : public UnaryExpression
{
public:
    IncOp(Expression *left); // **
    string getCode();
    void toCode();
    void toAssembly();
    string checkSemantics();
};

class DecOp : public UnaryExpression
{
public:
    DecOp(Expression *left); // **
    string getCode();
    void toCode();
    void toAssembly();
    string checkSemantics();
};

class NotOp : public UnaryExpression, public BooleanExpression
{
public:
    NotOp(Expression *right);
    string getCode();
    void toCode();
    void toAssembly();
    string checkSemantics();
};

class Program : public NonTerminal
{
    vector<FunctionDefinition *> func_defs;
    vector<FunctionDeclaration *> func_decs;
    vector<VariableDeclaration *> var_decs;

public:
    Program(); // **
    void addFunctionDefinition(FunctionDefinition *func_def);
    void addFunctionDeclaration(FunctionDeclaration *func_dec);
    void addVariableDeclaration(VariableDeclaration *var_dec);
    void addUnit(Unit *unit);
    const vector<FunctionDefinition *> &getFunctionDefinitions();
    const vector<FunctionDeclaration *> &getFunctionDeclarations();
    const vector<VariableDeclaration *> &getVariableDeclarations();
    string getCode();
    void toCode();
    void toAssembly();
    void checkSemantics();
};

class Unit : virtual public NonTerminal
{
    string u_type;

public:
    Unit(const string &u_type);
    const string &getUnitType();
};

class FunctionDefinition : public Unit, public Statement
{
    string ret_type;
    string func_name;
    string return_label;
    vector<Variable *> params; // Replace with vector<Variable*> params
    CompoundStatement *body;   // Replace with vector<Statement*> params
    Function *func;

public:
    FunctionDefinition(const string &func_name, const string &ret_type, vector<Variable *> params, CompoundStatement *body);
    const string &getReturnType();
    const string &getFunctionName();
    const vector<Variable *> &getParams();
    CompoundStatement *getBody();
    void setReturnLabel(const string &label);
    const string &getReturnLabel();
    string getCode();
    void toCode();
    void toAssembly();
    void checkSemantics();
    void setFunction(Function *func);
    Function *getFunction();
};

class FunctionDeclaration : public Unit, public Statement
{
    string ret_type;
    string func_name;
    vector<Variable *> params;

public:
    FunctionDeclaration(const string &func_name, const string &ret_type, vector<Variable *> params); // **
    const string &getReturnType();
    const string &getFunctionName();
    const vector<Variable *> &getParams();
    string getCode();
    void toCode();
    void toAssembly();
    void checkSemantics();
};

class VariableDeclaration : public Unit, public Statement
{
    vector<Variable *> decl_list;

public:
    VariableDeclaration(const string &data_type, const vector<Variable *> &list); // **
    void setDeclarationList(const vector<Variable *> &list);
    const vector<Variable *> &getDeclarationList();
    string getCode();
    void toCode();
    void toAssembly();
    void checkSemantics();
};

#endif