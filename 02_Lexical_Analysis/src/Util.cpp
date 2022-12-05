#include <iostream>
#include <sstream>
#include "../include/Util.hpp"

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

std::string Util::toUpper(std::string s)
{
    for (auto &ch : s)
        ch = toupper(ch);
    return s;
}

std::string Util::toLower(std::string s)
{
    for (auto &ch : s)
        ch = tolower(ch);
    return s;
}

char Util::getSpecialChar(char c)
{
    switch (c)
    {
    case '0':
        return 0;
        break;
    case 'a':
        return 7;
        break;
    case 'b':
        return 8;
        break;
    case 't':
        return 9;
        break;
    case 'n':
        return 10;
        break;
    case 'v':
        return 11;
        break;
    case 'f':
        return 12;
        break;
    case 'r':
        return 13;
        break;
    default:
        return c;
        break;
    }
}
char Util::getActualChar(std::string symbol)
{
    if (symbol[1] != '\\')
    {
        return symbol[1];
    }
    else
    {
        return getSpecialChar(symbol[2]);
    }
}

std::string Util::getActualString(std::string str, bool &is_multi)
{
    int n = str.length();
    std::string tmp = "";
    for (int i = 1; i < n - 1; i++)
    {
        if (str[i] == '\\')
        {
            i++;
            if (str[i] == '\r' or str[i] == '\n')
            {
                if (str[i] == '\r')
                {
                    i++;
                }
                is_multi = true;
            }
            else
            {
                tmp += getSpecialChar(str[i]);
            }
        }
        else
        {
            tmp += str[i];
        }
    }

    return tmp;
}