#include <iostream>
#include <cstdio>
#include "1905072_SymbolTable.h"
#include "1905072_SymbolInfo.h"
#include "1905072_ScopeTable.h"
using namespace std;

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
    cout << "ScopeTable # " << id << endl;
    for (int i = 0; i < n_buckets; i++)
    {
        cout << i << " --> ";
        SymbolInfo *cur = hash_table[i];
        while (cur != nullptr)
        {
            cout << "< " << cur->getName() << " : " << cur->getType() << "> ";
            cur = cur->getNext();
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    int n_buckets;
    cin >> n_buckets;
    SymbolTable sym_tab(n_buckets, sdbmHash);
    char command;
    while (cin >> command)
    {
        cout << command << " ";
        switch (command)
        {
        case 'I': // Insert symbol
        {
            string name, type;
            cin >> name >> type;
            cout << name << " " << type << endl;

            cout << endl;
            if (sym_tab.insert(SymbolInfo(name, type)))
            {
                cout << "Inserted in ScopeTable# " << sym_tab.getLastAccessedScopeId() << " at position " << sym_tab.getLastAccessedScope()->getLastAccessedLocation().first << ", " << sym_tab.getLastAccessedScope()->getLastAccessedLocation().second << endl;
            }
            else
            {
                cout << "< " << name << "," << type << " > already exists in current ScopeTable" << endl;
            }
            cout << endl;

            break;
        }
        case 'L': // Lookup symbol
        {
            string name;
            cin >> name;
            cout << name << endl;

            cout << endl;
            if (sym_tab.search(name) != nullptr)
            {
                cout << "Found in ScopeTable# " << sym_tab.getLastAccessedScopeId() << " at position " << sym_tab.getLastAccessedScope()->getLastAccessedLocation().first << ", " << sym_tab.getLastAccessedScope()->getLastAccessedLocation().second << endl;
            }
            else
            {
                cout << "Not Found" << endl;
            }
            cout << endl;

            break;
        }

        case 'D': // Delete symbol
        {
            string name;
            cin >> name;
            cout << name << endl;

            cout << endl;
            if (sym_tab.remove(name))
            {
                cout << "Deleted Entry " << sym_tab.getLastAccessedScope()->getLastAccessedLocation().first << ", " << sym_tab.getLastAccessedScope()->getLastAccessedLocation().second << " from current ScopeTable" << endl;
            }
            else
            {
                cout << name << " not found" << endl;
            }
            cout << endl;

            break;
        }
        case 'S': // Start scope
        {
            cout << endl;

            cout << endl;
            if (sym_tab.enterScope())
            {
                cout << "New ScopeTable with id " << sym_tab.getLastAccessedScopeId() << " created" << endl;
            }
            cout << endl;

            break;
        }
        case 'E': // End scope
        {
            cout << endl;

            cout << endl;
            if (sym_tab.exitScope())
            {
                cout << "ScopeTable with id " << sym_tab.getLastAccessedScopeId() << " removed" << endl;
            }
            cout << endl;

            break;
        }

        case 'P': // Print
        {
            char print_type;
            cin >> print_type;
            cout << print_type << endl;

            cout << endl;
            if (print_type == 'C')
            {
                sym_tab.printCurrentScope();
            }
            else if (print_type == 'A')
            {
                sym_tab.printAllScope();
            }
            cout << endl;

            break;
        }
        default:
            break;
        }
    }
    return 0;
}
