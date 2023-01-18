#!/bin/bash
#From Ashrafur Rahman

rm upload/1905072 -r
mkdir upload/1905072

cp src/ upload/1905072/ -r
cp include/ upload/1905072/ -r

cd upload
cd 1905072/
python3 ../../rename.py
cd ..

rm 1905072.zip
7z a 1905072.zip 1905072/