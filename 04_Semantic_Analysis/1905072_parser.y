%{
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "1905072_SymbolInfo.h"
#include "1905072_SymbolTable.h"
#include "1905072_ScopeTable.h"
#include "1905072_Node.h"
#include "1905072_Logger.h"
#include "1905072_Error_Handler.h"
#include "1905072_Semantic_Analyzer.h"
#include "1905072_Parse_Tree.h"
#include "1905072_Helper.h"
using namespace std;

extern ofstream logout;
extern ofstream errout;
extern ofstream tokenout;

int yylex(void);
extern int line_count;
extern int error_count;
extern SymbolTable *table;
bool in_function = false;
vector<SymbolInfo*> params;
vector<SymbolInfo*> ids;
vector<SymbolInfo*> args;
unsigned long sdbmHash(string str);

void yyerror(string s){
	logout<<"Error at line "<<line_count<<": "<<s<<"\n"<<endl;
	errout<<"Error at line "<<line_count<<": "<<s<<"\n"<<endl;
    error_count++;
}

void erm_s(SymbolInfo* s) // erase memory of SymbolInfo pointer
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

void freeArrayMemory(vector<SymbolInfo*> &symbols)
{
	freeMemory(symbols);
	symbols.clear();
}

%}

%error-verbose

%union{
    SymbolInfo* symbol;
}

%token <symbol> IF ELSE LOWER_THAN_ELSE SWITCH CASE DEFAULT FOR DO WHILE INT FLOAT DOUBLE CHAR STRING VOID BREAK RETURN CONTINUE INCOP DECOP ASSIGNOP NOT PRINTLN LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON  ID CONST_INT CONST_FLOAT CONST_CHAR ADDOP MULOP LOGICOP RELOP

%type <symbol> start program unit func_declaration func_definition parameter_list compound_statement var_declaration type_specifier declaration_list statements statement expression_statement variable expression logic_expression rel_expression simple_expression term unary_expression factor argument_list arguments constant


%destructor { erm_s($$);  } <symbol_info>

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

start 					: program
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"start");
							cout<<"Code compiled successfully"<<endl;
							freeMemory(child);
						}
						;

program 				:  program  unit 
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = printRuleAndCode(child,"program");
							freeMemory(child);			 
						}
						|  unit 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"program");
							freeMemory(child);
						}
						;
	
unit 					: var_declaration 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"unit");
							freeMemory(child);
						}
						| func_declaration 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"unit");
							freeMemory(child);
						}
						| func_definition 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"unit");
							freeMemory(child);
						}
						;
     
func_declaration 		: 	type_specifier ID LPAREN parameter_list RPAREN SEMICOLON 
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$6};
							$$ = printRuleAndCode(child,"func_declaration");
							declareFunction($1->getName(),$2,params);
							freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN parameter_list RPAREN error
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							$$ = printRuleAndCode(child,"func_declaration");
							declareFunction($1->getName(),$2,params);	
							freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN parameter_list error RPAREN SEMICOLON
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$6,$7};
							$$ = printRuleAndCode(child,"func_declaration");
							declareFunction($1->getName(),$2,params);
							freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN parameter_list error RPAREN error
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$6};
							$$ = printRuleAndCode(child,"func_declaration");
							declareFunction($1->getName(),$2,params);
							freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN RPAREN SEMICOLON
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							$$ = printRuleAndCode(child,"func_declaration");
							declareFunction($1->getName(),$2,{});
							freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN RPAREN error
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							$$ = printRuleAndCode(child,"func_declaration");
							declareFunction($1->getName(),$2,{});
							freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN error RPAREN SEMICOLON
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$5,$6};
							$$ = printRuleAndCode(child,"func_declaration");
							declareFunction($1->getName(),$2,{});
							freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN error RPAREN SEMICOLON error
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$5,$6};
							$$ = printRuleAndCode(child,"func_declaration");
							declareFunction($1->getName(),$2,{});
							freeArrayMemory(params);
							freeMemory(child);
						}
						;
		 
