#include "1905072_SymbolInfo.h"

void SymbolInfo::init()
{
    this->name = "";
    this->type = "";
    this->next = nullptr;
    this->data_type = "";
    this->id_type = "";
    this->is_definition = false;
    this->param_types = vector<string>();
    // cout << type << " Symbol created" << endl;
}
SymbolInfo::SymbolInfo()
{
    init();
}

SymbolInfo::SymbolInfo(string data_type)
{
    init();
    this->data_type = data_type;
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

SymbolInfo::SymbolInfo(const string &name, const string &type, string id_type)
{
    init();
    this->name = name;
    this->type = type;
    this->id_type = id_type;
}

SymbolInfo::SymbolInfo(const string &name, const string &type, string id_type, string data_type)
{
    init();
    this->name = name;
    this->type = type;
    this->id_type = id_type;
    this->data_type = data_type;
}
SymbolInfo::SymbolInfo(const string &name, const string &type, string data_type, string id_type, bool is_definition, vector<string> params)
{
    init();
    this->name = name;
    this->type = type;
    this->data_type = data_type;
    this->id_type = id_type;
    this->is_definition = is_definition;
    this->param_types = params;
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