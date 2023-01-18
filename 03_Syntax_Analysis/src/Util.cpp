#include <iostream>
#include <sstream>
#include "../include/Util.hpp"

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

int Util::getStringLineCount(std::string str)
{
    int n = str.length();
    // std::cout << "->" << str << " " << n << std::endl;
    int count = 1;
    for (int i = 1; i < n - 1; i++)
    {

        if (str[i] == '\\')
        {
            // std::cout << i << std::endl;
            i++;
            if (str[i] == '\r' or str[i] == '\n')
            {
                if (str[i] == '\r')
                {
                    i++;
                }
                count++;
            }
        }
    }
    // std::cout << str << " " << count << std::endl;
    return count;
}
int Util::getSingleCommentLineCount(std::string str)
{
    int n = str.length();
    int count = 1;
    for (int i = 0; i < n; i++)
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
                count++;
            }
        }
    }
    return count;
}

int Util::getMultiCommentLineCount(std::string str)
{
    int n = str.length();
    int count = 1;
    for (int i = 0; i < n; i++)
    {
        if (str[i] == '\r' or str[i] == '\n')
        {
            if (str[i] == '\r')
            {
                i++;
            }
            count++;
        }
    }
    return count;
}

std::string Util::getActualString(std::string str)
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