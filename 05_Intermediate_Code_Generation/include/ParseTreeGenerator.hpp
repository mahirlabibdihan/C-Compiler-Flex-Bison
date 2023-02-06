#ifndef __PARSE_TREE_GENERATOR_H
#define __PARSE_TREE_GENERATOR_H 1
#include "../include/ExtendedSymbol.hpp"
#include <vector>
#include <string>

namespace ParseTreeGenerator
{
    void createNode(NonTerminal *node, vector<SymbolInfo *> child);
    SymbolInfo *createErrorNode();
    NonTerminal *createNonTerminal(std::vector<SymbolInfo *> child, std::string name);
    Expression *createExpression(std::vector<SymbolInfo *> child, std::string name);
    ParameterList *createParameterList(std::vector<SymbolInfo *> child, std::string name);
    ArgumentList *createArgumentList(std::vector<SymbolInfo *> child, std::string name);
    DeclarationList *createDeclarationList(std::vector<SymbolInfo *> child, std::string name);
    ArrayCall *createArrayCall(std::vector<SymbolInfo *> child, std::string name);
    std::string getParseTree(SymbolInfo *curr);
    std::string getTree(SymbolInfo *node, int depth = 0);
    std::string getASTTree(ASTNode *node, int depth = 0);
    // void deleteTree(SymbolInfo *node);
};
#endif