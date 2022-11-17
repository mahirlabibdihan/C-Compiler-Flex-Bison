#include <string>
#include "1905072_Helper.hpp"
#include <vector>
#include "1905072_SymbolInfo.hpp"
#include "1905072_Symbol_Extended.hpp"
#include "1905072_Logger.hpp"

extern Logger *logger;
using namespace std;

string Helper::toUpper(string s)
{
    for (auto &ch : s)
        ch = toupper(ch);
    return s;
}

string Helper::toLower(string s)
{
    for (auto &ch : s)
        ch = tolower(ch);
    return s;
}

char Helper::getSpecialChar(char c)
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
char Helper::getActualChar(string symbol)
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

string Helper::getActualString(string str)
{
    int n = str.length();
    string tmp = "\"";
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
    return tmp + "\"";
}

string Helper::formatCode(vector<SymbolInfo *> tokens)
{
    string code = "";
    for (auto &i : tokens)
    {
        code += i->getSymbol();
        if (i->getType() == "type_specifier" || i->getType() == "ELSE" || i->getType() == "RETURN")
        {
            code += " ";
        }
        else if (i->getType() == "LCURL" || i->getType() == "unit" || i->getType() == "statement")
        {
            code += "\n";
        }
    }
    return code;
}

int Helper::getDataSize(string type)
{
    if (type == "void")
    {
        return 0;
    }
    else if (type == "char")
    {
        return 1;
    }
    else if (type == "int")
    {
        return 4;
    }
    else if (type == "float")
    {
        return 4;
    }
    else if (type == "double")
    {
        return 8;
    }
}