func_definition 		: type_specifier ID LPAREN parameter_list RPAREN 
						{
							defineFunction($2, params, $1->getName());
						} 
						compound_statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$7};
							$$ = printRuleAndCode(child,"func_declaration");
							in_function = false;
							freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN parameter_list error RPAREN 
						{
							defineFunction($2, params, $1->getName());
						} 
						compound_statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$6,$8};
							$$ = printRuleAndCode(child,"func_declaration");
							in_function = false;
							freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN RPAREN 
						{
							defineFunction($2, {}, $1->getName());
						} 
						compound_statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$6};
							$$ = printRuleAndCode(child,"func_declaration");
							in_function = false;
							freeArrayMemory(params);
							freeMemory(child);
						}
						| type_specifier ID LPAREN error RPAREN 
						{
							defineFunction($2, {}, $1->getName());
						}
						compound_statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$5,$7};
							$$ = printRuleAndCode(child,"func_declaration");
							in_function = false;
							freeArrayMemory(params);
							freeMemory(child);
						}
						;				

parameter_list  		: parameter_list COMMA type_specifier ID
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							$$ = printRuleAndCode(child,"parameter_list");
							params.push_back(new SymbolInfo($4->getName(),$4->getType(), "VARIABLE",$3->getName()));
							freeMemory(child);
						}
						| parameter_list error COMMA type_specifier ID
						{
							vector<SymbolInfo*> child = {$1,$3,$4,$5};
							$$ = printRuleAndCode(child,"parameter_list");
							params.push_back(new SymbolInfo($5->getName(), $5->getType(), "VARIABLE",$4->getName()));
							freeMemory(child);
						}
						| parameter_list COMMA type_specifier
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = printRuleAndCode(child,"parameter_list");
							params.push_back(new SymbolInfo("blank", "ID", "VARIABLE",$3->getName()));
							freeMemory(child);
						}
						| parameter_list error COMMA type_specifier
						{
							vector<SymbolInfo*> child = {$1,$3,$4};
							$$ = printRuleAndCode(child,"parameter_list");
							params.push_back(new SymbolInfo("blank", "ID", "VARIABLE",$3->getName()));
							freeMemory(child);
						}
						| type_specifier ID
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = printRuleAndCode(child,"parameter_list");
							params.push_back(new SymbolInfo($2->getName(),$2->getType(),"VARIABLE",$1->getName()));
							freeMemory(child);
						}
						| type_specifier
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"parameter_list");
							params.push_back(new SymbolInfo("blank", "ID", "VARIABLE", $1->getName()));
							freeMemory(child);
						}
						;
 		
compound_statement 		: LCURL create_scope statements RCURL
						{
							vector<SymbolInfo*> child = {$1,$3,$4};
							$$ = printRuleAndCode(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
						| LCURL create_scope statements error RCURL
						{
							vector<SymbolInfo*> child = {$1,$3,$5};
							$$ = printRuleAndCode(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
						| LCURL create_scope error statements RCURL
						{
							vector<SymbolInfo*> child = {$1,$4,$5};
							$$ = printRuleAndCode(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
						| LCURL create_scope RCURL
						{
							vector<SymbolInfo*> child = {$1,$3};
							$$ = printRuleAndCode(child,"compound_statement");
							table->printAllScope();
							table->exitScope();
							freeMemory(child);
						}
						| LCURL create_scope error RCURL
						{
							vector<SymbolInfo*> child = {$1,$4};
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
								for(auto i:params)
								{
									if(i->getName() == "blank") continue;
									if(!table->insert(*i))
									{
										handleError(MULTIPLE_DECLARATION, line_count, i->getName());
									}
								}
							}
						}

var_declaration 		: type_specifier declaration_list SEMICOLON 
						{ 				
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = printRuleAndCode(child,"var_declaration");
							declareVariable($1->getName(),$2->getName(),ids);
							freeArrayMemory(ids);
							freeMemory(child);
						}
						| type_specifier declaration_list error SEMICOLON 
						{ 			
							vector<SymbolInfo*> child = {$1,$2,$4};
							$$ = printRuleAndCode(child,"var_declaration");
							declareVariable($1->getName(),$2->getName(),ids);
							freeArrayMemory(ids);
							freeMemory(child);
						}
						;
 		 
type_specifier			: INT 	
						{ 
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"type_specifier");
							freeMemory(child);
						}
						| FLOAT
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"type_specifier");
							freeMemory(child);
						}
						| VOID
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"type_specifier");
							freeMemory(child);
						}
						;
 		
