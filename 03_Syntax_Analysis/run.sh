#!/bin/bash

bison -d -y -v -Wnone 1905072_parser.y
echo 'Generated the parser C file as well the header file'
g++ -w -c -o parser.o y.tab.c
echo 'Generated the parser object file'
flex -o scanner.c 1905072_scanner.l
echo 'Generated the scanner C file'
g++ -w -c -o scanner.o scanner.c
# if the above command doesn't work try g++ -fpermissive -w -c -o l.o lex.yy.c
echo 'Generated the scanner object file'
g++ 1905072_Node.cpp ../01_Symbol_Table/1905072_SymbolInfo.cpp ../01_Symbol_Table/1905072_ScopeTable.cpp ../01_Symbol_Table/1905072_SymbolTable.cpp 1905072_Helper.cpp 1905072_Logger.cpp 1905072_Tokenizer.cpp 1905072_Error_Handler.cpp  -c
echo 'Generated the symbol table object files'
g++ 1905072_SymbolInfo.o 1905072_ScopeTable.o 1905072_SymbolTable.o 1905072_Helper.o 1905072_Node.o 1905072_Logger.o 1905072_Tokenizer.o 1905072_Error_Handler.o parser.o scanner.o -lfl -o main.out
echo 'All ready, running'
./main.out input.txt && rm *.o
