#include <iostream>
#include <functional>
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

int SymbolTable::getBucketSize() const
{
    return n_buckets;
}

void SymbolTable::setBucketSize(const int &size)
{
    this->n_buckets = size;
}

void SymbolTable::enterScope()
{
    ScopeTable *st = new ScopeTable(n_buckets, hash_value);

    st->setParentScope(current_scope);
    current_scope->setChildCount(current_scope->getChildCount() + 1);
    current_scope = st;

    if (st->getParentScope() != nullptr)
    {
        st->setId(st->getParentScope()->getId() + "." + to_str(st->getParentScope()->getChildCount()));
    }

    cout << "New ScopeTable with id " << st->getId() << " created" << endl;
}

void SymbolTable::exitScope()
{
    if (current_scope != nullptr)
    {
        cout << "ScopeTable with id " << current_scope->getId() << " removed" << endl;
        ScopeTable *temp = current_scope;
        current_scope = current_scope->getParentScope();
        delete temp;
    }
    else
    {
        cout << "NO CURRENT SCOPE" << endl;
    }
}

bool SymbolTable::insertSymbol(const SymbolInfo &symbol)
{
    return current_scope->insert(symbol);
}

bool SymbolTable::removeSymbol(const string &key)
{
    return current_scope->remove(key);
}

SymbolInfo *SymbolTable::searchSymbol(const string &key)
{
    ScopeTable *cur = current_scope;
    while (cur != nullptr)
    {
        SymbolInfo *symbol = cur->search(key);
        if (symbol != nullptr)
        {
            return symbol;
        }
        cur = cur->getParentScope();
    }
    cout << "Not Found" << endl;
    return nullptr;
}

void SymbolTable::printCurrentScope()
{
    current_scope->print();
}

void SymbolTable::printAllScope()
{
    ScopeTable *cur = current_scope;
    while (cur != nullptr)
    {
        cur->print();
        cur = cur->getParentScope();
    }
    cout << endl;
}
