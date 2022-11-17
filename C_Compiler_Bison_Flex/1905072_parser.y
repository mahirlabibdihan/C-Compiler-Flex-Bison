%{
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>
#include "1905072_SymbolInfo.hpp"
#include "1905072_SymbolTable.hpp"
#include "1905072_ScopeTable.hpp"
#include "1905072_Logger.hpp"
#include "1905072_Error_Handler.hpp"
#include "1905072_Semantic_Analyzer.hpp"
#include "1905072_Helper.hpp"
#include "1905072_Assembly_Generator.hpp"
#include "1905072_Symbol_Extended.hpp"
#include "1905072_Tokenizer.hpp"
using namespace std;

extern ofstream logout;
extern ofstream errout;
extern ofstream tokenout;
extern ofstream codeout;
Expression *last_exp;
int yylex(void);
extern int line_count;
extern int error_count;
extern SymbolTable *table;
extern AssemblyGenerator* asm_gen;
extern SemanticAnalyzer* sem_anlz;
bool in_function = false;
unsigned long sdbmHash(string str);
extern vector<string> data_segment;
void yyerror(string s){
	logout<<"Error at line "<<line_count<<": "<<s<<"\n"<<endl;
	errout<<"Error at line "<<line_count<<": "<<s<<"\n"<<endl;
    error_count++;
}

void erm_s(SymbolInfo* s) // erase memory of SymbolInfo pointer
{
    if(s!=NULL) delete s;
}

void erm_nt(NonTerminal* nt) // erase memory of SymbolInfo pointer
{
    if(nt!=NULL) delete nt;
}

void erm_t(Terminal* t) // erase memory of SymbolInfo pointer
{
    if(t!=NULL) delete t;
}
void erm_e(Expression* s) // erase memory of SymbolInfo pointer
{
    if(s!=NULL) delete s;
}

void erm_v(Variable* s) // erase memory of SymbolInfo pointer
{
    if(s!=NULL) delete s;
}

void freeMemory(vector<SymbolInfo*> symbols)
{
	for(auto &i: symbols)
	{
		erm_s(i);
	}
}

// void freeMemory(vector<NonTerminal*> symbols)
// {
// 	for(auto &i: symbols)
// 	{
// 		erm_nt(i);
// 	}
// }
// void freeMemory(vector<Expression*> symbols)
// {
// 	for(auto &i: symbols)
// 	{
// 		erm_e(i);
// 	}
// }
// void freeMemory(vector<Variable*> symbols)
// {
// 	for(auto &i: symbols)
// 	{
// 		erm_v(i);
// 	}
// }

// void freeArrayMemory(vector<Variable*> &symbols)
// {
// 	freeMemory(symbols);
// 	symbols.clear();
// }
// void freeArrayMemory(vector<Expression*> symbols)
// {
// 	freeMemory(symbols);
// 	symbols.clear();
// }
%}

%error-verbose

%union{
	Terminal *terminal;
	NonTerminal *non_terminal;
	Expression *expression;
	ArgumentList *args;
	ParameterList *params;
	DeclarationList *vars;
}

%token <terminal> IF ELSE THEN SWITCH CASE DEFAULT FOR DO WHILE INT FLOAT DOUBLE CHAR STRING VOID BREAK RETURN CONTINUE INCOP DECOP ASSIGNOP NOT PRINTLN LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON ID CONST_INT CONST_FLOAT CONST_CHAR ADDOP MULOP LOGICOP RELOP


%type <non_terminal> start program unit func_declaration func_definition compound_statement var_declaration type_specifier statements statement  create_if_block expression_statement 
 
%type <args> argument_list arguments
%type <params> parameter_list
%type <vars> declaration_list
%type <expression> expression logic_expression rel_expression simple_expression term unary_expression factor variable constant

%destructor { erm_t($$); } <terminal>
%destructor { erm_nt($$); } <non_terminal>
%destructor { erm_e($$);  } <expression>

%left COMMA
%right ASSIGNOP
%left LOGICOP
%left RELOP
%left ADDOP
%left MULOP
%left LCURL RCURL
%left LPAREN RPAREN
%left NOT INCOP DECOP

%nonassoc THEN
%nonassoc ELSE

%%

start 					: program
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createNonTerminal(child,"start");
							if(error_count==0) asm_gen->endCode();
							cout<<"Code compiled successfully"<<endl;
							freeMemory(child);
						}
						;

