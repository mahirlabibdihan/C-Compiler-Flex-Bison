#include <string>
#include "1905072_Helper.h"
#include <vector>
#include "1905072_SymbolInfo.h"
#include "1905072_Expression.h"
using namespace std;

string toUpper(string s)
{
    for (auto &ch : s)
        ch = toupper(ch);
    return s;
}

string toLower(string s)
{
    for (auto &ch : s)
        ch = tolower(ch);
    return s;
}

char getSpecialChar(char c)
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
char getActualChar(string symbol)
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

string getActualString(string str)
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

string formatCode(vector<SymbolInfo *> tokens)
{
    string code = "";
    for (auto &i : tokens)
    {
        code += i->getName();
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
string formatCode(vector<Segment *> segments)
{
    string code = "";
    for (auto &i : segments)
    {
        code += i->getCode();
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
string replaceAll(string source, string toReplace, string replaceBy)
{
    if (source.find(toReplace, 0) == string::npos)
    {
        return source;
    }
    for (string::size_type i = 0; (i = source.find(toReplace, i)) != string::npos;)
    {
        source.replace(i, toReplace.length(), replaceBy);
        i += replaceBy.length();
    }
    return source;
}

string newLabel(string var_name, string scope_id)
{
    return var_name + "_" + replaceAll(scope_id, ".", "_") + " DW ?";
}
string newLabel(string arr_name, string arr_size, string scope_id)
{
    return arr_name + "_" + replaceAll(scope_id, ".", "_") + " DW " + arr_size + " DUP ($)";
}

bool isConvertible(string to, string from)
{
    if (from == "NULL")
    {
        return true; // already error reported and converted to NULL , this is made true to supress more error
    }

    // if (og_p == "void")
    //     return pass_p == "void";
    if (to == "int" && from == "int")
        return true;
    if (to == "int" && from != "void")
        return true;
    return false;
}