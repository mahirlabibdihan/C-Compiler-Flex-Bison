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
#include "../include/Util.hpp"
#include "../include/ExtendedSymbol.hpp"
#include "../include/SyntaxAnalyzer.hpp"
using namespace std;

int yylex(void);
extern FILE *yyin;
extern SyntaxAnalyzer *syn_anlzr;

void yyerror(string error){
	syn_anlzr->handleError();
}

%}

%union{
	Terminal *terminal;
	NonTerminal *non_terminal;
	Expression *expression;
	ArgumentList *args;
	ParameterList *params;
	DeclarationList *vars;
	Program *program;
	Unit *unit;
	FunctionDeclaration *func_decl;
	FunctionDefinition *func_def;
	VariableDeclaration *var_decl;
	CompoundStatement *stmt_list;
	Statement *stmt;
	VariableCall *var_call;
	ExpressionStatement* expr_stmt;
}

%token <terminal> IF ELSE THEN SWITCH CASE DEFAULT FOR DO WHILE INT FLOAT DOUBLE CHAR STRING VOID BREAK RETURN CONTINUE INCOP DECOP ASSIGNOP NOT PRINTLN LPAREN RPAREN LCURL RCURL LSQUARE RSQUARE COMMA SEMICOLON ID CONST_INT CONST_FLOAT CONST_CHAR ADDOP MULOP LOGICOP RELOP BITOP

%type <program> start program 
%type <unit> unit 
%type <func_decl> func_declaration 
%type <func_def> func_definition 
%type <var_decl> var_declaration
%type <stmt_list> compound_statement statements
%type <terminal> type_specifier 
%type <stmt> statement
%type <expr_stmt> expression_statement

%type <args> argument_list arguments
%type <params> parameter_list
%type <vars> declaration_list
%type <expression> expression logic_expression rel_expression simple_expression term unary_expression factor 
%type <var_call> variable

%destructor { if($$!=NULL) delete $$; } <*>

%nonassoc THEN
%nonassoc ELSE
%%

start 					: program
						{
							$$ = $1;
							
							vector<SymbolInfo*> child = {$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "start");

							syn_anlzr->setASTRoot($$);
							$$ = NULL;
						}
						;

program 				: program  unit
						{
							$$ = $1;
							$$->addUnit($2);	

							vector<SymbolInfo*> child = {$1,$2};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "program");	
						}
						|  unit
						{
							$$ = new Program(); 
							$$->addUnit($1);

							vector<SymbolInfo*> child = {$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "program");
						}
						;
	
unit 					: var_declaration
						{
							$$ = $1;
							if($$ != NULL) $$->setNonTerminalType("UNIT");

							vector<SymbolInfo*> child = {$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "unit");
						}
						| func_declaration
						{
							$$ = $1;
							if($$ != NULL) $$->setNonTerminalType("UNIT");

							vector<SymbolInfo*> child = {$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "unit");
						}
						| func_definition
						{
							$$ = $1;
							if($$ != NULL) $$->setNonTerminalType("UNIT");

							vector<SymbolInfo*> child = {$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "unit");	
						}
						;
    
func_declaration 		: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON // 
						{
							$$ = new FunctionDeclaration($2->getSymbol(), $1->getType(), $4->getParams());

							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$6};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren((Unit*)$$, child, "func_declaration");
						}
						| type_specifier ID LPAREN parameter_list error RPAREN SEMICOLON
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$6,$7};
							syn_anlzr->handleError("function declaration","parameter list");	
							$$ = NULL;
						}
						| type_specifier ID LPAREN RPAREN SEMICOLON
						{
							$$ = new FunctionDeclaration($2->getSymbol(), $1->getType(), {});

							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren((Unit*)$$, child, "func_declaration"); 
						}
						;
		 

func_definition 		: type_specifier ID LPAREN parameter_list RPAREN compound_statement 
						{
							$$ = new FunctionDefinition($2->getSymbol(),$1->getType(), $4->getParams(), $6->getStatements());

							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$6};	
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren((Unit*)$$, child, "func_definition");
						}
						| type_specifier ID LPAREN parameter_list error RPAREN compound_statement
						{
							syn_anlzr->handleError("function definition","parameter list");
							$$ = NULL;	
							
							delete $1, $2, $3, $4, $6, $7;
						}
						| type_specifier ID LPAREN RPAREN compound_statement
						{
							$$ = new FunctionDefinition($2->getSymbol(), $1->getType(), {}, $5->getStatements());

							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren((Unit*)$$, child, "func_definition");
						}
						;				

