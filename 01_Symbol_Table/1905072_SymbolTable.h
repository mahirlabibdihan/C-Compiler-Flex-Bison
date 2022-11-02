
#ifndef __SYMBOL_TABLE__
#define __SYMBOL_TABLE__
#include <iostream>
#include <functional>
#include <sstream>
#include "1905072_ScopeTable.h"
using namespace std;

class SymbolTable
{
    ScopeTable *current_scope;
    int n_buckets;
    function<unsigned long(string)> hash_value;
    ScopeTable *last_accessed_scope;
    string last_accessed_scope_id;
    void operator=(const SymbolTable &) {} // Protect assignment
    SymbolTable(const SymbolTable &) {}    // Protect copy constructor
public:
    SymbolTable(const int &size, function<unsigned long(string)> hash_value);
    ~SymbolTable();

    ScopeTable *getCurrentScope() const;
    void setCurrentScope(ScopeTable *currentScopeTable);

    int getBucketSize() const;
    void setBucketSize(const int &size);

    bool enterScope();
    bool exitScope();

    bool insertSymbol(const SymbolInfo &symbol);
    bool removeSymbol(const string &key);
    SymbolInfo *searchSymbol(const string &key);

    void printCurrentScope();
    void printAllScope();

    ScopeTable *getLastAccessedScope();
    string getLastAccessedScopeId();
};
#endif
