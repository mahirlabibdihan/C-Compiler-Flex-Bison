
#ifndef __SCOPE_TABLE__
#define __SCOPE_TABLE__
#include <iostream>
#include <functional>
#include <vector>
#include "1905072_SymbolInfo.h"
using namespace std;

class ScopeTable
{
private:
    ScopeTable *parent_scope;
    string id;
    int child_count;
    int n_buckets;
    vector<SymbolInfo *> hash_table;
    function<unsigned long(string)> hash_value;

    void operator=(const ScopeTable &) {} // Protect assignment
    ScopeTable(const ScopeTable &) {}     // Protect copy constructor

public:
    template <typename T>
    ScopeTable(int size, T func)
    {
        this->id = "1";
        this->child_count = 0;
        this->parent_scope = nullptr;
        this->n_buckets = size;
        this->hash_value = func;
        this->hash_table = vector<SymbolInfo *>(size, nullptr);
    }
    ~ScopeTable();

    ScopeTable *getParentScope() const;
    void setParentScope(ScopeTable *parentScope);

    string getId() const;
    void setId(const string &id);

    int getChildCount() const;
    void setChildCount(const int &count);

    int getBucketSize() const;
    void setBucketSize(const int &size);

    vector<SymbolInfo *> getHashTable() const;
    void setHashTable(vector<SymbolInfo *> hash_table);

    int hash(const string &key);

    SymbolInfo *search(const string &key);
    bool insert(const SymbolInfo &symbol);
    bool remove(const string &key);
    void print();
};
#endif
