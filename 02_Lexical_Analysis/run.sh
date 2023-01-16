flex -o build/scanner.c src/scanner.l
echo 'Generated the scanner C file'
g++ src/*.cpp build/scanner.c -lfl -o bin/scanner.exe
echo 'Generated executable file'
bin/scanner.exe io/input.txt
echo 'Generated token.txt log.txt'


# flex -o build/scanner.c 1905072.l
# g++ *.cpp *.c -lfl -o scanner.exe
# bin/scanner.exe io/input.txt