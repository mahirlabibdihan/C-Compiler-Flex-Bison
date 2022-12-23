%{
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <string>
#include "../include/SymbolTable.hpp"
#include "../include/Logger.hpp"
#include "../include/ErrorHandler.hpp"
#include "../include/SemanticAnalyzer.hpp"
#include "../include/Util.hpp"
#include "../include/ExtendedSymbol.hpp"
#include "../include/Tokenizer.hpp"
#include "../include/ParseTreeGenerator.hpp"
using namespace std;

int yylex(void);
extern FILE *yyin;
extern SemanticAnalyzer* sem_anlzr;

void yyerror(string error){
	// err_hndlr->handlSyntaxError(error, sem_anlzr->getLineCount());
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

%}

%define parse.error verbose

%union{
	Terminal *terminal;
	NonTerminal *non_terminal;
	Expression *expression;
	ArgumentList *args;
	ParameterList *params;
	DeclarationList *vars;
}

%token <terminal> IF ELSE THEN SWITCH CASE DEFAULT FOR DO WHILE INT FLOAT DOUBLE CHAR STRING VOID BREAK RETURN CONTINUE INCOP DECOP ASSIGNOP NOT PRINTLN LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON ID CONST_INT CONST_FLOAT CONST_CHAR ADDOP MULOP LOGICOP RELOP BITOP


%type <non_terminal> start program unit func_declaration func_definition compound_statement var_declaration type_specifier statements statement expression_statement 
 
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
							$$ = ParseTreeGenerator::createNonTerminal(child,"start");
							cout<<"Code compiled successfully"<<endl;
							freeMemory(child);
						}
						;

program 				:  program  unit 
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = ParseTreeGenerator::createNonTerminal(child,"program");
							freeMemory(child);			 
						}
						|  unit 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"program");
							freeMemory(child);
						}
						;
	
unit 					: var_declaration 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"unit");
							freeMemory(child);
						}
						| func_declaration 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"unit");
							freeMemory(child);
						}
						| func_definition 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"unit");
							freeMemory(child);
						}
						;

// No temporary variables     
func_declaration 		: 	type_specifier ID LPAREN parameter_list RPAREN SEMICOLON 
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$6};
							$$ = ParseTreeGenerator::createNonTerminal(child,"func_declaration");
							sem_anlzr->declareFunction($1->getSymbol(),$2->getSymbol(),$4->getParams());
							freeMemory(child);
						}
						| type_specifier ID LPAREN parameter_list RPAREN error
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							$$ = ParseTreeGenerator::createNonTerminal(child,"func_declaration");
							sem_anlzr->declareFunction($1->getSymbol(),$2->getSymbol(),$4->getParams());	
							freeMemory(child);
						}
						| type_specifier ID LPAREN parameter_list error RPAREN SEMICOLON
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$6,$7};
							$$ = ParseTreeGenerator::createNonTerminal(child,"func_declaration");
							sem_anlzr->declareFunction($1->getSymbol(),$2->getSymbol(),$4->getParams());
							freeMemory(child);
						}
						| type_specifier ID LPAREN parameter_list error RPAREN error
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$6};
							$$ = ParseTreeGenerator::createNonTerminal(child,"func_declaration");
							sem_anlzr->declareFunction($1->getSymbol(),$2->getSymbol(),$4->getParams());
							freeMemory(child);
						}
						| type_specifier ID LPAREN RPAREN SEMICOLON
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							$$ = ParseTreeGenerator::createNonTerminal(child,"func_declaration");
							sem_anlzr->declareFunction($1->getSymbol(),$2->getSymbol(),{});
							freeMemory(child);
						}
						| type_specifier ID LPAREN RPAREN error
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							$$ = ParseTreeGenerator::createNonTerminal(child,"func_declaration");
							sem_anlzr->declareFunction($1->getSymbol(),$2->getSymbol(),{});
							freeMemory(child);
						}
						| type_specifier ID LPAREN error RPAREN SEMICOLON
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$5,$6};
							$$ = ParseTreeGenerator::createNonTerminal(child,"func_declaration");
							sem_anlzr->declareFunction($1->getSymbol(),$2->getSymbol(),{});
							freeMemory(child);
						}
						| type_specifier ID LPAREN error RPAREN error
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$5};
							$$ = ParseTreeGenerator::createNonTerminal(child,"func_declaration");
							sem_anlzr->declareFunction($1->getSymbol(),$2->getSymbol(),{});
							freeMemory(child);
						}
						;
		 

