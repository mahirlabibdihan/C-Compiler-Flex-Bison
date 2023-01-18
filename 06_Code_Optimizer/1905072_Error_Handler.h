#ifndef __ERROR_HANDLER__
#define __ERROR_HANDLER__
#include <iostream>
#include <string>
using namespace std;
// Lexical errors
#define TOO_MANY_DECIMAL 0
#define ILL_NUMBER 1
#define INVALID_IDENTIFIER 2
#define MULTI_CHARACTER 3
#define UNTERMINATED_CHARACTER 4
#define EMPTY_CHARACTER 5
#define UNTERMINATED_STRING 6
#define UNTERMINATED_COMMENT 7
#define UNRECOGNIZED 8

// Semantic Errors
#define MULTIPLE_DECLARATION 9
#define INVALID_ARRAY_SIZE 10
#define INVALID_ARRAY_INDEX 11
#define INCOMPATIBLE_OPERAND 12
#define VOID_FUNCTION_EXP 13
#define INCOMPATIBLE_MOD 14
#define MOD_BY_ZERO 15
#define UNDECLARED_VARIABLE 16
#define UNDECLARED_FUNCTION 17
#define TYPE_MISMATCH 18
#define ARGUMENT_TYPE_MISMATCH 19
#define DECLARATION_DEFINITION_CLASH 20
#define ARGUMENT_NUMBER_MISMATCH 21
#define UNDEFINED_FUNCTION 22
#define RETURN_TYPE_MISMATCH 23
#define NOT_FUNCTION 24
#define NESTED_FUNCTION 25
#define VOID_VARIABLE 26
#define NOT_ARRAY 27
#define MISSING_PARAM_NAME 28
#define PARAM_NUMBER_MISMATCH 29
#define PARAM_TYPE_MISMATCH 30
#define INVALID_OPERAND 31
#define INVALID_CONVERSION 32
#define TOO_FEW_ARGUMENTS 33
#define TOO_MANY_ARGUMENTS 34

void printErrorLog(string error, int line);
void handleError(int type, int line, string lexeme = "");
#endif