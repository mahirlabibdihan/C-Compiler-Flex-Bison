
#ifndef __SYMBOL_INFO__
#define __SYMBOL_INFO__
#include <iostream>
#include <vector>
using namespace std;
class SymbolInfo
{
private:
    SymbolInfo(const SymbolInfo &) {}
    void operator=(const SymbolInfo &) {} // Protect assignment     // Protect copy constructor
protected:
    string name;
    string type;
    SymbolInfo *next;
    void init();

public:
    SymbolInfo();
    SymbolInfo(const string &name, const string &type);
    SymbolInfo(const string &name, const string &type, SymbolInfo *next);
    virtual ~SymbolInfo();
    const string &getSymbol() const;
    void setSymbol(const string &name);
    const string &getType() const;
    void setType(const string &type);
    SymbolInfo *getNext() const;
    void setNext(SymbolInfo *next);
};
#endif