parameter_list  		: parameter_list COMMA type_specifier ID
						{
							$$ = $1; 
							Variable* param = new Variable($4->getSymbol(),$3->getType());
							param->setStartLine($3->getStartLine());
							$$->addParam(param);
							// $$->addParam($3->getType(),$4->getSymbol());

							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "parameter_list");
						}
						| parameter_list COMMA type_specifier 
						{
							$$ = $1; 
							Variable* param = new Variable("blank",$3->getType());
							param->setStartLine($3->getStartLine());
							$$->addParam(param);
							// $$->addParam($3->getType());

							vector<SymbolInfo*> child = {$1,$2,$3};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "parameter_list");	
						}
						| type_specifier ID 
						{
							$$ = new ParameterList(); 
							Variable* param = new Variable($2->getSymbol(),$1->getType());
							param->setStartLine($1->getStartLine());
							$$->addParam(param);
							// $$->addParam($1->getType(),$2->getSymbol());

							vector<SymbolInfo*> child = {$1,$2};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "parameter_list");
						}
						| type_specifier
						{
							$$ = new ParameterList(); 
							Variable* param = new Variable("blank",$1->getType());
							param->setStartLine($1->getStartLine());
							$$->addParam(param);
							// $$->addParam($1->getType());

							vector<SymbolInfo*> child = {$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "parameter_list");
						}
						;

compound_statement 		: LCURL statements RCURL
						{
							$$ = $2;

							vector<SymbolInfo*> child = {$1,$2,$3};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "compound_statement");
						}
						| LCURL RCURL
						{
							$$ = new CompoundStatement();

							vector<SymbolInfo*> child = {$1,$2};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "compound_statement");
						}
						;

var_declaration 		: type_specifier declaration_list SEMICOLON
						{ 				
							$$ = new VariableDeclaration($1->getType(), $2->getDeclarations());

							vector<SymbolInfo*> child = {$1,$2,$3};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren((Unit*)$$, child, "var_declaration");							
						}
						| type_specifier declaration_list error SEMICOLON 
						{ 	
							$$ = new VariableDeclaration($1->getType(), $2->getDeclarations());

							vector<SymbolInfo*> child = {$1,$2,$4};
							syn_anlzr->handleError("variable declaration","declaration list");
						}
						;

type_specifier			: INT
						{ 
							$$ = $1;
							
							vector<SymbolInfo*> child = {$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "type_specifier");	
						}
						| FLOAT
						{
							$$ = $1;

							vector<SymbolInfo*> child = {$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "type_specifier");
						}
						| VOID
						{
							$$ = $1;

							vector<SymbolInfo*> child = {$1};	
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "type_specifier");				
						}
						;
	
declaration_list 		: declaration_list COMMA ID
						{
							$$ = $1; 
							$$->addVariable($3->getSymbol());
							
							vector<SymbolInfo*> child = {$1,$2,$3};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "declaration_list");							
						}
						| declaration_list COMMA ID LSQUARE CONST_INT RSQUARE
						{
							$$ = $1; 
							$$->addArray($3->getSymbol(),$5->getSymbol());	
							
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$6};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "declaration_list");								
						}
						| ID
						{ 
							$$ = new DeclarationList();
							$$->addVariable($1->getSymbol());	

							vector<SymbolInfo*> child = {$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "declaration_list");
						}
						| ID LSQUARE CONST_INT RSQUARE
						{
							$$ = new DeclarationList();
							$$->addArray($1->getSymbol(),$3->getSymbol());

							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "declaration_list");
						}
						;
 		  
statements 				: statement
						{
							$$ = new CompoundStatement(); 
							if($1 != NULL) $$->addStatement($1);

							vector<SymbolInfo*> child = {$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "statements");
						}
						| statements statement
						{
							$$ = $1; 
							if($2 != NULL) $$->addStatement($2);

							vector<SymbolInfo*> child = {$1,$2};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "statements");
						}
						;

