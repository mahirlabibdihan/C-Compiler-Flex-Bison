
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
    pair<int, int> last_accessed_location;

    void operator=(const ScopeTable &) {} // Protect assignment
    ScopeTable(const ScopeTable &) {}     // Protect copy constructor

public:
    ScopeTable(const int &size, function<unsigned long(string)> func);
    ~ScopeTable();

    ScopeTable *getParentScope() const;
    void setParentScope(ScopeTable *parentScope);

    string getId() const;
    void setId(const string &id);

    int getChildCount() const;
    void setChildCount(const int &count);

    // int getBucketSize() const;
    // void setBucketSize(const int &size);

    // SymbolInfo **getHashTable() const;
    // void setHashTable(SymbolInfo **hash_table);

    int hash(const string &key);

    SymbolInfo *search(const string &key);
    bool insert(SymbolInfo &symbol);
    bool remove(const string &key);

    void print();

    pair<int, int> getLastAccessedLocation();
};
#endif
