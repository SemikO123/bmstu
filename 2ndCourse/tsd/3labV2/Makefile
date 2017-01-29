CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic 

ifeq ($(mode), debug)
	FLAGS += -g3
endif

ifeq ($(mode), release)
	FLAGS += -DNDEBUG -g0
endif

3lab.o : 3lab.c 
	$(CC) $(FLAGS) -c 3lab.c 

3lab.exe : 3lab.o 
	$(CC) -o 3lab.exe 3lab.o 


st: 3lab.exe
	./3lab.exe