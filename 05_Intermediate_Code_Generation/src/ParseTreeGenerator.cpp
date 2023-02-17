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
extern ErrorHandler *error_hndlr;
// void ParseTreeGenerator::createNode(NonTerminal *node, vector<SymbolInfo *> child)
// {
//     node->setChildren(child);

//     if (child.empty())
//     {
//         node->setStartLine(sem_anlzr->getLineCount());
//         node->setEndLine(sem_anlzr->getLineCount());
//     }
//     else
//     {
//         node->setStartLine(child.front()->getStartLine());
//         node->setEndLine(child.back()->getEndLine());
//     }

//     logout << Logger::getRule(node, child) << std::endl;
// }
// SymbolInfo *ParseTreeGenerator::createErrorNode()
// {
//     SymbolInfo *node = new SymbolInfo("error", "error");
//     node->setStartLine(error_hndlr->getSyntaxErrorLine());
//     node->setEndLine(error_hndlr->getSyntaxErrorLine());
//     return node;
// }
// NonTerminal *ParseTreeGenerator::createNonTerminal(vector<SymbolInfo *> child, string name)
// {
//     NonTerminal *node = new NonTerminal(
//         Util::formatCode(child),
//         name);
//     createNode(node, child);
//     return node;
// }

// Expression *ParseTreeGenerator::createExpression(vector<SymbolInfo *> child, string name)
// {
//     Expression *node = new Expression(
//         Util::formatCode(child),
//         name);
//     createNode(node, child);
//     return node;
// }

// ParameterList *ParseTreeGenerator::createParameterList(vector<SymbolInfo *> child, string name)
// {
//     ParameterList *node = new ParameterList(
//         Util::formatCode(child),
//         name);
//     createNode(node, child);
//     return node;
// }

// DeclarationList *ParseTreeGenerator::createDeclarationList(vector<SymbolInfo *> child, string name)
// {
//     DeclarationList *node = new DeclarationList(
//         Util::formatCode(child),
//         name);
//     createNode(node, child);
//     return node;
// }

// ArgumentList *ParseTreeGenerator::createArgumentList(vector<SymbolInfo *> child, string name)
// {
//     ArgumentList *node = new ArgumentList(
//         Util::formatCode(child),
//         name);
//     createNode(node, child);
//     return node;
// }

// ArrayCall *ParseTreeGenerator::createArrayCall(vector<SymbolInfo *> child, string name)
// {
//     ArrayCall *node = new ArrayCall(
//         Util::formatCode(child),
//         name);
//     createNode(node, child);
//     return node;
// }

// std::string ParseTreeGenerator::getParseTree(SymbolInfo *curr)
// {
//     std::string rule;
//     if (curr->getType() == "TERMINAL")
//     {
//         rule += Logger::getRuleAndLine(curr);
//     }
//     else
//     {
//         std::vector<SymbolInfo *> child = ((NonTerminal *)curr)->getChildren();
//         rule += Logger::getRuleAndLine(curr, child);
//         for (auto &c : child)
//         {
//             rule += getParseTree(c);
//         }
//     }
//     return rule;
// }

// std::string ParseTreeGenerator::getTree(SymbolInfo *node, int depth)
// {
//     if (node->getType() == "error")
//     {
//         return "";
//     }
//     std::string tree;
//     for (int i = 0; i < depth; i++)
//     {
//         tree += " ";
//     }
//     if (node->getType() == "NON_TERMINAL")
//     {
//         std::vector<SymbolInfo *> child = ((NonTerminal *)node)->getChildren();
//         tree += Logger::getRuleAndLine(node, child) + "\n";
//         for (auto c : child)
//         {
//             tree += getTree(c, depth + 1);
//         }
//     }
//     else
//     {
//         tree += Logger::getRuleAndLine(node) + "\n";
//     }
//     return tree;
// }

// // void ParseTreeGenerator::deleteTree(SymbolInfo *node)
// // {
// //     if (node->getType() == "NON_TERMINAL")
// //     {
// //         std::vector<SymbolInfo *> child = ((NonTerminal *)node)->getChildren();
// //         for (auto c : child)
// //         {
// //             deleteTree(c);
// //         }
// //     }
// //     delete node;
// // }

/*
std::string ParseTreeGenerator::getASTTree(ASTNode *node, int depth)
{
    std::string tree;
    for (int i = 0; i < depth; i++)
    {
        tree += " ";
    }
    if (node->getASTType() == "NON_TERMINAL")
    {
        NonTerminal *non_term = (NonTerminal *)node;
        string type = non_term->getNonTerminalType();

        if (type == "EXPRESSION")
        {
            Expression *expr = (Expression *)non_term;
            string type = expr->getExpType();
            if (type == "CALL_EXPRESSION")
            {
            }
            if (type == "BINARY_EXPRESSION")
            {
            }
            if (type == "UNARY_EXPRESSION")
            {
            }
        }
        if (type == "STATEMENT")
        {
            Statement *stmt = (Statement *)non_term;
            string type = stmt->getStatementType();
        }
        if (type == "UNIT")
        {
            Unit *unit = (Unit *)non_term;
            string type = unit->getUnitType();
            tree += type + "\n";
            if (type == "VARIABLE_DECLARATION")
            {
                VariableDeclaration *var_decl = (VariableDeclaration *)unit;
                tree += "Data Type: " + var_decl->getDataType() + "\n";
                tree += getASTTree(var_decl->getDeclarationList(), depth + 1);
            }
            if (type == "FUNCTION_DECLARATION")
            {
            }
            if (type == "FUNCTION_DEFINITION")
            {
            }
        }
        if (type == "PROGRAM")
        {
            Program *prog = (Program *)non_term;
            vector<Unit *> units = prog->getUnits();
            tree += type + "\n";
            for (Unit *u : units)
            {
                tree += getASTTree(u, depth + 1);
            }
        }
        if (type == "LIST")
        {
            List *list = (List *)non_term;
            string type = list->getListType();
            if (type == "DECLARATION_LIST")
            {
                DeclarationList *decl_list = (DeclarationList *)list;
                vector<Variable *> var_list = decl_list->getDeclarations();
                for (Variable *var : var_list)
                {
                    tree += var->getSymbol() + "\n";
                }
            }
        }
    }
    else
    {
        // tree += Logger::getRuleAndLine(node) + "\n";
    }
    return tree;
}
*/