func_definition 		: type_specifier ID LPAREN parameter_list RPAREN 
						{
							sem_anlzr->defineFunction($1->getSymbol(),$2->getSymbol(), $4->getParams());
						} 
						compound_statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$7};
							$$ = ParseTreeGenerator::createNonTerminal(child,"func_definition");
							sem_anlzr->endFunction();
							freeMemory(child);
						}
						| type_specifier ID LPAREN parameter_list error RPAREN 
						{
							sem_anlzr->defineFunction($1->getSymbol(),$2->getSymbol(), $4->getParams());
						} 
						compound_statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$6,$8};
							$$ = ParseTreeGenerator::createNonTerminal(child,"func_definition");
							sem_anlzr->endFunction();
							freeMemory(child);
						}
						| type_specifier ID LPAREN RPAREN 
						{
							sem_anlzr->defineFunction($1->getSymbol(),$2->getSymbol(), {});
						} 
						compound_statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$6};
							$$ = ParseTreeGenerator::createNonTerminal(child,"func_definition");
							sem_anlzr->endFunction();
							freeMemory(child);
						}
						| type_specifier ID LPAREN error RPAREN 
						{
							sem_anlzr->defineFunction($1->getSymbol(),$2->getSymbol(), {});
						}
						compound_statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$5,$7};
							$$ = ParseTreeGenerator::createNonTerminal(child,"func_definition");
							sem_anlzr->endFunction();
							freeMemory(child);
						}
						;				

// No temporary variables
parameter_list  		: parameter_list COMMA type_specifier ID
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							$$ = ParseTreeGenerator::createParameterList(child,"parameter_list");
							$$->addParams($1);
							$$->addParam($3->getSymbol(),$4->getSymbol());
							freeMemory(child);
						}
						| parameter_list error COMMA type_specifier ID
						{
							vector<SymbolInfo*> child = {$1,$3,$4,$5};
							$$ = ParseTreeGenerator::createParameterList(child,"parameter_list");
							$$->addParams($1);
							$$->addParam($4->getSymbol(),$5->getSymbol());
							freeMemory(child);
						}
						| parameter_list COMMA type_specifier
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = ParseTreeGenerator::createParameterList(child,"parameter_list");
							$$->addParams($1);
							$$->addParam($3->getSymbol());
							freeMemory(child);
						}
						| parameter_list error COMMA type_specifier
						{
							vector<SymbolInfo*> child = {$1,$3,$4};
							$$ = ParseTreeGenerator::createParameterList(child,"parameter_list");
							$$->addParams($1);
							$$->addParam($4->getSymbol());
							freeMemory(child);
						}
						| type_specifier ID
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = ParseTreeGenerator::createParameterList(child,"parameter_list");
							$$->addParam($1->getSymbol(),$2->getSymbol());
							freeMemory(child);
						}
						| type_specifier
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createParameterList(child,"parameter_list");
							$$->addParam($1->getSymbol());
							freeMemory(child);
						}
						;
 		
compound_statement 		: LCURL create_scope statements RCURL
						{
							vector<SymbolInfo*> child = {$1,$3,$4};
							$$ = ParseTreeGenerator::createNonTerminal(child,"compound_statement");
							sem_anlzr->endScope();
							freeMemory(child);
						}
						| LCURL create_scope statements error RCURL
						{
							vector<SymbolInfo*> child = {$1,$3,$5};
							$$ = ParseTreeGenerator::createNonTerminal(child,"compound_statement");
							sem_anlzr->endScope();
							freeMemory(child);
						}
						| LCURL create_scope error statements RCURL
						{
							vector<SymbolInfo*> child = {$1,$4,$5};
							$$ = ParseTreeGenerator::createNonTerminal(child,"compound_statement");
							sem_anlzr->endScope();
							freeMemory(child);
						}
						| LCURL create_scope RCURL
						{
							vector<SymbolInfo*> child = {$1,$3};
							$$ = ParseTreeGenerator::createNonTerminal(child,"compound_statement");
							sem_anlzr->endScope();
							freeMemory(child);
						}
						| LCURL create_scope error RCURL
						{
							vector<SymbolInfo*> child = {$1,$4};
							$$ = ParseTreeGenerator::createNonTerminal(child,"compound_statement");
							sem_anlzr->endScope();
							freeMemory(child);
						}
						;

// No temporary variables
create_scope			: 
						{ 
							sem_anlzr->startScope();
						}

// No temporary variables
var_declaration 		: type_specifier declaration_list SEMICOLON 
						{ 				
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = ParseTreeGenerator::createNonTerminal(child,"var_declaration");
							sem_anlzr->declareVariables($1->getSymbol(),$2->getSymbol(),$2->getDeclarations());
							freeMemory(child);
						}
						| type_specifier declaration_list error SEMICOLON 
						{ 			
							vector<SymbolInfo*> child = {$1,$2,$4};
							$$ = ParseTreeGenerator::createNonTerminal(child,"var_declaration");
							sem_anlzr->declareVariables($1->getSymbol(),$2->getSymbol(),$2->getDeclarations());
							freeMemory(child);
						}
						;

