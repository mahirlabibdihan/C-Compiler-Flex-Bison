#ifndef __TOKENIZER__
#define __TOKENIZER__
#include <string>
#include <map>
using namespace std;
#define KEYWORD_TOKEN 0
#define INTEGER_TOKEN 1
#define FLOAT_TOKEN 2
#define CHARACTER_TOKEN 3
#define STRING_TOKEN 4
#define OPERATOR_TOKEN 5
#define IDENTIFIER_TOKEN 6

extern map<string, int> operatorToken;
extern map<string, int> keywordToken;
void printToken(string token);
void generateToken(int type, string lexeme);
int getToken(int type, string lexeme);
#endif