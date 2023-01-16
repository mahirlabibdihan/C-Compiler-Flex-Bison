bison -d -y src/parser.y
mv y.tab.c src/
mv y.tab.h include/
echo 'Generated the parser C file as well the header file'
g++ -w -c -o build/parser.o src/y.tab.c
echo 'Generated the parser object file'
flex -o src/scanner.c src/scanner.l
echo 'Generated the scanner C file'
g++ -w -c -o build/scanner.o src/scanner.c
# if the above command doesn't work try g++ -fpermissive -w -c -o l.o lex.yy.c
echo 'Generated the scanner object file'
g++ src/*.cpp -c
mv *.o build/
echo 'Generated the symbol table object files'
g++ -g build/*.o -lfl -o bin/main.exe 
echo 'All ready, running'
./bin/main.exe io/input.txt
rm build/*
rm src/y.tab.c src/scanner.c include/y.tab.h
