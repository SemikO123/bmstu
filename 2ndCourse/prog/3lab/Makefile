maCC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	FLAGS += -g3
endif

ifeq ($(mode), release)
	FLAGS += -DNDEBUG -g0
endif

3lab.exe : 3lab.o functions.o 
	$(CC) -o 3lab.exe 3lab.o functions.o

tests.exe : tests.o functions.o
	$(CC) -o tests.exe tests.o functions.o

3lab.o : 3lab.c functions.h errors.h
	$(CC) $(FLAGS) -c 3lab.c

functions.o : functions.c functions.h errors.h
	$(CC) $(FLAGS) -c functions.c

tests.o : tests.c functions.h errors.h
	$(CC) $(FLAGS) -c tests.c

st : 3lab.exe
	./3lab.exe input.txt output.txt 1

stt : tests.exe
	./tests.exe 

vlgr : 3lab.exe
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./3lab.exe input.txt output.txt 6

vlgrt : tests.exe
	valgrind --tool=memcheck ./tests.exe

rm : 
	rm *.exe *.o
