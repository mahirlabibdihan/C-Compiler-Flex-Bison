%{
/**
 * Author: Mahir Labib Dihan
 * Last modified: January 18, 2023
 */
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
extern ofstream parseout;
extern ErrorHandler *error_hndlr;
extern ofstream logout;
extern ofstream errorout;

void yyerror(string error){
	logout << error_hndlr->handleSyntaxError(sem_anlzr->getLineCount()) << std::endl;
}

void syntax_error(string parent,string error_child){
	errorout << error_hndlr->handleSyntaxError(parent, error_child, sem_anlzr->getLineCount()) << std::endl;
}

void syntax_error(string parent){
	errorout << error_hndlr->handleSyntaxError(parent, sem_anlzr->getLineCount()) << std::endl;
}

%}
%union{
	Terminal *terminal;
	NonTerminal *non_terminal;
	Expression *expression;
	ArgumentList *args;
	ParameterList *params;
	DeclarationList *vars;
}

%token <terminal> IF ELSE THEN SWITCH CASE DEFAULT FOR DO WHILE INT FLOAT DOUBLE CHAR STRING VOID BREAK RETURN CONTINUE INCOP DECOP ASSIGNOP NOT PRINTLN LPAREN RPAREN LCURL RCURL LSQUARE RSQUARE COMMA SEMICOLON ID CONST_INT CONST_FLOAT CONST_CHAR ADDOP MULOP LOGICOP RELOP BITOP

%type <non_terminal> start program unit func_declaration func_definition compound_statement var_declaration type_specifier statements statement expression_statement

%type <args> argument_list arguments
%type <params> parameter_list
%type <vars> declaration_list
%type <expression> expression logic_expression rel_expression simple_expression term unary_expression factor variable

%nonassoc THEN
%nonassoc ELSE
%%

start 					: program
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"start");
							cout<<"Code compiled successfully"<<endl;
							parseout<<ParseTreeGenerator::getTree($$);
							ParseTreeGenerator::deleteTree($$);
						}
						;

program 				: program  unit 
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = ParseTreeGenerator::createNonTerminal(child,"program");			 
						}
						|  unit 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"program");
						}
						;
	
unit 					: var_declaration 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"unit");
							
						}
						| func_declaration 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"unit");
							
						}
						| func_definition 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"unit");
							
						}
						// | error {
						// 	SymbolInfo *s = ParseTreeGenerator::createErrorNode(sem_anlzr->getLineCount());
						// 	vector<SymbolInfo*> child = {s};
						// 	$$ = ParseTreeGenerator::createNonTerminal(child,"unit");
						// 	syntax_error("unit");
						// }
						;

// No temporary variables     
func_declaration 		: 	type_specifier ID LPAREN parameter_list RPAREN SEMICOLON 
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$6};
							$$ = ParseTreeGenerator::createNonTerminal(child,"func_declaration");

							if ($4->getChildren().size() == 1 && $4->getChildren().front()->getType() == "error") {
								syntax_error("function declaration","parameter list");
							} else{
								sem_anlzr->declareFunction($1->getSymbol(),$2->getSymbol(),$4->getParams());
							}
						}
						| type_specifier ID LPAREN parameter_list error RPAREN SEMICOLON
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$6,$7};
							SymbolInfo *s = ParseTreeGenerator::createErrorNode(sem_anlzr->getLineCount());
							$4->setChildren({s});
							$$ = ParseTreeGenerator::createNonTerminal(child,"func_declaration");
							syntax_error("function declaration","parameter list");	
						}
						| type_specifier ID LPAREN RPAREN SEMICOLON
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							$$ = ParseTreeGenerator::createNonTerminal(child,"func_declaration");
							sem_anlzr->declareFunction($1->getSymbol(),$2->getSymbol(),{});	
						}
						;
		 

func_definition 		: type_specifier ID LPAREN parameter_list RPAREN 
						{
							if ($4->getChildren().size() == 1 && $4->getChildren().front()->getType() == "error") {
								syntax_error("function definition","parameter list");
							 }
							else {
								sem_anlzr->defineFunction($1->getSymbol(),$2->getSymbol(), $4->getParams());
							}
						} 
						compound_statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$7};
							$$ = ParseTreeGenerator::createNonTerminal(child,"func_definition");
							sem_anlzr->endFunction();	
						}
						| type_specifier ID LPAREN parameter_list error RPAREN 
						{
							syntax_error("function definition","parameter list");
						} 
						compound_statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$6,$8};
							SymbolInfo *s = ParseTreeGenerator::createErrorNode(sem_anlzr->getLineCount());
							$4->setChildren({s});
							$$ = ParseTreeGenerator::createNonTerminal(child,"func_definition");
							sem_anlzr->endFunction();	
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
						}
						;				

