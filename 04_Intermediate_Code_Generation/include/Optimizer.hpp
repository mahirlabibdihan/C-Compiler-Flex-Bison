#ifndef __OPTIMIZER__
#define __OPTIMIZER__
#include <string>
#include <vector>
#include <fstream>
using namespace std;
class Optimizer
{
    std::ifstream asmin;
    std::ofstream asmout;

public:
    void
    optimize(string in_file, string out_file);
    void peephole(vector<string> &lines);
    vector<string> split(string s);
    void print(string code);
    void _print(string code);
    void printLabel(string code);
    void comment(string code);
    bool isFunctionStart(string line);
    bool isFunctionEnd(string line);
    void removeLabel(string in_file, string out_file);
};
#endif

// Need to remove dead codes