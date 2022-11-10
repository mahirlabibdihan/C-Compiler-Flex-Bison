#include <string>
#include "1905072_Node.h"
#include <vector>
#include "1905072_SymbolInfo.h"

Node::Node(){};
// Helper::Helper(string text, vector<SymbolInfo *> v)
// {
//     this->text = text;
//     this->v = v;
// }

string Node::getCode() { return code; }
void Node::setCode(string text) { this->code = text; }
vector<SymbolInfo *> &Node::getList() { return list; }
void Node::setList(vector<SymbolInfo *> list) { this->list = list; };
void Node::setSymbol(SymbolInfo *s) { symbol = s; }
SymbolInfo *Node::getSymbol() { return symbol; }
void Node::setDataType(string type) { data_type = type; }
string Node::getDataType() { return data_type; }
// void Helper::print()
// {
//     cout << "Text : " << text << endl;

//     cout << "Vector Size : " << v.size() << endl;
//     cout << "Vector  : " << endl;
//     for (auto s : v)
//     {
//         cout << s->getName() << " , " << s->getType() << endl;
//     }
// }