program 				:  program  unit 
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = createNonTerminal(child,"program");
							freeMemory(child);			 
						}
						|  unit 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createNonTerminal(child,"program");
							freeMemory(child);
						}
						;
	
unit 					: var_declaration 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createNonTerminal(child,"unit");
							freeMemory(child);
						}
						| func_declaration 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createNonTerminal(child,"unit");
							freeMemory(child);
						}
						| func_definition 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createNonTerminal(child,"unit");
							freeMemory(child);
						}
						;

// No temporary variables     
func_declaration 		: 	type_specifier ID LPAREN parameter_list RPAREN SEMICOLON 
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$6};
							$$ = createNonTerminal(child,"func_declaration");
							sem_anlz->declareFunction($1->getSymbol(),$2->getSymbol(),$4->getParams());
							// freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN parameter_list RPAREN error
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							$$ = createNonTerminal(child,"func_declaration");
							sem_anlz->declareFunction($1->getSymbol(),$2->getSymbol(),$4->getParams());	
							// freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN parameter_list error RPAREN SEMICOLON
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$6,$7};
							$$ = createNonTerminal(child,"func_declaration");
							sem_anlz->declareFunction($1->getSymbol(),$2->getSymbol(),$4->getParams());
							// freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN parameter_list error RPAREN error
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$6};
							$$ = createNonTerminal(child,"func_declaration");
							sem_anlz->declareFunction($1->getSymbol(),$2->getSymbol(),$4->getParams());
							// freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN RPAREN SEMICOLON
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							$$ = createNonTerminal(child,"func_declaration");
							sem_anlz->declareFunction($1->getSymbol(),$2->getSymbol(),{});
							// freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN RPAREN error
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							$$ = createNonTerminal(child,"func_declaration");
							sem_anlz->declareFunction($1->getSymbol(),$2->getSymbol(),{});
							// freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN error RPAREN SEMICOLON
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$5,$6};
							$$ = createNonTerminal(child,"func_declaration");
							sem_anlz->declareFunction($1->getSymbol(),$2->getSymbol(),{});
							// freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN error RPAREN SEMICOLON error
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$5,$6};
							$$ = createNonTerminal(child,"func_declaration");
							sem_anlz->declareFunction($1->getSymbol(),$2->getSymbol(),{});
							// freeArrayMemory(params);
							freeMemory(child);
						}
						;
		 

func_definition 		: type_specifier ID LPAREN parameter_list RPAREN 
						{
							//asm_gen->addComment($1->getSymbol()+" "+$2->getSymbol()+"("+$4->getSymbol()+")");
							sem_anlz->defineFunction($1->getSymbol(),$2->getSymbol(), $4->getParams());
						} 
						compound_statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$7};
							$$ = createNonTerminal(child,"func_definition");
							// in_function = false;
							// freeArrayMemory(params);
							sem_anlz->endFunction();
							asm_gen->endFunction($2->getSymbol());
							freeMemory(child);
						}
						| type_specifier ID LPAREN parameter_list error RPAREN 
						{
							sem_anlz->defineFunction($1->getSymbol(),$2->getSymbol(), $4->getParams());
						} 
						compound_statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$6,$8};
							$$ = createNonTerminal(child,"func_definition");
							// in_function = false;
							// freeArrayMemory(params);
							sem_anlz->endFunction();
							freeMemory(child);
						}
						| type_specifier ID LPAREN RPAREN 
						{
							//asm_gen->addComment($1->getSymbol()+" "+$2->getSymbol()+"()");
							sem_anlz->defineFunction($1->getSymbol(),$2->getSymbol(), vector<Variable*>());
						} 
						compound_statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$6};
							$$ = createNonTerminal(child,"func_definition");
							// in_function = false;
							// freeArrayMemory(params);
							sem_anlz->endFunction();
							asm_gen->endFunction($2->getSymbol());
							
							freeMemory(child);
						}
						| type_specifier ID LPAREN error RPAREN 
						{
							sem_anlz->defineFunction($1->getSymbol(),$2->getSymbol(), vector<Variable*>());
						}
						compound_statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$5,$7};
							$$ = createNonTerminal(child,"func_definition");
							// in_function = false;
							// freeArrayMemory(params);
							sem_anlz->endFunction();
							freeMemory(child);
						}
						;				

