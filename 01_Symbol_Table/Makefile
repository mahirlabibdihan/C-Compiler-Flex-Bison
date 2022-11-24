
fin?=input.txt
fout?=output.txt

all: run

run: main.exe
	main.exe $(fin) ${fout}

main.exe: 1905072_SymbolInfo.o 1905072_ScopeTable.o 1905072_SymbolTable.o 1905072_main.o
	g++ -std=c++17 1905072_SymbolInfo.o 1905072_ScopeTable.o 1905072_SymbolTable.o 1905072_main.o -o main.exe

1905072_SymbolInfo.o: 1905072_SymbolInfo.cpp 1905072_SymbolInfo.hpp
	g++ -std=c++17 1905072_SymbolInfo.cpp -c

1905072_ScopeTable.o: 1905072_ScopeTable.cpp 1905072_ScopeTable.hpp
	g++ -std=c++17 1905072_ScopeTable.cpp -c

1905072_SymbolTable.o: 1905072_SymbolTable.cpp 1905072_SymbolTable.hpp
	g++ -std=c++17 1905072_SymbolTable.cpp -c

1905072_main.o: 1905072_main.cpp
	g++ -std=c++17 1905072_main.cpp -c

clean:
	rm *.o