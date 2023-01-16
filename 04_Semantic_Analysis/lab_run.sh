cd upload/1905072

bison -d -y -Wnone 1905072.y
g++ -w -c -o parser.o y.tab.c
flex -o scanner.c 1905072.l
g++ -w -c -o scanner.o scanner.c
g++ *.cpp -c
g++ *.o -lfl -o main.exe
./main.exe ../../io/input.txt

rm y.tab.c y.tab.h *.o
cd ../../