// No temporary variables
parameter_list  		: parameter_list COMMA type_specifier ID
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							$$ = createParameterList(child,"parameter_list");

							$$->addParams($1);
							$$->addParam($3->getSymbol(),$4->getSymbol());
							freeMemory(child);
						}
						| parameter_list error COMMA type_specifier ID
						{
							vector<SymbolInfo*> child = {$1,$3,$4,$5};
							$$ = createParameterList(child,"parameter_list");

							$$->addParams($1);
							$$->addParam($4->getSymbol(),$5->getSymbol());
							freeMemory(child);
						}
						| parameter_list COMMA type_specifier
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = createParameterList(child,"parameter_list");

							$$->addParams($1);
							$$->addParam($3->getSymbol());
							freeMemory(child);
						}
						| parameter_list error COMMA type_specifier
						{
							vector<SymbolInfo*> child = {$1,$3,$4};
							$$ = createParameterList(child,"parameter_list");

							$$->addParams($1);
							$$->addParam($4->getSymbol());
							freeMemory(child);
						}
						| type_specifier ID
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = createParameterList(child,"parameter_list");

							$$->addParam($1->getSymbol(),$2->getSymbol());
							freeMemory(child);
						}
						| type_specifier
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createParameterList(child,"parameter_list");

							$$->addParam($1->getSymbol());
							freeMemory(child);
						}
						;
 		
