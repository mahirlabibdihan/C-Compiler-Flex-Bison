#include "../include/ParseTreeGenerator.hpp"
#include "../include/Logger.hpp"
#include "../include/Util.hpp"
#include "../include/SemanticAnalyzer.hpp"
#include <iostream>
#include <fstream>
// Terminal - Symbol - <Line: Line_Count>
// NonTerminal - Children - <Line: Start - Line_Count>
extern std::ofstream logout;
extern SemanticAnalyzer *sem_anlzr;
void ParseTreeGenerator::createNode(NonTerminal *node, vector<SymbolInfo *> child)
{

    node->setChildren(child);

    if (child.empty())
    {
        node->setStartLine(sem_anlzr->getLineCount());
        node->setEndLine(sem_anlzr->getLineCount());
    }
    else
    {
        node->setStartLine(child.front()->getStartLine());
        node->setEndLine(child.back()->getEndLine());
    }

    if (child.size() == 1 && child.front()->getType() == "error")
    {
        // logout << "Syntax error" << std::endl;
    }
    else
    {
        // std::cout << node->getNonTerminalType() << std::endl;
        logout << Logger::getRule(node, child) << std::endl;
    }
}
SymbolInfo *ParseTreeGenerator::createErrorNode(int line_no)
{
    SymbolInfo *node = new SymbolInfo("error", "error");
    // logout << "Error at line no " << line_no << " : syntax error" << std::endl;
    node->setStartLine(line_no);
    node->setEndLine(line_no);
    return node;
}
NonTerminal *ParseTreeGenerator::createNonTerminal(vector<SymbolInfo *> child, string name)
{
    NonTerminal *node = new NonTerminal(
        Util::formatCode(child),
        name);
    createNode(node, child);
    return node;
}

Expression *ParseTreeGenerator::createExpression(vector<SymbolInfo *> child, string name)
{
    Expression *node = new Expression(
        Util::formatCode(child),
        name);
    createNode(node, child);
    return node;
}

ParameterList *ParseTreeGenerator::createParameterList(vector<SymbolInfo *> child, string name)
{
    ParameterList *node = new ParameterList(
        Util::formatCode(child),
        name);
    createNode(node, child);
    return node;
}

DeclarationList *ParseTreeGenerator::createDeclarationList(vector<SymbolInfo *> child, string name)
{
    DeclarationList *node = new DeclarationList(
        Util::formatCode(child),
        name);
    createNode(node, child);
    return node;
}

ArgumentList *ParseTreeGenerator::createArgumentList(vector<SymbolInfo *> child, string name)
{
    ArgumentList *node = new ArgumentList(
        Util::formatCode(child),
        name);
    createNode(node, child);
    return node;
}

ArrayCall *ParseTreeGenerator::createArrayCall(vector<SymbolInfo *> child, string name)
{
    ArrayCall *node = new ArrayCall(
        Util::formatCode(child),
        name);
    createNode(node, child);
    return node;
}

// void ParseTreeGenerator::setRoot(SymbolInfo *symbol)
// {
//     root = symbol;
// }

// SymbolInfo *ParseTreeGenerator::getRoot()
// {
//     return root;
// }
std::string ParseTreeGenerator::getParseTree(SymbolInfo *curr)
{
    std::string rule;
    if (curr->getType() == "TERMINAL")
    {
        rule += Logger::getRuleAndLine(curr);
    }
    else
    {
        std::vector<SymbolInfo *> child = ((NonTerminal *)curr)->getChildren();
        rule += Logger::getRuleAndLine(curr, child);
        for (auto &c : child)
        {
            rule += getParseTree(c);
        }
    }
    return rule;
}

// std::string ParseTreeGenerator::getParseTree()
// {
//     return getParseTree();
// }

std::string ParseTreeGenerator::getTree(SymbolInfo *node, int depth)
{
    if (node->getType() == "error")
    {
        // std::cout << node->getSymbol() << " " << node->getType() << std::endl;
        return "";
    }
    std::string tree;
    for (int i = 0; i < depth; i++)
    {
        tree += " ";
    }
    if (node->getType() == "NON_TERMINAL")
    {
        std::vector<SymbolInfo *> child = ((NonTerminal *)node)->getChildren();
        tree += Logger::getRuleAndLine(node, child) + "\n";
        for (auto c : child)
        {
            tree += getTree(c, depth + 1);
        }
    }
    else
    {
        tree += Logger::getRuleAndLine(node) + "\n";
    }
    return tree;
}

void ParseTreeGenerator::deleteTree(SymbolInfo *node)
{
    if (node->getType() == "error")
    {
        return;
    }
    if (node->getType() == "NON_TERMINAL")
    {
        std::vector<SymbolInfo *> child = ((NonTerminal *)node)->getChildren();
        for (auto c : child)
        {
            deleteTree(c);
        }
    }
    else
    {
    }
    delete node;
}