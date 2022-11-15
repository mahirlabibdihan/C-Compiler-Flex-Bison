#include "1905072_Expression.h"

Segment::Segment()
{
    this->code = "";
    this->type = "";
    this->is_expression = false;
}
Segment::Segment(const string &code, const string &type, bool is_exp)
{
    this->code = code;
    this->type = type;
    this->is_expression = is_exp;
}
Segment::~Segment()
{
}
const string &Segment::getCode()
{
    return code;
}
void Segment::setCode(const string &code)
{
    this->code = code;
}
const string &Segment::getType()
{
    return type;
}
void Segment::setType(const string &type)
{
    this->type = type;
}

bool Segment::isExpression()
{
    return is_expression;
}

void Segment::setIsExpression(bool is_exp)
{
    this->is_expression = is_exp;
}

Expression::Expression(const string &code, const string &type) : Segment(code, type, true)
{
}
Expression::Expression(const string &code, const string &type, const string &data_type) : Segment(code, type, true)
{
    this->data_type = data_type;
}
Expression::~Expression()
{
}
const string &Expression::getDataType()
{
    return data_type;
}
void Expression::setDataType(const string &data_type)
{
    this->data_type = data_type;
}

const string &Expression::getExpression()
{
    return this->getCode();
}
void Expression::setExpression(const string &exp)
{
    this->setCode(exp);
}