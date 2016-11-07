CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic 

ifeq ($(mode), debug)
	FLAGS += -g3
endif

ifeq ($(mode), release)
	FLAGS += -DNDEBUG -g0
endif

3.exe : 3.o functions.o
	$(CC) -o 3.exe 3.o functions.o

3.o : 3.c functions.h structurs.h
	$(CC) $(FLAGS) -c 3.c functions.h structurs.h

functions.o : functions.c functions.h structurs.h
	$(CC) $(FLAGS) -c functions.c functions.h structurs.h

st : 3.exe
	./3.exe

vlgr : 3.exe
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./3.exe 

rm :
	rm *.o *.exe