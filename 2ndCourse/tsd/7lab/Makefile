CC := gcc
FLAGS := -g -std=c99 -Wall -Werror -pedantic 

ifeq ($(mode), debug)
	FLAGS += -g6
endif

ifeq ($(mode), release)
	FLAGS += -DNDEBUG -g0
endif

7.exe : 7.o #functions.o
	$(CC) -o 7.exe 7.o #functions.o

7.o : 7.c #functions.h
	$(CC) $(FLAGS) -c 7.c 

#functions.o : functions.c functions.h
#	$(CC) $(FLAGS) -c functions.c

rm :
	rm *.exe *.o

st : 7.exe
	./7.exe