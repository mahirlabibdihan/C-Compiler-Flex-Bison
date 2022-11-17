
#ifndef __SYMBOL_TABLE__
#define __SYMBOL_TABLE__
#include <iostream>
#include <functional>
#include <sstream>
#include "1905072_ScopeTable.hpp"
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

    int size() const;

    bool enterScope();
    bool exitScope();

    bool insert(SymbolInfo &symbol);
    bool insert(SymbolInfo *symbol);
    bool remove(const string &key);
    SymbolInfo *search(const string &key);

    void printCurrentScope();
    void printAllScope();

    string getScopeIdOfSymbol(const string &key);
    pair<int, int> getLocationOfSymbol(const string &key);

    ScopeTable *getLastAccessedScope();
    string getLastAccessedScopeId();
};
#endif