// No temporary variables		 
type_specifier			: INT 	
						{ 
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"type_specifier");
							freeMemory(child);
						}
						| FLOAT
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"type_specifier");
							freeMemory(child);
						}
						| VOID
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"type_specifier");
							freeMemory(child);
						}
						;

// No temporary variables 		
declaration_list 		: declaration_list COMMA ID
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = ParseTreeGenerator::createDeclarationList(child,"declaration_list");
							$$->addVariables($1);
							$$->addVariable($3->getSymbol());
							freeMemory(child);
						}
						| declaration_list error COMMA ID
						{
							vector<SymbolInfo*> child = {$1,$3,$4};
							$$ = ParseTreeGenerator::createDeclarationList(child,"declaration_list");
							$$->addVariables($1);
							$$->addVariable($4->getSymbol());
							freeMemory(child);
						}
						| declaration_list COMMA ID LTHIRD constant RTHIRD
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$6};
							$$ = ParseTreeGenerator::createDeclarationList(child,"declaration_list");
							sem_anlzr->checkArraySize($5);
							$$->addVariables($1);
							$$->addArray($3->getSymbol(),$5->getSymbol());
							freeMemory(child);
						}
						| declaration_list error COMMA ID LTHIRD constant RTHIRD
						{
							vector<SymbolInfo*> child = {$1,$3,$4,$5,$6,$7};
							$$ = ParseTreeGenerator::createDeclarationList(child,"declaration_list");
							sem_anlzr->checkArraySize($6);
							$$->addVariables($1);
							$$->addArray($4->getSymbol(),$6->getSymbol());
							freeMemory(child);
						}
						| ID 
						{ 
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createDeclarationList(child,"declaration_list");	
							$$->addVariable($1->getSymbol());
							freeMemory(child);
						}
						| ID LTHIRD constant RTHIRD // handleArrayDeclaration({$1,$2,$3,$4})
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							$$ = ParseTreeGenerator::createDeclarationList(child,"declaration_list");
							sem_anlzr->checkArraySize($3);
							$$->addArray($1->getSymbol(),$3->getSymbol());
							freeMemory(child);
						}
						;
 		  
statements 				: statement
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statements");
							freeMemory(child);
						}
						| statements statement
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statements");
							freeMemory(child);
						}
						| statements error statement
						{
							vector<SymbolInfo*> child = {$1,$3};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statements");
							freeMemory(child);
						}
						;
	   
statement 				: var_declaration
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statement");
							freeMemory(child);
						}
						| func_definition {
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statement");
							sem_anlzr->handleInvalidFunctionScoping();
							freeMemory(child);
						}
						| func_declaration {
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statement");
							sem_anlzr->handleInvalidFunctionScoping();
							freeMemory(child);
						}
						| expression_statement
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statement");
							freeMemory(child);
						}
						| compound_statement
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statement");
							freeMemory(child);
						}
						| FOR LPAREN expression_statement expression_statement expression RPAREN statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$6,$7};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statement");
							freeMemory(child);
						}
						| IF LPAREN expression RPAREN statement %prec THEN
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statement");
							freeMemory(child);
						}		
						| IF LPAREN expression RPAREN statement ELSE statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$6,$7};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statement");
							freeMemory(child);
						}
						| WHILE LPAREN expression RPAREN statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statement");
							freeMemory(child);
						}
						| PRINTLN LPAREN ID RPAREN SEMICOLON
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statement");	
							sem_anlzr->handlePrintfCall($3->getSymbol());
							freeMemory(child);
						}
						| RETURN expression SEMICOLON
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statement");
							sem_anlzr->returnFunction($2);
							freeMemory(child);
						}
						| RETURN SEMICOLON {
							// New rule
							vector<SymbolInfo*> child = {$1,$2};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statement");
							freeMemory(child);
						}
						;

expression_statement 	: SEMICOLON		
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"expression_statement");
							freeMemory(child);
						}	
						| expression SEMICOLON 
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = ParseTreeGenerator::createNonTerminal(child,"expression_statement");
							freeMemory(child);
						}
						;
	  
variable 				: ID 		
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createExpression(child,"variable");
							$$->setDataType(sem_anlzr->callVariable($1->getSymbol()));
							freeMemory(child);
						}
						| ID LTHIRD expression RTHIRD 
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							$$ = createArrayCall(child,"variable");
							$$->setDataType(sem_anlzr->callArray($1->getSymbol(),$3));
							freeMemory(child);
						}
						;
	 
 expression 			: logic_expression	
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createExpression(child,"expression");
							$$->setDataType($1->getDataType());				
							freeMemory(child);
						}
						| variable ASSIGNOP logic_expression 
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = ParseTreeGenerator::createExpression(child,"expression");
							$$->setDataType(sem_anlzr->assignOp($1,$3));
							freeMemory(child);
						}	
						;
			
