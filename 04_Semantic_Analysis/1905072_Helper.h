#ifndef __HELPER__
#define __HELPER__
#include <string>
#include <vector>
#include "1905072_SymbolInfo.h"
using namespace std;

string toUpper(string s);
string toLower(string s);
char getSpecialChar(char c);
char getActualChar(string symbol);
string getActualString(string str);
string formatCode(vector<SymbolInfo *> tokens);
#endif