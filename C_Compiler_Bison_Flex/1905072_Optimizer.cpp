#include "1905072_Optimizer.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

extern ofstream codeout;
extern ifstream codein;

string getLabel(string label)
{
    label.pop_back();
    return label;
}

bool isNumber(string str)
{
    for (char c : str)
    {
        if (isdigit(c) == 0)
        {
            return false;
        }
    }
    return true;
}

int strToInt(string str)
{
    stringstream ss;
    int num;
    ss << str;
    ss >> num;
    return num;
}

bool isJump(string s)
{
    if (s == "JMP" || s == "JE" || s == "JL" || s == "JLE" || s == "JG" || s == "JGE" ||
        s == "JNE" || s == "JNL" || s == "JNLE" || s == "JNG" || s == "JNGE")
    {
        return true;
    }
    return false;
}

vector<string> Optimizer::split(string s)
{
    // Tokenize string: delimitors -> ' ', '\t', ','
    vector<string> tokens;
    string token = "";
    string str = "";
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] != '\t')
        {
            str += s[i];
        }
    }
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == ' ' || str[i] == ',' || str[i] == '\t')
        {
            if (token != "")
            {
                tokens.push_back(token);
                token = "";
            }
        }
        else
        {
            token += str[i];
        }
    }

    if (token != "")
    {
        tokens.push_back(token);
    }

    return tokens;
}

void Optimizer::optimize()
{
    string line, nextLine;
    vector<string> portions, nextPortions;
    vector<string> lines;
    vector<string> opt_lines;

    while (getline(codein, line))
    {
        line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
        if (line[0] == ';')
        {
            continue;
        }
        if ((split(line).size() == 0))
        {
            continue;
        }
        lines.push_back(line);
    }

    for (int i = 0; i < lines.size() - 1; i++)
    {
        if ((split(lines[i]).size() == 0))
        {
            continue;
        }

        line = lines[i];
        nextLine = lines[i + 1];
        portions = split(line);
        nextPortions = split(nextLine);
        if (portions[0] == "PUSH")
        {
            if (nextPortions[0] == "POP")
            {
                if (portions[1] == nextPortions[1])
                { // PUSH AX ; POP AX
                    lines[i] = ";----Optimized Code----\n\t\t;" + lines[i];
                    lines[i + 1] = ";" + lines[i + 1];
                }
            }
        }

        if (portions[0] == "POP")
        {
            if (nextPortions[0] == "PUSH")
            {
                if (portions[1] == nextPortions[1])
                { // POP AX ; PUSH AX
                    lines[i] = ";----Optimized Code----\n\t\t;" + lines[i];
                    lines[i + 1] = ";" + lines[i + 1];
                }
            }
        }

        if (portions[0] == "MOV")
        {
            if (portions[1] == portions[2])
            { // MOV AX, AX
                lines[i] = "\t\t;----Optimized Code----\n";
                lines[i] += "\t\t;" + lines[i];
            }
            if (nextPortions[0] == "MOV")
            {
                if ((portions[1] == nextPortions[2]) && (portions[2] == nextPortions[1]))
                { // MOV AX, BX ; MOV BX, AX
                    lines[i + 1] = ";----Optimized Code----\n\t\t;" + lines[i + 1];
                }
                if (portions[1] == nextPortions[1])
                { // MOV AX, BX ; MOV AX, CX or MOV AX, BX ; MOV AX, BX
                    lines[i] = ";----Optimized Code----\n\t\t;" + lines[i];
                }
            }
        }
        if (nextPortions[0] == "MOV")
        {
            if (nextPortions[1] == nextPortions[2])
            { // MOV AX, AX
                lines[i + 1] = ";----Optimized Code----\n";
                lines[i + 1] += "\t\t;" + lines[i + 1];
            }
        }
        if (portions[0] == "ADD" || portions[0] == "SUB")
        {
            if (isNumber(portions[2]))
            {
                if (strToInt(portions[2]) == 0)
                {
                    // SUB AX, 0
                    // ADD AX, 0
                    lines[i] = ";----Optimized Code----\n\t\t;" + lines[i];
                }
            }
        }

        if (portions[0] == "IMUL" || portions[0] == "IDIV")
        {
            if (isNumber(portions[2]))
            {
                if (strToInt(portions[2]) == 1)
                {
                    // IMUL AX, 1
                    // IDIV AX, 1
                    lines[i] = ";----Optimized Code----\n\t\t;" + lines[i];
                }
            }
        }
        if ((portions[0] == "ADD" && nextPortions[0] == "ADD") || (portions[0] == "SUB" && nextPortions[0] == "SUB"))
        {
            if (isNumber(portions[2]) && isNumber(nextPortions[2]))
            {
                if (portions[1] == nextPortions[1])
                {
                    // ADD AX, 1
                    // ADD AX, 2
                    // ADD AX, 3
                    lines[i] = ";----Optimized Code----\n\t\t;" + lines[i];
                    int x = strToInt(portions[2]) + strToInt(nextPortions[2]);
                    lines[i + 1] = portions[0] + " " + portions[1] + ", " + to_string(x);
                }
            }
        }

        if (isJump(portions[0]) && portions[1] == getLabel(nextPortions[0])) // L1: -> L1
        {
            lines[i] = ";----Optimized Code----\n\t\t;" + lines[i];
        }
        if (portions[0] == "CMP" && !isJump((nextPortions[0])))
        {
            lines[i] = ";----Optimized Code----\n\t\t;" + lines[i];
        }
    }

    codeout.open("1905072_optimized_code.asm");
    for (int i = 0; i < lines.size(); i++)
    {
        if ((split(lines[i]).size() == 0))
        {
            continue;
        }
        codeout << "\t\t" << lines[i] << endl;
    }
    codeout.close();
}