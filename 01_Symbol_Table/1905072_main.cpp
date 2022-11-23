#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include "1905072_Symboltable.hpp"

// For file input output
std::ifstream fin;
std::ofstream fout;
SymbolTable *table;

// Just to keep all i/o instructions in main file
void ScopeTable::print() const
{
    fout << '\t' << "ScopeTable# " << id << std::endl;
    for (int i = 0; i < num_buckets; i++)
    {
        fout << "\t" << i + 1 << " --> ";
        SymbolInfo *cur = hash_table[i];
        while (cur != nullptr)
        {
            fout << "<" << cur->getSymbol() << " : " << cur->getType() << "> ";
            cur = cur->getNext();
        }
        fout << std::endl;
    }
}

std::vector<std::string> split(const std::string &line, char delm = ' ')
{
    std::vector<std::string> tokens;
    std::string token;
    for (char c : line)
    {
        if (c != delm)
        {
            token += c;
        }
        else
        {
            if (!token.empty())
            {
                tokens.push_back(token);
            }
            token.clear();
        }
    }
    if (!token.empty())
    {
        tokens.push_back(token);
    }

    return tokens;
}

bool checkParameter(std::vector<std::string> tokens, int num)
{
    if (tokens.size() != num)
    {
        fout << '\t' << "Number of parameters mismatch for the command " << tokens[0] << std::endl;
        return false;
    }
    return true;
}
void insertCommand(std::vector<std::string> tokens)
{
    if (!checkParameter(tokens, 3))
        return;

    std::string name = tokens[1], type = tokens[2];
    if (table->insert(name, type))
    {
        std::pair<int, int> location = table->getLocationOfSymbol(name);
        int bucket_index = location.first;
        int chain_index = location.second;
        int scope = table->getScopeIdOfSymbol(name);

        fout << '\t' << "Inserted in ScopeTable# " << scope << " at position " << bucket_index << ", " << chain_index << std::endl;
    }
    else
    {
        fout << '\t' << "<" << name << "," << type << " > already exists in current ScopeTable" << std::endl;
    }
}

void lookupCommand(std::vector<std::string> tokens)
{
    if (!checkParameter(tokens, 2))
        return;

    std::string name = tokens[1];
    if (table->find(name) != nullptr)
    {
        std::pair<int, int> location = table->getLocationOfSymbol(name);
        int bucket_index = location.first;
        int chain_index = location.second;
        int scope = table->getScopeIdOfSymbol(name);

        fout << '\t' << "'" << name << "' "
             << "Found in ScopeTable# " << scope << " at position " << bucket_index << ", " << chain_index << std::endl;
    }
    else
    {
        fout << '\t' << "'" << name << "' "
             << "not found in any of the ScopeTables" << std::endl;
    }
}

void deleteCommand(std::vector<std::string> tokens)
{
    if (!checkParameter(tokens, 2))
        return;

    std::string name = tokens[1];
    std::pair<int, int> location = table->getLocationOfSymbol(name);
    int bucket_index = location.first;
    int chain_index = location.second;
    int scope = table->getScopeIdOfSymbol(name);
    if (table->erase(name))
    {
        // Search message
        fout << '\t' << "'" << name << "' "
             << "Found in ScopeTable# " << scope << " at position " << bucket_index << ", " << chain_index << std::endl;

        // Remove message
        fout << '\t' << "Deleted '" << name << "' from ScopeTable#" << scope << " at position " << bucket_index << ", " << chain_index << std::endl;
    }
    else
    {
        fout << '\t' << "Not found in the current ScopeTable" << std::endl;
    }
}

void enterScopeCommand(std::vector<std::string> tokens)
{
    if (!checkParameter(tokens, 1))
        return;

    if (table->enterScope())
    {
        int scope = table->getCurrentScope()->getId();
        fout << '\t' << "ScopeTable# " << scope << " created" << std::endl;
    }
}

void exitScopeCommand(std::vector<std::string> tokens)
{
    if (!checkParameter(tokens, 1))
        return;

    int scope = table->getCurrentScope()->getId();
    if (table->exitScope())
    {
        fout << '\t' << "ScopeTable# " << scope << " removed" << std::endl;
    }
}

void printCommand(std::vector<std::string> tokens)
{
    if (!checkParameter(tokens, 2))
        return;

    char print_type = tokens[1][0];
    if (print_type == 'C')
    {
        table->printCurrentScope();
    }
    else if (print_type == 'A')
    {
        table->printAllScope();
    }
}

int main()
{
    fin.open("input.txt");
    fout.open("output.txt");

    int n_buckets;
    fin >> n_buckets;
    table = new SymbolTable(n_buckets);
    int scope = table->getCurrentScope()->getId();
    fout << '\t' << "ScopeTable# " << scope << " created" << std::endl;

    std::string cmd;
    std::getline(fin, cmd);
    for (int cmd_count = 1; std::getline(fin, cmd); cmd_count++)
    {
        fout << "Cmd " << cmd_count << ": " << cmd << std::endl;
        std::vector<std::string> tokens = split(cmd, ' ');

        switch (tokens[0][0])
        {
        case 'I': // Insert symbol
            insertCommand(tokens);
            break;
        case 'L': // Lookup symbol
            lookupCommand(tokens);
            break;
        case 'D': // Delete symbol
            deleteCommand(tokens);
            break;
        case 'S': // Start scope
            enterScopeCommand(tokens);
            break;
        case 'E': // End scope
            exitScopeCommand(tokens);
            break;
        case 'P': // Print
            printCommand(tokens);
            break;
        default:
            break;
        }
    }

    fin.close();
    fout.close();
    delete table;

    return EXIT_SUCCESS;
}
