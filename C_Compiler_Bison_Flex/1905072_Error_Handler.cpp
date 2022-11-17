#include "1905072_Error_Handler.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include "1905072_SymbolTable.hpp"
using namespace std;

extern ofstream logout;
extern ofstream errout;
extern int error_count;
extern int line_count;
extern SymbolTable *table;

void ErrorHandler::printError(string error, int line)
{
    error_count++;

    logout << "Error at line " << line << ": " << error << "\n"
           << endl;
    errout << "Error at line " << line << ": " << error << "\n"
           << endl;
}
void ErrorHandler::printLexicalError(string error, int line)
{
    printError("lexical error, " + error, line);
}
void ErrorHandler::printSemanticError(string error, int line)
{
    printError("semantic error, " + error, line);
}

void ErrorHandler::handleLexicalError(LexicalError type, int line, string lexeme)
{
    switch (type)
    {
    case TOO_MANY_DECIMAL:
        printLexicalError("Too Many Decimal Points " + lexeme, line);
        break;
    case ILL_NUMBER:
        printLexicalError("Ill formed number " + lexeme, line);
        break;
    case INVALID_IDENTIFIER:
        printLexicalError("Invalid prefix on ID or invalid suffix on Number " + lexeme, line);
        break;
    case MULTI_CHARACTER:
        printLexicalError("Multi Character Constant Error " + lexeme, line);
        break;
    case UNTERMINATED_CHARACTER:
        printLexicalError("Unterminated Character " + lexeme, line);
        break;
    case EMPTY_CHARACTER:
        printLexicalError("Empty Character Constant Error " + lexeme, line);
        break;
    case UNTERMINATED_STRING:
        printLexicalError("Unterminated String " + lexeme, line);
        break;
    case UNTERMINATED_COMMENT:
        printLexicalError("Unterminated Comment " + lexeme, line);
        break;
    case UNRECOGNIZED:
        printLexicalError("Unrecognized character " + lexeme, line);
        break;
    default:
        break;
    }
}

void ErrorHandler::handleSemanticError(SemanticError type, int line, string lexeme)
{
    switch (type)
    {
    case MULTIPLE_DECLARATION:
        // table->printAllScope();
        printSemanticError("Multiple declaration of '" + lexeme + "'", line);
        break;
    case INVALID_ARRAY_SIZE:
        printSemanticError("Non-integer Array size " + lexeme, line);
        break;
    case INVALID_ARRAY_INDEX:
        printSemanticError("Non-integer Array index " + lexeme, line);
        break;
    case INVALID_OPERAND:
        printSemanticError("Invalid Operands " + lexeme, line);
        break;
    case INCOMPATIBLE_OPERAND:
        printSemanticError("Incompatible Operands " + lexeme, line);
        break;
    case MOD_BY_ZERO:
        printSemanticError("Modulus by Zero " + lexeme, line);
        break;
    case UNDECLARED_VARIABLE:
        printSemanticError("Undeclared variable '" + lexeme + "'", line);
        break;
    case UNDECLARED_FUNCTION:
        printSemanticError("Undeclared function '" + lexeme + "'", line);
        break;
    case UNDEFINED_FUNCTION:
        printSemanticError("Undefined function '" + lexeme + "'", line);
        break;
    case NESTED_FUNCTION:
        printSemanticError("A function is defined inside function '" + lexeme + "'", line);
        break;
    case NOT_FUNCTION:
        printSemanticError("'" + lexeme + "' cannot be used as a function ", line);
        break;
    case NOT_ARRAY:
        printSemanticError("'" + lexeme + "' cannot be used as an array ", line);
        break;
    case MISSING_PARAM_NAME:
        printSemanticError("Parameter's name not given in definition of function '" + lexeme + "'", line);
        break;
    case VOID_VARIABLE:
        printSemanticError("Variable '" + lexeme + "' declared void", line);
        break;
    case INVALID_CONVERSION:
        // function return type conflict
        // function arguments mismatch
        printSemanticError("Invalid conversion " + lexeme, line);
        break;
    case PARAM_TYPE_MISMATCH:
        printSemanticError("Type of paramters mismatch with function-declaration in function '" + lexeme + "'", line);
        break;
    case PARAM_NUMBER_MISMATCH:
        printSemanticError("Total number of paramters mismatch with function-declaration in function '" + lexeme + "'", line);
        break;
    case RETURN_TYPE_MISMATCH:
        printSemanticError("Return type mismatch with function-declaration in function '" + lexeme + "'", line);
        break;
    case ARGUMENT_TYPE_MISMATCH:
        printSemanticError("Type of arguments mismatch with declaration in function '" + lexeme + "'", line);
        break;
    case TOO_FEW_ARGUMENTS:
        printSemanticError("Too few arguments to function '" + lexeme + "'", line);
        break;
    case TOO_MANY_ARGUMENTS:
        printSemanticError("Too many arguments to function '" + lexeme + "'", line);
        break;
    case TYPE_MISMATCH:
        printSemanticError("Type mismatch '" + lexeme + "'", line);
        break;
    case FUNCTION_NOT_RETURNED:
        printSemanticError("Not returned from function '" + lexeme + "'", line);
        break;
    default:
        break;
    }
}
