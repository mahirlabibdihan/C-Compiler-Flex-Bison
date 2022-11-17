#ifndef __ASSEMBLY_GENERATOR__
#define __ASSEMBLY_GENERATOR__
#include "1905072_SymbolInfo.hpp"
#include "1905072_Symbol_Extended.hpp"
#include "1905072_Symbol_Extended.hpp"
#include <fstream>
#include <stack>
#include <map>
#include <string>
using namespace std;

class AssemblyGenerator
{
    int label_count, tmp_count, curr_tmp;
    // int offset;
    stack<int> offset_history;
    string header;
    string data_segment;
    string code_segment;
    string tmp_var_segment;
    string declared_var_segment;

    ofstream codeout;
    Function *curr_func;
    string outfile;

    stack<string> ifBlockEndLabel, elseBlockEndLabel;
    stack<string> forLoopEndLabel, forLoopStartLabel, forLoopDelayedCode;
    stack<string> whileLoopStartLabel, whileLoopEndLabel;

    string forLoopIncDecCode = "";
    string forLoopExpressionCode = "";
    // CommentGenerator *cmnt_gen;
    bool stopPrinting = false;
    bool isInForLoop = false;
    // stack<SymbolInfo *> st;
    void addInDataSegment(string);
    void writeInCodeSegment(string);
    void writeInDataSegment();
    void addInCodeSegment(string);

    void addInDeclaredVariable(string);
    void addInTemporaryVariable(string);

    void operator=(const AssemblyGenerator &) {}    // Protect assignment
    AssemblyGenerator(const AssemblyGenerator &) {} // Protect copy constructor

public:
    AssemblyGenerator(string file);
    ~AssemblyGenerator();
    void startCode();
    void endCode();

    void declareArray(Array *);
    void declareVariable(Variable *);
    void defineFunction(Function *);

    string callFunction(Function *, vector<Expression *>);
    string callVariable(string);
    // string callConstant(Constant *);
    string callArray(string, Expression *);

    string newLabel();
    string newTemp();

    // Change value of variable
    string assignOp(Expression *, Expression *);
    void decrementOperation(Expression *var);
    void incrementOperation(Expression *var);

    // Operations
    string addOp(Expression *, string, Expression *);
    string mulOp(Expression *, string, Expression *);
    string relOp(Expression *, string, Expression *);
    string logicOp(Expression *, string, Expression *);
    string notOperation(Expression *);
    string unaryOperation(string op, Expression *sym);

    /*** FUNCTION ***/
    void startFunction(Function *);
    void startMain();
    void endFunction(string);
    void returnFunction(Expression * = NULL);
    void createFunctionScope();

    /** PRINT NUMBER **/
    void writePrintFunc();
    void printId(Variable *sym);

    /** IF ELSE **/
    void createIfBlock(Expression *);
    void endIfBlock();
    void createElseBlock();
    void endIfElseBlock();

    /**  WHILE LOOP **/
    void whileLoopStart();
    void whileLoopConditionCheck(Expression *);
    void endWhileLoop();

    /** FOR LOOP  **/
    void forLoopStart();
    void forLoopConditionCheck(Expression *);
    void gotoNextStepInForLoop();
    void endForLoop();

    string getVariableName(Variable *var);
    string getVariableName(string var_name);
    string evaluateArrayIndex(Expression *index);

    void addComment(string);
    void moveIndex(ArrayCall *);
    string arrayToFactor(Expression *);

    void resetTmpVar();
};
#endif