statement 				: var_declaration
						{
							$$ = $1;
							$$->setNonTerminalType("STATEMENT");
							vector<SymbolInfo*> child = {(Statement*)$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "statement");
						}
						| func_definition
						{
							$$ = $1;
							$$->setNonTerminalType("STATEMENT");

							vector<SymbolInfo*> child = {(Statement*)$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "statement");
						}
						| func_declaration
						{
							$$ = $1;
							$$->setNonTerminalType("STATEMENT");

							vector<SymbolInfo*> child = {(Statement*)$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "statement");	
						}
						| expression_statement
						{
							$$ = $1;

							vector<SymbolInfo*> child = {$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "statement");
						}
						| compound_statement
						{
							$$ = $1;

							vector<SymbolInfo*> child = {$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "statement");
						}
						| FOR LPAREN expression_statement expression_statement expression RPAREN statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$6,$7};

							Expression *cond =  $4->getExpression();
							if(cond->getExpType()!="BINARY_BOOLEAN" && cond->getExpType()!="UNARY_BOOLEAN")
							{
								cond = new RelOp(cond, new IntegerCall("0"), "!=");
							}

							$$ = new ForLoop($3->getExpression(), cond, $5, $7);

							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "statement");
						}
						| IF LPAREN expression RPAREN statement %prec THEN
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};

							Expression *cond =  $3;
							if(cond->getExpType()!="BINARY_BOOLEAN" && cond->getExpType()!="UNARY_BOOLEAN")
							{
								cond = new RelOp(cond, new IntegerCall("0"), "!=");
							}

							$$ = new IfStatement(cond, $5);

							
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "statement");
						}		
						| IF LPAREN expression RPAREN statement ELSE statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$6,$7};

							Expression *cond =  $3;
							if(cond->getExpType()!="BINARY_BOOLEAN" && cond->getExpType()!="UNARY_BOOLEAN")
							{
								cond = new RelOp(cond, new IntegerCall("0"), "!=");
							}

							$$ = new IfElseStatement(cond, $5, $7);

							
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "statement");
						}
						| WHILE LPAREN expression RPAREN statement
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};

							Expression *cond =  $3;
							if(cond->getExpType()!="BINARY_BOOLEAN" && cond->getExpType()!="UNARY_BOOLEAN")
							{
								cond = new RelOp(cond, new IntegerCall("0"), "!=");
							}

							$$ = new WhileLoop(cond, $5);
										
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "statement");
						}
						| PRINTLN LPAREN ID RPAREN SEMICOLON 
						{
							$$ = new PrintStatement(new VariableCall($3->getSymbol()));

							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "statement");
						}
						| RETURN expression SEMICOLON
						{
							$$ = new ReturnStatement($2);

							vector<SymbolInfo*> child = {$1,$2,$3};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "statement");
						}
						| RETURN SEMICOLON {
							$$ = new ReturnStatement(NULL);

							vector<SymbolInfo*> child = {$1,$2};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "statement");
						}
						;

expression_statement 	: SEMICOLON
						{
							$$ = NULL;
							delete $1;
						}	
						| expression SEMICOLON // $$ = $1;
						{
							$$ = new ExpressionStatement($1);

							vector<SymbolInfo*> child = {$1,$2};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "expression_statement");
						}
						| error SEMICOLON {
							syn_anlzr->handleError("expression statement","expression");
							$$ = NULL;

							delete $2;
						} 
						;
	  
variable 				: ID 
						{
							$$ = new VariableCall($1->getSymbol());

							vector<SymbolInfo*> child = {$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "variable");
						}
						| ID LSQUARE expression RSQUARE
						{
							$$ = new ArrayCall($1->getSymbol(),$3);		

							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "variable");		
						}
						;
	 
 expression 			: logic_expression 
						{
							$$ = $1;

							vector<SymbolInfo*> child = {$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "expression");
						}
						| variable ASSIGNOP logic_expression
						{
							vector<SymbolInfo*> child = {$1,$2,$3};

							// if($3->getExpType() == "BINARY_BOOLEAN" || $3->getExpType() == "UNARY_BOOLEAN")
							// {
							// 	$3 = new RelOp($3,new IntegerCall("0"), "!=");
							// }

							$$ = new AssignOp($1,$3);
														
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "expression");
						}
						;
			
