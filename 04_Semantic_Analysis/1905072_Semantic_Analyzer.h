#include <string>
#include <vector>
#include "1905072_Node.h"
#include "1905072_SymbolInfo.h"
using namespace std;

string implicitTypecast(string left, string right);
bool isConvertible(string to, string from);
bool checkAssignment(string left, string right);
void defineFunction(SymbolInfo *function, vector<SymbolInfo *> params, string ret_type);
void declareFunction(string ret_type, SymbolInfo *id, vector<SymbolInfo *> params);
string callFunction(string id, vector<SymbolInfo *> args);
void declareVariable(string data_type, string id_names, vector<SymbolInfo *> ids);
string callVariable(string id);
string callArray(string id, SymbolInfo *index);
string assignmentOperation(string left, string right);
string logicalOperation(string left, string op, string right);
string relationalOperation(string left, string op, string right);
string additionalOperation(string left, string op, string right);
string multiplicationalOperation(string left, string op, string right);