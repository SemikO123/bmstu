CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic

5lab.exe : 5lab.o my_snprintf.o
	$(CC) -o 5lab.exe 5lab.o my_snprintf.o

5lab.o : 5lab.c my_snprintf.h
	$(CC) $(FLAGS) -c 5lab.c

my_snprintf.o : my_snprintf.c my_snprintf.h
	$(CC) $(FLAGS) -c my_snprintf.c

st : 5lab.exe
	./5lab.exe

rm :
	rm *.exe *.o