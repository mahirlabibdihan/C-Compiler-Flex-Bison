%{
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include "../01_Symbol_Table/1905072_SymbolTable.h"
#include "../01_Symbol_Table/1905072_SymbolInfo.h"
#include "../01_Symbol_Table/1905072_ScopeTable.h"
#include "1905072_Logger.h"
#include "1905072_Node.h"

using namespace std;

ofstream logout;
ofstream errout;
ofstream tokenout;

int yyparse(void);
int yylex(void);
extern FILE *yyin;
extern int yylineno;
// SymbolTable *table;
int line_count;
int error_count;
SymbolTable *table;
unsigned long sdbmHash(string str)
{
    unsigned long hash = 0;
    for (auto ch : str)
    {
        int c = ch;
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

void ScopeTable::print()
{
    logout << "ScopeTable # " << id << endl;
    for (int i = 0; i < n_buckets; i++)
    {
        SymbolInfo *cur = hash_table[i];
        if (cur == nullptr)
        {
            continue;
        }
        logout << " " << i << " --> ";

        while (cur != nullptr)
        {
            logout << "< " << cur->getName() << " : " << cur->getType() << "> ";
            cur = cur->getNext();
        }
        logout << endl;
    }
    logout << endl;
}

void yyerror(string s){
	logout<<"Error at line "<<line_count<<": "<<s<<"\n"<<endl;
	errout<<"Error at line "<<line_count<<": "<<s<<"\n"<<endl;
    error_count++;
}


%}

%error-verbose

%union{
    SymbolInfo* symbol;
	Node* node;
}


%token IF ELSE LOWER_THAN_ELSE SWITCH CASE DEFAULT FOR DO WHILE INT FLOAT DOUBLE CHAR STRING VOID BREAK RETURN CONTINUE
%token INCOP DECOP ASSIGNOP NOT PRINTLN
%token LPAREN RPAREN LCURL RCURL LTHIRD RTHIRD COMMA SEMICOLON

%token <symbol> INT FLOAT VOID
%token <symbol> ID CONST_INT CONST_FLOAT CONST_CHAR ADDOP MULOP LOGICOP RELOP

%type <node> start program unit func_declaration func_definition parameter_list compound_statement var_declaration type_specifier declaration_list statements statement expression_statement variable expression logic_expression rel_expression simple_expression term unary_expression factor argument_list arguments LCURL_2

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

start 	: program
		{
			printRule("start","program");
			cout<<"Code compiled successfully"<<endl;
		}
		;

program : program unit 
		{
			printRule("program","program unit");
			$$ = new Node();
            $$->setCode($1->getCode()+"\n\n"+$2->getCode());
            printCode($$->getCode()); 
		}
	    | unit 
		{
			printRule("program","unit");
			$$ = new Node();
            $$->setCode($1->getCode());
            printCode($$->getCode()); 
		}
	    ;
	
unit 	: var_declaration 
		{
			printRule("unit","var_declaration");
			$$ = new Node();
            $$->setCode($1->getCode());
            printCode($$->getCode()); 
		}
     	| func_declaration 
		{
			printRule("unit","func_declaration");
			$$ = new Node();
            $$->setCode($1->getCode());
            printCode($$->getCode()); 
		}
     	| func_definition 
	 	{
			printRule("unit","func_definition");	
			$$ = new Node();
            $$->setCode($1->getCode());
            printCode($$->getCode()); 
		}
     	;
     
func_declaration 	: 	type_specifier ID LPAREN parameter_list RPAREN SEMICOLON 
					{
						printRule("func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
						$$ = new Node();
						$$->setCode(
							$1->getCode()+" "+
							$2->getName()+"("+
							$4->getCode()+")"+";"
						);
						table->insert(*$2);
						printCode($$->getCode());
					}
					| type_specifier ID LPAREN parameter_list RPAREN error
					{
						printRule("func_declaration","type_specifier ID LPAREN parameter_list RPAREN");
						$$ = new Node();
						$$->setCode(
							$1->getCode()+" "+
							$2->getName()+"("+
							$4->getCode()+")"
						);
						table->insert(*$2);
						printCode($$->getCode());
					}
					| type_specifier ID LPAREN parameter_list error RPAREN SEMICOLON
					{
						printRule("func_declaration","type_specifier ID LPAREN parameter_list RPAREN SEMICOLON");
						$$ = new Node();
						$$->setCode(
							$1->getCode()+" "+
							$2->getName()+"("+
							$4->getCode()+")"+";"
						);
						table->insert(*$2);
						printCode($$->getCode());
					}
					| type_specifier ID LPAREN parameter_list error RPAREN error
					{
						printRule("func_declaration","type_specifier ID LPAREN parameter_list RPAREN");
						$$ = new Node();
						$$->setCode(
							$1->getCode()+" "+
							$2->getName()+"("+
							$4->getCode()+")"
						);
						table->insert(*$2);
						printCode($$->getCode());
					}
					| type_specifier ID LPAREN RPAREN SEMICOLON
					{
						printRule("func_declaration","type_specifier ID LPAREN RPAREN SEMICOLON");
						$$ = new Node();
						$$->setCode(
							$1->getCode()+" "+
							$2->getName()+"("+")"+";"
						);
						table->insert(*$2);
						printCode($$->getCode());
					}
					| type_specifier ID LPAREN RPAREN error
					{
						printRule("func_declaration","type_specifier ID LPAREN RPAREN");
						$$ = new Node();
						$$->setCode(
							$1->getCode()+" "+
							$2->getName()+"("+")"
						);
						table->insert(*$2);
						printCode($$->getCode());
					}
					| type_specifier ID LPAREN error RPAREN SEMICOLON
					{
						printRule("func_declaration","type_specifier ID LPAREN RPAREN SEMICOLON");
						$$ = new Node();
						$$->setCode(
							$1->getCode()+" "+
							$2->getName()+"("+")"+";"
						);
						table->insert(*$2);
						printCode($$->getCode());
					}
					| type_specifier ID LPAREN error RPAREN SEMICOLON error
					{
						printRule("func_declaration","type_specifier ID LPAREN RPAREN");
						$$ = new Node();
						$$->setCode(
							$1->getCode()+" "+
							$2->getName()+"("+")"
						);
						table->insert(*$2);
						printCode($$->getCode());
					}
					;
		 
func_definition : type_specifier ID LPAREN parameter_list RPAREN {table->insert(*$2);} compound_statement
				{
					printRule("func_definition","func_defintype_specifier ID LPAREN parameter_list RPAREN compound_statement");
					$$ = new Node();
					$$->setCode(
						$1->getCode()+" "+
						$2->getName()+"("+
						$4->getCode()+")"+
						$7->getCode()
					);
					printCode($$->getCode());
				}
				| type_specifier ID LPAREN parameter_list error RPAREN {table->insert(*$2);} compound_statement
				{
					printRule("func_definition","func_defintype_specifier ID LPAREN parameter_list RPAREN compound_statement");
					$$ = new Node();
					$$->setCode(
						$1->getCode()+" "+
						$2->getName()+"("+
						$4->getCode()+")"+
						$8->getCode()
					);
					printCode($$->getCode());
				}
				| type_specifier ID LPAREN RPAREN {table->insert(*$2);} compound_statement
				{
					printRule("func_definition","type_specifier ID LPAREN RPAREN compound_statement");
					$$ = new Node();
					$$->setCode(
						$1->getCode()+" "+
						$2->getName()+"()"+
						$6->getCode()
					);
					printCode($$->getCode());
				}
				| type_specifier ID LPAREN error RPAREN {table->insert(*$2);} compound_statement
				{
					printRule("func_definition","type_specifier ID LPAREN RPAREN compound_statement");
					$$ = new Node();
					$$->setCode(
						$1->getCode()+" "+
						$2->getName()+"()"+
						$7->getCode()
					);
					printCode($$->getCode());
				}
 				;				


parameter_list  : parameter_list COMMA type_specifier ID
				{
					printRule("parameter_list","parameter_list COMMA type_specifier ID");
					$$ = new Node();
					$$->setCode($1->getCode()+","+$3->getCode()+" "+$4->getName());
					printCode($$->getCode());
				}
				| parameter_list error COMMA type_specifier ID
				{
					printRule("parameter_list","parameter_list COMMA type_specifier ID");
					$$ = new Node();
					$$->setCode($1->getCode()+","+$4->getCode()+" "+$5->getName());
					printCode($$->getCode());
				}
				| parameter_list COMMA type_specifier
				{
					printRule("parameter_list","parameter_list COMMA type_specifier ID");
					$$ = new Node();
					$$->setCode($1->getCode()+","+$3->getCode());
					printCode($$->getCode());
				}
				| parameter_list error COMMA type_specifier
				{
					printRule("parameter_list","parameter_list COMMA type_specifier ID");
					$$ = new Node();
					$$->setCode($1->getCode()+","+$4->getCode());
					printCode($$->getCode());
				}
				| type_specifier ID
				{
					printRule("parameter_list","type_specifier ID");
					$$ = new Node();
					$$->setCode($1->getCode()+" "+$2->getName());
					printCode($$->getCode());
				}
				| type_specifier
				{
					printRule("parameter_list","type_specifier");
					$$ = new Node();
					$$->setCode($1->getCode());
					printCode($$->getCode());
				}
				;

 		
compound_statement :	LCURL_2 statements RCURL
						{
							printRule("compound_statement","LCURL statements RCURL");
							$$ = new Node();
							$$->setCode("{\n" + $2->getCode() + "\n}"); 
							printCode($$->getCode());

							table->printAllScope();
							table->exitScope();
						}
						| LCURL_2 statements error RCURL
						{
							printRule("compound_statement","LCURL statements RCURL");
							$$ = new Node();
							$$->setCode("{\n" + $2->getCode() + "\n}"); 
							printCode($$->getCode());

							table->printAllScope();
							table->exitScope();
						}
						| LCURL_2 error statements RCURL
						{
							printRule("compound_statement","LCURL statements RCURL");
							$$ = new Node();
							$$->setCode("{\n" + $3->getCode() + "\n}"); 
							printCode($$->getCode());

							table->printAllScope();
							table->exitScope();
						}
						| LCURL_2 RCURL
						{
							printRule("compound_statement","LCURL RCURL");
							$$ = new Node();
							$$->setCode("{}"); 
							printCode($$->getCode());

							table->printAllScope();
							table->exitScope();
						}
						| LCURL_2 error RCURL
						{
							printRule("compound_statement","LCURL RCURL");
							$$ = new Node();
							$$->setCode("{}"); 
							printCode($$->getCode());

							table->printAllScope();
							table->exitScope();
						}
						;

LCURL_2	:	LCURL { table->enterScope(); }

var_declaration : type_specifier declaration_list SEMICOLON 
				{ 
					printRule("var_declaration","type_specifier declaration_list SEMICOLON"); 					
					$$ = new Node();
					$$->setCode($1->getCode()+" "+$2->getCode()+";");
					for(auto i:$2->getList())
					{
						table->insert(*i);
					}
					printCode($$->getCode());
				}
				| type_specifier declaration_list error SEMICOLON 
				{ 
					printRule("var_declaration","type_specifier declaration_list SEMICOLON"); 					
					$$ = new Node();
					$$->setCode($1->getCode()+" "+$2->getCode()+";");
					for(auto i:$2->getList())
					{
						table->insert(*i);
					}
					printCode($$->getCode());
				}
 		 		;
 		 
type_specifier	: INT 	
				{ 
					printRule("type_specifier","INT"); 
					$$ = new Node();
					$$->setCode("int"); 
					printCode($$->getCode());
				}
				| FLOAT
				{
					printRule("type_specifier","FLOAT"); 
					$$ = new Node();
					$$->setCode("float"); 
					printCode($$->getCode());
				}
				| VOID
				{
					printRule("type_specifier","VOID"); 
					$$ = new Node();
					$$->setCode("void"); 
					printCode($$->getCode());
				}
				;
 		
declaration_list 	: declaration_list COMMA ID
					{
						printRule("declaration_list","declaration_list COMMA ID");
						$$ = new Node();
						$$->setCode($1->getCode()+","+$3->getName());
						$$->setList($1->getList());
						$$->getList().push_back($3);
						printCode($$->getCode());
					}
					| declaration_list error COMMA ID
					{
						printRule("declaration_list","declaration_list COMMA ID");
						$$ = new Node();
						$$->setCode($1->getCode()+","+$4->getName());
						$$->setList($1->getList());
						$$->getList().push_back($4);
						printCode($$->getCode());
					}
					| declaration_list COMMA ID LTHIRD CONST_INT RTHIRD
					{
						printRule("declaration_list","declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
						$$ = new Node();
						$$->setCode($1->getCode()+","+$3->getName()+"["+$5->getName()+"]");
						$$->setList($1->getList());
						$$->getList().push_back($3);
						printCode($$->getCode());
					}
					| declaration_list error COMMA ID LTHIRD CONST_INT RTHIRD
					{
						printRule("declaration_list","declaration_list COMMA ID LTHIRD CONST_INT RTHIRD");
						$$ = new Node();
						$$->setCode($1->getCode()+","+$4->getName()+"["+$6->getName()+"]");
						$$->setList($1->getList());
						$$->getList().push_back($4);
						printCode($$->getCode());
					}
					| ID 
					{ 
						printRule("declaration_list","ID"); 
						$$ = new Node();
						$$->setCode($1->getName());
						$$->getList().push_back($1);
						printCode($$->getCode());
					}
					| ID LTHIRD CONST_INT RTHIRD
					{
						printRule("declaration_list","ID LTHIRD CONST_INT RTHIRD");
						$$ = new Node();
						$$->setCode($1->getName()+"["+$3->getName()+"]");
						$$->getList().push_back($1);
						printCode($$->getCode());
					}
					;
 		  
statements 	: statement
			{
				printRule("statements","statement");
				$$ = new Node();
            	$$->setCode($1->getCode());
            	printCode($$->getCode());
			}
	   		| statements statement
	   		{
				printRule("statements","statements statement");
				$$ = new Node();
				$$->setCode($1->getCode() + "\n" + $2->getCode());
				printCode($$->getCode());
	   		}
			| statements error statement
			{
				printRule("statements","statements statement");
				$$ = new Node();
				$$->setCode($1->getCode() + "\n" + $3->getCode());
				printCode($$->getCode());
			}
	   		;
	   
statement 	: var_declaration
			{
				printRule("statement","var_declaration");
				$$ = new Node();
            	$$->setCode($1->getCode());
            	printCode($$->getCode()); 
			}
			| expression_statement
			{
				printRule("statement","expression_statement");
				$$ = new Node();
            	$$->setCode($1->getCode());
            	printCode($$->getCode()); 
			}
			| compound_statement
			{
				printRule("statement","compound_statement");
				$$ = new Node();
            	$$->setCode($1->getCode());
            	printCode($$->getCode()); 
			}
			| FOR LPAREN expression_statement expression_statement expression RPAREN statement
			{
				printRule("statement","FOR LPAREN expression_statement expression_statement expression RPAREN statement");
				$$ = new Node();
            	$$->setCode(
					"for("+$3->getCode()+
					$4->getCode()+$5->getCode()+
					")"+$7->getCode()
				);
            	printCode($$->getCode()); 
			}
			| IF LPAREN expression RPAREN statement %prec LOWER_THAN_ELSE
			{
				printRule("statement","IF LPAREN expression RPAREN statement");
				$$ = new Node();
            	$$->setCode("if("+$3->getCode()+")"+$5->getCode());
            	printCode($$->getCode()); 
			}
			| IF LPAREN expression RPAREN statement ELSE statement
			{
				printRule("statement","IF LPAREN expression RPAREN statement ELSE statement");
				$$ = new Node();
            	$$->setCode(
					"if("+$3->getCode()+")"+
					$5->getCode()+"\nelse "+
					$7->getCode()
				);
            	printCode($$->getCode()); 
			}
			| WHILE LPAREN expression RPAREN statement
			{
				printRule("statement","WHILE LPAREN expression RPAREN statement");
				$$ = new Node();
            	$$->setCode("while("+$3->getCode()+")"+$5->getCode());
            	printCode($$->getCode()); 
			}
			| PRINTLN LPAREN ID RPAREN SEMICOLON
			{
				printRule("statement","PRINTLN LPAREN ID RPAREN SEMICOLON");
				$$ = new Node();
            	$$->setCode("printf("+$3->getName()+");");
            	printCode($$->getCode()); 
			}
			| RETURN expression SEMICOLON
			{
				printRule("statement","RETURN expression SEMICOLON");
				$$ = new Node();
            	$$->setCode("return "+$2->getCode()+";");
            	printCode($$->getCode()); 
			}
			;
	  
expression_statement 	: SEMICOLON		
						{
							printRule("expression_statement","SEMICOLON");
							$$ = new Node();
							$$->setCode(";");
							printCode($$->getCode());
						}	
						| expression SEMICOLON 
						{
							printRule("expression_statement","expression SEMICOLON");
							$$ = new Node();
							$$->setCode($1->getCode()+";");
							printCode($$->getCode());
						}
						;
	  
variable 	: ID 		
			{
				printRule("variable","ID");
				$$ = new Node();
            	$$->setCode($1->getName());
            	printCode($$->getCode());
			}
			| ID LTHIRD expression RTHIRD 
			{
				printRule("variable","ID LTHIRD expression RTHIRD");
				$$ = new Node();
            	$$->setCode($1->getName()+"["+$3->getCode()+"]");
            	printCode($$->getCode());
			}
	 		;
	 
 expression : logic_expression	
			{
				printRule("expression","logic_expression");
				$$ = new Node();
				$$->setCode($1->getCode());
				printCode($$->getCode());
			}
			| variable ASSIGNOP logic_expression 
			{
				printRule("expression","variable ASSIGNOP logic_expression");
				$$ = new Node();
				$$->setCode($1->getCode()+"="+$3->getCode());
				printCode($$->getCode());
			}	
			;
			
logic_expression 	: rel_expression 	
					{
						printRule("logic_expression","rel_expression");
						$$ = new Node();
						$$->setCode($1->getCode());
						printCode($$->getCode());
					}
					| rel_expression LOGICOP rel_expression 	
					{
						printRule("logic_expression","rel_expression LOGICOP rel_expression");
						$$ = new Node();
						$$->setCode($1->getCode()+$2->getName()+$3->getCode());
						printCode($$->getCode());
					}
					;
			
rel_expression	: simple_expression 
				{
					printRule("rel_expression","simple_expression");
					$$ = new Node();
					$$->setCode($1->getCode());
					printCode($$->getCode());
				}
				| simple_expression RELOP simple_expression	
				{
					printRule("rel_expression","simple_expression RELOP simple_expression");
					$$ = new Node();
					$$->setCode($1->getCode()+$2->getName()+$3->getCode());
					printCode($$->getCode());
				}
				;
				
simple_expression 	: term 
					{
						printRule("simple_expression","term");
						$$ = new Node();
						$$->setCode($1->getCode());
						printCode($$->getCode());
					}
					| simple_expression ADDOP term 
					{
						printRule("simple_expression","simple_expression ADDOP term");
						$$ = new Node();
						$$->setCode($1->getCode()+$2->getName()+$3->getCode());
						printCode($$->getCode());
					}
					;
					
term 	:	unary_expression
		{
			printRule("term","unary_expression");
			$$ = new Node();
			$$->setCode($1->getCode());
			printCode($$->getCode());
		}
		|  term MULOP unary_expression
		{
			printRule("term","term MULOP unary_expression");
			$$ = new Node();
			$$->setCode($1->getCode()+$2->getName()+$3->getCode());
			printCode($$->getCode());
		}
		;

unary_expression 	: ADDOP unary_expression
					{ 
						printRule("unary_expression","ADDOP unary_expression");
						$$ = new Node();
						$$->setCode($1->getName()+$2->getCode());
						printCode($$->getCode());
					}  
					| NOT unary_expression 
					{
						printRule("unary_expression","NOT unary_expression");
						$$ = new Node();
						$$->setCode("!"+$2->getCode());
						printCode($$->getCode());
					}
					| factor 
					{
						printRule("unary_expression","factor");
						$$ = new Node();
						$$->setCode($1->getCode());
						printCode($$->getCode());
					}
					;
	
factor	: variable 
		{
			printRule("factor","variable");
			$$ = new Node();
			$$->setCode($1->getCode());
			printCode($$->getCode());
		}
		| ID LPAREN argument_list RPAREN
		{
			printRule("factor","ID LPAREN argument_list RPAREN");
			$$ = new Node();
			$$->setCode($1->getName()+"("+$3->getCode()+")");
			printCode($$->getCode());
		}
		| LPAREN expression RPAREN
		{
			printRule("factor","LPAREN expression RPAREN");
			$$ = new Node();
			$$->setCode("("+$2->getCode()+")");
			printCode($$->getCode());
		}
		| CONST_INT 
		{
			printRule("factor","CONST_INT");
			$$ = new Node();
			$$->setCode($1->getName());
			printCode($$->getCode());
		}
		| CONST_FLOAT
		{
			printRule("factor","CONST_FLOAT");
			$$ = new Node();
			$$->setCode($1->getName());
			printCode($$->getCode());
		}
		| variable INCOP 
		{
			printRule("factor","variable INCOP");
			$$ = new Node();
            $$->setCode($1->getCode()+"++");
            printCode($$->getCode());
		}
		| variable DECOP
		{
			printRule("factor","variable DECOP");
			$$ = new Node();
            $$->setCode($1->getCode()+"--");
            printCode($$->getCode());
		}
		;
	
argument_list 	: arguments
				{
					printRule("argument_list","arguments");
					$$ = new Node();
                    $$->setCode($1->getCode());
                    printCode($$->getCode());
				}
			  	| 
				{ 
					printRule("argument_list","");	
					$$ = new Node();		
				}
			  	;
	
arguments 	: arguments COMMA logic_expression
			{
				printRule("arguments","arguments COMMA logic_expression");
				$$ = new Node();
                $$->setCode($1->getCode()+","+$3->getCode()); 
                printCode($$->getCode());
			}
			| logic_expression
			{
				printRule("arguments","logic_expression");
				$$ = new Node();
                $$->setCode($1->getCode()); 
                printCode($$->getCode());
			}
			;
 

%%
int main(int argc,char *argv[]){
	if (argc != 2)
    {
        printf("Please provide input file name and try again\n");
        return 0;
    }

    FILE *fin = fopen(argv[1], "r");
    if (fin == NULL)
    {
        printf("Cannot open specified file\n");
        return 0;
    }

    errout.open("1905072_error.txt");
    logout.open("1905072_log.txt");
	tokenout.open("1905072_token.txt");

	table = new SymbolTable(7,sdbmHash);
    yyin = fin;
    line_count = yylineno = 1;
	error_count = 0;
    yyparse();
    fclose(yyin);

    table->printAllScope();

    logout << "Total lines: " << yylineno << endl;
    logout << "Total errors: " << error_count;

    errout.close();
    logout.close();
	tokenout.close();

    return EXIT_SUCCESS;
}


