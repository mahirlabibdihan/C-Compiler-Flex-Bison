#ifndef __HELPER__
#define __HELPER__
#include <string>
#include <vector>
#include "1905072_SymbolInfo.h"
#include "1905072_Expression.h"
using namespace std;

string toUpper(string s);
string toLower(string s);
char getSpecialChar(char c);
char getActualChar(string symbol);
string getActualString(string str);
string formatCode(vector<SymbolInfo *> tokens);
string formatCode(vector<Segment *> segments);
string newLabel(string var_name, string scope_id);
string newLabel(string arr_name, string arr_size, string scope_id);
bool isConvertible(string to, string from);
#endif