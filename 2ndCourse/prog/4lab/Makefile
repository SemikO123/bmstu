CC := gcc
FLAGS := -std=gnu99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	FLAGS += -g3
endif

ifeq ($(mode), release)
	FLAGS += -DNDEBUG -g0
endif

tests.exe : tests.o functions.o
	$(CC) -o  tests.exe tests.o functions.o

tests2.exe : tests2.o functions.o
	$(CC) -o  tests2.exe tests2.o functions.o

4lab.exe : 4lab.o functions.o
	$(CC) -o 4lab.exe 4lab.o functions.o

4lab.o : 4lab.c functions.h
	$(CC) $(FLAGS) -c 4lab.c functions.h

tests.o : tests.c functions.h
	$(CC) $(FLAGS) -c tests.c functions.h

tests2.o : tests2.c functions.h
	$(CC) $(FLAGS) -c tests2.c functions.h

functions.o : functions.c functions.h
	$(CC) $(FLAGS) -c functions.c functions.h

vlgr : tests.exe
	valgrind --tool=memcheck ./tests.exe

st : tests.exe
	./tests.exe

tests : tests2.exe
	./tests2.exe

prog : 4lab.exe
	./4lab.exe input.txt output.txt

rm : 
	rm *.o *.exe