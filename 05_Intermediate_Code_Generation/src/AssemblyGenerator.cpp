#include "../include/AssemblyGenerator.hpp"
#include "../include/Util.hpp"
#include <sstream>

AssemblyGenerator::AssemblyGenerator(std::ofstream &out) : asmout(out)
{
    indent = 0;
}

void AssemblyGenerator::startProgram(Program *prog)
{
    vector<FunctionDefinition *> func_defs = prog->getFunctionDefinitions();
    vector<VariableDeclaration *> var_decs = prog->getVariableDeclarations();

    print(".MODEL SMALL");
    print(".STACK 100H");
    print(".DATA");
    indent++;
    for (VariableDeclaration *var_dec : var_decs)
    {
        declareVariables(var_dec);
    }
    indent--;
    print(".CODE");
    indent++;
    for (FunctionDefinition *func_def : func_defs)
    {
        defineFunction(func_def);
    }
    indent--;
    print("END MAIN");
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

void AssemblyGenerator::defineFunction(FunctionDefinition *func_def)
{
    string ret_type = func_def->getReturnType();
    string func_name = func_def->getFunctionName();
    vector<Variable *> params = func_def->getParams();
    vector<Statement *> stmt_list = func_def->getBody();

    print(func_name + " PROC");

    indent++;
    print("PUSH BP");
    print("MOV BP, SP");
    print("PUSH AX");
    print("PUSH BX");
    print("PUSH CX");
    print("PUSH DX");

    print("XOR AX, AX");
    print("XOR BX, BX");
    print("XOR CX, CX");
    print("XOR DX, DX");
    // declareFunctionParams(params);
    for (Statement *stmt : stmt_list)
    {
        // analyzeStatement(stmt);
    }

    print("POP DX");
    print("POP CX");
    print("POP BX");
    print("POP AX");
    print("POP BP");

    indent--;
    print(func_name + " ENDP");
}

void AssemblyGenerator::print(const string &code)
{
    string *lines = Util::split(code, '\n');
    int count = Util::countTokens(code, '\n');
    for (int i = 0; i < count; i++)
    {
        for (int j = 1; j <= indent; j++)
        {
            asmout << "\t";
        }
        asmout << lines[i] << std::endl;
    }
}