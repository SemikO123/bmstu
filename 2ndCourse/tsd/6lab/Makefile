CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic 

ifeq ($(mode), debug)
	FLAGS += -g6
endif

ifeq ($(mode), release)
	FLAGS += -DNDEBUG -g0
endif

6.exe : 6.o #functions.o
	$(CC) -o 6.exe 6.o #functions.o

6.o : 6.c #functions.h
	$(CC) $(FLAGS) -c 6.c 

#functions.o : functions.c functions.h
#	$(CC) $(FLAGS) -c functions.c

st : 6.exe
	./6.exe

vlgr : 6.exe
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./6.exe 

clean :
	rm *.o *.exe 
