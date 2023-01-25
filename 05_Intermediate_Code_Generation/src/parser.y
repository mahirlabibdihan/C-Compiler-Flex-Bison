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
#include "../include/Util.hpp"
#include "../include/ExtendedSymbol.hpp"
#include "../include/LexicalAnalyzer.hpp"
using namespace std;

int yyparse(Program*);
int yylex(void);
extern FILE *yyin;
extern ErrorHandler *error_hndlr;
extern ofstream logout;
extern ofstream errorout;
extern LexicalAnalyzer *lexer;
Program *prog;
void yyerror(string error){
	logout << error_hndlr->handleSyntaxError(lexer->getLineCount()) << std::endl;
}

void syntax_error(string parent,string error_child){
	errorout << error_hndlr->handleSyntaxError(parent, error_child, lexer->getLineCount()) << std::endl;
}

void syntax_error(string parent){
	errorout << error_hndlr->handleSyntaxError(parent, lexer->getLineCount()) << std::endl;
}

template <typename T>
void erm(T s)
{
	if(s!=NULL) delete s;
}

void setChildren(SymbolInfo* node,const vector<SymbolInfo *> &child, const string &type)
{
	if(node == NULL) return;
	node->setSymbol(Util::formatCode(child));
	// node->setType(type);
	if (child.empty())
    {
        node->setStartLine(lexer->getLineCount());
        node->setEndLine(lexer->getLineCount());
    }
    else
    {
		if(child.front()!=NULL)
        node->setStartLine(child.front()->getStartLine());
		if(child.back()!=NULL)
        node->setEndLine(child.back()->getEndLine());
    }
	// if(((ASTNode*)node)->getASTType()=="NON_TERMINAL") 
	// {
	// 	cout<<type<<"ERROR"<<endl;
	// 	((NonTerminal*)node)->setChildren(child);
	// 	cout<<type<<"ERROR"<<endl;
	// }
		
	logout << Logger::getRule(node, child) << std::endl;
	// logout << node->getSymbol() << std::endl;
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

%destructor { erm($$); } <*>

%nonassoc THEN
%nonassoc ELSE
%%

start 					: program
						{
							$$ = $1;
							
							vector<SymbolInfo*> child = {$1};
							setChildren($$, child, "start");

							prog = $$;
							$$ = NULL;
						}
						;

program 				: program  unit
						{
							$$ = $1;
							if($2 != NULL) 
							{
								string type = $2->getUnitType();
								if(type == "FUNCTION_DEFINITION")
								{
									$$->addFunctionDefinition((FunctionDefinition*)$2);
								}
								if(type == "FUNCTION_DECLARATION")
								{
									$$->addFunctionDeclaration((FunctionDeclaration*)$2);
								}
								if(type == "VARIABLE_DECLARATION")
								{
									$$->addVariableDeclaration((VariableDeclaration*)$2);
								}
							}	

							vector<SymbolInfo*> child = {$1,$2};
							setChildren($$, child, "program");	
						}
						|  unit
						{
							$$ = new Program(); 
							if($1 != NULL)
							{
								string type = $1->getUnitType();
								if(type == "FUNCTION_DEFINITION")
								{
									$$->addFunctionDefinition((FunctionDefinition*)$1);
								}
								if(type == "FUNCTION_DECLARATION")
								{
									$$->addFunctionDeclaration((FunctionDeclaration*)$1);
								}
								if(type == "VARIABLE_DECLARATION")
								{
									$$->addVariableDeclaration((VariableDeclaration*)$1);
								}
							}

							vector<SymbolInfo*> child = {$1};
							setChildren($$, child, "program");
						}
						;
	
unit 					: var_declaration
						{
							$$ = $1;
							if($$ != NULL) $$->setNonTerminalType("UNIT");

							vector<SymbolInfo*> child = {(Unit*)$1};
							setChildren($$, child, "unit");
						}
						| func_declaration
						{
							$$ = $1;
							if($$ != NULL) $$->setNonTerminalType("UNIT");

							vector<SymbolInfo*> child = {(Unit*)$1};
							setChildren($$, child, "unit");
						}
						| func_definition
						{
							$$ = $1;
							if($$ != NULL) $$->setNonTerminalType("UNIT");

							vector<SymbolInfo*> child = {(Unit*)$1};
							setChildren($$, child, "unit");	
						}
						;
    
func_declaration 		: type_specifier ID LPAREN parameter_list RPAREN SEMICOLON // 
						{
							$$ = new FunctionDeclaration($2->getSymbol(), $1->getType(), $4->getParams());

							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$6};
							setChildren((Unit*)$$, child, "func_declaration");
						}
						| type_specifier ID LPAREN parameter_list error RPAREN SEMICOLON
						{
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$6,$7};
							syntax_error("function declaration","parameter list");	
							$$ = NULL;
						}
						| type_specifier ID LPAREN RPAREN SEMICOLON
						{
							$$ = new FunctionDeclaration($2->getSymbol(), $1->getType(), {});

							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							setChildren((Unit*)$$, child, "func_declaration"); 
						}
						;
		 

