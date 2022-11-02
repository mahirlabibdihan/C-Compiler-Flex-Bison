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
        case 'I':
        {
            string name, sym_type;
            cin >> name >> sym_type;
            cout << name << " " << sym_type << endl;
            cout << endl;
            sym_tab.insertSymbol(SymbolInfo(name, sym_type));
            cout << endl;
            break;
        }
        case 'L':
        {
            string name;
            cin >> name;
            cout << name << endl;
            cout << endl;
            sym_tab.searchSymbol(name);
            cout << endl;
            break;
        }
        case 'D':
        {
            string name;
            cin >> name;
            cout << name << endl;
            cout << endl;
            sym_tab.removeSymbol(name);
            cout << endl;
            break;
        }
        case 'S':
        {
            cout << endl;
            cout << endl;
            sym_tab.enterScope();
            cout << endl;
            break;
        }
        case 'E':
            cout << endl;
            cout << endl;
            sym_tab.exitScope();
            cout << endl;
            break;
        case 'P':
        {
            char print_type;
            cin >> print_type;
            cout << print_type << endl;
            cout << endl;
            if (print_type == 'C')
                sym_tab.printCurrentScope();
            else if (print_type == 'A')
                sym_tab.printAllScope();
            break;
        }
        default:
            break;
        }
    }
    return 0;
}
