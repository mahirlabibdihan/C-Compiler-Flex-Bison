# **C Compiler (Bison+Flex)**

Preprocessor: `source.c` &rarr; `source.i`
**Compiler: `source.i` &rarr; `source.asm`**
Assembler: `source.asm` &rarr; `source.exe`

## Demo

Youtube: https://youtu.be/E7yGnD405UM?si=MQiZXQOHkM-sjeWF

https://user-images.githubusercontent.com/62663759/220677637-45c0c1f6-6a7d-403d-a189-6154b872da3e.mp4


<!-- 
<video width="900">
  <source src="demo.mp4" type="video/mp4">
</video>
 -->
 
## Compiler basics

- **Pattern:** Regex describing all the lexemes that can represent a particular token in source language
- **Lexeme:** Sequence of characters in the source program that matches the pattern for a token
- **Token:** Terminal symbols of the source language
<!-- ## Limitations
- Keywords
  - break
  - continue
  - do
  - switch
  - case
  - default
- Limited syntax error recovery -->

## AST Nodes

<img align="center" alt="Mahir Labib Dihan's LinkdeIn"  src="AST_Node.png" />

## Classes

- **SymbolInfo:** Holds the details of a symbol
- **ScopeTable:** Keeps track of the declared identifier in a scope
- **SymbolTable:** Keeps track of the scopes
- **ErrorHandler:** Prints out errors
- **Scanner:** Converts input C code to a list of tokens
- **Logger:** Prints out log output
- **Parser:** Creates Abstract Syntax Tree using given cfg and tokens from scanner
- **Tokenizer:** Creates token from a lexeme
- **LexicalAnalyzer:** Converts input C code to stream of tokens
- **SyntaxAnalyzer:** Checks if the grammar is syntactically correct
- **SemanticAnalyzer:** Checks if the grammar is semantically correct
- **AssemblyGenerator:** Converts the C code to Intel 8086 Assembly code
- **Optimizer:** Peephole optimization of the generated assembly code
- **CommentGenerator:** Documentation
- **ASTGenerator:** AST Printer
- **CodeGenerator:** AST to C converter
<!-- ## Variants of symbols
- Terminal
  - Identifier
    - Variable - Array
      - Function
- NonTerminal - Expression - ArrayCall - List - ParameterList - ArgumentList - DeclarationList - Block - if - if-else - for - while -->

## Workflow

<img align="center" alt="Mahir Labib Dihan's LinkdeIn"  src="Workflow.png" />

## Tools

- flex 2.6.4
- bison 3.8.2