func_definition 		: type_specifier ID LPAREN parameter_list RPAREN compound_statement 
						{
							$$ = new FunctionDefinition($2->getSymbol(),$1->getType(), $4->getParams(), $6->getStatements());

							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$6};	
							setChildren((Unit*)$$, child, "func_definition");
						}
						| type_specifier ID LPAREN parameter_list error RPAREN compound_statement
						{
							syntax_error("function definition","parameter list");
							$$ = NULL;	
							
							delete $1, $2, $3, $4, $6, $7;
						}
						| type_specifier ID LPAREN RPAREN compound_statement
						{
							$$ = new FunctionDefinition($2->getSymbol(), $1->getType(), {}, $5->getStatements());

							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							setChildren((Unit*)$$, child, "func_definition");
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
							setChildren($$, child, "parameter_list");
						}
						| parameter_list COMMA type_specifier 
						{
							$$ = $1; 
							Variable* param = new Variable("blank",$3->getType());
							param->setStartLine($3->getStartLine());
							$$->addParam(param);
							// $$->addParam($3->getType());

							vector<SymbolInfo*> child = {$1,$2,$3};
							setChildren($$, child, "parameter_list");	
						}
						| type_specifier ID 
						{
							$$ = new ParameterList(); 
							Variable* param = new Variable($2->getSymbol(),$1->getType());
							param->setStartLine($1->getStartLine());
							$$->addParam(param);
							// $$->addParam($1->getType(),$2->getSymbol());

							vector<SymbolInfo*> child = {$1,$2};
							setChildren($$, child, "parameter_list");
						}
						| type_specifier
						{
							$$ = new ParameterList(); 
							Variable* param = new Variable("blank",$1->getType());
							param->setStartLine($1->getStartLine());
							$$->addParam(param);
							// $$->addParam($1->getType());

							vector<SymbolInfo*> child = {$1};
							setChildren($$, child, "parameter_list");
						}
						;

compound_statement 		: LCURL statements RCURL
						{
							$$ = $2;

							vector<SymbolInfo*> child = {$1,$2,$3};
							setChildren($$, child, "compound_statement");
						}
						| LCURL RCURL
						{
							$$ = NULL;
							delete $1, $2;
						}
						;

var_declaration 		: type_specifier declaration_list SEMICOLON
						{ 				
							$$ = new VariableDeclaration($1->getType(), $2->getDeclarations());

							vector<SymbolInfo*> child = {$1,$2,$3};
							setChildren((Unit*)$$, child, "var_declaration");							
						}
						| type_specifier declaration_list error SEMICOLON 
						{ 	
							$$ = new VariableDeclaration($1->getType(), $2->getDeclarations());

							vector<SymbolInfo*> child = {$1,$2,$4};
							syntax_error("variable declaration","declaration list");
						}
						;

type_specifier			: INT
						{ 
							$$ = $1;
							
							vector<SymbolInfo*> child = {$1};
							setChildren($$, child, "type_specifier");	
						}
						| FLOAT
						{
							$$ = $1;

							vector<SymbolInfo*> child = {$1};
							setChildren($$, child, "type_specifier");
						}
						| VOID
						{
							$$ = $1;

							vector<SymbolInfo*> child = {$1};	
							setChildren($$, child, "type_specifier");				
						}
						;
	
