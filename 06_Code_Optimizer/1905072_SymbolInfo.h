
#ifndef __SYMBOL_INFO__
#define __SYMBOL_INFO__
#include <iostream>
#include <vector>
using namespace std;
class SymbolInfo
{
private:
    string name;
    string type;
    SymbolInfo *next;
    SymbolInfo(const SymbolInfo &) {}
    void operator=(const SymbolInfo &) {} // Protect assignment     // Protect copy constructor
    void init();

public:
    SymbolInfo();
    SymbolInfo(const string &name, const string &type);
    SymbolInfo(const string &name, const string &type, SymbolInfo *next);
    ~SymbolInfo();
    const string &getName() const;
    void setName(const string &name);
    const string &getType() const;
    void setType(const string &type);
    SymbolInfo *getNext() const;
    void setNext(SymbolInfo *next);
};
#endif
