bison -d -y -v -Wnone 1905072_parser.y
@REM echo 'Generated the parser C file as well the header file'
g++ -std=c++17 -w -c -o parser.o y.tab.c
@REM echo 'Generated the parser object file'
flex 1905072_scanner.l
@REM echo 'Generated the scanner C file'
g++ -std=gnu++11 -w -c -o scanner.o lex.yy.c
@REM # if the above command doesn't work try g++ -fpermissive -w -c -o l.o lex.yy.c
@REM echo 'Generated the scanner object file'
g++ -std=c++17 *.cpp  -c
@REM echo 'Generated the symbol table object files'
g++ -std=c++17 *.o  -o main.exe
@REM echo 'All ready, running'
main.exe input.txt