declaration_list 		: declaration_list COMMA ID
						{
							$$ = $1; 
							$$->addVariable($3->getSymbol());
							
							vector<SymbolInfo*> child = {$1,$2,$3};
							setChildren($$, child, "declaration_list");							
						}
						| declaration_list COMMA ID LSQUARE CONST_INT RSQUARE
						{
							$$ = $1; 
							$$->addArray($3->getSymbol(),$5->getSymbol());	
							
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$6};
							setChildren($$, child, "declaration_list");								
						}
						| ID
						{ 
							$$ = new DeclarationList();
							$$->addVariable($1->getSymbol());	

							vector<SymbolInfo*> child = {$1};
							setChildren($$, child, "declaration_list");
						}
						| ID LSQUARE CONST_INT RSQUARE
						{
							$$ = new DeclarationList();
							$$->addArray($1->getSymbol(),$3->getSymbol());

							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							setChildren($$, child, "declaration_list");
						}
						;
 		  
statements 				: statement
						{
							$$ = new CompoundStatement(); 
							if($1 != NULL) $$->addStatement($1);

							vector<SymbolInfo*> child = {$1};
							setChildren($$, child, "statements");
						}
						| statements statement
						{
							$$ = $1; 
							if($2 != NULL) $$->addStatement($2);

							vector<SymbolInfo*> child = {$1,$2};
							setChildren($$, child, "statements");
						}
						;

statement 				: var_declaration
						{
							$$ = $1;
							$$->setNonTerminalType("STATEMENT");
							vector<SymbolInfo*> child = {(Statement*)$1};
							setChildren($$, child, "statement");
						}
						| func_definition
						{
							$$ = $1;
							$$->setNonTerminalType("STATEMENT");

							vector<SymbolInfo*> child = {(Statement*)$1};
							setChildren($$, child, "statement");
						}
						| func_declaration
						{
							$$ = $1;
							$$->setNonTerminalType("STATEMENT");

							vector<SymbolInfo*> child = {(Statement*)$1};
							setChildren($$, child, "statement");	
						}
						| expression_statement
						{
							$$ = $1;

							vector<SymbolInfo*> child = {$1};
							setChildren($$, child, "statement");
						}
						| compound_statement
						{
							$$ = $1;

							vector<SymbolInfo*> child = {$1};
							setChildren($$, child, "statement");
						}
						| FOR LPAREN expression_statement expression_statement expression RPAREN statement
						{
							$$ = new ForLoop($3->getExpression(), $4->getExpression(), $5, $7);

							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$6,$7};
							setChildren($$, child, "statement");
						}
						| IF LPAREN expression RPAREN statement %prec THEN
						{
							$$ = new IfStatement($3, $5);

							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							setChildren($$, child, "statement");
						}		
						| IF LPAREN expression RPAREN statement ELSE statement
						{
							$$ = new IfElseStatement($3, $5, $7);

							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5,$6,$7};
							setChildren($$, child, "statement");
						}
						| WHILE LPAREN expression RPAREN statement
						{
							$$ = new WhileLoop($3, $5);
							
							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							setChildren($$, child, "statement");
						}
						| PRINTLN LPAREN ID RPAREN SEMICOLON 
						{
							$$ = new PrintStatement(new VariableCall($3->getSymbol()));

							vector<SymbolInfo*> child = {$1,$2,$3,$4,$5};
							setChildren($$, child, "statement");
						}
						| RETURN expression SEMICOLON
						{
							$$ = new ReturnStatement($2);

							vector<SymbolInfo*> child = {$1,$2,$3};
							setChildren($$, child, "statement");
						}
						| RETURN SEMICOLON {
							$$ = new ReturnStatement(NULL);

							vector<SymbolInfo*> child = {$1,$2};
							setChildren($$, child, "statement");
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
							setChildren($$, child, "expression_statement");
						}
						| error SEMICOLON {
							syntax_error("expression statement","expression");
							$$ = NULL;

							delete $2;
						} 
						;
	  
variable 				: ID 
						{
							$$ = new VariableCall($1->getSymbol());

							vector<SymbolInfo*> child = {$1};
							setChildren($$, child, "variable");
						}
						| ID LSQUARE expression RSQUARE
						{
							$$ = new ArrayCall($1->getSymbol(),$3);		

							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							setChildren($$, child, "variable");		
						}
						;
	 
 expression 			: logic_expression 
						{
							$$ = $1;

							vector<SymbolInfo*> child = {$1};
							setChildren($$, child, "expression");
						}
						| variable ASSIGNOP logic_expression
						{
							$$ = new AssignOp($1,$3);
							
							vector<SymbolInfo*> child = {$1,$2,$3};
							setChildren($$, child, "expression");
						}
						;
			
