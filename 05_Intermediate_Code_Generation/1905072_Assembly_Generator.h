#ifndef __ASSEMBLY_GENERATOR__
#define __ASSEMBLY_GENERATOR__
#include "1905072_SymbolInfo.h"
#include "1905072_Expression.h"
#include "1905072_Token.h"
#include "1905072_Comment_Generator.h"
#include <fstream>
#include <stack>
#include <map>
using namespace std;

class AssemblyGenerator
{
    int label_count;
    int offset;
    stack<int> offset_history;
    string header;
    string data_segment;
    string code_segment;
    ofstream codeout;
    Function *curr_func;
    string outfile;
    stack<string> forLoopEndLabel, forLoopStartLabel;
    stack<string> elseBlockEndLabel;
    stack<string> forLoop;
    stack<string> whileLoopStartLabel, whileLoopEndLabel;
    map<string, int> id_offset;
    string forLoopIncDecCode = "";
    string forLoopExpressionCode = "";
    // CommentGenerator *cmnt_gen;
    bool isForLoop = false;
    // stack<SymbolInfo *> st;
    void addInDataSegment(string);
    void addInCodeSegment(string);
    void writeInCodeSegment(string);
    void writeInDataSegment();
    void declareGlobalVariable(SymbolInfo *);
    void declareLocalVariable(SymbolInfo *);
    void operator=(const AssemblyGenerator &) {}    // Protect assignment
    AssemblyGenerator(const AssemblyGenerator &) {} // Protect copy constructor
public:
    AssemblyGenerator(string file);
    ~AssemblyGenerator();
    void startCode();
    void startMain();
    void declareArray(Array *);
    void declareVariable(Variable *);
    void defineFunction(Function *);
    void declareParam(Variable *);
    void callFunction(Function *);
    void callVariable(Variable *);
    void callConstant(Constant *);
    void callArray(Array *, string);
    void returnFunction(Function *);
    void setOffset(SymbolInfo *, int);
    int getOffset(SymbolInfo *);
    void endCode();
    void assignOp(Variable *, Expression *);
    void addOp(string, Expression *, Expression *);
    void mulOp(string, Expression *, Expression *);
    void relOp(string, Expression *, Expression *);
    void logicOp(string, Expression *, Expression *);
    void notOperation(Expression *);
    void unaryOperation(string op, Expression *sym);
    void decrementOperation(Variable *var);
    void incrementOperation(Variable *var);
    void incdecOperation(Variable *var, string op);
    void startProcedure(Function *);
    void endProcedure(string);
    void returnProcedure();
    string newLabel();
    void createFunctionScope(vector<Variable *>);
    void writePrintFunc();
    void returnFunction();
    void printId(Identifier *sym);
    string declareLabel(string label, bool conditionValue);
    string conditionalJump(string condition, string label);
    string jumpInstant(string label);
    void whileLoopConditionCheck(string var);
    void endWhileLoop();
    void popArrayFromStack(string reg, Variable *var);
    void handleExtraExpressionPush(string name);
    void forLoopStart();
    void forLoopConditionCheck();
    void gotoNextStepInForLoop(string var);
    void endForLoop();
    Segment *createIfBlock();
    void endIfBlock(string label);
    void createElseBlock(string label);
    void endIfElseBlock();
    void whileLoopStart();
    void writeENDPForFunc(string name);
};
#endif