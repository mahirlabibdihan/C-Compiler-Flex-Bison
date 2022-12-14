// Windows compile: g++ -std=c++17 1905072_SymbolInfo.cpp 1905072_ScopeTable.cpp 1905072_SymbolTable.cpp 1905072_main.cpp -o main

// Linux compile: g++ 1905072_SymbolInfo.cpp 1905072_ScopeTable.cpp 1905072_SymbolTable.cpp 1905072_main.cpp -o main

#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include "../include/SymbolTable.hpp"
#include "../include/Util.hpp"
#include "../include/LineTracker.hpp"
// For file input output
std::ifstream fin;
std::ofstream logout;
std::ofstream tokenout;
SymbolTable *table;
LineTracker *line_trkr;
extern FILE *yyin;
extern int yylineno;
extern int yylex(void);
int line_count;
int error_count;
int lexical_error_count;
// Just to keep all i/o instructions in main file
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
        return 0;
    }

    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL)
    {
        printf("Cannot open specified file\n");
        return 0;
    }

    tokenout.open("io/token.txt");
    logout.open("io/log.txt");

    table = new SymbolTable(10);
    line_trkr = new LineTracker();
    yyin = fin;
    line_count = yylineno = 1;
    error_count = lexical_error_count = 0;
    yylex();
    fclose(yyin);

    table->printAllScope();

    logout << "Total lines: " << yylineno << std::endl;
    logout << "Total errors: " << error_count << std::endl;

    tokenout.close();
    logout.close();

    return EXIT_SUCCESS;
}