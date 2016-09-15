CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	FLAGS += -g3
endif

ifeq ($(mode), release)
	FLAGS += -DNDEBUG -g0
endif

1lab.exe : 1lab.o functions.o
	$(CC) -o  1lab.exe 1lab.o functions.o

tests.exe : tests.o functions.o
	$(CC) -o tests.exe tests.o functions.o

1lab.o : 1lab.c functions.h errors.h 
	$(CC) $(FLAGS) -c 1lab.c

functions.o : functions.c functions.h errors.h
	$(CC) $(FLAGS) -c functions.c

tests.o : tests.c functions.h errors.h
	$(CC) $(FLAGS) -c tests.c


st : 1lab.exe
	./1lab.exe input.txt out.txt

stnofile : 1lab.exe
	./1lab.exe 

stbadname : 1lab.exe
	./1lab.exe name.txt

tests : tests.exe
	./tests.exe 

rm : 
	rm *.o *.exe


