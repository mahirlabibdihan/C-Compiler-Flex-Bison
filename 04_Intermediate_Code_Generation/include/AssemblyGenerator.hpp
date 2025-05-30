#ifndef __ASSEMBLY_GENERATOR_H
#define __ASSEMBLY_GENERATOR_H 1
#include "../include/ExtendedSymbol.hpp"
#include "../include/SymbolTable.hpp"
#include <fstream>
#include <stack>
#include <map>
class AssemblyGenerator
{

public:
    std::ofstream &asmout;
    int offset_history;
    FunctionDefinition *curr_func;
    int label_count;
    int indent;

public:
    static map<string, string> RelOpASM;

public:
    AssemblyGenerator(std::ofstream &asmout);

    void declareVariable(Variable *var);
    void declareArray(Array *arr);
    void returnFunction();
    void definePrintFunction();

    void declareFunctionParams(std::vector<Variable *> params);
    void print(const string &code);
    void printLabel(const string &label);
    void comment(const string &msg);
    void comment(const string &msg, int line);

    // Short Circuit
    void jumpBoolean(BooleanExpression *expr);
    void jumpLogicOp(LogicOp *expr);
    void jumpRelOp(RelOp *expr);
    void jumpNotOp(NotOp *expr);
    void jumpAndOp(LogicOp *expr);
    void jumpOrOp(LogicOp *expr);

    void incdecOp(VariableCall *expr, std::string op);

    void assignVariable(VariableCall *var_call);
    std::string newLabel();

    bool isZero(Expression *expr);
    bool isOne(Expression *expr);
    bool isConstant(Expression *expr);
    string getConstant(Expression *expr);

    void assignRegister(Expression *expr, string dst_reg);
    void popExpression(Expression *expr);
    void pushExpression(Expression *expr);
};
#endif