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

tests.o : tests.c functions.h
	$(CC) $(FLAGS) -c tests.c functions.h

functions.o : functions.c functions.h
	$(CC) $(FLAGS) -c functions.c functions.h

vlgr : tests.exe
	valgrind --tool=memcheck ./tests.exe

st : tests.exe
	./tests.exe

rm : 
	rm *.o *.exe