compound_statement 		: LCURL create_scope statements RCURL
						{
							vector<SymbolInfo*> child = {$1,$3,$4};
							$$ = createNonTerminal(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
						| LCURL create_scope statements error RCURL
						{
							vector<SymbolInfo*> child = {$1,$3,$5};
							$$ = createNonTerminal(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
						| LCURL create_scope error statements RCURL
						{
							vector<SymbolInfo*> child = {$1,$4,$5};
							$$ = createNonTerminal(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
						| LCURL create_scope RCURL
						{
							vector<SymbolInfo*> child = {$1,$3};
							$$ = createNonTerminal(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
						| LCURL create_scope error RCURL
						{
							vector<SymbolInfo*> child = {$1,$4};
							$$ = createNonTerminal(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
						;

// No temporary variables
create_scope			: 
						{ 
							table->enterScope(); 
							if(in_function)
							{	
								sem_anlz->declareFunctionParams();
								asm_gen->createFunctionScope();	
								in_function = false;
							}
						}

// No temporary variables
var_declaration 		: type_specifier declaration_list SEMICOLON 
						{ 				
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = createNonTerminal(child,"var_declaration");

							//asm_gen->addComment($$->getSymbol());
							sem_anlz->declareVariables($1->getSymbol(),$2->getSymbol(),$2->getDeclarations());
							// freeArrayMemory(vars);
							freeMemory(child);
						}
						| type_specifier declaration_list error SEMICOLON 
						{ 			
							vector<SymbolInfo*> child = {$1,$2,$4};
							$$ = createNonTerminal(child,"var_declaration");
							sem_anlz->declareVariables($1->getSymbol(),$2->getSymbol(),$2->getDeclarations());
							// freeArrayMemory(vars);
							freeMemory(child);
						}
						;

// No temporary variables		 
type_specifier			: INT 	
						{ 
							vector<SymbolInfo*> child = {$1};
							$$ = createNonTerminal(child,"type_specifier");
							freeMemory(child);
						}
						| FLOAT
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createNonTerminal(child,"type_specifier");
							freeMemory(child);
						}
						| VOID
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createNonTerminal(child,"type_specifier");
							freeMemory(child);
						}
						;

// No temporary variables 		
declaration_list 		: declaration_list COMMA ID
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = createDeclarationList(child,"declaration_list");
							
							$$->addVariables($1);
							$$->addVariable($3->getSymbol());

							freeMemory(child);
						}
						| declaration_list error COMMA ID
						{
							vector<SymbolInfo*> child = {$1,$3,$4};
							$$ = createDeclarationList(child,"declaration_list");

							$$->addVariables($1);
							$$->addVariable($4->getSymbol());
							freeMemory(child);
						}
						| declaration_list COMMA ID LTHIRD constant RTHIRD
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$6};
							$$ = createDeclarationList(child,"declaration_list");

							if($5->getDataType()=="float")
							{
								handleError(INVALID_ARRAY_SIZE, line_count, $5->getSymbol());
							}

							$$->addVariables($1);
							$$->addArray($3->getSymbol(),$5->getSymbol());

							freeMemory(child);
						}
						| declaration_list error COMMA ID LTHIRD constant RTHIRD
						{
							vector<SymbolInfo*> child = {$1,$3,$4,$5,$6,$7};
							$$ = createDeclarationList(child,"declaration_list");

							if($6->getDataType() == "float")
							{
								handleError(INVALID_ARRAY_SIZE, line_count, $6->getSymbol());
							}

							$$->addVariables($1);
							$$->addArray($4->getSymbol(),$6->getSymbol());

							freeMemory(child);
						}
						| ID 
						{ 
							vector<SymbolInfo*> child = {$1};
							$$ = createDeclarationList(child,"declaration_list");
							
							
							$$->addVariable($1->getSymbol());

							freeMemory(child);
						}
						| ID LTHIRD constant RTHIRD
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							$$ = createDeclarationList(child,"declaration_list");

							if($3->getDataType()=="float")
							{
								handleError(INVALID_ARRAY_SIZE, line_count, $3->getSymbol());
							}

							$$->addArray($1->getSymbol(),$3->getSymbol());
							freeMemory(child);
						}
						;
 		  
statements 				: statement
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createNonTerminal(child,"statements");
							asm_gen->resetTmpVar();
							freeMemory(child);
						}
						| statements statement
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = createNonTerminal(child,"statements");
							asm_gen->resetTmpVar();
							freeMemory(child);
						}
						| statements error statement
						{
							vector<SymbolInfo*> child = {$1,$3};
							$$ = createNonTerminal(child,"statements");
							freeMemory(child);
						}
						;
	   
statement 				: var_declaration
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createNonTerminal(child,"statement");
							freeMemory(child);
						}
						| func_definition {
							vector<SymbolInfo*> child = {$1};
							$$ = createNonTerminal(child,"statement");
							handleError(NESTED_FUNCTION, line_count);
							freeMemory(child);
						}
						| func_declaration {
							vector<SymbolInfo*> child = {$1};
							$$ = createNonTerminal(child,"statement");
							handleError(NESTED_FUNCTION, line_count);
							freeMemory(child);
						}
						| expression_statement
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createNonTerminal(child,"statement");
							freeMemory(child);
						}
						| compound_statement
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createNonTerminal(child,"statement");
							freeMemory(child);
						}
						| FOR LPAREN expression_statement 
						{ 
							asm_gen->forLoopStart(); 
						} 
						expression_statement expression 
						{ 
							asm_gen->gotoNextStepInForLoop(); 
						}
						RPAREN statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$5,$6,$8,$9};
							$$ = createNonTerminal(child,"statement");
							asm_gen->endForLoop();
							freeMemory(child);
						}
						| IF LPAREN expression RPAREN create_if_block
						statement %prec THEN
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$6};
							$$ = createNonTerminal(child,"statement");
							asm_gen->endIfBlock();
							freeMemory(child);
						}		
						| IF LPAREN expression RPAREN create_if_block
						statement ELSE  
						{ 
							// //asm_gen->addComment("else");
							asm_gen->createElseBlock(); 
						} 
						statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$6,$7,$9};
							$$ = createNonTerminal(child,"statement");
							asm_gen->endIfElseBlock();
							freeMemory(child);
						}
						| WHILE  
						{ 
							//asm_gen->addComment($1->getSymbol());
							asm_gen->whileLoopStart(); 
						} 
						LPAREN expression 
						{ 
							//asm_gen->addComment($4->getSymbol());
							asm_gen->whileLoopConditionCheck($4); 
						}
						RPAREN statement
						{
							vector<SymbolInfo*> child = {$1,$3,$4,$6,$7};
							$$ = createNonTerminal(child,"statement");
							asm_gen->endWhileLoop();
							freeMemory(child);
						}
						| PRINTLN LPAREN ID RPAREN SEMICOLON
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							$$ = createNonTerminal(child,"statement");	
							Identifier* id = (Identifier*)table->search($3->getSymbol());	
							if(id == NULL)
							{
								handleError(UNDECLARED_VARIABLE, line_count, $3->getSymbol());
							}
							else if(id->getIdentity()=="FUNCTION")
							{
								handleError(UNDECLARED_VARIABLE, line_count, $3->getSymbol());
							}
							else
							{
								Variable*  var = (Variable*) id;
								//asm_gen->addComment($$->getSymbol());
								asm_gen->printId(var);
							}
							freeMemory(child);
						}
						| RETURN expression SEMICOLON
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = createNonTerminal(child,"statement");
							sem_anlz->returnFunction($2);
							//asm_gen->addComment($$->getSymbol());
							asm_gen->returnFunction($2);
							freeMemory(child);
						}
						| RETURN SEMICOLON {
							// New rule
							vector<SymbolInfo*> child = {$1,$2};
							$$ = createNonTerminal(child,"statement");
							//asm_gen->addComment($$->getSymbol());
							asm_gen->returnFunction();
							freeMemory(child);
						}
						;

