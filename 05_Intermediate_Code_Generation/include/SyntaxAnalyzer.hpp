#ifndef __SYNTAX_ANALYZER_H
#define __SYNTAX_ANALYZER_H 1

#include "../include/ExtendedSymbol.hpp"
#include "../include/LexicalAnalyzer.hpp"
class SyntaxAnalyzer
{
    Program *ast_root;
    SymbolTable *table;
    ErrorHandler *error_hndlr;
    LexicalAnalyzer *lexer;
    ofstream &logout;
    ofstream &errorout;

public:
    SyntaxAnalyzer(LexicalAnalyzer *lexer, SymbolTable *table, ErrorHandler *error_hndlr, ofstream &logout, ofstream &errorout);
    void setASTRoot(Program *ast_root);
    Program *getASTRoot();
    void deleteChildren(vector<SymbolInfo *> child);
    void setChildren(SymbolInfo *node, const vector<SymbolInfo *> &child, const string &type);
    int getLineCount();
    void handleError(string parent, string error_child);
    void handleError();
};
#endif