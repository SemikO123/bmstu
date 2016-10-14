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

tests.exe : tests.o functions.o
	$(CC) -o  tests.exe tests.o functions.o

2lab.o : 2lab.c functions.h errors.h
	$(CC) $(FLAGS) -c 2lab.c

functions.o : functions.c functions.h errors.h
	$(CC) $(FLAGS) -c functions.c

tests.o : tests.c functions.h errors.h
	$(CC) $(FLAGS) -c tests.c

st : 2lab.exe 
	./2lab.exe input.txt

sttests : tests.exe
	./tests.exe

vg : 2lab.exe
	valgrind --tool=memcheck ./2lab.exe input.txt

vgtest : tests.exe
	valgrind --tool=memcheck ./tests.exe

rm : 
	rm *.exe *.o

