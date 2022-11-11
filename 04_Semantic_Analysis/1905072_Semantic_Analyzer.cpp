#include <string>
#include "1905072_SymbolInfo.h"
#include "1905072_Error_Handler.h"
#include "1905072_SymbolTable.h"
#include "1905072_Semantic_Analyzer.h"
#include "1905072_Node.h"
using namespace std;

extern int line_count;
extern bool in_function;
extern SymbolTable *table;
string implicitTypecast(string left, string right)
{
    // cout << left << "," << right << endl;
    if (left == "NULL" || right == "NULL")
    {
        return "NULL"; // already reported , now supressing more errors
    }
    if (left == "void" || right == "void")
    {
        return "ERROR";
    }
    if (left == "float" && right == "float")
    {
        return "float";
    }
    if (left == "float" && right == "int")
    {
        return "float";
    }
    if (left == "int" && right == "float")
    {
        return "float";
    }
    if (left == "int" && right == "int")
    {
        return "int";
    }
    return "ERROR";
}

bool isConvertible(string to, string from)
{
    if (from == "NULL")
    {
        return true; // already error reported and converted to NULL , this is made true to supress more error
    }

    // if (og_p == "void")
    //     return pass_p == "void";
    if (to == "int" && from == "int")
        return true;
    if (to == "int" && from != "void")
        return true;
    return false;
}

bool checkAssignment(string left, string right)
{
    // cout << line_count << " " << left << " " << right << endl;
    if (left == "NULL" || right == "NULL")
    {
        return true; // already error reported and converted to NULL , this is made true to supress more error
    }
    if (left == "void" || right == "void") // Void not allowed
    {
        return false;
    }
    if (left == "" || right == "") // Not an expression/variable
    {
        return false;
    }
    if (left == "int" && right == "int")
    {
        return true;
    }
    if (left == "float")
    {
        return true;
    }
    return false;
}

void defineFunction(SymbolInfo *function, vector<SymbolInfo *> params, string ret_type)
{
    in_function = true;
    function->setDataType(ret_type);

    for (auto &temp_p : params)
    {
        function->getParamTypes().push_back(temp_p->getDataType());
    }

    if (!table->insert(*function))
    {
        SymbolInfo *symbol = table->search(function->getName());
        if (symbol->getIdType() != "FUNCTION" or symbol->isDefined()) // Already declared as non-function type or Defined as function
        {
            handleError(MULTIPLE_DECLARATION, line_count, function->getName());
        }
        else
        {
            symbol->define();
            if (symbol->getDataType() != function->getDataType())
            {
                handleError(RETURN_TYPE_MISMATCH, line_count, function->getName());
            }
            if (symbol->getParamTypes().size() != function->getParamTypes().size())
            {
                handleError(PARAM_NUMBER_MISMATCH, line_count, function->getName());
            }
            else
            {
                for (int i = 0; i < symbol->getParamTypes().size(); i++)
                {
                    if (symbol->getParamTypes()[i] != function->getParamTypes()[i])
                    {
                        handleError(PARAM_TYPE_MISMATCH, line_count, function->getName());
                        break;
                    }
                }
            }
        }
    }
    else
    {
        SymbolInfo *symbol = table->search(function->getName());
        symbol->define();
        symbol->setIdType("FUNCTION");

        for (auto &i : params)
        {
            if (i->getName() == "blank")
            {
                handleError(MISSING_PARAM_NAME, line_count, function->getName());
            }
        }
    }
}

void declareFunction(string ret_type, SymbolInfo *id, vector<SymbolInfo *> params)
{
    id->setDataType(ret_type);
    id->setIdType("FUNCTION");

    for (auto i : params)
    {
        id->getParamTypes().push_back(i->getDataType());
    }

    if (table->insert(*id))
    {
        SymbolInfo *symbol = table->search(id->getName());
    }
    else
    {
        handleError(MULTIPLE_DECLARATION, line_count, id->getName());
    }
}

string callFunction(string id, vector<SymbolInfo *> args)
{
    SymbolInfo *symbol = table->search(id);

    if (symbol == NULL)
    {
        handleError(UNDECLARED_FUNCTION, line_count, id);
        return "NULL";
    }
    else if (symbol->getIdType() != "FUNCTION")
    {
        handleError(NOT_FUNCTION, line_count, id);
        return "NULL";
    }
    else
    {
        if (!symbol->isDefined())
        {
            handleError(UNDEFINED_FUNCTION, line_count, id);
        }
        else if (symbol->getParamTypes().size() < args.size())
        {
            handleError(TOO_MANY_ARGUMENTS, line_count, id);
        }
        else if (symbol->getParamTypes().size() > args.size())
        {
            handleError(TOO_FEW_ARGUMENTS, line_count, id);
        }
        else
        {
            for (int i = 0; i < symbol->getParamTypes().size(); i++)
            {
                if (!isConvertible(
                        symbol->getParamTypes()[i],
                        args[i]->getDataType()))
                {
                    handleError(ARGUMENT_TYPE_MISMATCH, line_count, id);
                    break;
                }
            }
        }
        return symbol->getDataType();
    }
}
void declareVariable(string data_type, string id_names, vector<SymbolInfo *> ids)
{
    if (data_type == "void")
    {
        handleError(VOID_VARIABLE, line_count, id_names);
    }
    else
    {
        for (auto &i : ids)
        {
            if (i->getIdType() == "ARRAY")
            {
                i->setDataType(data_type + "_array");
            }
            else
            {
                i->setDataType(data_type);
            }

            if (!table->insert(*i)) // already present in current scope
            {
                handleError(MULTIPLE_DECLARATION, line_count, i->getName());
            }
        }
    }
}

