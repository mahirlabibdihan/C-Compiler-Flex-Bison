#include <iostream>
#include <fstream>
#include <string>
#include "../include/ErrorHandler.hpp"
#include "../include/SymbolTable.hpp"
using namespace std;

ErrorHandler::ErrorHandler()
{
    error_count = 0;
}
std::string ErrorHandler::getError(string error, int line)
{
    error_count++;
    // std::cout << error << std::endl;
    return error;
}
std::string ErrorHandler::getLexicalError(string error, int line)
{
    lexical_error_count++;
    return "Error at line# " + std::to_string(line) + ": " + getError(error, line);
}

std::string ErrorHandler::getSemanticError(string error, int line)
{
    semantic_error_count++;
    return "Line# " + std::to_string(line) + ": " + getError(error, line);
}

std::string ErrorHandler::getSyntaxError(string error, int line)
{
    syntax_error_count++;
    return "Line# " + std::to_string(line) + ": " + getError(error, line);
}

std::string ErrorHandler::handleLexicalError(LexicalError type, int line, string lexeme)
{
    switch (type)
    {
    case TOO_MANY_DECIMAL:
        return getLexicalError("TOO_MANY_DECIMAL_POINTS " + lexeme, line);
        break;
    case ILL_NUMBER:
        return getLexicalError("ILLFORMED_NUMBER " + lexeme, line);
        break;
    case INVALID_IDENTIFIER:
        return getLexicalError("INVALID_ID_SUFFIX_NUM_PREFIX " + lexeme, line);
        break;
    case MULTI_CHARACTER:
        return getLexicalError("MULTICHAR_CONST_CHAR " + lexeme, line);
        break;
    case UNFINISHED_CHARACTER:
        return getLexicalError("UNFINISHED_CONST_CHAR " + lexeme, line);
        break;
    case EMPTY_CHARACTER:
        return getLexicalError("EMPTY_CONST_CHAR " + lexeme, line);
        break;
    case UNFINISHED_STRING:
        return getLexicalError("UNFINISHED_STRING " + lexeme, line);
        break;
    case UNFINISHED_COMMENT:
        return getLexicalError("UNFINISHED_COMMENT " + lexeme, line);
        break;
    case UNRECOGNIZED:
        return getLexicalError("UNRECOGNIZED_CHAR " + lexeme, line);
        break;
    default:
        break;
    }
    return getLexicalError("Unknown Lexical Error", line);
}

std::string ErrorHandler::handleSemanticError(SemanticError type, int line, string lexeme)
{
    switch (type)
    {
    case MULTIPLE_DECLARATION:
        // table->printAllScope();
        return getSemanticError("Multiple declaration of '" + lexeme + "'", line);
        break;
    case INVALID_ARRAY_SIZE:
        return getSemanticError("Non-integer Array size " + lexeme, line);
        break;
    case INVALID_ARRAY_INDEX:
        return getSemanticError("Array subscript is not an integer", line);
        break;
    case INVALID_OPERAND:
        return getSemanticError("Invalid Operands " + lexeme, line);
        break;
    case INCOMPATIBLE_OPERAND:
        return getSemanticError("Incompatible Operands " + lexeme, line);
        break;
    case MOD_BY_ZERO:
        return getSemanticError("Warning: division by zero", line);
        break;
    case UNDECLARED_VARIABLE:
        return getSemanticError("Undeclared variable '" + lexeme + "'", line);
        break;
    case UNDECLARED_FUNCTION:
        return getSemanticError("Undeclared function '" + lexeme + "'", line);
        break;
    case UNDEFINED_FUNCTION:
        return getSemanticError("Undefined function '" + lexeme + "'", line);
        break;
    case NESTED_FUNCTION:
        return getSemanticError("A function is defined inside function '" + lexeme + "'", line);
        break;
    case NOT_FUNCTION:
        return getSemanticError("'" + lexeme + "' cannot be used as a function", line);
        break;
    case NOT_ARRAY:
        return getSemanticError("'" + lexeme + "' is not an array", line);
        break;
    case MISSING_PARAM_NAME:
        return getSemanticError("Parameter's name not given in definition of function '" + lexeme + "'", line);
        break;
    case VOID_VARIABLE:
        return getSemanticError("Variable or field '" + lexeme + "' declared void", line);
        break;
    case INVALID_CONVERSION:
        // function return type conflict
        // function arguments mismatch
        return getSemanticError("Invalid conversion " + lexeme, line);
        break;
    case PARAM_TYPE_MISMATCH:
        return getSemanticError("Type of parameters mismatch with function-declaration in function '" + lexeme + "'", line);
        break;
    case PARAM_NUMBER_MISMATCH:
        return getSemanticError("Total number of paramters mismatch with function-declaration in function '" + lexeme + "'", line);
        break;
    case RETURN_TYPE_MISMATCH:
        return getSemanticError("Return type mismatch with function-declaration in function '" + lexeme + "'", line);
        break;
    case ARGUMENT_TYPE_MISMATCH:
        return getSemanticError("Type mismatch for argument " + lexeme, line);
        break;
    case TOO_FEW_ARGUMENTS:
        return getSemanticError("Too few arguments to function '" + lexeme + "'", line);
        break;
    case TOO_MANY_ARGUMENTS:
        return getSemanticError("Too many arguments to function '" + lexeme + "'", line);
        break;
    case TYPE_MISMATCH:
        return getSemanticError("Type mismatch '" + lexeme + "'", line);
        break;
    case FUNCTION_NOT_RETURNED:
        return getSemanticError("Not returned from function '" + lexeme + "'", line);
        break;
    case PARAM_REDEFINITION:
        return getSemanticError("Redefinition of parameter '" + lexeme + "'", line);
        break;
    case DATA_LOSS:
        return getSemanticError("Warning: possible loss of data in assignment of " + lexeme, line);
        break;
    case TYPE_CONFLICT:
        return getSemanticError("Conflicting types for '" + lexeme + "'", line);
        break;
    case DIFF_DECLARATION:
        return getSemanticError("'" + lexeme + "' redeclared as different kind of symbol", line);
        break;
    case VOID_FUNCTION_EXP:
        return getSemanticError("Void cannot be used in expression", line);
        break;
    case NONINT_MOD:
        return getSemanticError("Operands of modulus must be integers", line);
        break;
    default:
        break;
    }
    return getLexicalError("Unknown Semantic Error", line);
}
std::string ErrorHandler::handleSyntaxError(string error, int line)
{
    return getSyntaxError(error, line);
}
int ErrorHandler::getErrorCount()
{
    return error_count;
}
