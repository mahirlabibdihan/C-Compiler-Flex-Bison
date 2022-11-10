#include <iostream>
#include <functional>
#include <cassert>
#include "1905072_ScopeTable.h"
#include "1905072_SymbolTable.h"
using namespace std;

SymbolTable::SymbolTable(const int &size, function<unsigned long(string)> hash_value)
{
    this->n_buckets = size;
    this->hash_value = hash_value;
    this->current_scope = new ScopeTable(size, hash_value);
}
SymbolTable::~SymbolTable()
{
    while (current_scope != nullptr)
    {
        ScopeTable *tmp = current_scope->getParentScope();
        delete current_scope;
        current_scope = tmp;
    }
}

ScopeTable *SymbolTable::getCurrentScope() const
{
    return current_scope;
}

void SymbolTable::setCurrentScope(ScopeTable *scope)
{
    this->current_scope = scope;
}

int SymbolTable::size() const
{
    return n_buckets;
}

bool SymbolTable::enterScope()
{
    ScopeTable *st = new ScopeTable(n_buckets, hash_value);

    st->setParentScope(current_scope);
    current_scope->setChildCount(current_scope->getChildCount() + 1);
    current_scope = st;

    if (st->getParentScope() != nullptr)
    {
        st->setId(st->getParentScope()->getId() + "." + to_string(st->getParentScope()->getChildCount()));
        last_accessed_scope = st;
        last_accessed_scope_id = st->getId();
        return true;
    }
    return false;
}

bool SymbolTable::exitScope()
{
    if (current_scope != nullptr)
    {
        ScopeTable *tmp = current_scope;
        current_scope = current_scope->getParentScope();
        last_accessed_scope = tmp;
        last_accessed_scope_id = tmp->getId();
        delete tmp;
        return true;
    }
    else
    {
        return false;
    }
}

bool SymbolTable::insert(SymbolInfo &symbol)
{
    if (current_scope == nullptr)
    {
        current_scope = new ScopeTable(n_buckets, hash_value);
    }
    last_accessed_scope = current_scope;
    last_accessed_scope_id = current_scope->getId();
    return current_scope->insert(symbol);
}

bool SymbolTable::remove(const string &key)
{
    if (current_scope == nullptr)
    {
        return false;
    }
    last_accessed_scope = current_scope;
    last_accessed_scope_id = current_scope->getId();
    return current_scope->remove(key);
}

SymbolInfo *SymbolTable::search(const string &key)
{
    ScopeTable *cur = current_scope;
    while (cur != nullptr)
    {
        SymbolInfo *symbol = cur->search(key);
        if (symbol != nullptr)
        {
            last_accessed_scope = cur;
            last_accessed_scope_id = cur->getId();
            return symbol;
        }
        cur = cur->getParentScope();
    }
    return nullptr;
}

void SymbolTable::printCurrentScope()
{
    if (current_scope != nullptr)
    {
        current_scope->print();
    }
}

void SymbolTable::printAllScope()
{
    ScopeTable *cur = current_scope;
    while (cur != nullptr)
    {
        cur->print();
        cur = cur->getParentScope();
    }
}

ScopeTable *SymbolTable::getLastAccessedScope()
{
    return last_accessed_scope;
}
string SymbolTable::getLastAccessedScopeId()
{
    return last_accessed_scope_id;
}