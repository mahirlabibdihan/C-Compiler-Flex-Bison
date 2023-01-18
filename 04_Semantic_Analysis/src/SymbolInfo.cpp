/**
 * Author: Mahir Labib Dihan
 * Last modified: January 18, 2023
 */
#include "../include/SymbolInfo.hpp"

SymbolInfo::SymbolInfo(const std::string &name, const std::string &type, SymbolInfo *next)
{
    this->name = name;
    this->type = type;
    this->next = next;
}

SymbolInfo::~SymbolInfo() {}

const std::string &SymbolInfo::getSymbol() const
{
    return name;
}

void SymbolInfo::setSymbol(const std::string &name)
{
    this->name = name;
}

const std::string &SymbolInfo::getType() const
{
    return type;
}

void SymbolInfo::setType(const std::string &type)
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

void SymbolInfo::setStartLine(int line)
{
    this->start_line = line;
}
int SymbolInfo::getStartLine()
{
    return start_line;
}
void SymbolInfo::setEndLine(int line)
{
    this->end_line = line;
}
int SymbolInfo::getEndLine()
{
    return end_line;
}