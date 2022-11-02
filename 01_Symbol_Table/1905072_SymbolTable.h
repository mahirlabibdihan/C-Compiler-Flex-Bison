
#ifndef __SYMBOL_TABLE__
#define __SYMBOL_TABLE__
#include <iostream>
#include <functional>
#include <sstream>
#include "1905072_ScopeTable.h"
using namespace std;

template <class T>
string to_str(T x)
{
    stringstream ss;
    ss << x;
    return ss.str();
}

class SymbolTable
{
    ScopeTable *current_scope;
    int n_buckets;
    function<unsigned long(string)> hash_value;

    void operator=(const SymbolTable &) {} // Protect assignment
    SymbolTable(const SymbolTable &) {}    // Protect copy constructor
public:
    template <typename T>
    SymbolTable(const int &size, T hash_value)
    {
        this->n_buckets = size;
        this->hash_value = hash_value;
        this->current_scope = new ScopeTable(size, hash_value);
    }
    ~SymbolTable();

    ScopeTable *getCurrentScope() const;
    void setCurrentScope(ScopeTable *currentScopeTable);

    int getBucketSize() const;
    void setBucketSize(const int &size);

    void enterScope();
    void exitScope();

    bool insertSymbol(const SymbolInfo &symbol);
    bool removeSymbol(const string &key);
    SymbolInfo *searchSymbol(const string &key);

    void printCurrentScope();
    void printAllScope();
};
#endif
