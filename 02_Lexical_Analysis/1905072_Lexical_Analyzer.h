#include <iostream>
#include <fstream>
#include <map>
#include "../01_Symbol_Table/1905072_ScopeTable.h"
#include "../01_Symbol_Table/1905072_SymbolTable.h"
using namespace std;

ofstream logout;
ofstream tokenout;

int error_count = 0;
int nl_inside = 0;

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

int bucket_size = 7;
SymbolTable sym_tab(bucket_size, sdbmHash);

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
            logout << "< " << cur->getName() << " : " << cur->getType() << "> ";
            cur = cur->getNext();
        }
        logout << endl;
    }
    logout << endl;
}

string toUpper(string s)
{
    for (auto &ch : s)
        ch = toupper(ch);
    return s;
}

void printLogData(string token, string lexeme, int line = yylineno)
{
    logout << "Line no " << line << ": Token <" << token << "> Lexeme " << lexeme << " found\n"
           << endl;
}

void printToken(string token)
{
    tokenout << "<" << token << "> ";
    printLogData(token, yytext);
}

void printTokenWithSymbol(string token, string symbol)
{
    tokenout << "<" << token << ", " << symbol << "> ";
    printLogData(token, symbol);
}

void printErrorLog(string error, int line = yylineno)
{
    error_count++;
    logout << "Error at line no " << line << ": " << error << "\n"
           << endl;
}

void insertIntoHashTable(string token, string lexeme)
{
    if (sym_tab.insert(SymbolInfo(lexeme, token)))
    {
        sym_tab.printAllScope();
    }
    else
    {
        // logout << yytext << " already exists in current ScopeTable\n"
        //        << endl;
    }
}

void addKeyword()
{
    printToken(toUpper(yytext));
}

void addConstant(string token)
{
    printTokenWithSymbol(token, yytext);
    insertIntoHashTable(token, yytext);
}

char getSpecialChar(char c)
{
    switch (c)
    {
    case '0':
        return 0;
        break;
    case 'a':
        return 7;
        break;
    case 'b':
        return 8;
        break;
    case 't':
        return 9;
        break;
    case 'n':
        return 10;
        break;
    case 'v':
        return 11;
        break;
    case 'f':
        return 12;
        break;
    case 'r':
        return 13;
        break;
    default:
        return c;
        break;
    }
}
char makeSpecialChar(string symbol)
{
    if (symbol[0] != '\\')
    {
        return symbol[0];
    }
    else
    {
        return getSpecialChar(symbol[1]);
    }
}

string makeSpecialString(string str)
{
    int n = str.length();
    string tmp;
    for (int i = 0; i < n; i++)
    {
        if (str[i] == '\\')
        {
            i++;
            tmp += getSpecialChar(str[i]);
        }
        else
        {
            tmp += str[i];
        }
    }
    return tmp;
}
void addCharacter(string token, string symbol)
{
    tokenout << "<"
             << "CHAR_CONST"
             << ", " << makeSpecialChar(symbol) << "> ";
    logout << "Line no " << yylineno << ": Token <" << token << "> Lexeme '"
           << symbol
           << "' found "
           << "--> <"
           << "CHAR_CONST"
           << ", " << makeSpecialChar(symbol) << ">\n"
           << endl;
    insertIntoHashTable(token, "'" + symbol + "'");
}

void addString(string token, string lexeme, string symbol)
{
    tokenout << "<" << token << ", \"" << symbol << "\"> ";
    logout << "Line no " << yylineno - nl_inside << ": Token <" << token << "> Lexeme \""
           << lexeme
           << "\" found "
           << "--> <" << token << ", \"" << symbol << "\">\n"
           << endl;
}

void addIdentifier(string token)
{
    printTokenWithSymbol(token, yytext);
    insertIntoHashTable(token, yytext);
}

void addOperator(string token)
{
    printTokenWithSymbol(token, yytext);
}

void addComment(string token, string lexeme)
{
    printLogData(token, lexeme, yylineno - nl_inside);
}

/*
Corner cases:
'\0a'
'abc
//asdasd\
asdsa

*/