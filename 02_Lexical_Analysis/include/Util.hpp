/**
 * Author: Mahir Labib Dihan
 * Last modified: December 05, 2022
 */

#ifndef _UTIL_H
#define _UTIL_H 1
#include <string>
#include "../include/SymbolTable.hpp"
namespace Util
{
    std::string toUpper(std::string s);
    std::string toLower(std::string s);
    char getSpecialChar(char c);
    char getActualChar(std::string symbol);
    std::string getActualString(std::string str, bool &);
    int countTokens(const std::string &line, char delim = ' ');
    std::string *split(const std::string &line, char delim = ' ');
};

#endif