

fin?=io/input.txt
OBJECTS=build/SymbolInfo.o build/ScopeTable.o build/SymbolTable.o build/Util.o build/Logger.o build/ErrorHandler.o build/Tokenizer.o build/LexicalAnalyzer.o build/LineTracker.o build/SemanticAnalyzer.o build/ParseTreeGenerator.o build/ExtendedSymbol.o build/main.o

CXX = g++
CXXFLAGS = -std=c++17 -O9
SRCDIR = src/
OBJDIR = build/
BINDIR = bin/
INCDIR = include/

.PHONY: all clean

all: build run

run: $(BINDIR)main.exe
	$< $(fin)

$(BINDIR)main.exe: build
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) $(OBJDIR)scanner.o $(OBJDIR)parser.o

build: $(OBJDIR)parser.o $(OBJDIR)scanner.o $(OBJECTS) 

$(OBJDIR)scanner.o: $(OBJDIR)scanner.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)scanner.c: $(SRCDIR)scanner.l
	flex -o $@ $<

$(OBJDIR)parser.o: $(OBJDIR)parser.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)parser.c: $(SRCDIR)parser.y
	bison -d -y -Wcounterexamples -Wother -Wconflicts-sr -Wno-yacc $<
	mv y.tab.c $(OBJDIR)parser.c
	mv y.tab.h $(INCDIR)

$(OBJDIR)%.o: $(SRCDIR)%.cpp $(INCDIR)%.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)main.o: $(SRCDIR)main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm $(OBJDIR)* $(BINDIR)*