logic_expression 		: rel_expression 	
						{
							$$ = $1;
							
							vector<SymbolInfo*> child = {$1};
							setChildren($$, child, "logic_expression");
						}
						| rel_expression LOGICOP rel_expression
						{
							$$ = new LogicOp($1,$3,$2->getSymbol());

							vector<SymbolInfo*> child = {$1,$2,$3};
							setChildren($$, child, "logic_expression");
						}
						;
			
rel_expression			: simple_expression 
						{
							$$ = $1;

							vector<SymbolInfo*> child = {$1};
							setChildren($$, child, "rel_expression");
						}
						| simple_expression RELOP simple_expression
						{
							$$ = new RelOp($1,$3,$2->getSymbol());

							vector<SymbolInfo*> child = {$1,$2,$3};
							setChildren($$, child, "rel_expression");
						}
						;
				
simple_expression 		: term
						{
							$$ = $1;

							vector<SymbolInfo*> child = {$1};
							setChildren($$, child, "simple_expression");
						}
						| simple_expression ADDOP term
						{
							$$ = new AddOp($1,$3,$2->getSymbol());

							vector<SymbolInfo*> child = {$1,$2,$3};
							setChildren($$, child, "simple_expression");
						}
						;
					
term 					: unary_expression
						{
							$$ = $1;

							vector<SymbolInfo*> child = {$1};
							setChildren($$, child, "term");
						}
						| term MULOP unary_expression
						{
							$$ = new MulOp($1,$3,$2->getSymbol());	
							
							vector<SymbolInfo*> child = {$1,$2,$3};	
							setChildren($$, child, "term");					
						}
						;

unary_expression 		: ADDOP unary_expression
						{ 
							$$ = new UAddOp($2,$1->getSymbol());

							vector<SymbolInfo*> child = {$1,$2};
							setChildren($$, child, "unary_expression");
						}  
						| NOT unary_expression 
						{
							$$ = new NotOp($2);

							vector<SymbolInfo*> child = {$1,$2};
							setChildren($$, child, "unary_expression");
						}
						| factor 
						{
							$$ = $1;

							vector<SymbolInfo*> child = {$1};	
							setChildren($$, child, "unary_expression");
						}
						;

factor					: variable
						{
							$$ = $1;
							
							vector<SymbolInfo*> child = {$1};
							setChildren($$, child, "factor");
						}
						| ID LPAREN argument_list RPAREN
						{
							$$ = new FunctionCall($1->getSymbol(), $3->getArgs());

							vector<SymbolInfo*> child = {$1,$2,$3,$4};
							setChildren($$, child, "factor");				
						}
						| LPAREN expression RPAREN 
						{
							$$ = $2;

							vector<SymbolInfo*> child = {$1,$2,$3};
							setChildren($$, child, "factor");
						}
						| CONST_INT
						{
							$$ = new IntegerCall($1->getSymbol());
							$$->setSymbol($1->getSymbol());

							vector<SymbolInfo*> child = {$1};
							setChildren($$, child, "factor");
						}
						| CONST_FLOAT
						{
							$$ = new FloatCall($1->getSymbol());
							$$->setSymbol($1->getSymbol());

							vector<SymbolInfo*> child = {$1};
							setChildren($$, child, "factor");	
						}
						| variable INCOP
						{
							$$ = new IncOp($1);

							vector<SymbolInfo*> child = {$1,$2};	
							setChildren($$, child, "factor");
						}
						| variable DECOP
						{
							$$ = new DecOp($1);

							vector<SymbolInfo*> child = {$1,$2};	
							setChildren($$, child, "factor");
						}
						;
	
argument_list 			: arguments 
						{
							$$ = $1;	

							vector<SymbolInfo*> child = {$1};					
							setChildren($$, child, "argument_list");
						}
						| 
						{ 
							$$ = new ArgumentList();

							vector<SymbolInfo*> child = {};		
							setChildren($$, child, "argument_list");
						}
						;
	
arguments 				: arguments COMMA logic_expression
						{
							$$ = $1; 
							$$->addArg($3);

							vector<SymbolInfo*> child = {$1,$2,$3};
							setChildren($$, child, "arguments");
						}
						| logic_expression
						{
							$$ = new ArgumentList(); 
							$$->addArg($1);

							vector<SymbolInfo*> child = {$1};
							setChildren($$, child, "arguments");
						}
						;
%%

Program *runParser(FILE *fin)
{
	yyin = fin;
    if(yyparse() == 0) return prog;
	return NULL;
}