declaration_list 		: declaration_list COMMA ID
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = printRuleAndCode(child,"declaration_list");
							ids.push_back(new SymbolInfo($3->getName(),$3->getType(),"VARIABLE"));
							freeMemory(child);
						}
						| declaration_list error COMMA ID
						{
							vector<SymbolInfo*> child = {$1,$3,$4};
							$$ = printRuleAndCode(child,"declaration_list");
							ids.push_back(new SymbolInfo($4->getName(),$4->getType(),"VARIABLE"));
							freeMemory(child);
						}
						| declaration_list COMMA ID LTHIRD constant RTHIRD
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$6};
							$$ = printRuleAndCode(child,"declaration_list");
							ids.push_back(new SymbolInfo($3->getName(),$3->getType(),"ARRAY"));
							if($5->getDataType()=="float")
							{
								handleError(INVALID_ARRAY_SIZE, line_count, $5->getName());
							}
							freeMemory(child);
						}
						| declaration_list error COMMA ID LTHIRD constant RTHIRD
						{
							vector<SymbolInfo*> child = {$1,$3,$4,$5,$6,$7};
							$$ = printRuleAndCode(child,"declaration_list");						
							ids.push_back(new SymbolInfo($4->getName(),$4->getType(),"ARRAY"));
							if($6->getDataType()=="float")
							{
								handleError(INVALID_ARRAY_SIZE, line_count, $6->getName());
							}
							freeMemory(child);
						}
						| ID 
						{ 
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"declaration_list");
							ids.push_back(new SymbolInfo($1->getName(),$1->getType(),"VARIABLE"));
							freeMemory(child);
						}
						| ID LTHIRD constant RTHIRD
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							$$ = printRuleAndCode(child,"declaration_list");
							ids.push_back(new SymbolInfo($1->getName(),$1->getType(),"ARRAY"));
							if($3->getDataType()=="float")
							{
								handleError(INVALID_ARRAY_SIZE, line_count, $3->getName());
							}
							freeMemory(child);
						}
						;
 		  
statements 				: statement
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"statements");
							freeMemory(child);
						}
						| statements statement
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = printRuleAndCode(child,"statements");
							freeMemory(child);
						}
						| statements error statement
						{
							vector<SymbolInfo*> child = {$1,$3};
							$$ = printRuleAndCode(child,"statements");
							freeMemory(child);
						}
						;
	   
statement 				: var_declaration
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"statement");
							freeMemory(child);
						}
						| func_definition {
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"statement");
							handleError(NESTED_FUNCTION, line_count);
							freeMemory(child);
						}
						| func_declaration {
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"statement");
							handleError(NESTED_FUNCTION, line_count);
							freeMemory(child);
						}
						| expression_statement
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"statement");
							freeMemory(child);
						}
						| compound_statement
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"statement");
							freeMemory(child);
						}
						| FOR LPAREN expression_statement expression_statement expression RPAREN statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$6,$7};
							$$ = printRuleAndCode(child,"statement");
							freeMemory(child);
						}
						| IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							$$ = printRuleAndCode(child,"statement");
							freeMemory(child);
						}
						| IF LPAREN expression RPAREN statement ELSE statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$6,$7};
							$$ = printRuleAndCode(child,"statement");
							freeMemory(child);
						}
						| WHILE LPAREN expression RPAREN statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							$$ = printRuleAndCode(child,"statement");
							freeMemory(child);
						}
						| PRINTLN LPAREN ID RPAREN SEMICOLON
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							$$ = printRuleAndCode(child,"statement");		
							if(!table->search($3->getName()))
							{
								handleError(UNDECLARED_VARIABLE, line_count, $3->getName());
								$$->setDataType("NULL");
							}
							freeMemory(child);
						}
						| RETURN expression SEMICOLON
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = printRuleAndCode(child,"statement");
							freeMemory(child);
						}
						| RETURN SEMICOLON {
							// New rule
							vector<SymbolInfo*> child = {$1,$2};
							$$ = printRuleAndCode(child,"statement");
							freeMemory(child);
						}
						;
	  
expression_statement 	: SEMICOLON		
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"expression_statement");
							freeMemory(child);
						}	
						| expression SEMICOLON 
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = printRuleAndCode(child,"expression_statement");
							freeMemory(child);
						}
						;
	  
