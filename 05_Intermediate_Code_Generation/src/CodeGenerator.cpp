#include "../include/CodeGenerator.hpp"
#include "../include/Util.hpp"
#include "../include/ExtendedSymbol.hpp"
CodeGenerator::CodeGenerator(std::ofstream &out) : codeout(out)
{
    indent = 0;
    new_line = true;
}

void CodeGenerator::print(const std::string &code)
{
    std::string *lines = Util::split(code, '\n');
    int count = Util::countTokens(code, '\n');
    for (int i = 0; i < count; i++)
    {
        if (new_line)
        {
            for (int j = 1; j <= indent; j++)
            {
                codeout << "\t";
            }
        }
        codeout << lines[i];
        if (i < count - 1)
        {
            codeout << std::endl;
            new_line = true;
        }
    }
    new_line = false;
}

void CodeGenerator::println(const std::string &code)
{
    print(code);
    codeout << std::endl;
    new_line = true;
}

extern CodeGenerator *code_gen;

void Program::toCode()
{
    for (VariableDeclaration *var_dec : var_decs)
    {
        var_dec->toCode();
    }
    for (FunctionDeclaration *func_dec : func_decs)
    {
        func_dec->toCode();
    }
    for (FunctionDefinition *func_def : func_defs)
    {
        func_def->toCode();
    }
}

void VariableDeclaration::toCode()
{
    code_gen->print(Util::toLower(decl_list.front()->getDataType()) + " ");
    for (int i = 0; i < decl_list.size(); i++)
    {
        code_gen->print(decl_list[i]->getIdName());
        if (decl_list[i]->getVarType() == "ARRAY")
        {
            code_gen->print("[" + ((Array *)decl_list[i])->getArraySize() + "]");
        }
        if (i < decl_list.size() - 1)
        {
            code_gen->print(",");
        }
    }
    code_gen->println(";");
}

void FunctionDeclaration::toCode()
{
    code_gen->print(Util::toLower(ret_type) + " ");
    code_gen->print(func_name + "(");
    for (int i = 0; i < params.size(); i++)
    {
        code_gen->print(Util::toLower(params[i]->getDataType()) + " " + params[i]->getIdName());
        if (i < params.size() - 1)
        {
            code_gen->print(",");
        }
    }
    code_gen->println(");");
}

void FunctionDefinition::toCode()
{
    code_gen->print(Util::toLower(ret_type) + " ");
    code_gen->print(func_name + "(");
    for (int i = 0; i < params.size(); i++)
    {
        code_gen->print(Util::toLower(params[i]->getDataType()) + " " + params[i]->getIdName());
        if (i < params.size() - 1)
        {
            code_gen->print(",");
        }
    }
    code_gen->print(")");
    body->toCode();
}

void NotOp::toCode()
{
    code_gen->print(op_symbol);
    operand->toCode();
}

void DecOp::toCode()
{
    operand->toCode();
    code_gen->print(op_symbol);
}

void IncOp::toCode()
{
    operand->toCode();
    code_gen->print(op_symbol);
}

void UAddOp::toCode()
{
    code_gen->print(op_symbol);
    operand->toCode();
}

void BinaryExpression::toCode()
{
    code_gen->print("(");
    left_opr->toCode();
    code_gen->print(op_symbol);
    right_opr->toCode();
    code_gen->print(")");
}

void FunctionCall::toCode()
{
    code_gen->print(id_name + "(");
    for (int i = 0; i < args.size(); i++)
    {
        args[i]->toCode();
        if (i < args.size() - 1)
        {
            code_gen->print(",");
        }
    }
    code_gen->print(")");
}

void VariableCall::toCode()
{
    code_gen->print(id_name);
}
void ArrayCall::toCode()
{
    code_gen->print(id_name + "[");
    idx->toCode();
    code_gen->print("]");
}

void ConstantCall::toCode()
{
    code_gen->print(literal);
}

void IfStatement::toCode()
{
    code_gen->print("if(");
    condition->toCode();
    code_gen->print(")");
    if_body->toCode();
}

void IfElseStatement::toCode()
{
    code_gen->print("if(");
    condition->toCode();
    code_gen->print(")");
    if_body->toCode();
    code_gen->print("else ");
    else_body->toCode();
}

void ForLoop::toCode()
{
    code_gen->print("for(");
    initialize->toCode();
    code_gen->print(";");
    condition->toCode();
    code_gen->print(";");
    inc_dec->toCode();
    code_gen->print(")");
    body->toCode();
}

void WhileLoop::toCode()
{
    code_gen->print("while(");
    condition->toCode();
    code_gen->print(")");
    body->toCode();
}

void PrintStatement::toCode()
{
    code_gen->print("println(");
    var_call->toCode();
    code_gen->println(");");
}

void ReturnStatement::toCode()
{
    code_gen->print("return ");
    expr->toCode();
    code_gen->println(";");
}

void ExpressionStatement::toCode()
{
    expr->toCode();
    code_gen->println(";");
}
void CompoundStatement::toCode()
{
    code_gen->println("\n{");
    code_gen->indent++;
    for (VariableDeclaration *var_dec : var_decs)
    {
        var_dec->toCode();
    }
    for (Statement *stmt : stmt_list)
    {
        stmt->toCode();
    }
    code_gen->indent--;
    code_gen->println("}");
}