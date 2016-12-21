CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic

rk.exe : rk.o func.o
	$(CC) -o  rk.exe rk.o func.o

rk.o : rk.c func.h
	$(CC) $(FLAGS) -c rk.c func.h

func.o : func.c func.h
	$(CC) $(FLAGS) -c func.c func.h