// No temporary variables
create_if_block			:
						{
							asm_gen->createIfBlock(last_exp);
						}
						
expression_statement 	: SEMICOLON		
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createNonTerminal(child,"expression_statement");
							freeMemory(child);
						}	
						| expression SEMICOLON 
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = createNonTerminal(child,"expression_statement");
							asm_gen->forLoopConditionCheck($1);
							freeMemory(child);
						}
						;
	  
variable 				: ID 		
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createExpression(child,"variable");
							$$->setDataType(sem_anlz->callVariable($1->getSymbol()));
							if($$->getDataType()!="NULL")
							{
								$$->setTmpVar(asm_gen->callVariable($1->getSymbol()));
							}
							freeMemory(child);
						}
						| ID LTHIRD expression RTHIRD 
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							$$ = createArrayCall(child,"variable");

							$$->setDataType(sem_anlz->callArray($1->getSymbol(),$3));
							if($$->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								$3->setTmpVar(asm_gen->evaluateArrayIndex($3));
								$$->setTmpVar(asm_gen->callArray($1->getSymbol(),$3));
								((ArrayCall*)$$)->setIndex($3);
							}
							// logout<<$$->getExpression()<<" "<<line_count<<endl;
							freeMemory(child);
						}
						;
	 
 expression 			: logic_expression	
						{
							vector<SymbolInfo*> child = {$1};
							
							$$ = createExpression(child,"expression");
							$$->setDataType($1->getDataType());
							$$->setTmpVar($1->getTmpVar());

							last_exp = new Expression($1); // For IF condition
							
							freeMemory(child);
						}
						| variable ASSIGNOP logic_expression 
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = createExpression(child,"expression");
							$$->setDataType(sem_anlz->assignOp($1,$3));
							if($$->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								$$->setTmpVar(asm_gen->assignOp($1,$3));
							}
							freeMemory(child);
						}	
						;
			
logic_expression 		: rel_expression 	
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createExpression(child,"logic_expression");
							$$->setDataType($1->getDataType());
							$$->setTmpVar($1->getTmpVar());
							freeMemory(child);
						}
						| rel_expression LOGICOP rel_expression 	
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = createExpression(child,"logic_expression");
							$$->setDataType(sem_anlz->logicOp($1,$2->getSymbol(),$3));
							if($$->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								$$->setTmpVar(asm_gen->logicOp($1,$2->getSymbol(),$3));
							}
							
							freeMemory(child);
						}
						;
			
rel_expression			: simple_expression 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createExpression(child,"rel_expression");
							$$->setDataType($1->getDataType());
							$$->setTmpVar($1->getTmpVar());
							freeMemory(child);
						}
						| simple_expression RELOP simple_expression	
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = createExpression(child,"rel_expression");
							$$->setDataType(sem_anlz->relOp($1,$2->getSymbol(),$3));
							if($$->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								$$->setTmpVar(asm_gen->relOp($1,$2->getSymbol(),$3));
							}
							
							freeMemory(child);
						}
						;
				
simple_expression 		: term 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createExpression(child,"simple_expression");
							$$->setDataType($1->getDataType());
							$$->setTmpVar($1->getTmpVar());
							freeMemory(child);
						}
						| simple_expression ADDOP term 
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = createExpression(child,"simple_expression");

							$$->setDataType(sem_anlz->addOp($1,$2->getSymbol(),$3));
							if($$->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								$$->setTmpVar(asm_gen->addOp($1,$2->getSymbol(),$3));
							}
							
							freeMemory(child);
						}
						;
					
