rm upload/1905072 -r
mkdir upload/1905072

cp print.asm upload/1905072/ -r
cp src/*.cpp upload/1905072/ -r
cp src/*.l upload/1905072/ -r
cp src/*.y upload/1905072/ -r
cp include/*.hpp upload/1905072/ -r
python rename.py

cd upload
rm *.zip