#ifndef __ASSEMBLY_GENERATOR_H
#define __ASSEMBLY_GENERATOR_H 1
#include "../include/ExtendedSymbol.hpp"
#include <fstream>
class AssemblyGenerator
{
    std::ofstream &asmout;
    int indent;

public:
    AssemblyGenerator(std::ofstream &asmout);
    void startProgram(Program *prog);

    void declareVariable(Variable *var);
    void declareArray(Array *arr);

    void declareVariables(VariableDeclaration *var_decl);
    void declareFunction(FunctionDeclaration *func_decl);
    void defineFunction(FunctionDefinition *func_def);

    void print(const string &code);
};
#endif