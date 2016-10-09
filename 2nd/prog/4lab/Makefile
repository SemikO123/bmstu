CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	FLAGS += -g3
endif

ifeq ($(mode), release)
	FLAGS += -DNDEBUG -g0
endif

4lab.exe : 4lab.o functions.o
	$(CC) -o  4lab.exe 4lab.o functions.o

4lab.o : 4lab.c functions.h
	$(CC) $(FLAGS) -c 4lab.c functions.h

functions.o : functions.c functions.h
	$(CC) $(FLAGS) -c functions.c functions.h

vlgr : 4lab.exe
	valgrind --tool=memcheck ./4lab.exe

st : 4lab.exe
	./4lab.exe

rm : 
	rm *.o *.exe