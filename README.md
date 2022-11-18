# **C Compiler (Bison+Flex)**

Preprocessor: `source.c` &rarr; `source.i`
**Compiler: `source.i` &rarr; `source.asm`**
Assembler: `source.asm` &rarr; `source.exe`
## Compiler basics
- **Pattern:** Regex describing all the lexemes that can represent a particular token in source language
- **Lexeme:** Sequence of characters in the source program that matches the pattern for a token
- **Token:** Terminal symbols of the source language
## Limitations
- Keywords
  - break
  - continue
  - do
  - switch
  - case
  - default
- Limited syntax error recovery


## Classes Introduction

- **SymbolInfo:** Holds the details of a symbol
- **ScopeTable:** Keeps track of the declared identifier in a scope
- **SymbolTable:** Keeps track of the scopes
- **ErrorHandler:** Prints out errors
- **Scanner:** Converts input C code to a list of tokens
- **Parser:** Creates Abstract Syntax Tree using given cfg and tokens from scanner
- **Tokenizer:** Creates token from a lexeme
- **Logger:** Prints out log output
- **SemanticAnalyzer:** Checks if the grammar is semantically correct
- **AssemblyGenerator:** Converts the C code to Intel 8086 Assembly code
- **Optimizer:** Peephole optimization of the generated assembly code

## Variants of symbols
- Terminal
	- Identifier
		- Variable
    		- Array
     	- Function
- NonTerminal
  	- Expression
    	- ArrayCall
  	- List
     	- ParameterList
     	- ArgumentList
     	- DeclarationList
  	- Block
     	- if
     	- if-else
     	- for
     	- while