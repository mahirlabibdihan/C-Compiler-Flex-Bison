#include "../include/AssemblyGenerator.hpp"

AssemblyGenerator::AssemblyGenerator(std::ofstream &out) : asmout(out)
{
}

void AssemblyGenerator::startProgram(Program *prog)
{
    vector<FunctionDefinition *> func_defs = prog->getFunctionDefinitions();
    vector<FunctionDeclaration *> func_decs = prog->getFunctionDeclarations();
    vector<VariableDeclaration *> var_decs = prog->getVariableDeclarations();

    asmout << ".MODEL SMALL" << std::endl;
    asmout << ".STACK 100H" << std::endl;
    asmout << ".DATA" << std::endl;
    for (VariableDeclaration *var_dec : var_decs)
    {
        declareVariables(var_dec);
    }
    asmout << ".CODE" << std::endl;
    for (FunctionDefinition *func_def : func_defs)
    {
        // defineFunction(func_def);
    }
    asmout << "END MAIN" << std::endl;
}

void AssemblyGenerator::declareVariables(VariableDeclaration *var_decl)
{
    vector<Variable *> vars = var_decl->getDeclarationList();

    for (Variable *var : vars)
    {
        if (var->getVarType() == "ARRAY")
        {
            declareArray((Array *)var);
        }
        else
        {
            declareVariable(var);
        }
    }
}

void AssemblyGenerator::declareVariable(Variable *var)
{
    asmout << "\t" << var->getIdName() << " DW ?" << std::endl;
}
void AssemblyGenerator::declareArray(Array *arr)
{
    asmout << "\t" << arr->getIdName() << " DW " << arr->getArraySize() << " DUP(?)" << std::endl;
}