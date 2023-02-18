/**
 * Author: Mahir Labib Dihan
 * Last modified: January 18, 2023
 */
#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include "../include/SymbolTable.hpp"
#include "../include/Util.hpp"
#include "../include/LineTracker.hpp"
#include "../include/LexicalAnalyzer.hpp"
#include "../include/SyntaxAnalyzer.hpp"
#include "../include/ErrorHandler.hpp"
#include "../include/Logger.hpp"
#include "../include/Tokenizer.hpp"
#include "../include/SemanticAnalyzer.hpp"
#include "../include/ParseTreeGenerator.hpp"
#include "../include/ASTGenerator.hpp"
#include "../include/AssemblyGenerator.hpp"
#include "../include/Optimizer.hpp"
#include "../include/CodeGenerator.hpp"
#include "../include/Compiler.hpp"
// For file input output
std::ofstream logout, tokenout, errorout, astout, codeout, asmout, optout;
CodeGenerator *code_gen;
LexicalAnalyzer *lexer;
SemanticAnalyzer *sem_anlzr;
SyntaxAnalyzer *syn_anlzr;
ErrorHandler *error_hndlr;
AssemblyGenerator *asm_gen;
SymbolTable *table;
Compiler *compiler;
Program *runParser(FILE *fin);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Please provide input file name and try again\n");
        return EXIT_FAILURE;
    }

    logout.open("io/log.txt");
    tokenout.open("io/token.txt");
    errorout.open("io/error.txt");
    astout.open("io/ast.txt");
    codeout.open("io/code.c");
    asmout.open("io/code.asm");

    table = new SymbolTable(11);
    error_hndlr = new ErrorHandler();
    lexer = new LexicalAnalyzer(error_hndlr, logout, tokenout);
    sem_anlzr = new SemanticAnalyzer(lexer, table, error_hndlr, logout, errorout);
    syn_anlzr = new SyntaxAnalyzer(lexer, error_hndlr, logout, errorout);
    asm_gen = new AssemblyGenerator(asmout);
    code_gen = new CodeGenerator(codeout);
    compiler = new Compiler(runParser, lexer, sem_anlzr, error_hndlr, logout, astout);

    compiler->compile(argv[1]);

    asmout.close();
    codeout.close();
    logout.close();
    astout.close();
    errorout.close();
    tokenout.close();

    delete compiler;
    delete code_gen;
    delete asm_gen;
    delete syn_anlzr;
    delete sem_anlzr;
    delete lexer;
    delete error_hndlr;
    delete table;

    return EXIT_SUCCESS;
}

void ScopeTable::print() const
{
    logout << '\t' << "ScopeTable# " << id << std::endl;
    for (int i = 0; i < num_buckets; i++)
    {
        SymbolInfo *cur = hash_table[i];
        if (cur == nullptr)
        {
            continue;
        }
        logout << "\t" << i + 1 << "--> ";
        while (cur != nullptr)
        {
            if (((ASTNode *)cur)->getASTType() == "TERMINAL")
            {
                Terminal *cur_2 = (Terminal *)cur;
                if (cur_2->getTerminalType() == "IDENTIFIER")
                {
                    Identifier *cur_3 = (Identifier *)cur_2;
                    if (cur_3->getIdentity() == "FUNCTION")
                    {
                        Function *cur_4 = (Function *)cur_3;
                        logout << "<" << cur_4->getUniqueName() << ", " << cur_4->getIdentity() << ", " << cur_4->getReturnType() << "> ";
                    }
                    else if (cur_3->getIdentity() == "VARIABLE")
                    {
                        Variable *cur_4 = (Variable *)cur_3;
                        if (cur_4->getVarType() == "ARRAY")
                        {
                            logout << "<" << cur_4->getUniqueName() << ", " << cur_4->getVarType() << ", " << cur_4->getDataType() << "> ";
                        }
                        else if (cur_4->getVarType() == "PRIMITIVE")
                        {
                            logout << "<" << cur_4->getUniqueName() << ", " << cur_4->getDataType() << "> ";
                        }
                    }
                }
            }
            cur = cur->getNext();
        }
        logout << std::endl;
    }
}
