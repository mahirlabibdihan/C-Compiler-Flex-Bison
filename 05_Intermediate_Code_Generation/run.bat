bison -d -y src/parser.y
mv y.tab.c src/parser.c
mv y.tab.h include/
echo 'Generated the parser C file as well the header file'
g++ -w -c -o build/parser.o src/parser.c
echo 'Generated the parser object file'
flex src/scanner.l
mv lex.yy.c src/scanner.c
echo 'Generated the scanner C file'
g++ -w -c -o build/scanner.o src/scanner.c
echo 'Generated the scanner object file'
g++ src/*.cpp -c
mv *.o build/
echo 'Generated the object files'
g++ -g build/*.o -o bin/main.exe 
echo 'All ready, running'
"bin/main.exe" io/input.txt
rm build/*
rm src/parser.c src/scanner.c include/y.tab.h
