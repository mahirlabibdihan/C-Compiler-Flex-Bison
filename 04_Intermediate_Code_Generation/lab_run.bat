cd upload/1905072
bison -d -y 1905072.y
mv y.tab.c parser.c
echo 'Generated the parser C file as well the header file'
g++ -w -c -o parser.o parser.c
echo 'Generated the parser object file'
flex 1905072.l
mv lex.yy.c scanner.c
echo 'Generated the scanner C file'
g++ -w -c -o scanner.o scanner.c
echo 'Generated the scanner object file'
g++ *.cpp -c
echo 'Generated the object files'
g++ -g *.o -o main.exe 
echo 'All ready, running'
main.exe ../../io/input.txt
