#ifndef __TOKENIZER__
#define __TOKENIZER__
#include <string>
#include <map>
using namespace std;

enum Token
{
    KEYWORD_TOKEN,
    INTEGER_TOKEN,
    FLOAT_TOKEN,
    CHARACTER_TOKEN,
    STRING_TOKEN,
    OPERATOR_TOKEN,
    IDENTIFIER_TOKEN
};

extern map<string, int> operatorToken;
extern map<string, int> keywordToken;
void printToken(string token);
void generateToken(Token type, string lexeme);
int getToken(Token type, string lexeme);
#endif