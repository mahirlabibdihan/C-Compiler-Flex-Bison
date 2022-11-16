#ifndef __EXPRESSION__
#define __EXPRESSION__
#include <string>
using namespace std;

class Block
{
};

class Segment
{
    string code;
    bool is_expression; // Expression, Statement, BLock
    string type;

public:
    Segment();
    Segment(const string &, const string &, bool = false);
    ~Segment();
    const string &getCode();
    void setCode(const string &);
    const string &getType();
    void setType(const string &);
    bool isExpression();
    void setIsExpression(bool);
};

class Expression : public Segment
{
    string data_type; // int, float,
    string tmp_var;
    string idx_var;

public:
    Expression();
    Expression(Expression *);
    Expression(const string &, const string &type);
    Expression(const string &, const string &type, const string &data_type);
    ~Expression();
    const string &getDataType();
    void setDataType(const string &);
    const string &getExpression();
    void setExpression(const string &);
    string getTmpVar();
    void setTmpVar(string);
    // int getIndex();
    // void setIndex(int);
    string getIndexVar();
    void setIndexVar(string);
};

#endif