logic_expression 		: rel_expression 	
						{
							$$ = $1;
							
							vector<SymbolInfo*> child = {$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "logic_expression");
						}
						| rel_expression LOGICOP rel_expression
						{
							vector<SymbolInfo*> child = {$1,$2,$3};

							if($1->getExpType()!="BINARY_BOOLEAN" && $1->getExpType()!="UNARY_BOOLEAN")
							{
								$1 = new RelOp($1,new IntegerCall("0"), "!=");
							}

							if($3->getExpType()!="BINARY_BOOLEAN" && $3->getExpType()!="UNARY_BOOLEAN")
							{
								$3 = new RelOp($3,new IntegerCall("0"), "!=");
							}
							
							$$ = new LogicOp($1,$3,$2->getSymbol());
					
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "logic_expression");
						}
						;
			
rel_expression			: simple_expression 
						{
							$$ = $1;

							vector<SymbolInfo*> child = {$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "rel_expression");
						}
						| simple_expression RELOP simple_expression
						{
							$$ = new RelOp($1,$3,$2->getSymbol());

							vector<SymbolInfo*> child = {$1,$2,$3};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "rel_expression");
						}
						;
				
simple_expression 		: term
						{
							$$ = $1;

							vector<SymbolInfo*> child = {$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "simple_expression");
						}
						| simple_expression ADDOP term
						{
							$$ = new AddOp($1,$3,$2->getSymbol());

							vector<SymbolInfo*> child = {$1,$2,$3};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "simple_expression");
						}
						;
					
term 					: unary_expression
						{
							$$ = $1;

							vector<SymbolInfo*> child = {$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "term");
						}
						| term MULOP unary_expression
						{
							$$ = new MulOp($1,$3,$2->getSymbol());	
							
							vector<SymbolInfo*> child = {$1,$2,$3};	
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "term");					
						}
						;

unary_expression 		: ADDOP unary_expression
						{ 
							$$ = new UAddOp($2,$1->getSymbol());

							vector<SymbolInfo*> child = {$1,$2};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "unary_expression");
						}  
						| NOT unary_expression 
						{
							$$ = new NotOp($2);

							vector<SymbolInfo*> child = {$1,$2};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "unary_expression");
						}
						| factor 
						{
							$$ = $1;

							vector<SymbolInfo*> child = {$1};	
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "unary_expression");
						}
						;

factor					: variable
						{
							$$ = $1;
							
							vector<SymbolInfo*> child = {$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "factor");
						}
						| ID LPAREN argument_list RPAREN
						{
							$$ = new FunctionCall($1->getSymbol(), $3->getArgs());

							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "factor");				
						}
						| LPAREN expression RPAREN 
						{
							$$ = $2;

							vector<SymbolInfo*> child = {$1,$2,$3};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "factor");
						}
						| CONST_INT
						{
							$$ = new IntegerCall($1->getSymbol());
							
							vector<SymbolInfo*> child = {$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "factor");
						}
						| CONST_FLOAT
						{
							$$ = new FloatCall($1->getSymbol());

							vector<SymbolInfo*> child = {$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "factor");	
						}
						| variable INCOP
						{
							$$ = new IncOp($1);

							vector<SymbolInfo*> child = {$1,$2};	
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "factor");
						}
						| variable DECOP
						{
							$$ = new DecOp($1);
							vector<SymbolInfo*> child = {$1,$2};	
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "factor");
						}
						;
	
argument_list 			: arguments 
						{
							$$ = $1;	

							vector<SymbolInfo*> child = {$1};					
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "argument_list");
						}
						| 
						{ 
							$$ = new ArgumentList();

							vector<SymbolInfo*> child = {};		
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "argument_list");
						}
						;
	
arguments 				: arguments COMMA logic_expression
						{
							$$ = $1; 
							$$->addArg($3);

							vector<SymbolInfo*> child = {$1,$2,$3};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "arguments");
						}
						| logic_expression
						{
							$$ = new ArgumentList(); 
							$$->addArg($1);

							vector<SymbolInfo*> child = {$1};
							// $$->setSymbol(Util::formatCode(child));				
							syn_anlzr->setChildren($$, child, "arguments");
						}
						;
%%

bool runParser(FILE *fin)
{
	yyin = fin;
    return yyparse() == 0;
}