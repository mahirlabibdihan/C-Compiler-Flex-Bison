#include "../include/SyntaxAnalyzer.hpp"
#include "../include/Util.hpp"
SyntaxAnalyzer::SyntaxAnalyzer(LexicalAnalyzer *lexer, SymbolTable *table, ErrorHandler *error_hndlr, ofstream &log, ofstream &error) : logout(log), errorout(error)
{
    this->lexer = lexer;
    this->table = table;
    this->error_hndlr = error_hndlr;
}
void SyntaxAnalyzer::setASTRoot(Program *ast_root)
{
    this->ast_root = ast_root;
}
Program *SyntaxAnalyzer::getASTRoot()
{
    return ast_root;
}
void SyntaxAnalyzer::deleteChildren(vector<SymbolInfo *> child)
{
    while (!child.empty())
    {
        delete child.back();
        child.pop_back();
    }
}
void SyntaxAnalyzer::setChildren(SymbolInfo *node, const vector<SymbolInfo *> &child, const string &type)
{
    if (node == NULL)
        return;
    node->setSymbol(Util::formatCode(child));
    // node->setType(type);
    if (child.empty())
    {
        node->setStartLine(lexer->getLineCount());
        node->setEndLine(lexer->getLineCount());
    }
    else
    {
        if (child.front() != NULL)
            node->setStartLine(child.front()->getStartLine());
        if (child.back() != NULL)
            node->setEndLine(child.back()->getEndLine());
    }

    // logout << Logger::getRule(node, child) << std::endl;
    // logout << node->getSymbol() << std::endl;
}

int SyntaxAnalyzer::getLineCount()
{
    return lexer->getLineCount();
}

void SyntaxAnalyzer::handleError(string parent, string error_child)
{
    errorout << error_hndlr->handleSyntaxError(parent, error_child, this->getLineCount()) << std::endl;
}

void SyntaxAnalyzer::handleError()
{
    logout << error_hndlr->handleSyntaxError(this->getLineCount()) << std::endl;
}