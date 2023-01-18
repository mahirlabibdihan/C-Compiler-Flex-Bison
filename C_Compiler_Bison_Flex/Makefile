
file?=input.c

all: run

run: main.exe
	main.exe $(file)

main.exe: parser.o scanner.o 1905072_SymbolInfo.o 1905072_ScopeTable.o 1905072_SymbolTable.o 1905072_Helper.o 1905072_Logger.o 1905072_Symbol_Extended.o 1905072_Error_Handler.o 1905072_Semantic_Analyzer.o  1905072_Assembly_Generator.o 1905072_Tokenizer.o 1905072_Optimizer.o 1905072_main.o
	g++ -std=c++17 1905072_SymbolInfo.o 1905072_ScopeTable.o 1905072_SymbolTable.o 1905072_Helper.o  1905072_Logger.o 1905072_Symbol_Extended.o 1905072_Error_Handler.o parser.o scanner.o 1905072_Semantic_Analyzer.o 1905072_Tokenizer.o 1905072_Assembly_Generator.o 1905072_main.o 1905072_Optimizer.o -o main.exe

parser.o: y.tab.c
	g++ -std=c++17 -w -c -o parser.o y.tab.c

y.tab.c: 1905072_parser.y
	bison -d -y -v -Wnone 1905072_parser.y

scanner.o: lex.yy.c
	g++ -std=gnu++11 -w -c -o scanner.o lex.yy.c

lex.yy.c:
	flex 1905072_scanner.l

1905072_SymbolInfo.o: 1905072_SymbolInfo.cpp 1905072_SymbolInfo.hpp
	g++ -std=c++17 1905072_SymbolInfo.cpp -c

1905072_ScopeTable.o: 1905072_ScopeTable.cpp 1905072_ScopeTable.hpp
	g++ -std=c++17 1905072_ScopeTable.cpp -c

1905072_SymbolTable.o: 1905072_SymbolTable.cpp 1905072_SymbolTable.hpp
	g++ -std=c++17 1905072_SymbolTable.cpp -c

1905072_Helper.o: 1905072_Helper.cpp 1905072_Helper.hpp
	g++ -std=c++17 1905072_Helper.cpp -c

1905072_Logger.o: 1905072_Logger.cpp 1905072_Logger.hpp
	g++ -std=c++17 1905072_Logger.cpp -c

1905072_Symbol_Extended.o: 1905072_Symbol_Extended.cpp 1905072_Symbol_Extended.hpp
	g++ -std=c++17 1905072_Symbol_Extended.cpp -c

1905072_Error_Handler.o: 1905072_Error_Handler.cpp 1905072_Error_Handler.hpp
	g++ -std=c++17 1905072_Error_Handler.cpp -c

1905072_Semantic_Analyzer.o: 1905072_Semantic_Analyzer.cpp 1905072_Semantic_Analyzer.hpp
	g++ -std=c++17 1905072_Semantic_Analyzer.cpp -c

1905072_Assembly_Generator.o: 1905072_Assembly_Generator.cpp 1905072_Assembly_Generator.hpp
	g++ -std=c++17 1905072_Assembly_Generator.cpp -c
	
1905072_Tokenizer.o: 1905072_Tokenizer.cpp 1905072_Tokenizer.hpp
	g++ -std=c++17 1905072_Tokenizer.cpp -c
	
1905072_Optimizer.o: 1905072_Optimizer.cpp 1905072_Optimizer.hpp
	g++ -std=c++17 1905072_Optimizer.cpp -c

1905072_main.o: 1905072_main.cpp
	g++ -std=c++17 1905072_main.cpp -c

clean:
	rm *.o lex.yy.c y.tab.c y.tab.hpp