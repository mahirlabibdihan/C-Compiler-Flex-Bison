#ifndef __PARSE_TREE_H
#define __PARSE_TREE_H 1
#include "../include/ExtendedSymbol.hpp"
#include <vector>
#include <string>
// NonTerminal - child
// Terminal - no child
// class Node
// {
//     std::string name;
//     std::vector<Node *> children;
//     Node *parent;
//     void operator=(const Node &) {} // Protect assignment
//     Node(const Node &) {}           // Protect copy constructor
// public:
//     // Constructor
//     Node(std::string name)
//     {
//         this->name = name;
//         this->parent = NULL;
//         children = std::vector<Node *>();
//     }
//     // Destructor
//     ~Node() {}
// };
namespace ParseTreeGenerator
{
    void createNode(NonTerminal *node, vector<SymbolInfo *> child);
    SymbolInfo *createErrorNode(int line_no);
    NonTerminal *createNonTerminal(std::vector<SymbolInfo *> child, std::string name);
    Expression *createExpression(std::vector<SymbolInfo *> child, std::string name);
    ParameterList *createParameterList(std::vector<SymbolInfo *> child, std::string name);
    ArgumentList *createArgumentList(std::vector<SymbolInfo *> child, std::string name);
    DeclarationList *createDeclarationList(std::vector<SymbolInfo *> child, std::string name);
    ArrayCall *createArrayCall(std::vector<SymbolInfo *> child, std::string name);
    // std::string getParseTree();
    std::string getParseTree(SymbolInfo *curr);
    // void setRoot(SymbolInfo *root);
    // SymbolInfo *getRoot();
    std::string getTree(SymbolInfo *node, int depth = 0);
    void deleteTree(SymbolInfo *node);
};
#endif