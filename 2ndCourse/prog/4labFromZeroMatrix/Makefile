CC := gcc 
FLAGS := -std=c99 -Wall -lm -Werror -pedantic

matrix.exe : matrix.o functions.o
	$(CC) -o matrix.exe matrix.o functions.o

tests.exe : tests.o functions.o
	$(CC) -lm -o tests.exe tests.o functions.o

matrix.o : matrix.c functions.c functions.h
	$(CC) $(FLAGS) -c matrix.c 

functions.o : functions.c functions.h
	$(CC) $(FLAGS) -c functions.c

tests.o : tests.c functions.c functions.h
	$(CC) $(FLAGS) -c tests.c

st1 : matrix.exe
	./matrix.exe 1.txt 2.txt + result.txt

st2 : matrix.exe
	./matrix.exe 1.txt 2.txt x result.txt

st3 : matrix.exe
	./matrix.exe 1.txt 2.txt - result.txt

tests : tests.exe
	./tests.exe

rm :
	rm *.exe *.o
