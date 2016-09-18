CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic 

ifeq ($(mode), debug)
	FLAGS += -g3
endif

ifeq ($(mode), release)
	FLAGS += -DNDEBUG -g0
endif

2lab.exe : 2lab.o functions.o
	$(CC) -o  2lab.exe 2lab.o functions.o

2lab.o : 2lab.c functions.h errors.h
	$(CC) $(FLAGS) -c 2lab.c

functions.o : functions.c functions.h errors.h
	$(CC) $(FLAGS) -c functions.c

st : 2lab.exe 
	./2lab.exe input.txt

vlgr : 2lab.exe
	valgrind --tool=memcheck ./2lab.exe input.txt

rm : 
	rm *.exe *.o

