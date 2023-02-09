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
    SymbolTable *table;
    std::ofstream &asmout;
    std::vector<int> offset_history;
    FunctionDefinition *curr_func;
    int label_count;
    int indent;

public:
    static map<string, string> RelOpASM;

public:
    AssemblyGenerator(SymbolTable *table, std::ofstream &asmout);

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
    void evaluateCondition(BooleanExpression *expr);
    void evaluateLogicOp(LogicOp *expr);
    void evaluateRelOp(RelOp *expr);
    void evaluateNotOp(NotOp *expr);
    void evaluateAndOp(LogicOp *expr);
    void evaluateOrOp(LogicOp *expr);

    std::string getRelOpASM(string op);
    void incdecOp(VariableCall *expr, std::string op);

    void assignVariable(VariableCall *var_call);
    std::string newLabel();

    bool isZero(Expression *expr);
    bool isOne(Expression *expr);
};
#endif