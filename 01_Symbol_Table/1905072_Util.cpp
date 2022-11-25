#include "1905072_Util.hpp"

std::vector<std::string> Util::split(const std::string &line, char delm)
{
    std::vector<std::string> tokens;
    std::string token;
    for (char c : line)
    {
        if (c != delm)
        {
            token += c;
        }
        else
        {
            if (!token.empty())
            {
                tokens.push_back(token);
            }
            token.clear();
        }
    }
    if (!token.empty())
    {
        tokens.push_back(token);
    }
    return tokens;
}