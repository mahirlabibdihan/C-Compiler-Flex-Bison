#include "1905072_Comment_Generator.h"

extern int line_count;

CommentGenerator::CommentGenerator()
{
}
CommentGenerator::~CommentGenerator()
{
}
string CommentGenerator::declareVariable(Variable *var)
{
    return "\t; In line no " + to_string(line_count) + ": " + var->getName() + " declared";
}

string CommentGenerator::declareArray(Array *arr)
{
    return "\t\t; In line no " + to_string(line_count) + ": Array named " + arr->getName() + " with size " + to_string(arr->getArraySize()) + " declared";
}