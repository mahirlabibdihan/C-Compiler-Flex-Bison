#ifndef __TOKENIZER__
#define __TOKENIZER__
#include <string>
#include <map>
using namespace std;

enum TokenType
{
    KEYWORD_TOKEN = 0,
    INTEGER_TOKEN,
    FLOAT_TOKEN,
    CHARACTER_TOKEN,
    STRING_TOKEN,
    OPERATOR_TOKEN,
    IDENTIFIER_TOKEN
};

class Tokenizer
{
public:
    void printToken(string token);
    void printToken(string type, string token_type);
    void printToken(string type, string symbol, string token_type);
    void generateToken(TokenType type, string lexeme);
    int getToken(TokenType type, string lexeme);
};

#endif