#ifndef __ERROR_HANDLER__
#define __ERROR_HANDLER__
#include <iostream>
#include <string>
using namespace std;
#define TOO_MANY_DECIMAL 0
#define ILL_NUMBER 1
#define INVALID_IDENTIFIER 2
#define MULTI_CHARACTER 3
#define UNTERMINATED_CHARACTER 4
#define EMPTY_CHARACTER 5
#define UNTERMINATED_STRING 6
#define UNTERMINATED_COMMENT 7
#define UNRECOGNIZED 8

void printErrorLog(string error, int line);
void handleError(int type, int line, string lexeme);
#endif