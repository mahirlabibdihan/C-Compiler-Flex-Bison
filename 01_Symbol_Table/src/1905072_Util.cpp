#include "../include/1905072_Util.hpp"
#include <iostream>

int Util::countTokens(const std::string &line, char delim)
{
    int count = 0;
    std::string token;
    for (char c : line)
    {
        if (c != delim)
        {
            token += c;
        }
        else
        {
            if (!token.empty())
            {
                count++;
            }
            token.clear();
        }
    }
    if (!token.empty())
    {
        count++;
    }
    return count;
}
std::string *Util::split(const std::string &line, char delim)
{
    int count = countTokens(line, delim);
    std::string *tokens = new std::string[count];
    std::string token;
    int i = 0;
    for (char c : line)
    {
        if (c != delim)
        {
            token += c;
        }
        else
        {
            if (!token.empty())
            {
                tokens[i++] = token;
            }
            token.clear();
        }
    }
    if (!token.empty())
    {
        tokens[i++] = token;
    }
    return tokens;
}