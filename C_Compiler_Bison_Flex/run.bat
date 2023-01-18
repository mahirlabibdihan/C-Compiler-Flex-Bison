bison -d -y -v -Wnone 1905072_parser.y
@REM echo 'Generated the parser C file as well the header file'
g++ -std=c++17 -w -c -o parser.o y.tab.c
@REM echo 'Generated the parser object file'
flex 1905072_scanner.l
@REM echo 'Generated the scanner C file'
g++ -std=gnu++11 -w -c -o scanner.o lex.yy.c
@REM # if the above command doesn't work try g++ -fpermissive -w -c -o l.o lex.yy.c
@REM echo 'Generated the scanner object file'
g++ -std=c++17 1905072_SymbolInfo.cpp 1905072_ScopeTable.cpp 1905072_SymbolTable.cpp 1905072_Helper.cpp 1905072_Logger.cpp 1905072_Tokenizer.cpp 1905072_Error_Handler.cpp 1905072_Semantic_Analyzer.cpp 1905072_Assembly_Generator.cpp 1905072_Symbol_Extended.cpp 1905072_main.cpp 1905072_Optimizer.cpp -c
@REM echo 'Generated the symbol table object files'
g++ -std=c++17 1905072_SymbolInfo.o 1905072_ScopeTable.o 1905072_SymbolTable.o 1905072_Helper.o  1905072_Logger.o 1905072_Symbol_Extended.o 1905072_Error_Handler.o parser.o scanner.o 1905072_Semantic_Analyzer.o 1905072_Tokenizer.o 1905072_Assembly_Generator.o 1905072_main.o 1905072_Optimizer.o -o main.exe
@REM echo 'All ready, running'
main.exe input.c
