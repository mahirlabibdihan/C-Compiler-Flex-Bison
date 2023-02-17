#!/bin/bash
#From Ashrafur Rahman

rm upload/1905072 -r
mkdir upload/1905072

cp print.asm upload/1905072/ -r
cp src/*.cpp src/*.l src/*.y upload/1905072/ -r
cp include/*.hpp upload/1905072/ -r
python3.9 rename.py

cd upload
rm *.zip
7z a 1905072.zip 1905072/