string callVariable(string id)
{
    SymbolInfo *symbol = table->search(id);

    if (symbol == NULL)
    {
        handleError(UNDECLARED_VARIABLE, line_count, id);
        return "NULL";
    }
    else
    {
        if (symbol->getIdType() == "ARRAY")
        {
            handleError(TYPE_MISMATCH, line_count, id + " is not a variable"); // should i change this to indexing
            return "NULL";
        }
        else
        {
            return symbol->getDataType();
        }
    }
}

string callArray(string id, SymbolInfo *index)
{

    SymbolInfo *symbol = table->search(id);

    if (symbol == NULL)
    {
        handleError(UNDECLARED_VARIABLE, line_count, id);
        return "NULL";
    }
    else
    {
        if (symbol->getIdType() != "ARRAY")
        {
            handleError(TYPE_MISMATCH, line_count, id + " is not an array");
            return "NULL";
        }
        else
        {
            return symbol->getDataType() == "int_array" ? "int" : "float";
        }
    }

    if (index->getDataType() != "int")
    {
        handleError(INVALID_ARRAY_INDEX, line_count, index->getName());
    }
}

string assignmentOperation(string left, string right)
{
    if (!checkAssignment(left, right))
    {
        if (left == "void" || right == "void")
        {
            handleError(INVALID_OPERAND, line_count, "of types '" + left + "' and '" + right + "' to 'operator='");
            return "NULL";
        }
        else
        {
            handleError(INVALID_CONVERSION, line_count, "from '" + right + "' to '" + left + "'");
            return "NULL";
        }
    }
    else
    {
        return left;
    }
}

string logicalOperation(string left, string op, string right)
{
    string type = implicitTypecast(left, right);

    if (type != "NULL")
    {
        if (type != "ERROR")
        {
            return "int";
        }
        else
        {
            if (left == "void" || right == "void")
            {
                handleError(INVALID_OPERAND, line_count, "of types '" + left + "' and '" + right + "' to 'operator" + op + "'");
            }
            else
            {
                handleError(INCOMPATIBLE_OPERAND, line_count);
            }
            return "NULL";
        }
    }
    else
    {
        return "NULL";
    }
}

string relationalOperation(string left, string op, string right)
{
    string type = implicitTypecast(left, right);

    if (type != "NULL")
    {
        if (type != "ERROR")
        {
            return "int";
        }
        else
        {
            if (left == "void" || right == "void")
            {
                handleError(INVALID_OPERAND, line_count, "of types '" + left + "' and '" + right + "' to 'operator" + op + "'");
            }
            else
            {
                handleError(INCOMPATIBLE_OPERAND, line_count);
            }
            return "NULL";
        }
    }
    else
    {
        return "NULL";
    }
}

string additionalOperation(string left, string op, string right)
{
    string type = implicitTypecast(left, right);

    if (type != "NULL")
    {
        if (type != "ERROR")
        {
            return type;
        }
        else
        {
            if (left == "void" || right == "void")
            {
                handleError(INVALID_OPERAND, line_count, "of types '" + left + "' and '" + right + "' to 'operator" + op + "'");
            }
            else
            {
                handleError(INCOMPATIBLE_OPERAND, line_count);
            }
            return "NULL";
        }
    }
    else
    {
        return "NULL";
    }
}

string multiplicationalOperation(string left, string op, string right)
{
    string type = implicitTypecast(left, right);

    if (op == "%") // both operand should be integer
    {
        if (right == "0")
        {
            handleError(MOD_BY_ZERO, line_count, left + "%" + right);
            return "NULL";
        }
        else
        {
            if (type != "int")
            {
                handleError(INVALID_OPERAND, line_count, "of types '" + left + "' and '" + right + "' to 'operator" + op + "'");
                return "NULL";
            }
            else
            {
                return "int";
            }
        }
    }
    else if (type != "NULL")
    {
        if (type != "ERROR")
        {
            return type;
        }
        else
        {
            if (left == "void" || right == "void")
            {
                handleError(INVALID_OPERAND, line_count, "of types '" + left + "' and '" + right + "' to 'operator" + op + "'");
            }
            else
            {
                handleError(INCOMPATIBLE_OPERAND, line_count);
            }
            return "NULL";
        }
    }
    else
    {
        return "NULL";
    }
}