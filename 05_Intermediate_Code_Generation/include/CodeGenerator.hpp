#ifndef __CODE_GENERATOR_H
#define __CODE_GENERATOR_H
#include <fstream>
#include <string>
class CodeGenerator
{
    bool new_line;
    std::ofstream &codeout;

public:
    int indent;
    CodeGenerator(std::ofstream &codeout);
    void print(const std::string &code);
    void println(const std::string &code);
};
#endif