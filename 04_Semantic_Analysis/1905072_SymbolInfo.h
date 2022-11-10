
#ifndef __SYMBOL_INFO__
#define __SYMBOL_INFO__
#include <iostream>
#include <vector>
using namespace std;
class SymbolInfo
{
private:
    string name;
    string type;
    SymbolInfo *next;
    string id_type;   // VARIABLE, ARRAY, FUNCTION
    string data_type; // return type for function
    bool is_definition;
    vector<string> param_types;

    void operator=(const SymbolInfo &) {} // Protect assignment
    SymbolInfo(const SymbolInfo &) {}     // Protect copy constructor
public:
    SymbolInfo();
    SymbolInfo(const string &name, const string &type);
    SymbolInfo(const string &name, const string &type, SymbolInfo *next);
    SymbolInfo(const string &name, const string &type, string data_type, string id_type, bool is_definition, vector<string> params);
    ~SymbolInfo();
    const string &getName() const;
    void setName(const string &name);
    const string &getType() const;
    void setType(const string &type);
    SymbolInfo *getNext() const;
    void setNext(SymbolInfo *next);
    const string &getIdType() const;
    void setIdType(const string &name);
    const string &getDataType() const;
    void setDataType(const string &name);
    const bool &isDefined() const;
    void define();
    vector<string> &getParamTypes();
    void setParamTypes(vector<string> pt);
};
#endif
