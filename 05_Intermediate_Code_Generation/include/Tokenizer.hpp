/**
 * Author: Mahir Labib Dihan
 * Last modified: December 05, 2022
 */
#ifndef __TOKENIZER_H
#define __TOKENIZER_H 1
#include <fstream>
#include <string>
#include <map>
#include "../include/ExtendedSymbol.hpp"
#include "../include/Parser.hpp"
namespace Tokenizer
{
    extern std::map<std::string, std::string> operatorType;
    extern std::map<std::string, int> operatorToken;
    extern std::map<std::string, int> keywordToken;

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
    int getToken(TokenType type, std::string lexeme);
};

#endif