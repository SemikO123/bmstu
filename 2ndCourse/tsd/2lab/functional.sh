#!/bin/bash
./2lab.exe < tests/in1.txt > tests/out1.txt
echo -e '\e[31m     10 elements\e[0m'
head -n 2 tests/out1.txt | tail -n 1
head -n 7 tests/out1.txt | tail -n 1
head -n 21 tests/out1.txt | tail -n 1
head -n 28 tests/out1.txt | tail -n 1

./2lab.exe < tests/in2.txt > tests/out2.txt
echo -e '\e[31m     100 elements\e[0m'
head -n 2 tests/out2.txt | tail -n 1
head -n 7 tests/out2.txt | tail -n 1
head -n 111 tests/out2.txt | tail -n 1
head -n 116 tests/out2.txt | tail -n 1

./2lab.exe < tests/in3.txt > tests/out3.txt
echo -e '\e[31m     1000 elements\e[0m'
head -n 2 tests/out3.txt | tail -n 1
head -n 7 tests/out3.txt | tail -n 1
head -n 1011 tests/out3.txt | tail -n 1
head -n 1016 tests/out3.txt | tail -n 1