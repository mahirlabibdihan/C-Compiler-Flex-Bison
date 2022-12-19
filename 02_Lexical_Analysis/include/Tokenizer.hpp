/**
 * Author: Mahir Labib Dihan
 * Last modified: December 05, 2022
 */
#ifndef __TOKENIZER_H
#define __TOKENIZER_H 1
#include <fstream>
#include <string>
#include <map>

namespace Tokenizer
{
    extern std::map<std::string, std::string> operatorType;
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
    std::string getToken(std::string type, std::string token_type);
    std::string generateToken(TokenType type, std::string lexeme);
};

#endif