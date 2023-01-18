#!/bin/bash

bison -d -y -v -Wno-yacc -Wnone 1905072_parser.y
echo 'Generated the parser C file as well the header file'
g++ -w -c -o parser.o y.tab.c
echo 'Generated the parser object file'
flex -o scanner.c 1905072_scanner.l
echo 'Generated the scanner C file'
g++ -w -c -o scanner.o scanner.c
# if the above command doesn't work try g++ -fpermissive -w -c -o l.o lex.yy.c
echo 'Generated the scanner object file'
g++ 1905072_SymbolInfo.cpp 1905072_ScopeTable.cpp 1905072_SymbolTable.cpp 1905072_Helper.cpp 1905072_Logger.cpp 1905072_Error_Handler.cpp 1905072_Semantic_Analyzer.cpp 1905072_Assembly_Generator.cpp 1905072_Tokenizer.cpp 1905072_Symbol_Extended.cpp 1905072_main.cpp 1905072_Optimizer.cpp -c
echo 'Generated the symbol table object files'
g++ 1905072_SymbolInfo.o 1905072_ScopeTable.o 1905072_SymbolTable.o 1905072_Helper.o  1905072_Logger.o 1905072_Symbol_Extended.o 1905072_Error_Handler.o parser.o scanner.o 1905072_Semantic_Analyzer.o 1905072_Assembly_Generator.o 1905072_Tokenizer.o 1905072_main.o 1905072_Optimizer.o -lfl -o main.out
echo 'All ready, running'
./main.out input.c && rm *.o scanner.c y.tab.c y.tab.h
