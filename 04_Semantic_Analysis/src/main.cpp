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
#include "../include/ErrorHandler.hpp"
#include "../include/Logger.hpp"
#include "../include/Tokenizer.hpp"
#include "../include/SemanticAnalyzer.hpp"
#include "../include/ParseTreeGenerator.hpp"
// For file input output
std::ofstream logout;
std::ofstream tokenout;
std::ofstream errorout;
std::ofstream parseout;
LexicalAnalyzer *lexer;
SemanticAnalyzer *sem_anlzr;
ErrorHandler *error_hndlr;
SymbolTable *table;

void runParser(FILE *fin);
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
            if (cur->getType() == "TERMINAL")
            {
                Terminal *cur_2 = (Terminal *)cur;
                if (cur_2->getTerminalType() == "ID")
                {
                    Identifier *cur_3 = (Identifier *)cur_2;
                    if (cur_3->getIdentity() == "FUNCTION")
                    {
                        Function *cur_4 = (Function *)cur_3;
                        logout << "<" << cur_4->getSymbol() << ", " << cur_4->getIdentity() << ", " << cur_4->getReturnType() << "> ";
                    }
                    else if (cur_3->getIdentity() == "VARIABLE")
                    {
                        Variable *cur_4 = (Variable *)cur_3;
                        if (cur_4->getVarType() == "ARRAY")
                        {
                            logout << "<" << cur_4->getSymbol() << ", " << cur_4->getVarType() << ", " << cur_4->getDataType() << "> ";
                        }
                        else if (cur_4->getVarType() == "PRIMITIVE")
                        {
                            logout << "<" << cur_4->getSymbol() << ", " << cur_4->getDataType() << "> ";
                        }
                    }
                }
            }
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
    errorout.open("io/error.txt");
    parseout.open("io/parsetree.txt");

    table = new SymbolTable(11);
    error_hndlr = new ErrorHandler();
    lexer = new LexicalAnalyzer(error_hndlr, logout, tokenout);
    sem_anlzr = new SemanticAnalyzer(lexer, table, error_hndlr, logout, errorout);

    runParser(fin); // Main Parser

    // table->printAllScope();
    logout << "Total Lines: " << lexer->getLineCount() << std::endl;
    logout << "Total Errors: " << lexer->getErrorCount() << std::endl;

    NonTerminal *root = sem_anlzr->getParseTreeRoot();
    parseout << ParseTreeGenerator::getTree(root);
    delete root;

    fclose(fin);
    logout.close();
    parseout.close();
    errorout.close();
    tokenout.close();

    delete sem_anlzr;
    delete lexer;
    delete error_hndlr;
    delete table;

    return EXIT_SUCCESS;
}