variable 				: ID 		
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"variable");
							$$->setDataType(callVariable($1->getName()));
							freeMemory(child);
						}
						| ID LTHIRD expression RTHIRD 
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							$$ = printRuleAndCode(child,"variable");
							$$->setDataType(callArray($1->getName(),$3));
						}
						;
	 
 expression 			: logic_expression	
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"expression");
							$$->setDataType($1->getDataType());
							freeMemory(child);
						}
						| variable ASSIGNOP logic_expression 
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = printRuleAndCode(child,"expression");
							$$->setDataType(assignmentOperation($1->getDataType(),$3->getDataType()));
							freeMemory(child);
						}	
						;
			
logic_expression 		: rel_expression 	
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"logic_expression");
							$$->setDataType($1->getDataType());
							freeMemory(child);
						}
						| rel_expression LOGICOP rel_expression 	
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = printRuleAndCode(child,"logic_expression");
							$$->setDataType(logicalOperation($1->getDataType(),$2->getName(),$3->getDataType()));
							freeMemory(child);
						}
						;
			
rel_expression			: simple_expression 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"rel_expression");
							$$->setDataType($1->getDataType());
							freeMemory(child);
						}
						| simple_expression RELOP simple_expression	
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = printRuleAndCode(child,"rel_expression");
							$$->setDataType(relationalOperation($1->getDataType(),$2->getName(),$3->getDataType()));
							freeMemory(child);
						}
						;
				
simple_expression 		: term 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"simple_expression");
							$$->setDataType($1->getDataType());
							freeMemory(child);
						}
						| simple_expression ADDOP term 
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = printRuleAndCode(child,"simple_expression");
							$$->setDataType(additionalOperation($1->getDataType(),$2->getName(),$3->getDataType()));
							freeMemory(child);
						}
						;
					
term 					:	unary_expression
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"term");
							$$->setDataType($1->getDataType());
							freeMemory(child);
						}
						|  term MULOP unary_expression
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = printRuleAndCode(child,"term");
							$$->setDataType(multiplicationalOperation($1->getDataType(),$2->getName(),$3->getDataType()));
							freeMemory(child);
						}
						;

unary_expression 		: ADDOP unary_expression
						{ 
							vector<SymbolInfo*> child = {$1,$2};
							$$ = printRuleAndCode({$1,$2},"unary_expression");
							$$->setDataType($2->getDataType());
							freeMemory(child);
						}  
						| NOT unary_expression 
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = printRuleAndCode(child,"unary_expression");
							$$->setDataType($2->getDataType());
							freeMemory(child);
						}
						| factor 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"unary_expression");
							$$->setDataType($1->getDataType());
							freeMemory(child);
						}
						;
	
factor					: variable 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"factor");
							$$->setDataType($1->getDataType());
							freeMemory(child);
						}
						| ID LPAREN argument_list RPAREN
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							$$ = printRuleAndCode(child,"factor");
							$$->setDataType(callFunction($1->getName(), args));
							freeArrayMemory(args);
							freeMemory(child);
						}
						| LPAREN expression RPAREN
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = printRuleAndCode(child,"factor");
							$$->setDataType($2->getDataType());
							freeMemory(child);
						}
						| CONST_INT 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"factor");
							$$->setDataType("int");
							$$->setIdType("CONSTANT");
							freeMemory(child);
						}
						| CONST_FLOAT
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"factor");
							$$->setDataType("float");
							$$->setIdType("CONSTANT");
							freeMemory(child);
						}
						| variable INCOP 
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = printRuleAndCode(child,"factor");
							freeMemory(child);
						}
						| variable DECOP
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = printRuleAndCode(child,"factor");
							freeMemory(child);
						}
						;
	
argument_list 			: arguments
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"argument_list");
							freeMemory(child);
						}
						| 
						{ 
							vector<SymbolInfo*> child = {};
							$$ = printRuleAndCode(child,"argument_list");
							freeMemory(child);
						}
						;
	
arguments 				: arguments COMMA logic_expression
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = printRuleAndCode(child,"arguments");
							args.push_back(new SymbolInfo($1->getDataType()));
							freeMemory(child);
						}
						| logic_expression
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"arguments");
							args.push_back(new SymbolInfo($1->getDataType()));
							freeMemory(child);
						}
						;

constant 				: CONST_INT 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"constant");
							$$->setDataType("int");
							$$->setIdType("CONSTANT");
							freeMemory(child);
						}
						| CONST_FLOAT
						{
							vector<SymbolInfo*> child = {$1};
							$$ = printRuleAndCode(child,"constant");
							$$->setDataType("float");
							$$->setIdType("CONSTANT");
							freeMemory(child);
						}
%%
