#include "1905072_SymbolInfo.h"

void SymbolInfo::init()
{
    this->name = "";
    this->type = "";
    this->next = nullptr;
}
SymbolInfo::SymbolInfo()
{
    init();
}

SymbolInfo::SymbolInfo(const string &name, const string &type)
{
    init();
    this->name = name;
    this->type = type;
}

SymbolInfo::SymbolInfo(const string &name, const string &type, SymbolInfo *next)
{
    init();
    this->name = name;
    this->type = type;
    this->next = next;
}

SymbolInfo::~SymbolInfo()
{
    // cout << type << " Symbol destructed" << endl;
}

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
