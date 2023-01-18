#include <iostream>
#include <fstream>
#include "1905072_SymbolTable.hpp"
#include "1905072_Assembly_Generator.hpp"
#include "1905072_Semantic_Analyzer.hpp"
#include "1905072_Optimizer.hpp"
#include "1905072_Tokenizer.hpp"
#include "1905072_Logger.hpp"
#include "1905072_Error_Handler.hpp"
#include "1905072_Helper.hpp"
using namespace std;

ofstream errout;
ofstream logout;
ofstream lexlogout;
ofstream tokenout;
ofstream codeout;
ifstream codein;
SymbolTable *table;
vector<string> data_segment;
vector<string> code_segment;
int line_count;
int error_count;
int lexical_error_count;
int syntax_error_count;
int semantic_error_count;
AssemblyGenerator *asm_gen;
SemanticAnalyzer *sem_anlz;
Tokenizer *tknzr;
Optimizer *optmzr;
Logger *logger;
ErrorHandler *err_hndlr;
Helper *hlpr;

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
            logout << "< " << cur->getSymbol() << " : " << cur->getType()
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
    lexlogout.open("1905072_lexlog.txt");
    tokenout.open("1905072_token.txt");
    codeout.open("1905072_code.asm");

    table = new SymbolTable(7, sdbmHash);
    asm_gen = new AssemblyGenerator("1905072_code.asm");
    sem_anlz = new SemanticAnalyzer();
    optmzr = new Optimizer();
    tknzr = new Tokenizer();
    logger = new Logger();
    err_hndlr = new ErrorHandler();
    hlpr = new Helper();

    yyin = fin;
    line_count = yylineno = 1;
    lexical_error_count = syntax_error_count = semantic_error_count = 0;

    asm_gen->startCode();
    yyparse();
    fclose(yyin);

    table->printAllScope();

    logout << "Total lines: " << yylineno << endl;
    logout << "Total Lexical Errors: " << lexical_error_count << endl;
    logout << "Total Syntax Errors: " << syntax_error_count << endl;
    logout << "Total Semantic Errors: " << semantic_error_count << endl;

    errout << "Total Lexical Errors: " << lexical_error_count << endl;
    errout << "Total Syntax Errors: " << syntax_error_count << endl;
    errout << "Total Semantic Errors: " << semantic_error_count << endl;

    errout.close();
    logout.close();
    tokenout.close();
    codeout.close();
    lexlogout.close();

    if (error_count == 0)
    {

        codein.open("1905072_code.asm");
        optmzr->optimize(); // For first level pass
        codein.close();
        }
    else
    {
        codeout.open("1905072_code.asm");
        codeout.close();
    }

    delete table;
    delete asm_gen;
    delete sem_anlz;
    delete optmzr;
    delete tknzr;
    delete logger;
    delete err_hndlr;
    delete hlpr;

    return EXIT_SUCCESS;
}