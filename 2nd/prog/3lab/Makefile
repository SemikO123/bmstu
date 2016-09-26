CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	FLAGS += -g3
endif

ifeq ($(mode), release)
	FLAGS += -DNDEBUG -g0
endif

3lab.exe : 3lab.o functions.h
	$(CC) -o 3lab.exe 3lab.o functions.h

3lab.o : 3lab.c
	$(CC) $(FLAGS) -c 3lab.c

st : 3lab.exe
	./3lab.exe input.txt output.txt 6

vlgr : 3lab.exe
	valgrind --tool=memcheck ./3lab.exe input.txt output.txt 6

rm : 
	rm *.exe *.o
