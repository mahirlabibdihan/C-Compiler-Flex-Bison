
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
    SymbolInfo **hash_table;
    function<unsigned long(string)> hash_value;

    void operator=(const ScopeTable &) {} // Protect assignment
    ScopeTable(const ScopeTable &) {}     // Protect copy constructor

public:
    ScopeTable(int size, function<unsigned long(string)> func)
    {
        this->id = "1";
        this->child_count = 0;
        this->parent_scope = nullptr;
        this->n_buckets = size;
        this->hash_value = func;
        this->hash_table = new SymbolInfo *[n_buckets];
        for (int i = 0; i < n_buckets; i++)
        {
            hash_table[i] = nullptr;
        }
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

    SymbolInfo **getHashTable() const;
    void setHashTable(SymbolInfo **hash_table);

    int hash(const string &key);

    SymbolInfo *search(const string &key);
    bool insert(const SymbolInfo &symbol);
    bool remove(const string &key);
    void print();
};
#endif
