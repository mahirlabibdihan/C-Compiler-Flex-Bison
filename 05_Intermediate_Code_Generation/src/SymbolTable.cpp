/**
 * Author: Mahir Labib Dihan
 * Last modified: January 18, 2023
 */
#include "../include/SymbolTable.hpp"
#include <iostream>
SymbolTable::SymbolTable(int n)
{
    this->scope_count = 1;
    this->num_buckets = n;
    this->current_scope = new ScopeTable(n);
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

bool SymbolTable::enterScope()
{
    ScopeTable *st = new ScopeTable(num_buckets);

    st->setParentScope(current_scope);
    current_scope = st;

    if (st->getParentScope() != nullptr)
    {
        st->setId(++scope_count);
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
        delete tmp;
        return true;
    }
    return false;
}

bool SymbolTable::insert(const std::string &name, const std::string &type)
{
    if (current_scope == nullptr)
    {
        // error recovery
        current_scope = new ScopeTable(num_buckets);
    }
    return current_scope->insert(name, type);
}

bool SymbolTable::insert(SymbolInfo *symbol)
{
    if (current_scope == nullptr)
    {
        current_scope = new ScopeTable(num_buckets);
    }
    return current_scope->insert(symbol);
}

bool SymbolTable::erase(const std::string &name)
{
    if (current_scope == nullptr)
    {
        return false;
    }
    return current_scope->erase(name);
}

SymbolInfo *SymbolTable::find(const std::string &name) const
{
    ScopeTable *curr = current_scope;

    while (curr != nullptr)
    {
        SymbolInfo *symbol = curr->find(name);
        if (symbol != nullptr)
        {
            return symbol;
        }
        curr = curr->getParentScope();
    }
    return nullptr;
}

std::pair<int, int> SymbolTable::getLocationOfSymbol(const std::string &name) const
{
    ScopeTable *curr = current_scope;
    while (curr != nullptr)
    {
        std::pair<int, int> location = curr->getLocationOfSymbol(name);
        if (location.first != 0)
        {
            return location;
        }
        curr = curr->getParentScope();
    }
    return {0, 0};
}

int SymbolTable::getScopeIdOfSymbol(const std::string &name) const
{
    ScopeTable *curr = current_scope;

    while (curr != nullptr)
    {
        SymbolInfo *symbol = curr->find(name);
        if (symbol != nullptr)
        {
            return curr->getId();
        }
        curr = curr->getParentScope();
    }
    return 0;
}

void SymbolTable::printCurrentScope() const
{
    if (current_scope != nullptr)
    {
        current_scope->print();
    }
}

void SymbolTable::printAllScope() const
{
    ScopeTable *curr = current_scope;
    while (curr != nullptr)
    {
        curr->print();
        curr = curr->getParentScope();
    }
}