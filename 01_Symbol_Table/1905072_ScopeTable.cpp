#include "1905072_ScopeTable.hpp"

ScopeTable::ScopeTable(int n)
{
    this->id = 1;
    this->parent_scope = nullptr;
    this->num_buckets = n;
    this->hash_table = new SymbolInfo *[n];
    for (int i = 0; i < num_buckets; i++)
    {
        hash_table[i] = nullptr;
    }
}
ScopeTable::~ScopeTable()
{
    for (int i = 0; i < num_buckets; i++)
    {
        SymbolInfo *curr = hash_table[i];
        while (curr != nullptr)
        {
            SymbolInfo *tmp = curr->getNext();
            delete curr;
            curr = tmp;
        }
    }
    delete[] hash_table;
}

ScopeTable *ScopeTable::getParentScope() const
{
    return parent_scope;
}
void ScopeTable::setParentScope(ScopeTable *parentScope)
{
    this->parent_scope = parentScope;
}

int ScopeTable::getId() const
{
    return id;
}
void ScopeTable::setId(int id)
{
    this->id = id;
}

unsigned long ScopeTable::sdbmHash(const std::string &str) const
{
    unsigned long hash = 0;
    for (auto c : str)
    {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

int ScopeTable::hash(const std::string &name) const
{
    int ret = sdbmHash(name) % num_buckets;
    return ret;
}

SymbolInfo *ScopeTable::find(const std::string &name) const
{
    int hash_index = hash(name);
    SymbolInfo *curr = hash_table[hash_index];

    for (int i = 0; curr != nullptr; i++)
    {
        if (curr->getSymbol() == name)
        {
            return curr;
        }
        curr = curr->getNext();
    }
    return nullptr;
}

std::pair<int, int> ScopeTable::getLocationOfSymbol(const std::string &name) const
{
    int hash_index = this->hash(name);

    SymbolInfo *curr = hash_table[hash_index];

    for (int i = 0; curr != nullptr; i++)
    {
        if (curr->getSymbol() == name)
        {
            return {hash_index + 1, i + 1};
        }
        curr = curr->getNext();
    }
    return {0, 0};
}

bool ScopeTable::insert(const std::string &name, const std::string &type)
{
    int hash_index = hash(name);
    SymbolInfo *new_info = new SymbolInfo(name, type);

    if (hash_table[hash_index] == nullptr)
    {
        hash_table[hash_index] = new_info; // First symbol
    }
    else
    {
        SymbolInfo *curr = hash_table[hash_index];
        for (int i = 1;; i++)
        {
            if (curr->getSymbol() == name)
            {
                return false;
            }
            if (curr->getNext() != nullptr)
            {
                curr = curr->getNext();
            }
            else
            {
                curr->setNext(new_info);
                break;
            }
        }
    }
    return true;
}

bool ScopeTable::erase(const std::string &name)
{
    int hash_index = hash(name);
    SymbolInfo *prv = nullptr;
    SymbolInfo *curr = hash_table[hash_index];
    SymbolInfo *location = find(name);

    if (location != nullptr)
    {
        for (int i = 0; curr != nullptr; i++)
        {
            if (curr->getSymbol() == name)
            {
                if (prv != nullptr)
                {
                    prv->setNext(curr->getNext());
                }
                else
                {
                    hash_table[hash_index] = curr->getNext(); // First symbol
                }
                delete (curr);
                break;
            }
            prv = curr;
            curr = curr->getNext();
        }
        return true;
    }
    else
    {
        return false;
    }
}