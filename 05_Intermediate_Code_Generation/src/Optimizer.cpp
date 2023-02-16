#include "../include/Optimizer.hpp"
#include "../include/Util.hpp"
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

string removeIndent(string line)
{
    string code = "";
    for (char c : line)
    {
        if ((c != '\t' && c != ' ') || !code.empty())
        {
            code += c;
        }
    }
    while (code.back() == ' ' || code.back() == '\t')
    {
        code.pop_back();
    }
    return code;
}
void Optimizer::print(string code)
{
    string *lines = Util::split(code, '\n');
    int count = Util::countTokens(code, '\n');
    for (int i = 0; i < count; i++)
    {
        asmout << "\t";
        asmout << lines[i] << std::endl;
    }
}
void Optimizer::_print(string code)
{
    string *lines = Util::split(code, '\n');
    int count = Util::countTokens(code, '\n');
    for (int i = 0; i < count; i++)
    {
        asmout << lines[i] << std::endl;
    }
}
void Optimizer::printLabel(string label)
{
    asmout << label << ":" << std::endl;
}
string getLabel(string label)
{
    label.pop_back();
    return label;
}
bool isLabel(string line)
{
    return line.back() == ':';
}
bool Optimizer::isFunctionStart(string line)
{
    vector<string> tokens = split(line);
    return (tokens.size() > 1 && (tokens[1] == "PROC" || tokens[1] == "proc"));
}
bool Optimizer::isFunctionEnd(string line)
{
    vector<string> tokens = split(line);
    return (tokens.size() > 1 && (tokens[1] == "ENDP" || tokens[1] == "endp"));
}
void Optimizer::comment(string msg)
{
    string *lines = Util::split(msg, '\n');
    int count = Util::countTokens(msg, '\n');
    for (int i = 0; i < count; i++)
    {
        asmout << "\t";
        asmout << "; " << lines[i] << std::endl;
    }
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

string ArrayToString(vector<string> arr, int idx)
{
    string code = "";
    for (int i = idx; i < arr.size(); i++)
    {
        code += arr[i];
    }
    return code;
}
void Optimizer::peephole(vector<string> &lines)
{
    vector<string> portions0, portions1, portions2, portions3;
    portions0 = split(lines[0]);
    portions1 = split(lines[1]);
    portions2 = split(lines[2]);
    portions3 = split(lines[3]);

    if (portions0.empty())
    {
        return;
    }
    if (isLabel(lines[0]))
    {
        _print(lines[0]);
        return;
    }

    if (portions0[0] == "ADD" || portions0[0] == "SUB")
    {
        if (isNumber(portions0[2]) && strToInt(portions0[2]) == 0)
        {
            // SUB AX, 0 || ADD AX, 0
            lines[0] = "; " + lines[0];
        }
    }

    if (portions0[0] == "MOV" && (portions0[1] == portions0[2]))
    {
        // MOV AX, AX
        lines[0] = "; " + lines[0];
    }

    if (portions1.empty())
    {
        print(lines[0]);
        return;
    }

    if (portions0[0] == "PUSH" && portions1[0] == "POP")
    {
        if (portions0[1] == portions1[1])
        { // PUSH AX ; POP AX
            lines[0] = "; " + lines[0];
            lines[1] = "; " + lines[1];
        }
        else
        {
            lines[0] = "; " + lines[0] + "\n; " + lines[1];
            lines[1] = "MOV " + portions1[1] + ", " + ArrayToString(portions0, 1);
        }
    }

    if (portions0[0] == "POP" && portions1[0] == "PUSH")
    {
        if (portions0[1] == portions1[1])
        { // POP AX ; PUSH AX
            lines[0] = "; " + lines[0];
            lines[1] = "; " + lines[1];
        }
    }

    if (portions0[0] == "MOV" && portions1[0] == "MOV")
    {
        if ((portions0[1] == portions1[2]) && (portions0[2] == portions1[1]))
        { // MOV AX, BX ; MOV BX, AX
            lines[1] = "; " + lines[1];
        }
        else if (portions0[1] == portions1[1])
        { // MOV AX, BX ; MOV AX, CX or MOV AX, BX ; MOV AX, BX
            lines[0] = "; " + lines[0];
        }
    }

    if ((portions0[0] == "ADD" && portions1[0] == "ADD") || (portions0[0] == "SUB" && portions1[0] == "SUB"))
    {
        if (portions0[1] == portions1[1])
        {
            if (isNumber(portions0[2]) && isNumber(portions1[2]))
            {
                // ADD AX, 1
                // ADD AX, 2
                // ADD AX, 3
                lines[0] = "; " + lines[0];
                int x = strToInt(portions0[2]) + strToInt(portions1[2]);
                lines[1] = portions0[0] + " " + portions0[1] + ", " + to_string(x);
            }
        }
    }

    if (isJump(portions0[0])) // L1: -> L1
    {
        if (portions0[1] == getLabel(portions1[0]))
        {
            lines[0] = "; " + lines[0];
        }
    }

    if (portions2.empty())
    {
        print(lines[0]);
        return;
    }

    if (portions2[0] == "ADD")
    {
        if (portions0[2] == portions1[2])
        {
            lines[0] = "; " + lines[0];
            lines[2] = portions2[0] + " AX, AX";
        }
    }

    if (portions3.empty())
    {
        print(lines[0]);
        return;
    }
    if (portions3[0] == "IMUL")
    {
        if (portions0[2] == portions1[2])
        {
            lines[0] = "; " + lines[0];
            lines[3] = portions3[0] + " AX";
        }
    }
    if (portions0[0] == "PUSH" && portions1[0] == "PUSH" && portions2[0] == "POP" && portions3[0] == "POP")
    {
        lines[0] = "; " + lines[0] + "\n;" + lines[3];
        lines[2] = "; " + lines[1] + "\n;" + lines[2];

        lines[1] = "MOV " + portions3[1] + ", " + ArrayToString(portions0, 1);
        lines[3] = "MOV " + portions2[1] + ", " + ArrayToString(portions1, 1);
    }
    if (!split(lines[0]).empty())
    {
        print(lines[0]);
    }
}

void Optimizer::optimize(string in_file, string out_file)
{
    asmin.open(in_file);
    asmout.open(out_file);
    string line1, line2;

    while (std::getline(asmin, line1))
    {
        _print(line1);
        if (line1 == ".CODE")
        {
            break;
        }
    }
    while (std::getline(asmin, line1))
    {
        if (isFunctionStart(line1))
        {
            _print(line1);

            vector<string> lines;
            string line;
            for (int i = 0; i < 3;) // First three not commented line
            {
                std::getline(asmin, line);
                line = removeIndent(line);
                if (line[0] == ';')
                {
                    // print(line);
                    continue;
                }
                lines.push_back(line);
                i++;
            }
            while (std::getline(asmin, line))
            {
                line = removeIndent(line);
                if (isFunctionEnd(line))
                {
                    for (int i = 0; i < 3; i++)
                    {
                        lines.push_back("");
                        peephole(lines);
                        lines.erase(lines.begin());
                    }
                    _print(line);
                    break;
                }
                if (line[0] == ';')
                {
                    // print(line);
                    continue;
                }
                lines.push_back(line);
                peephole(lines);
                lines.erase(lines.begin());
            }
        }
        else
        {
            _print(line1);
        }
    }
    asmout << line1 << endl;
    asmin.close();
    asmout.close();
}