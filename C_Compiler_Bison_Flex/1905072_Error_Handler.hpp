#ifndef __ERROR_HANDLER__
#define __ERROR_HANDLER__
#include <iostream>
#include <string>
using namespace std;
// Lexical errors

enum LexicalError
{
    TOO_MANY_DECIMAL = 0,
    ILL_NUMBER,
    INVALID_IDENTIFIER,
    MULTI_CHARACTER,
    UNTERMINATED_CHARACTER,
    EMPTY_CHARACTER,
    UNTERMINATED_STRING,
    UNTERMINATED_COMMENT,
    UNRECOGNIZED
};

// Semantic Errors
enum SemanticError
{
    MULTIPLE_DECLARATION = 10,
    INVALID_ARRAY_SIZE,
    INVALID_ARRAY_INDEX,
    INCOMPATIBLE_OPERAND,
    VOID_FUNCTION_EXP,
    INCOMPATIBLE_MOD,
    MOD_BY_ZERO,
    UNDECLARED_VARIABLE,
    UNDECLARED_FUNCTION,
    TYPE_MISMATCH,
    ARGUMENT_TYPE_MISMATCH,
    DECLARATION_DEFINITION_CLASH,
    ARGUMENT_NUMBER_MISMATCH,
    UNDEFINED_FUNCTION,
    RETURN_TYPE_MISMATCH,
    NOT_FUNCTION,
    NESTED_FUNCTION,
    VOID_VARIABLE,
    NOT_ARRAY,
    MISSING_PARAM_NAME,
    PARAM_NUMBER_MISMATCH,
    PARAM_TYPE_MISMATCH,
    INVALID_OPERAND,
    INVALID_CONVERSION,
    TOO_FEW_ARGUMENTS,
    TOO_MANY_ARGUMENTS,
    FUNCTION_NOT_RETURNED
};

class ErrorHandler
{
public:
    void printError(string error, int line);
    void printLexicalError(string error, int line);
    void printSemanticError(string error, int line);
    void handleLexicalError(LexicalError type, int line, string lexeme = "");
    void handleSemanticError(SemanticError type, int line, string lexeme = "");
};

#endif