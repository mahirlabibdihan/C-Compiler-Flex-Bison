
fin?=io/input.txt
fout?=io/output.txt
OBJECTS=obj/1905072_SymbolInfo.o obj/1905072_ScopeTable.o obj/1905072_SymbolTable.o obj/1905072_Util.o obj/1905072_main.o

CXX = g++
CXXFLAGS = -std=c++17 -O9
SRCDIR = src/
OBJDIR = obj/
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
