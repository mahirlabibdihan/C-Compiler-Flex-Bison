#ifndef __HELPER__
#define __HELPER__
#include <string>
#include <vector>
#include "1905072_SymbolInfo.hpp"
#include "1905072_Symbol_Extended.hpp"
using namespace std;

class Helper
{
public:
    string toUpper(string s);
    string toLower(string s);
    char getSpecialChar(char c);
    char getActualChar(string symbol);
    string getActualString(string str);
    string formatCode(vector<SymbolInfo *> tokens);
    int getDataSize(string);
};

#endif