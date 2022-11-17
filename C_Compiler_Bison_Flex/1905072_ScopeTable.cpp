#include <iostream>
#include "1905072_SymbolInfo.hpp"
#include "1905072_ScopeTable.hpp"
using namespace std;

ScopeTable::ScopeTable(const int &size, function<unsigned long(string)> func)
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
ScopeTable::~ScopeTable()
{
    for (int i = 0; i < n_buckets; i++)
    {
        SymbolInfo *cur = hash_table[i];
        while (cur != nullptr)
        {
            SymbolInfo *tmp = cur->getNext();
            delete cur;
            cur = tmp;
        }
    }
    delete[] hash_table;
}

// int ScopeTable::getBucketSize() const
// {
//     return n_buckets;
// }

// void ScopeTable::setBucketSize(const int &size)
// {
//     this->n_buckets = size;
// }

// SymbolInfo **ScopeTable::getHashTable() const
// {
//     return hash_table;
// }

// void ScopeTable::setHashTable(SymbolInfo **hashTable)
// {
//     this->hash_table = hash_table;
// }

ScopeTable *ScopeTable::getParentScope() const
{
    return parent_scope;
}
void ScopeTable::setParentScope(ScopeTable *parentScope)
{
    this->parent_scope = parentScope;
}

string ScopeTable::getId() const
{
    return id;
}
void ScopeTable::setId(const string &id)
{
    this->id = id;
}

int ScopeTable::getChildCount() const
{
    return child_count;
}
void ScopeTable::setChildCount(const int &count)
{
    this->child_count = count;
}

int ScopeTable::hash(const string &key)
{
    int ret = hash_value(key) % n_buckets;
    return ret;
}

SymbolInfo *ScopeTable::search(const string &key)
{
    int hash_index = hash(key);
    SymbolInfo *cur = hash_table[hash_index];

    for (int i = 0; cur != nullptr; i++)
    {
        if (cur->getSymbol() == key)
        {
            last_accessed_location = {hash_index, i};
            return cur;
        }
        cur = cur->getNext();
    }
    return nullptr;
}

pair<int, int> ScopeTable::getLocationOfSymbol(const string &key)
{
    int hash_index = hash(key);

    SymbolInfo *cur = hash_table[hash_index];

    for (int i = 0; cur != nullptr; i++)
    {
        if (cur->getSymbol() == key)
        {
            last_accessed_location = {hash_index, i};
            return {hash_index, i};
        }
        cur = cur->getNext();
    }
    return {-1, -1};
}

bool ScopeTable::insert(SymbolInfo &s_info)
{
    string name = s_info.getSymbol();
    string type = s_info.getType();

    int hash_index = hash(name);
    SymbolInfo *new_info = new SymbolInfo(name, type);
    // new_info->setScopeId(this->getId());

    if (hash_table[hash_index] == nullptr)
    {
        last_accessed_location = {hash_index, 0};
        hash_table[hash_index] = new_info; // First symbol
    }
    else
    {
        SymbolInfo *cur = hash_table[hash_index];
        for (int i = 1;; i++)
        {
            if (cur->getSymbol() == name)
            {
                return false;
            }
            if (cur->getNext() != nullptr)
            {
                cur = cur->getNext();
            }
            else
            {
                last_accessed_location = {hash_index, i};

                cur->setNext(new_info);
                break;
            }
        }
    }
    return true;
}

bool ScopeTable::insert(SymbolInfo *symbol)
{
    int hash_index = hash(symbol->getSymbol());
    if (hash_table[hash_index] == nullptr)
    {
        hash_table[hash_index] = symbol; // First symbol
    }
    else
    {
        SymbolInfo *cur = hash_table[hash_index];
        for (int i = 1;; i++)
        {
            if (cur->getSymbol() == symbol->getSymbol())
            {
                return false;
            }
            if (cur->getNext() != nullptr)
            {
                cur = cur->getNext();
            }
            else
            {
                cur->setNext(symbol);
                break;
            }
        }
    }
    return true;
}
bool ScopeTable::remove(const string &key)
{
    int hash_index = hash(key);
    SymbolInfo *prv = nullptr;
    SymbolInfo *cur = hash_table[hash_index];
    SymbolInfo *location = search(key);

    if (location != nullptr)
    {
        for (int i = 0; cur != nullptr; i++)
        {
            if (cur->getSymbol() == key)
            {
                last_accessed_location = {hash_index, i};

                if (prv != nullptr)
                {
                    prv->setNext(cur->getNext());
                }
                else
                {
                    hash_table[hash_index] = cur->getNext(); // First symbol
                }
                delete (cur);
                break;
            }
            prv = cur;
            cur = cur->getNext();
        }
        return true;
    }
    else
    {
        return false;
    }
}

pair<int, int> ScopeTable::getLastAccessedLocation()
{
    return last_accessed_location;
}