logic_expression 		: rel_expression 	
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createExpression(child,"logic_expression");
							$$->setDataType($1->getDataType());
							freeMemory(child);
						}
						| rel_expression LOGICOP rel_expression 	
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = ParseTreeGenerator::createExpression(child,"logic_expression");
							$$->setDataType(sem_anlzr->logicOp($1,$2->getSymbol(),$3));
							freeMemory(child);
						}
						;
			
rel_expression			: simple_expression 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createExpression(child,"rel_expression");
							$$->setDataType($1->getDataType());
							freeMemory(child);
						}
						| simple_expression RELOP simple_expression	
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = ParseTreeGenerator::createExpression(child,"rel_expression");
							$$->setDataType(sem_anlzr->relOp($1,$2->getSymbol(),$3));
							freeMemory(child);
						}
						;
				
simple_expression 		: term 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createExpression(child,"simple_expression");
							$$->setDataType($1->getDataType());
							freeMemory(child);
						}
						| simple_expression ADDOP term 
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = ParseTreeGenerator::createExpression(child,"simple_expression");
							$$->setDataType(sem_anlzr->addOp($1,$2->getSymbol(),$3));
							freeMemory(child);
						}
						;
					
term 					:	unary_expression
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createExpression(child,"term");
							$$->setDataType($1->getDataType());
							freeMemory(child);
						}
						|  term MULOP unary_expression
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = ParseTreeGenerator::createExpression(child,"term");
							$$->setDataType(sem_anlzr->mulOp($1,$2->getSymbol(),$3));						
							freeMemory(child);
						}
						;

unary_expression 		: ADDOP unary_expression
						{ 
							vector<SymbolInfo*> child = {$1,$2};
							$$ = ParseTreeGenerator::createExpression({$1,$2},"unary_expression");
							$$->setDataType($2->getDataType());
							freeMemory(child);
						}  
						| NOT unary_expression 
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = ParseTreeGenerator::createExpression(child,"unary_expression");
							$$->setDataType($2->getDataType());
							freeMemory(child);
						}
						| factor 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createExpression(child,"unary_expression");
							$$->setDataType($1->getDataType());
							freeMemory(child);
						}
						;
	
factor					: variable 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createExpression(child,"factor");
							$$->setDataType($1->getDataType());
							freeMemory(child);
						}
						| ID LPAREN argument_list RPAREN
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							$$ = ParseTreeGenerator::createExpression(child,"factor");
							$$->setDataType(sem_anlzr->callFunction($1->getSymbol(), $3->getArgs()));
							freeMemory(child);
						}
						| LPAREN expression RPAREN
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = ParseTreeGenerator::createExpression(child,"factor");
							$$->setDataType($2->getDataType());
							freeMemory(child);
						}
						| CONST_INT 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createExpression(child,"factor");
							$$->setDataType("int");
							freeMemory(child);
						}
						| CONST_FLOAT
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createExpression(child,"factor");
							$$->setDataType("float");
							freeMemory(child);
						}
						| variable INCOP 
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = ParseTreeGenerator::createExpression(child,"factor");
							$$->setDataType($1->getDataType());	
							freeMemory(child);
						}
						| variable DECOP
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = ParseTreeGenerator::createExpression(child,"factor");
							$$->setDataType($1->getDataType());
							freeMemory(child);
						}
						;
	
argument_list 			: arguments
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createArgumentList(child,"argument_list");
							$$->addArgs($1);
							freeMemory(child);
						}
						| 
						{ 
							vector<SymbolInfo*> child = {};
							$$ = ParseTreeGenerator::createArgumentList(child,"argument_list");
							freeMemory(child);
						}
						;
	
arguments 				: arguments COMMA logic_expression // handleArguments({$1,$2,$3})
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = ParseTreeGenerator::createArgumentList(child,"arguments");
							$$->addArgs($1);
							$$->addArg($3);
							freeMemory(child);
						}
						| logic_expression // handleArgument($1)
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createArgumentList(child,"arguments");
							$$->addArg($1);
							freeMemory(child);
						}
						;

// No temporary variables
constant 				: CONST_INT // handleConstant({$1},"int")
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createExpression(child,"constant");
							$$->setDataType("int");
							freeMemory(child);
						}
						| CONST_FLOAT // handleConstant({$1},"float")
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createExpression(child,"constant");
							$$->setDataType("float");
							freeMemory(child);
						}
%%

void runParser(FILE *fin)
{
	yyin = fin;
    yyparse();
}