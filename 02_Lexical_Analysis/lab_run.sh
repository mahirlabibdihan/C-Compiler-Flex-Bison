cd upload/1905072
flex -o scanner.c 1905072.l
g++ *.cpp scanner.c -lfl -o scanner.exe
./scanner.exe ../../io/input.txt

cd ../../