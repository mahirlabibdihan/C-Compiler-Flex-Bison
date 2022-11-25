
fin?=io/input.txt
fout?=io/output.txt
OBJECTS=build/1905072_SymbolInfo.o build/1905072_ScopeTable.o build/1905072_SymbolTable.o build/1905072_Util.o build/1905072_main.o

CXX = g++
CXXFLAGS = -std=c++17 -O9
SRCDIR = src/
OBJDIR = build/
BINDIR = bin/
INCDIR = include/

.PHONY: all clean

all: build run

run: $(BINDIR)main.exe
	$< $(fin) ${fout}

build: $(OBJECTS) 

$(BINDIR)main.exe:
	$(CXX) $(CXXFLAGS) -o $@ $^
	
$(OBJDIR)%.o: $(SRCDIR)%.cpp $(INCDIR)%.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)1905072_main.o: $(SRCDIR)1905072_main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm $(OBJDIR)*.o