term 					:	unary_expression
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createExpression(child,"term");
							$$->setDataType($1->getDataType());
							$$->setTmpVar($1->getTmpVar());
							freeMemory(child);
						}
						|  term MULOP unary_expression
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = createExpression(child,"term");

							$$->setDataType(sem_anlz->mulOp($1,$2->getSymbol(),$3));
							if($$->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								$$->setTmpVar(asm_gen->mulOp($1,$2->getSymbol(),$3));
							}
							
							freeMemory(child);
						}
						;

unary_expression 		: ADDOP unary_expression
						{ 
							vector<SymbolInfo*> child = {$1,$2};
							$$ = createExpression({$1,$2},"unary_expression");
							$$->setDataType($2->getDataType());
							if($$->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								$$->setTmpVar(asm_gen->unaryOperation($1->getSymbol(), $2));
							}
							freeMemory(child);
						}  
						| NOT unary_expression 
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = createExpression(child,"unary_expression");
							$$->setDataType($2->getDataType());
							if($$->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								$$->setTmpVar(asm_gen->notOperation($2));
							}
							freeMemory(child);
						}
						| factor 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createExpression(child,"unary_expression");
							$$->setDataType($1->getDataType());
							$$->setTmpVar($1->getTmpVar());
							freeMemory(child);
						}
						;
	
factor					: variable 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createExpression(child,"factor");
							$$->setDataType($1->getDataType());

							if($1->getExpType() == "ARRAY_CALL")
							{
								$$->setTmpVar(asm_gen->arrayToFactor($1));
							}
							else
							{
								$$->setTmpVar($1->getTmpVar());
							}
							freeMemory(child);
						}
						| ID LPAREN argument_list RPAREN
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							$$ = createExpression(child,"factor");
							$$->setDataType(sem_anlz->callFunction($1->getSymbol(), $3->getArgs()));

							if($$->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								$$->setTmpVar(
									asm_gen->callFunction((Function*)table->search($1->getSymbol()),$3->getArgs())
								);
							}
							

							// freeArrayMemory(args);
							freeMemory(child);
						}
						| LPAREN expression RPAREN
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = createExpression(child,"factor");
							$$->setDataType($2->getDataType());
							$$->setTmpVar($2->getTmpVar());
							freeMemory(child);
						}
						| CONST_INT 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createExpression(child,"factor");
							$$->setDataType("int");
							$$->setTmpVar($1->getSymbol());
							freeMemory(child);
						}
						| CONST_FLOAT
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createExpression(child,"factor");
							$$->setDataType("float");
							$$->setTmpVar($1->getSymbol());
							freeMemory(child);
						}
						| variable INCOP 
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = createExpression(child,"factor");
							$$->setDataType($1->getDataType());

							if($1->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								asm_gen->incrementOperation($1);
							}	
							$$->setTmpVar($1->getTmpVar());
							freeMemory(child);
						}
						| variable DECOP
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = createExpression(child,"factor");
							$$->setDataType($1->getDataType());
							if($1->getDataType()!="NULL")
							{
								//asm_gen->addComment($$->getSymbol());
								asm_gen->decrementOperation($1);
							}
							$$->setTmpVar($1->getTmpVar());
							freeMemory(child);
						}
						;
	
argument_list 			: arguments
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createArgumentList(child,"argument_list");

							$$->addArgs($1);
							freeMemory(child);
						}
						| 
						{ 
							vector<SymbolInfo*> child = {};
							$$ = createArgumentList(child,"argument_list");
							freeMemory(child);
						}
						;
	
arguments 				: arguments COMMA logic_expression
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = createArgumentList(child,"arguments");

							$$->addArgs($1);
							$$->addArg($3);
							freeMemory(child);
						}
						| logic_expression
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createArgumentList(child,"arguments");

							$$->addArg($1);
							freeMemory(child);
						}
						;

// No temporary variables
constant 				: CONST_INT 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createExpression(child,"constant");
							$$->setDataType("int");
							$$->setTmpVar($1->getSymbol());
							freeMemory(child);
						}
						| CONST_FLOAT
						{
							vector<SymbolInfo*> child = {$1};
							$$ = createExpression(child,"constant");
							$$->setDataType("float");
							$$->setTmpVar($1->getSymbol());
							freeMemory(child);
						}
%%
