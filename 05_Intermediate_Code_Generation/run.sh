bison -Wyacc -d -y -Wcounterexamples -Wother -Wconflicts-sr  -Wno-yacc src/parser.y
mv y.tab.c src/
mv y.tab.h include/
echo 'Generated the parser C file as well the header file'
g++ -w -c -o build/parser.o src/y.tab.c
echo 'Generated the parser object file'
flex -o src/scanner.c src/scanner.l
echo 'Generated the scanner C file'
g++ -w -c -o build/scanner.o src/scanner.c
echo 'Generated the scanner object file'
g++ src/*.cpp -c
mv *.o build/
echo 'Generated the object files'
g++ -g build/*.o -o bin/main.exe 
echo 'All ready, running'
./bin/main.exe io/input.txt
rm build/*
rm src/y.tab.c src/scanner.c include/y.tab.h
