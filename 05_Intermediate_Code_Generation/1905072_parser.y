%{
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>
#include "1905072_SymbolInfo.h"
#include "1905072_SymbolTable.h"
#include "1905072_ScopeTable.h"
#include "1905072_Logger.h"
#include "1905072_Error_Handler.h"
#include "1905072_Semantic_Analyzer.h"
#include "1905072_Helper.h"
#include "1905072_Assembly_Generator.h"
#include "1905072_Token.h"
#include "1905072_Expression.h"
using namespace std;

extern ofstream logout;
extern ofstream errout;
extern ofstream tokenout;
extern ofstream codeout;

int yylex(void);
extern int line_count;
extern int error_count;
extern SymbolTable *table;
extern AssemblyGenerator* asm_gen;
extern SemanticAnalyzer* sem_anlz;
bool in_function = false;
vector<Variable*> params;
vector<Variable*> vars;
vector<string> args;
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

void erm_se(Segment* s) // erase memory of SymbolInfo pointer
{
    if(s!=NULL) delete s;
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

void freeMemory(vector<Segment*> symbols)
{
	for(auto &i: symbols)
	{
		erm_se(i);
	}
}

void freeMemory(vector<Variable*> symbols)
{
	for(auto &i: symbols)
	{
		erm_v(i);
	}
}

void freeArrayMemory(vector<Variable*> &symbols)
{
	freeMemory(symbols);
	symbols.clear();
}

%}

%error-verbose

%union{
	Segment* segment;
	Expression* expression;
}

%token <segment> IF ELSE LOWER_THAN_ELSE SWITCH CASE DEFAULT FOR DO WHILE INT FLOAT DOUBLE CHAR STRING VOID BREAK RETURN CONTINUE INCOP DECOP ASSIGNOP NOT PRINTLN LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON ID CONST_INT CONST_FLOAT CONST_CHAR ADDOP MULOP LOGICOP RELOP


%type <segment> start program unit func_declaration func_definition parameter_list compound_statement var_declaration type_specifier declaration_list statements statement expression_statement argument_list arguments create_if_block
 
%type <expression> expression logic_expression rel_expression simple_expression term unary_expression factor variable constant

%destructor { erm_se($$); } <segment>
%destructor { erm_e($$);  } <expression>

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

start 					: program
						{
							vector<Segment*> child = {$1};
							$$ = printRuleAndCode(child,"start");
							if(error_count==0) asm_gen->endCode();
							cout<<"Code compiled successfully"<<endl;
							freeMemory(child);
						}
						;

program 				:  program  unit 
						{
							vector<Segment*> child = {$1,$2};
							$$ = printRuleAndCode(child,"program");
							freeMemory(child);			 
						}
						|  unit 
						{
							vector<Segment*> child = {$1};
							$$ = printRuleAndCode(child,"program");
							freeMemory(child);
						}
						;
	
unit 					: var_declaration 
						{
							vector<Segment*> child = {$1};
							$$ = printRuleAndCode(child,"unit");
							freeMemory(child);
						}
						| func_declaration 
						{
							vector<Segment*> child = {$1};
							$$ = printRuleAndCode(child,"unit");
							freeMemory(child);
						}
						| func_definition 
						{
							vector<Segment*> child = {$1};
							$$ = printRuleAndCode(child,"unit");
							freeMemory(child);
						}
						;
     
func_declaration 		: 	type_specifier ID LPAREN parameter_list RPAREN SEMICOLON 
						{
							vector<Segment*> child = {$1,$2,$3,$4,$5,$6};
							$$ = printRuleAndCode(child,"func_declaration");
							sem_anlz->declareFunction($1->getCode(),$2->getCode(),params);
							freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN parameter_list RPAREN error
						{
							vector<Segment*> child = {$1,$2,$3,$4,$5};
							$$ = printRuleAndCode(child,"func_declaration");
							sem_anlz->declareFunction($1->getCode(),$2->getCode(),params);	
							freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN parameter_list error RPAREN SEMICOLON
						{
							vector<Segment*> child = {$1,$2,$3,$4,$6,$7};
							$$ = printRuleAndCode(child,"func_declaration");
							sem_anlz->declareFunction($1->getCode(),$2->getCode(),params);
							freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN parameter_list error RPAREN error
						{
							vector<Segment*> child = {$1,$2,$3,$4,$6};
							$$ = printRuleAndCode(child,"func_declaration");
							sem_anlz->declareFunction($1->getCode(),$2->getCode(),params);
							freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN RPAREN SEMICOLON
						{
							vector<Segment*> child = {$1,$2,$3,$4,$5};
							$$ = printRuleAndCode(child,"func_declaration");
							sem_anlz->declareFunction($1->getCode(),$2->getCode(),vector<Variable*>());
							freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN RPAREN error
						{
							vector<Segment*> child = {$1,$2,$3,$4};
							$$ = printRuleAndCode(child,"func_declaration");
							sem_anlz->declareFunction($1->getCode(),$2->getCode(),{});
							freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN error RPAREN SEMICOLON
						{
							vector<Segment*> child = {$1,$2,$3,$5,$6};
							$$ = printRuleAndCode(child,"func_declaration");
							sem_anlz->declareFunction($1->getCode(),$2->getCode(),{});
							freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN error RPAREN SEMICOLON error
						{
							vector<Segment*> child = {$1,$2,$3,$5,$6};
							$$ = printRuleAndCode(child,"func_declaration");
							sem_anlz->declareFunction($1->getCode(),$2->getCode(),{});
							freeArrayMemory(params);
							freeMemory(child);
						}
						;
		 
func_definition 		: type_specifier ID LPAREN parameter_list RPAREN 
						{
							sem_anlz->defineFunction($1->getCode(),$2->getCode(), params);
						} 
						compound_statement
						{
							vector<Segment*> child = {$1,$2,$3,$4,$5,$7};
							$$ = printRuleAndCode(child,"func_definition");
							// in_function = false;
							// freeArrayMemory(params);
							asm_gen->endProcedure($2->getCode());
							freeMemory(child);
						}
						| type_specifier ID LPAREN parameter_list error RPAREN 
						{
							sem_anlz->defineFunction($1->getCode(),$2->getCode(), params);
						} 
						compound_statement
						{
							vector<Segment*> child = {$1,$2,$3,$4,$6,$8};
							$$ = printRuleAndCode(child,"func_definition");
							// in_function = false;
							// freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN RPAREN 
						{
							sem_anlz->defineFunction($1->getCode(),$2->getCode(), vector<Variable*>());
						} 
						compound_statement
						{
							vector<Segment*> child = {$1,$2,$3,$4,$6};
							$$ = printRuleAndCode(child,"func_definition");
							// in_function = false;
							// freeArrayMemory(params);
							asm_gen->endProcedure($2->getCode());
							freeMemory(child);
						}
						| type_specifier ID LPAREN error RPAREN 
						{
							sem_anlz->defineFunction($1->getCode(),$2->getCode(), vector<Variable*>());
						}
						compound_statement
						{
							vector<Segment*> child = {$1,$2,$3,$5,$7};
							$$ = printRuleAndCode(child,"func_definition");
							// in_function = false;
							// freeArrayMemory(params);
							freeMemory(child);
						}
						;				

parameter_list  		: parameter_list COMMA type_specifier ID
						{
							vector<Segment*> child = {$1,$2,$3,$4};
							$$ = printRuleAndCode(child,"parameter_list");
							params.push_back(new Variable($4->getCode(),$3->getCode()));
							freeMemory(child);
						}
						| parameter_list error COMMA type_specifier ID
						{
							vector<Segment*> child = {$1,$3,$4,$5};
							$$ = printRuleAndCode(child,"parameter_list");
							params.push_back(new Variable($5->getCode(),$4->getCode()));
							freeMemory(child);
						}
						| parameter_list COMMA type_specifier
						{
							vector<Segment*> child = {$1,$2,$3};
							$$ = printRuleAndCode(child,"parameter_list");
							params.push_back(new Variable("blank",$3->getCode()));
							freeMemory(child);
						}
						| parameter_list error COMMA type_specifier
						{
							vector<Segment*> child = {$1,$3,$4};
							$$ = printRuleAndCode(child,"parameter_list");
							params.push_back(new Variable("blank",$3->getCode()));
							freeMemory(child);
						}
						| type_specifier ID
						{
							vector<Segment*> child = {$1,$2};
							$$ = printRuleAndCode(child,"parameter_list");
							params.push_back(new Variable($2->getCode(),$1->getCode()));
							freeMemory(child);
						}
						| type_specifier
						{
							vector<Segment*> child = {$1};
							$$ = printRuleAndCode(child,"parameter_list");
							params.push_back(new Variable("blank",$1->getCode()));
							freeMemory(child);
						}
						;
 		
compound_statement 		: LCURL create_scope statements RCURL
						{
							vector<Segment*> child = {$1,$3,$4};
							$$ = printRuleAndCode(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
						| LCURL create_scope statements error RCURL
						{
							vector<Segment*> child = {$1,$3,$5};
							$$ = printRuleAndCode(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
						| LCURL create_scope error statements RCURL
						{
							vector<Segment*> child = {$1,$4,$5};
							$$ = printRuleAndCode(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
						| LCURL create_scope RCURL
						{
							vector<Segment*> child = {$1,$3};
							$$ = printRuleAndCode(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
						| LCURL create_scope error RCURL
						{
							vector<Segment*> child = {$1,$4};
							$$ = printRuleAndCode(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
						;

create_scope			: 
						{ 
							table->enterScope(); 
							// cout<<line_count<<" entering new scope"<<endl;
							if(in_function)
							{
								vector<Variable*> func_params;
								for(auto i:params)
								{
									if(i->getName() == "blank") continue;
									Variable *var = new Variable(i->getName(), i->getDataType());
									if(!table->insert(var))
									{
										handleError(MULTIPLE_DECLARATION, line_count, i->getName());
									}
									func_params.push_back(var);
								}
								asm_gen->createFunctionScope(func_params);
								in_function = false;
								freeArrayMemory(params);
							}
						}

var_declaration 		: type_specifier declaration_list SEMICOLON 
						{ 				
							vector<Segment*> child = {$1,$2,$3};
							$$ = printRuleAndCode(child,"var_declaration");
							sem_anlz->declareVariables($1->getCode(),$2->getCode(),vars);
							freeArrayMemory(vars);
							freeMemory(child);
						}
						| type_specifier declaration_list error SEMICOLON 
						{ 			
							vector<Segment*> child = {$1,$2,$4};
							$$ = printRuleAndCode(child,"var_declaration");
							sem_anlz->declareVariables($1->getCode(),$2->getCode(),vars);
							freeArrayMemory(vars);
							freeMemory(child);
						}
						;
 		 
type_specifier			: INT 	
						{ 
							vector<Segment*> child = {$1};
							$$ = printRuleAndCode(child,"type_specifier");
							freeMemory(child);
						}
						| FLOAT
						{
							vector<Segment*> child = {$1};
							$$ = printRuleAndCode(child,"type_specifier");
							freeMemory(child);
						}
						| VOID
						{
							vector<Segment*> child = {$1};
							$$ = printRuleAndCode(child,"type_specifier");
							freeMemory(child);
						}
						;
 		
declaration_list 		: declaration_list COMMA ID
						{
							vector<Segment*> child = {$1,$2,$3};
							$$ = printRuleAndCode(child,"declaration_list");

							Variable* tmp = new Variable("PRIMITIVE");
							tmp->setName($3->getCode());

							vars.push_back(tmp);
							freeMemory(child);
						}
						| declaration_list error COMMA ID
						{
							vector<Segment*> child = {$1,$3,$4};
							$$ = printRuleAndCode(child,"declaration_list");

							Variable* tmp = new Variable("PRIMITIVE");
							tmp->setName($4->getCode());

							vars.push_back(tmp);
							freeMemory(child);
						}
						| declaration_list COMMA ID LTHIRD constant RTHIRD
						{
							vector<Segment*> child = {$1,$2,$3,$4,$5,$6};
							$$ = printRuleAndCode(child,"declaration_list");

							Array* tmp = new Array($3->getCode());
							if($5->getDataType()=="float")
							{
								handleError(INVALID_ARRAY_SIZE, line_count, $5->getCode());
							}
							else
							{
								tmp->setArraySize(stoi($5->getCode()));
							}
							vars.push_back(tmp);

							freeMemory(child);
						}
						| declaration_list error COMMA ID LTHIRD constant RTHIRD
						{
							vector<Segment*> child = {$1,$3,$4,$5,$6,$7};
							$$ = printRuleAndCode(child,"declaration_list");

							Array* tmp = new Array($4->getCode());
							if($6->getDataType() == "float")
							{
								handleError(INVALID_ARRAY_SIZE, line_count, $6->getCode());
							}
							else
							{
								tmp->setArraySize(stoi($6->getCode()));
							}
							vars.push_back(tmp);

							freeMemory(child);
						}
						| ID 
						{ 
							vector<Segment*> child = {$1};
							$$ = printRuleAndCode(child,"declaration_list");

							Variable* tmp = new Variable("PRIMITIVE");
							tmp->setName($1->getCode());
							vars.push_back(tmp);

							freeMemory(child);
						}
						| ID LTHIRD constant RTHIRD
						{
							vector<Segment*> child = {$1,$2,$3,$4};
							$$ = printRuleAndCode(child,"declaration_list");

							Array* tmp = new Array($1->getCode());
							if($3->getDataType()=="float")
							{
								handleError(INVALID_ARRAY_SIZE, line_count, $3->getCode());
							}
							else
							{
								tmp->setArraySize(stoi($3->getCode()));
							}
							vars.push_back(tmp);

							freeMemory(child);
						}
						;
 		  
statements 				: statement
						{
							vector<Segment*> child = {$1};
							$$ = printRuleAndCode(child,"statements");
							freeMemory(child);
						}
						| statements statement
						{
							vector<Segment*> child = {$1,$2};
							$$ = printRuleAndCode(child,"statements");
							freeMemory(child);
						}
						| statements error statement
						{
							vector<Segment*> child = {$1,$3};
							$$ = printRuleAndCode(child,"statements");
							freeMemory(child);
						}
						;
	   
statement 				: var_declaration
						{
							vector<Segment*> child = {$1};
							$$ = printRuleAndCode(child,"statement");
							freeMemory(child);
						}
						| func_definition {
							vector<Segment*> child = {$1};
							$$ = printRuleAndCode(child,"statement");
							handleError(NESTED_FUNCTION, line_count);
							freeMemory(child);
						}
						| func_declaration {
							vector<Segment*> child = {$1};
							$$ = printRuleAndCode(child,"statement");
							handleError(NESTED_FUNCTION, line_count);
							freeMemory(child);
						}
						| expression_statement
						{
							vector<Segment*> child = {$1};
							$$ = printRuleAndCode(child,"statement");
							freeMemory(child);
						}
						| compound_statement
						{
							vector<Segment*> child = {$1};
							$$ = printRuleAndCode(child,"statement");
							freeMemory(child);
						}
						| FOR LPAREN expression_statement 
						{ asm_gen->forLoopStart(); } 
						expression_statement 
						{ asm_gen->forLoopConditionCheck(); } 
						expression 
						{ asm_gen->gotoNextStepInForLoop($7->getCode()); }
						RPAREN statement
						{
							vector<Segment*> child = {$1,$2,$3,$5,$7,$9,$10};
							$$ = printRuleAndCode(child,"statement");
							asm_gen->endForLoop();
							freeMemory(child);
						}
						| IF LPAREN expression RPAREN create_if_block statement %prec LOWER_THAN_ELSE
						{
							vector<Segment*> child = {$1,$2,$3,$4,$6};
							$$ = printRuleAndCode(child,"statement");
							asm_gen->endIfBlock($5->getCode());
							freeMemory(child);
							
						}
						| IF LPAREN expression RPAREN create_if_block statement ELSE  
						{ asm_gen->createElseBlock($5->getCode()); } 
						statement
						{
							vector<Segment*> child = {$1,$2,$3,$4,$6,$7,$9};
							$$ = printRuleAndCode(child,"statement");
							asm_gen->endIfElseBlock();
							freeMemory(child);
						}
						| WHILE  { asm_gen->whileLoopStart(); } LPAREN expression 
						{ asm_gen->whileLoopConditionCheck($4->getCode()); }RPAREN statement
						{
							vector<Segment*> child = {$1,$3,$4,$6,$7};
							$$ = printRuleAndCode(child,"statement");
							asm_gen->endWhileLoop();
							freeMemory(child);
						}
						| PRINTLN LPAREN ID RPAREN SEMICOLON
						{
							vector<Segment*> child = {$1,$2,$3,$4,$5};
							$$ = printRuleAndCode(child,"statement");	
							Identifier* id = (Identifier*)table->search($3->getCode());	
							if(id == NULL)
							{
								handleError(UNDECLARED_VARIABLE, line_count, $3->getCode());
							}
							else
							{
								asm_gen->printId(id);
							}
							freeMemory(child);
						}
						| RETURN expression SEMICOLON
						{
							vector<Segment*> child = {$1,$2,$3};
							$$ = printRuleAndCode(child,"statement");
							asm_gen->returnProcedure();
							freeMemory(child);
						}
						| RETURN SEMICOLON {
							// New rule
							vector<Segment*> child = {$1,$2};
							$$ = printRuleAndCode(child,"statement");
							asm_gen->returnProcedure();
							freeMemory(child);
						}
						;
	  
create_if_block			:
						{
								$$ = asm_gen->createIfBlock();
						}
						;

expression_statement 	: SEMICOLON		
						{
							vector<Segment*> child = {$1};
							$$ = printRuleAndCode(child,"expression_statement");
							freeMemory(child);
						}	
						| expression SEMICOLON 
						{
							vector<Segment*> child = {$1,$2};
							$$ = printRuleAndCode(child,"expression_statement");
							asm_gen->handleExtraExpressionPush($1->getExpression());
							freeMemory(child);
						}
						;
	  
variable 				: ID 		
						{
							vector<Segment*> child = {$1};
							$$ = (Expression*) printRuleAndCode(child,"variable", true);
							// $$->setToken(new Variable("PRIMITIVE"));
							$$->setDataType(sem_anlz->callVariable($1->getCode()));
							// $$->getToken()->setDataType(callVariable($1->getCode()));
							freeMemory(child);
						}
						| ID LTHIRD expression RTHIRD 
						{
							vector<Segment*> child = {$1,$2,$3,$4};
							$$ = (Expression*) printRuleAndCode(child,"variable",true);
							// $$->setToken(new Variable("ARRAY"));
							$$->setDataType(sem_anlz->callArray($1->getCode(),$3));
							// $$->getToken()->setDataType(callArray($1->getCode(),$3));
							freeMemory(child);
						}
						;
	 
 expression 			: logic_expression	
						{
							vector<Segment*> child = {$1};
							$$ = (Expression*) printRuleAndCode(child,"expression",true);
							$$->setDataType($1->getDataType());
							freeMemory(child);
						}
						| variable ASSIGNOP logic_expression 
						{
							vector<Segment*> child = {$1,$2,$3};
							$$ = (Expression*) printRuleAndCode(child,"expression",true);
							// new Variable($1->getCode(),$1->getDataType());
							
							string var_name = "";
							for(char c: $1->getCode())
							{
								if(c=='[') break;
								var_name += c;
							}
							Variable* var = (Variable*)table->search(var_name);

							$$->setDataType(sem_anlz->assignOp(var,$3));
							
							freeMemory(child);
						}	
						;
			
logic_expression 		: rel_expression 	
						{
							vector<Segment*> child = {$1};
							$$ = (Expression*) printRuleAndCode(child,"logic_expression",true);
							$$->setDataType($1->getDataType());
							freeMemory(child);
						}
						| rel_expression LOGICOP rel_expression 	
						{
							vector<Segment*> child = {$1,$2,$3};
							$$ = (Expression*) printRuleAndCode(child,"logic_expression",true);
							$$->setDataType(sem_anlz->logicOp($1,$2->getCode(),$3));
							freeMemory(child);
						}
						;
			
rel_expression			: simple_expression 
						{
							vector<Segment*> child = {$1};
							$$ = (Expression*) printRuleAndCode(child,"rel_expression",true);
							$$->setDataType($1->getDataType());
							freeMemory(child);
						}
						| simple_expression RELOP simple_expression	
						{
							vector<Segment*> child = {$1,$2,$3};
							$$ = (Expression*) printRuleAndCode(child,"rel_expression",true);
							$$->setDataType(sem_anlz->relOp($1,$2->getCode(),$3));
							freeMemory(child);
						}
						;
				
simple_expression 		: term 
						{
							vector<Segment*> child = {$1};
							$$ = (Expression*) printRuleAndCode(child,"simple_expression",true);
							$$->setDataType($1->getDataType());
							freeMemory(child);
						}
						| simple_expression ADDOP term 
						{
							vector<Segment*> child = {$1,$2,$3};
							$$ = (Expression*) printRuleAndCode(child,"simple_expression",true);
							$$->setDataType(sem_anlz->addOp($1,$2->getCode(),$3));
							freeMemory(child);
						}
						;
					
term 					:	unary_expression
						{
							vector<Segment*> child = {$1};
							$$ = (Expression*) printRuleAndCode(child,"term",true);
							$$->setDataType($1->getDataType());
							freeMemory(child);
						}
						|  term MULOP unary_expression
						{
							vector<Segment*> child = {$1,$2,$3};
							$$ = (Expression*) printRuleAndCode(child,"term",true);
							$$->setDataType(sem_anlz->mulOp($1,$2->getCode(),$3));
							freeMemory(child);
						}
						;

unary_expression 		: ADDOP unary_expression
						{ 
							vector<Segment*> child = {$1,$2};
							$$ = (Expression*) printRuleAndCode({$1,$2},"unary_expression",true);
							$$->setDataType($2->getDataType());
							asm_gen->unaryOperation($1->getCode(), $2);
							freeMemory(child);
						}  
						| NOT unary_expression 
						{
							vector<Segment*> child = {$1,$2};
							$$ = (Expression*) printRuleAndCode(child,"unary_expression",true);
							$$->setDataType($2->getDataType());
							asm_gen->notOperation($2);
							freeMemory(child);
						}
						| factor 
						{
							vector<Segment*> child = {$1};
							$$ = (Expression*) printRuleAndCode(child,"unary_expression",true);
							$$->setDataType($1->getDataType());
							freeMemory(child);
						}
						;
	
factor					: variable 
						{
							asm_gen->popArrayFromStack("BX", new Variable($1->getCode(),$1->getDataType(), ($1->getCode().back()==']'?"ARRAY":"PRIMITIVE")));

							vector<Segment*> child = {$1};
							$$ = (Expression*) printRuleAndCode(child,"factor",true);
							$$->setDataType($1->getDataType());
							freeMemory(child);
						}
						| ID LPAREN argument_list RPAREN
						{
							vector<Segment*> child = {$1,$2,$3,$4};
							$$ = (Expression*) printRuleAndCode(child,"factor",true);
							$$->setDataType(sem_anlz->callFunction($1->getCode(), args));
							args.clear();
							freeMemory(child);
						}
						| LPAREN expression RPAREN
						{
							vector<Segment*> child = {$1,$2,$3};
							$$ = (Expression*) printRuleAndCode(child,"factor",true);
							$$->setDataType($2->getDataType());
							freeMemory(child);
						}
						| CONST_INT 
						{
							vector<Segment*> child = {$1};
							$$ = (Expression*) printRuleAndCode(child,"factor", true);
							$$->setDataType("int");
							asm_gen->callConstant(new Constant($1->getCode(),"int"));
							// $$->setIdType("CONSTANT");
							freeMemory(child);
						}
						| CONST_FLOAT
						{
							vector<Segment*> child = {$1};
							$$ =(Expression*)  printRuleAndCode(child,"factor", true);
							$$->setDataType("float");
							asm_gen->callConstant(new Constant($1->getCode(),"float"));
							// $$->setIdType("CONSTANT");
							freeMemory(child);
						}
						| variable INCOP 
						{
							vector<Segment*> child = {$1,$2};
							$$ = (Expression*) printRuleAndCode(child,"factor",true);
							$$->setDataType($1->getDataType());

							if($1->getDataType()!="NULL")
							asm_gen->incrementOperation((Variable*)table->search($1->getCode()));
							freeMemory(child);
						}
						| variable DECOP
						{
							vector<Segment*> child = {$1,$2};
							$$ = (Expression*) printRuleAndCode(child,"factor",true);
							$$->setDataType($1->getDataType());
							if($1->getDataType()!="NULL")
							asm_gen->decrementOperation((Variable*)table->search($1->getCode()));
							freeMemory(child);
						}
						;
	
argument_list 			: arguments
						{
							vector<Segment*> child = {$1};
							$$ = printRuleAndCode(child,"argument_list");
							freeMemory(child);
						}
						| 
						{ 
							vector<Segment*> child = {};
							$$ = printRuleAndCode(child,"argument_list");
							freeMemory(child);
						}
						;
	
arguments 				: arguments COMMA logic_expression
						{
							vector<Segment*> child = {$1,$2,$3};
							$$ = printRuleAndCode(child,"arguments");
							args.push_back($3->getDataType());
							freeMemory(child);
						}
						| logic_expression
						{
							vector<Segment*> child = {$1};
							$$ = printRuleAndCode(child,"arguments");

							args.push_back($1->getDataType());

							freeMemory(child);
						}
						;

constant 				: CONST_INT 
						{
							vector<Segment*> child = {$1};
							$$ = (Expression*) printRuleAndCode(child,"constant",true);
							$$->setDataType("int");
							// $$->setIdType("CONSTANT");
							freeMemory(child);
						}
						| CONST_FLOAT
						{
							vector<Segment*> child = {$1};
							$$ = (Expression*) printRuleAndCode(child,"constant",true);
							$$->setDataType("float");
							// $$->setIdType("CONSTANT");
							freeMemory(child);
						}
%%
