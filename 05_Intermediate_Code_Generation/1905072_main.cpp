#include <iostream>
#include <fstream>
#include "1905072_SymbolTable.h"
#include "1905072_Assembly_Generator.h"
#include "1905072_Semantic_Analyzer.h"
using namespace std;

ofstream errout;
ofstream logout;
ofstream tokenout;
ofstream codeout;
SymbolTable *table;
vector<string> data_segment;
vector<string> code_segment;
int line_count;
int error_count;
AssemblyGenerator *asm_gen;
SemanticAnalyzer *sem_anlz;
int yyparse(void);
extern FILE *yyin;
extern int yylineno;

unsigned long sdbmHash(string str)
{
    unsigned long hash = 0;
    for (auto ch : str)
    {
        int c = ch;
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

void ScopeTable::print()
{
    logout << "ScopeTable # " << id << endl;
    for (int i = 0; i < n_buckets; i++)
    {
        SymbolInfo *cur = hash_table[i];
        if (cur == nullptr)
        {
            continue;
        }
        logout << " " << i << " --> ";

        while (cur != nullptr)
        {
            logout << "< " << cur->getName() << " : " << cur->getType()
                   << "> ";
            cur = cur->getNext();
        }
        logout << endl;
    }
    logout << endl;
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

    errout.open("1905072_error.txt");
    logout.open("1905072_log.txt");
    tokenout.open("1905072_token.txt");
    codeout.open("1905072_code.asm");

    table = new SymbolTable(7, sdbmHash);
    asm_gen = new AssemblyGenerator("1905072_code.asm");
    sem_anlz = new SemanticAnalyzer();
    yyin = fin;
    line_count = yylineno = 1;
    error_count = 0;
    asm_gen->startCode();
    yyparse();
    fclose(yyin);

    table->printAllScope();

    logout << "Total lines: " << yylineno << endl;
    logout << "Total errors: " << error_count;

    errout.close();
    logout.close();
    tokenout.close();
    codeout.close();

    return EXIT_SUCCESS;
}