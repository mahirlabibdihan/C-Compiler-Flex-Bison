#include "../include/ExtendedSymbol.hpp"
#include "../include/Util.hpp"
string Program::getCode()
{
    string code = "";
    for (VariableDeclaration *var_dec : var_decs)
    {
        code += var_dec->getCode() + "\n";
    }
    for (FunctionDeclaration *func_dec : func_decs)
    {
        code += func_dec->getCode() + "\n";
    }
    for (FunctionDefinition *func_def : func_defs)
    {
        code += func_def->getCode() + "\n";
    }
    return code;
}

string VariableDeclaration::getCode()
{
    string code = Util::toLower(decl_list.front()->getDataType()) + " ";

    for (Variable *var : decl_list)
    {
        code += var->getIdName();
        if (var->getVarType() == "ARRAY")
        {
            code += +"[" + ((Array *)var)->getArraySize() + "]";
        }
        code += ",";
    }
    if (code.back() == ',')
    {
        code.pop_back();
    }
    code += ";";
    return code;
}

string FunctionDeclaration::getCode()
{
    string code = "";
    code += Util::toLower(ret_type) + " ";
    code += func_name + "(";
    for (Variable *var : params)
    {
        code += Util::toLower(var->getDataType()) + " " + var->getIdName() + ",";
    }
    if (code.back() == ',')
    {
        code.pop_back();
    }
    code += ");";
    return code;
}

string FunctionDefinition::getCode()
{
    string code = "";
    code += Util::toLower(ret_type) + " ";
    code += func_name + "(";
    for (Variable *var : params)
    {
        code += Util::toLower(var->getDataType()) + " " + var->getIdName() + ",";
    }
    if (code.back() == ',')
    {
        code.pop_back();
    }
    code += ")";
    code += body->getCode();
    return code;
}
string NotOp::getCode()
{
    return op_symbol + operand->getCode();
}

string DecOp::getCode()
{
    return operand->getCode() + op_symbol;
}

string IncOp::getCode()
{
    return operand->getCode() + op_symbol;
}

string UAddOp::getCode()
{
    return op_symbol + operand->getCode();
}

string BinaryExpression::getCode()
{
    return this->left_opr->getCode() + op_symbol + this->right_opr->getCode();
}

string FunctionCall::getCode()
{
    string code = id_name + "(";
    for (Expression *arg : args)
    {
        code += arg->getCode() + ",";
    }
    if (code.back() == ',')
    {
        code.pop_back();
    }
    code += ")";
    return code;
}

string VariableCall::getCode()
{
    return id_name;
}

string ArrayCall::getCode()
{
    return id_name + "[" + idx->getCode() + "]";
}

string ConstantCall::getCode()
{
    return this->literal;
}

string IfStatement::getCode()
{
    string code = "";
    code += "if(";
    code += condition->getCode() + ")";
    code += if_body->getCode();
    return code;
}

string IfElseStatement::getCode()
{
    string code = "";
    code += "if(";
    code += condition->getCode() + ")";
    code += if_body->getCode();
    code += "else ";
    code += else_body->getCode();
    return code;
}

string ForLoop::getCode()
{
    string code = "";
    code += "for(";
    code += initialize->getCode() + ";";
    code += condition->getCode() + ";";
    code += inc_dec->getCode() + ")";
    code += body->getCode();
    return code;
}

string WhileLoop::getCode()
{
    string code = "";
    code += "while(";
    code += condition->getCode() + ")";
    code += body->getCode();
    return code;
}

string PrintStatement::getCode()
{
    return "println(" + this->var_call->getCode() + ");";
}

string ReturnStatement::getCode()
{
    return "return " + (expr != NULL ? expr->getCode() : "") + ";";
}

string ExpressionStatement::getCode()
{
    return expr->getCode() + ";";
}

string CompoundStatement::getCode()
{
    string code = "{\n";

    for (VariableDeclaration *var_dec : var_decs)
    {
        code += var_dec->getCode() + "\n";
    }
    for (Statement *stmt : stmt_list)
    {
        code += stmt->getCode() + "\n";
    }
    code += "}";
    return code;
}
