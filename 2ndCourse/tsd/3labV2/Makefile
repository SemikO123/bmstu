CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic 

ifeq ($(mode), debug)
	FLAGS += -g3
endif

ifeq ($(mode), release)
	FLAGS += -DNDEBUG -g0
endif

3lab.o : 3lab.c functions.h structurs.h
	$(CC) $(FLAGS) -c 3lab.c 

functions.o : functions.c functions.h structurs.h
	$(CC) $(FLAGS) -c functions.c

3lab.exe : 3lab.o functions.o
	$(CC) -o 3lab.exe 3lab.o functions.o


st: 3lab.exe
	./3lab.exe