#ifndef __LOGGER__
#define __LOGGER__
#include <string>
using namespace std;
#define KEYWORD_LOG 0
#define INTEGER_LOG 1
#define FLOAT_LOG 2
#define CHARACTER_LOG 3
#define STRING_LOG 4
#define OPERATOR_LOG 5
#define IDENTIFIER_LOG 6
#define COMMENT_LOG 7

void printLog(string token, string lexeme, int line);
void printLogWithToken(string token, string lexeme, string actual, int line);
void printLogData(int type, int line, string lexeme);
#endif