// No temporary variables
parameter_list  		: parameter_list COMMA type_specifier ID
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							$$ = ParseTreeGenerator::createParameterList(child,"parameter_list");
							$$->addParams($1);
							$$->addParam($3->getSymbol(),$4->getSymbol());
						}
						| parameter_list COMMA type_specifier
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = ParseTreeGenerator::createParameterList(child,"parameter_list");
							$$->addParams($1);
							$$->addParam($3->getSymbol());
						}
						| type_specifier ID
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = ParseTreeGenerator::createParameterList(child,"parameter_list");
							$$->addParam($1->getSymbol(),$2->getSymbol());	
						}
						| type_specifier
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createParameterList(child,"parameter_list");
							$$->addParam($1->getSymbol());
						}
						;
 		
compound_statement 		: LCURL create_scope statements RCURL
						{
							vector<SymbolInfo*> child = {$1,$3,$4};
							$$ = ParseTreeGenerator::createNonTerminal(child,"compound_statement");
							sem_anlzr->endScope();
							
						}
						| LCURL create_scope RCURL
						{
							vector<SymbolInfo*> child = {$1,$3};
							$$ = ParseTreeGenerator::createNonTerminal(child,"compound_statement");
							sem_anlzr->endScope();
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

							if ($2->getChildren().size() == 1 && $2->getChildren().front()->getType() == "error"){
								syntax_error("variable declaration","declaration list");
							 }
							sem_anlzr->declareVariables($1->getSymbol(),$2->getSymbol(),$2->getDeclarations());
							
						}
						| type_specifier declaration_list error SEMICOLON 
						{ 		
							vector<SymbolInfo*> child = {$1,$2,$4};
							SymbolInfo *s = ParseTreeGenerator::createErrorNode(sem_anlzr->getLineCount());
							$2->setChildren({s});
							$$ = ParseTreeGenerator::createNonTerminal(child,"var_declaration");
							sem_anlzr->declareVariables($1->getSymbol(),$2->getSymbol(),$2->getDeclarations());
							syntax_error("variable declaration","declaration list");
						}
						;

// No temporary variables		 
type_specifier			: INT 	
						{ 
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"type_specifier");
						}
						| FLOAT
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"type_specifier");
						}
						| VOID
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"type_specifier");							
						}
						;
	
declaration_list 		: declaration_list COMMA ID
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = ParseTreeGenerator::createDeclarationList(child,"declaration_list");
							$$->addVariables($1);
							$$->addVariable($3->getSymbol());
							
						}
						| declaration_list COMMA ID LSQUARE CONST_INT RSQUARE
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$6};
							$$ = ParseTreeGenerator::createDeclarationList(child,"declaration_list");
							$$->addVariables($1);
							$$->addArray($3->getSymbol(),$5->getSymbol());				
						}
						| ID
						{ 
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createDeclarationList(child,"declaration_list");	
							$$->addVariable($1->getSymbol());
						}
						| ID LSQUARE CONST_INT RSQUARE // handleArrayDeclaration({$1,$2,$3,$4})
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							$$ = ParseTreeGenerator::createDeclarationList(child,"declaration_list");
							$$->addArray($1->getSymbol(),$3->getSymbol());
						}
						;
 		  
statements 				: statement
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statements");
						}
						| statements statement
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statements");
						}
						;
	   
statement 				: var_declaration
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statement");
						}
						| func_definition 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statement");	
						}
						| func_declaration 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statement");	
						}
						| expression_statement
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statement");
						}
						| compound_statement
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statement");
						}
						| FOR LPAREN expression_statement expression_statement expression RPAREN statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$6,$7};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statement");	
						}
						| IF LPAREN expression RPAREN statement %prec THEN
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statement");
						}		
						| IF LPAREN expression RPAREN statement ELSE statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$6,$7};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statement");
						}
						| WHILE LPAREN expression RPAREN statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statement");
						}
						| PRINTLN LPAREN ID RPAREN SEMICOLON
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statement");	
							sem_anlzr->handlePrintlnCall($3->getSymbol());
						}
						| RETURN expression SEMICOLON
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statement");
							sem_anlzr->returnFunction($2);
						}
						| RETURN SEMICOLON {
							// New rule
							vector<SymbolInfo*> child = {$1,$2};
							$$ = ParseTreeGenerator::createNonTerminal(child,"statement");
						}
						;

expression_statement 	: SEMICOLON		
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createNonTerminal(child,"expression_statement");
							
						}	
						| expression SEMICOLON 
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = ParseTreeGenerator::createNonTerminal(child,"expression_statement");
							if ($1->getChildren().size() == 1 && $1->getChildren().front()->getType() == "error"){
								syntax_error("expression statement","expression");
							}
						}
						| error SEMICOLON {
							SymbolInfo *s = ParseTreeGenerator::createErrorNode(sem_anlzr->getLineCount());
							Expression *e = new Expression(Util::formatCode({s}),"expression");
							ParseTreeGenerator::createNode(e,{s});
							vector<SymbolInfo*> child = {e,$2};
							
							$$ = ParseTreeGenerator::createNonTerminal(child,"expression_statement");
							syntax_error("expression statement","expression");
						} 
						;
	  
