#include <iostream>
#include <cassert>
#include "1905072_SymbolInfo.h"
#include "1905072_ScopeTable.h"
using namespace std;

ScopeTable::~ScopeTable() // destructor
{
    for (int i = 0; i < n_buckets; i++)
    {
        SymbolInfo *cur = hash_table[i];
        while (cur != NULL)
        {
            SymbolInfo *tmp = cur->getNext();
            delete cur;
            cur = tmp;
        }
    }
}

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
        if (cur->getName() == key)
        {
            cout << "Found in ScopeTable# " << id << " at position " << hash_index << ", " << i << endl;
            return cur;
        }
        cur = cur->getNext();
    }
    return nullptr;
}

bool ScopeTable::insert(const SymbolInfo &s_info)
{
    string name = s_info.getName();
    string type = s_info.getType();
    int hash_index = hash(name);
    SymbolInfo *new_info = new SymbolInfo(name, type);

    if (hash_table[hash_index] == nullptr)
    {
        cout << "Inserted in ScopeTable# " << id << " at position " << hash_index << ", " << 0 << endl;
        hash_table[hash_index] = new_info; // First symbol
    }
    else
    {
        SymbolInfo *cur = hash_table[hash_index];
        for (int i = 1;; i++)
        {
            if (cur->getName() == name)
            {
                cout << "< " << cur->getName() << "," << cur->getType() << " > already exists in current ScopeTable" << endl;
                return false;
            }
            if (cur->getNext() != nullptr)
            {
                cur = cur->getNext();
            }
            else
            {
                cout << "Inserted in ScopeTable# " << id << " at position " << hash_index << ", " << i << endl;
                cur->setNext(new_info);
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
            if (cur->getName() == key)
            {
                cout << "Deleted Entry " << hash_index << "," << i << " from current ScopeTable" << endl;
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
        cout << "Not found" << endl
             << endl;
        cout << key << " not found" << endl;
        return false;
    }
}

void ScopeTable::print()
{
    cout << "ScopeTable # " << id << endl;
    for (int i = 0; i < n_buckets; i++)
    {
        cout << i << " --> ";
        SymbolInfo *cur = hash_table[i];
        while (cur != nullptr)
        {
            cout << "< " << cur->getName() << " : " << cur->getType() << " > ";
            cur = cur->getNext();
        }
        cout << endl;
    }
    cout << endl;
}
