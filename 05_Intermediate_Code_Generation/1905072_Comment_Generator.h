#ifndef __COMMENT_GENERATOR__
#define __COMMENT_GENERATOR__
#include <string>
#include "1905072_Token.h"
using namespace std;

class CommentGenerator
{
public:
    CommentGenerator();
    ~CommentGenerator();
    string declareVariable(Variable *var);
    string declareArray(Array *arr);
};

#endif