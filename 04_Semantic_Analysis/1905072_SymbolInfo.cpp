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
    this->data_type = "";
    this->id_type = "";
    this->is_definition = false;
    this->param_types = vector<string>();
}

SymbolInfo::SymbolInfo(const string &name, const string &type, SymbolInfo *next)
{
    this->name = name;
    this->type = type;
    this->next = next;
    this->data_type = "";
    this->id_type = "";
    this->is_definition = false;
    this->param_types = vector<string>();
}

SymbolInfo::SymbolInfo(const string &name, const string &type, string data_type, string id_type, bool is_definition, vector<string> params)
{
    this->name = name;
    this->type = type;
    this->data_type = data_type;
    this->id_type = id_type;
    this->is_definition = is_definition;
    this->param_types = params;
    this->next = nullptr;
}

SymbolInfo::~SymbolInfo()
{
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

const string &SymbolInfo::getIdType() const
{
    return id_type;
}
void SymbolInfo::setIdType(const string &type)
{
    id_type = type;
}
const string &SymbolInfo::getDataType() const
{
    return data_type;
}
void SymbolInfo::setDataType(const string &type)
{
    data_type = type;
}
const bool &SymbolInfo::isDefined() const
{
    return is_definition;
}
void SymbolInfo::define()
{
    is_definition = true;
}
vector<string> &SymbolInfo::getParamTypes()
{
    return param_types;
}
void SymbolInfo::setParamTypes(vector<string> pt)
{
    param_types = pt;
}