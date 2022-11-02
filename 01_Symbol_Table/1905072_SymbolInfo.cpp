#include "1905072_SymbolInfo.h"

SymbolInfo::SymbolInfo()
{
    this->next = nullptr;
}

SymbolInfo::SymbolInfo(const string &name, const string &type)
{
    this->name = name;
    this->type = type;
    this->next = nullptr;
}

SymbolInfo::SymbolInfo(const string &name, const string &type, SymbolInfo *next)
{
    this->name = name;
    this->type = type;
    this->next = next;
}

SymbolInfo::~SymbolInfo() {}

const string &SymbolInfo::getName() const
{
    return name;
}

void SymbolInfo::setName(const string &name)
{
    this->name = name;
}

const string &SymbolInfo::getType() const
{
    return type;
}

void SymbolInfo::setType(const string &type)
{
    this->type = type;
}

SymbolInfo *SymbolInfo::getNext() const
{
    return next;
}

void SymbolInfo::setNext(SymbolInfo *next)
{
    this->next = next;
}
