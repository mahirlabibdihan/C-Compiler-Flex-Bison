#ifndef __COMPILER_H
#define __COMPILER_H

#include <cstdio>
#include "../include/ExtendedSymbol.hpp"
#include "../include/LexicalAnalyzer.hpp"
#include "../include/ErrorHandler.hpp"
#include "../include/SemanticAnalyzer.hpp"
#include <functional>
class Compiler
{
    std::function<Program *(FILE *)> runParser;
    Program *ast_root;
    LexicalAnalyzer *lexer;
    ErrorHandler *error_hndlr;
    std::ofstream &logout;
    std::ofstream &parseout;
    SemanticAnalyzer *sem_anlzr;

public:
    Compiler(std::function<Program *(FILE *)>, LexicalAnalyzer *lexer, SemanticAnalyzer *sem_anlzr, ErrorHandler *error_hndlr, std::ofstream &logout, std::ofstream &parseout);
    Program *getASTRoot();
    void setASTRoot(Program *);
    int compile(const string &code_file);
};
#endif