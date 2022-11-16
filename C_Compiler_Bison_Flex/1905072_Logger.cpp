#include "1905072_Logger.h"
#include "1905072_Helper.h"
#include "1905072_Tokenizer.h"
#include "1905072_Expression.h"
#include <iostream>
#include <fstream>
extern ofstream logout;
extern int line_count;
void printLog(string token, string lexeme, int line)
{
    logout << "Line no " << line << ": Token <" << token << "> Lexeme " << lexeme << " found\n"
           << endl;
}
void printLogWithToken(string token, string lexeme, string actual, int line)
{
    logout << "Line no " << line << ": Token <" << token << "> Lexeme " << lexeme << " found --> <" << token << ", " << actual << ">\n"
           << endl;
}
void printLogData(int type, int line, string lexeme)
{
    // switch (type)
    // {
    // case KEYWORD_LOG:
    //     printLog(toUpper(lexeme), lexeme, line);
    //     break;
    // case INTEGER_LOG:
    //     printLog("CONST_INT", lexeme, line);
    //     break;
    // case FLOAT_LOG:
    //     printLog("CONST_FLOAT", lexeme, line);
    //     break;
    // case CHARACTER_LOG:
    //     printLogWithToken("CONST_CHAR", lexeme, string(1, getActualChar(lexeme)), line);
    //     break;
    // case STRING_LOG:
    //     printLogWithToken("STRING", lexeme, getActualString(lexeme), line);
    //     break;
    // case OPERATOR_LOG:
    //     printLog(operatorToken[lexeme], lexeme, line);
    //     break;
    // case IDENTIFIER_LOG:
    //     printLog("ID", lexeme, line);
    //     break;
    // case COMMENT_LOG:
    //     printLog("COMMENT", lexeme, line);
    //     break;
    // default:
    //     break;
    // }
}

void printRule(string left_part, string right_part)
{
    logout << "Line " << line_count << ": " << left_part << " : " << right_part << "\n"
           << endl;
}
void printRule(Segment *parent, vector<Segment *> children)
{
    string left = parent->getType();
    string right = "";
    for (auto &i : children)
    {
        right += i->getType() + " ";
    }
    printRule(left, right);
}
void printCode(string code)
{
    logout << code << "\n"
           << endl;
}

Segment *printRuleAndCode(vector<Segment *> child, string name, bool is_exp)
{
    if (is_exp)
    {
        Expression *node = new Expression(
            formatCode(child),
            name);
        printRule(node, child);
        printCode(node->getCode());
        return node;
    }
    else
    {
        Segment *node = new Segment(
            formatCode(child),
            name);
        printRule(node, child);
        printCode(node->getCode());
        return node;
    }
}