#include "../include/ParseTreeGenerator.hpp"
#include "../include/Logger.hpp"
#include "../include/Util.hpp"

// Terminal - Symbol - <Line: Line_Count>
// NonTerminal - Children - <Line: Start - Line_Count>

void ParseTreeGenerator::createNode(NonTerminal *node, vector<SymbolInfo *> child)
{
    node->setChidren(child);
    node->setStartLine(child.front()->getStartLine());
    node->setEndLine(child.back()->getStartLine());
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
        Logger::getRuleAndLine(((Terminal *)curr)->getTerminalType(), curr->getSymbol());
    }
    else
    {
        std::vector<SymbolInfo *> child = ((NonTerminal *)curr)->getChidren();
        rule += Logger::getRuleAndLine(curr, child);
        for (auto &c : child)
        {
            rule += getParseTree(c);
        }
    }
    return rule;
}

std::string ParseTreeGenerator::getParseTree()
{
    return getParseTree();
}