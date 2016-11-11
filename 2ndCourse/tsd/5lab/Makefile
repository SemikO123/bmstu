CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic 

ifeq ($(mode), debug)
	FLAGS += -g5
endif

ifeq ($(mode), release)
	FLAGS += -DNDEBUG -g0
endif

5.exe : 5.o #functions.o
	$(CC) -o 5.exe 5.o #functions.o

5.o : 5.c #functions.h structurs.h
	$(CC) $(FLAGS) -c 5.c 

st : 5.exe
	./5.exe

vlgr : 5.exe
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./5.exe 

clean :
	rm *.o *.exe 
