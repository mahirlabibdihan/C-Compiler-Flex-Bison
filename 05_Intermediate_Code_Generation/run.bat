flex src/scanner.l
mv lex.yy.c build/
g++ -std=gnu++11 -w -c -o build/scanner.o build/lex.yy.c
g++ -std=c++17 src/*.cpp build/scanner.o -o bin/scanner
"bin/scanner.exe" io/input.txt