variable 				: ID 		
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createExpression(child,"variable");
							$$->setDataType(sem_anlzr->callVariable($1->getSymbol()));
							
						}
						| ID LSQUARE expression RSQUARE 
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							$$ =  ParseTreeGenerator::createArrayCall(child,"variable");
							$$->setDataType(sem_anlzr->callArray($1->getSymbol(),$3));
							
						}
						;
	 
 expression 			: logic_expression 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createExpression(child,"expression");
							$$->setDataType($1->getDataType());
						}
						| variable ASSIGNOP logic_expression 
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = ParseTreeGenerator::createExpression(child,"expression");
							$$->setDataType(sem_anlzr->assignOp($1,$3));
							
						}
						;
			
logic_expression 		: rel_expression 	
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createExpression(child,"logic_expression");
							$$->setDataType($1->getDataType());
						}
						| rel_expression LOGICOP rel_expression 	
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = ParseTreeGenerator::createExpression(child,"logic_expression");
							$$->setDataType(sem_anlzr->logicOp($1,$2->getSymbol(),$3));
						}
						;
			
rel_expression			: simple_expression 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createExpression(child,"rel_expression");
							$$->setDataType($1->getDataType());
							
						}
						| simple_expression RELOP simple_expression	
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = ParseTreeGenerator::createExpression(child,"rel_expression");
							$$->setDataType(sem_anlzr->relOp($1,$2->getSymbol(),$3));	
						}
						;
				
simple_expression 		: term 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createExpression(child,"simple_expression");
							$$->setDataType($1->getDataType());
						}
						| simple_expression ADDOP term 
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = ParseTreeGenerator::createExpression(child,"simple_expression");
							$$->setDataType(sem_anlzr->addOp($1,$2->getSymbol(),$3));
						}
						;
					
term 					:	unary_expression
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createExpression(child,"term");
							$$->setDataType($1->getDataType());
						}
						|  term MULOP unary_expression
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = ParseTreeGenerator::createExpression(child,"term");
							$$->setDataType(sem_anlzr->mulOp($1,$2->getSymbol(),$3));							
						}
						;

unary_expression 		: ADDOP unary_expression
						{ 
							vector<SymbolInfo*> child = {$1,$2};
							$$ = ParseTreeGenerator::createExpression({$1,$2},"unary_expression");
							$$->setDataType($2->getDataType());	
						}  
						| NOT unary_expression 
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = ParseTreeGenerator::createExpression(child,"unary_expression");
							$$->setDataType($2->getDataType());
							
						}
						| factor 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createExpression(child,"unary_expression");
							$$->setDataType($1->getDataType());	
						}
						;
	
factor					: variable 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createExpression(child,"factor");
							$$->setDataType($1->getDataType());
							
						}
						| ID LPAREN argument_list RPAREN
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							$$ = ParseTreeGenerator::createExpression(child,"factor");
							$$->setDataType(sem_anlzr->callFunction($1->getSymbol(), $3->getArgs()));						
						}
						| LPAREN expression RPAREN
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = ParseTreeGenerator::createExpression(child,"factor");
							$$->setDataType($2->getDataType());
						}
						| CONST_INT 
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createExpression(child,"factor");
							$$->setDataType("INT");
							
						}
						| CONST_FLOAT
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createExpression(child,"factor");
							$$->setDataType("FLOAT");
							
						}
						| variable INCOP 
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = ParseTreeGenerator::createExpression(child,"factor");
							$$->setDataType($1->getDataType());	
							
						}
						| variable DECOP
						{
							vector<SymbolInfo*> child = {$1,$2};
							$$ = ParseTreeGenerator::createExpression(child,"factor");
							$$->setDataType($1->getDataType());	
						}
						;
	
argument_list 			: arguments
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createArgumentList(child,"argument_list");
							$$->addArgs($1);
							
						}
						| 
						{ 
							vector<SymbolInfo*> child = {};
							$$ = ParseTreeGenerator::createArgumentList(child,"argument_list");			
						}
						;
	
arguments 				: arguments COMMA logic_expression
						{
							vector<SymbolInfo*> child = {$1,$2,$3};
							$$ = ParseTreeGenerator::createArgumentList(child,"arguments");
							$$->addArgs($1);
							$$->addArg($3);
							
						}
						| logic_expression
						{
							vector<SymbolInfo*> child = {$1};
							$$ = ParseTreeGenerator::createArgumentList(child,"arguments");
							$$->addArg($1);
						}
						;
%%

void runParser(FILE *fin)
{
	yyin = fin;
    yyparse();
}