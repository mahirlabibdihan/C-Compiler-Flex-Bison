#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include "../include/SymbolTable.hpp"
#include "../include/Util.hpp"
#include "../include/LineTracker.hpp"
#include "../include/LexicalAnalyzer.hpp"
#include "../include/ErrorHandler.hpp"
#include "../include/Logger.hpp"
#include "../include/Tokenizer.hpp"
// For file input output
std::ofstream logout;
std::ofstream tokenout;
LexicalAnalyzer *lexer;
void runFlex(FILE *fin);
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
            logout << "<" << cur->getSymbol() << "," << cur->getType() << "> ";
            cur = cur->getNext();
        }
        logout << std::endl;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Please provide input file name and try again\n");
        return EXIT_FAILURE;
    }

    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL)
    {
        printf("Cannot open specified file\n");
        return EXIT_FAILURE;
    }

    logout.open("io/log.txt");
    tokenout.open("io/token.txt");

    SymbolTable *table = new SymbolTable(10);
    ErrorHandler *error_hndlr = new ErrorHandler();

    lexer = new LexicalAnalyzer(table, error_hndlr, logout, tokenout);

    runFlex(fin); // Main lexer

    table->printAllScope();
    logout << "Total lines: " << lexer->getLineCount() << std::endl;
    logout << "Total errors: " << lexer->getErrorCount() << std::endl;

    fclose(fin);
    logout.close();

    delete lexer;
    delete error_hndlr;
    delete table;

    return EXIT_SUCCESS;
}