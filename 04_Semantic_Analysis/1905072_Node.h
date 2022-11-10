#ifndef __NODE__
#define __NODE__
#include <string>
#include <vector>
#include "1905072_SymbolInfo.h"
using namespace std;
// Internal Node for parse tree
class Node
{
    // code, list, symbol
private:
    string code;               // Formatted code to print
    vector<SymbolInfo *> list; // If the non terminal returns any list like declaration list, function params, arguments
    SymbolInfo *symbol;        // To store symbol info's if needed
    string data_type;
    // Node(string text, vector<SymbolInfo *> v);

    void operator=(const Node &) {} // Protect assignment
    Node(const Node &) {}           // Protect copy constructor
public:
    Node();
    string getCode();
    void setCode(string text);
    vector<SymbolInfo *> &getList();
    void setList(vector<SymbolInfo *> list);
    void setSymbol(SymbolInfo *s);
    SymbolInfo *getSymbol();
    void setDataType(string);
    string getDataType();
    // void print();
};
#endif