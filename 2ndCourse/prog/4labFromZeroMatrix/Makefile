CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic

matrix.exe : matrix.o #functions.o
	$(CC) -o matrix.exe matrix.o

matrix.o : matrix.c #functions.c #functions.h
	$(CC) $(FLAGS) -c matrix.c 

st1 : matrix.exe
	./matrix.exe 1.txt 2.txt + result.txt

st2 : matrix.exe
	./matrix.exe 1.txt 2.txt x result.txt

st3 : matrix.exe
	./matrix.exe 1.txt 2.txt - result.txt

rm :
	rm *.exe *.o
