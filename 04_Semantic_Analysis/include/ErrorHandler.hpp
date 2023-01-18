/**
 * Author: Mahir Labib Dihan
 * Last modified: December 05, 2022
 */
#ifndef __ERROR_HANDLER_H
#define __ERROR_HANDLER_H 1
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class ErrorHandler
{
    int error_count;
    int lexical_error_count;
    int semantic_error_count;
    int syntax_error_count;
    int syntax_error_line;

public:
    // Lexical error types
    enum LexicalError
    {
        TOO_MANY_DECIMAL = 0,
        ILL_NUMBER,
        INVALID_IDENTIFIER,
        MULTI_CHARACTER,
        UNFINISHED_CHARACTER,
        EMPTY_CHARACTER,
        UNFINISHED_STRING,
        UNFINISHED_COMMENT,
        UNRECOGNIZED
    };

    enum SemanticError
    {
        MULTIPLE_DECLARATION = 10,
        MULTIPLE_DEFINITION,
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
        FUNCTION_NOT_RETURNED,
        PARAM_REDEFINITION,
        FUNCTION_REDEFINITION,
        DATA_LOSS,
        TYPE_CONFLICT,
        DIFF_DECLARATION,
        NONINT_MOD
    };

    ErrorHandler();
    std::string getError(string error, int line);
    std::string getLexicalError(string error, int line);
    std::string getSemanticError(string error, int line);
    std::string getSyntaxError(string error, int line);
    std::string handleLexicalError(LexicalError type, int line, string lexeme = "");
    std::string handleSemanticError(SemanticError type, int line, string lexeme = "");
    std::string handleSyntaxError(string parent, string error_child, int line);
    std::string handleSyntaxError(string parent, int line);
    std::string handleSyntaxError(int line);
    int getErrorCount();
};

#endif