#include <string>
using namespace std;

string toUpper(string s)
{
    for (auto &ch : s)
        ch = toupper(ch);
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