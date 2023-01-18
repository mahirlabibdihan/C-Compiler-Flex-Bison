

fin?=io/input.txt
OBJECTS=build/SymbolInfo.o build/ScopeTable.o build/SymbolTable.o build/Util.o build/Logger.o build/ErrorHandler.o build/Tokenizer.o build/LexicalAnalyzer.o build/LineTracker.o build/main.o

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
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS) $(OBJDIR)scanner.o

build: $(OBJECTS) $(OBJDIR)scanner.o

$(OBJDIR)scanner.o: $(OBJDIR)scanner.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)scanner.c: $(SRCDIR)scanner.l
	flex -o $@ $<
	

$(OBJDIR)%.o: $(SRCDIR)%.cpp $(INCDIR)%.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJDIR)main.o: $(SRCDIR)main.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm $(OBJDIR)*.o $(BINDIR)*.exe
