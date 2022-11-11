#ifndef __NODE__
#define __NODE__
#include <string>
#include <vector>
#include "../01_Symbol_Table/1905072_SymbolInfo.h"
using namespace std;
// Internal Node for parse tree
class Node
{
    // code, list, symbol
private:
    string code;               // Formatted code to print
    vector<SymbolInfo *> list; // If the non terminal returns any list like declaration list, function params, arguments
    SymbolInfo *symbol;        // To store symbol info's if needed

    // Node(string text, vector<SymbolInfo *> v);
public:
    Node();
    string getCode();
    void setCode(string text);
    vector<SymbolInfo *> &getList();
    void setList(vector<SymbolInfo *> list);
    void setSymbol(SymbolInfo *s);
    SymbolInfo *getSymbol();
    // void print();
};
#endif