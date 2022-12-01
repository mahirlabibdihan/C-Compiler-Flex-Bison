#include "../include/1905072_Util.hpp"
#include <iostream>
#include <sstream>
int Util::countTokens(const std::string &line, char delim)
{
    int count = 0;
    std::string token;
    std::stringstream ss(line);
    while (std::getline(ss, token, ' '))
    {
        if (!token.empty())
        {
            count++;
        }
    }
    return count;
}
std::string *Util::split(const std::string &line, char delim)
{
    int count = countTokens(line, delim);
    std::string *tokens = new std::string[count];
    std::string token;
    std::stringstream ss(line);
    for (int i = 0; std::getline(ss, token, ' ');)
    {
        if (!token.empty())
        {
            tokens[i++] = token;
        }
    }
    return tokens;
}