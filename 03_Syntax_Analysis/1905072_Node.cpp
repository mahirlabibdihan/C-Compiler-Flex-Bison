#include <string>
#include <vector>
#include "../01_Symbol_Table/1905072_SymbolInfo.h"
#include "1905072_Node.h"

Node::Node(){};
string Node::getCode() { return code; }
void Node::setCode(string text) { this->code = text; }
vector<SymbolInfo *> &Node::getList() { return list; }
void Node::setList(vector<SymbolInfo *> list) { this->list = list; };
void Node::setSymbol(SymbolInfo *s) { symbol = s; }
SymbolInfo *Node::getSymbol() { return symbol; }