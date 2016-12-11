CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic 

ifeq ($(mode), debug)
	FLAGS += -g6
endif

ifeq ($(mode), release)
	FLAGS += -DNDEBUG -g0
endif

8lab.exe : 8lab.o #functions.o
	$(CC) -o 8lab.exe 8lab.o #functions.o

8lab.o : 8lab.c #functions.h
	$(CC) $(FLAGS) -c 8lab.c 

#functions.o : functions.c functions.h
#	$(CC) $(FLAGS) -c functions.c

st : 8lab.exe
	./8lab.exe
