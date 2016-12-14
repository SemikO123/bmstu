CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic

5lab.exe : 5lab.o #functions.o
	$(CC) -o 5lab.exe 5lab.o #functions.o

5lab.o : 5lab.c
	$(CC) $(FLAGS) -c 5lab.c

st : 5lab.exe
	./5lab.exe

rm :
	rm *.exe *.o