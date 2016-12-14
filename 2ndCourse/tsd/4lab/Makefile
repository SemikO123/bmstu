CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic 

ifeq ($(mode), debug)
	FLAGS += -g3
endif

ifeq ($(mode), release)
	FLAGS += -DNDEBUG -g0
endif

4.exe : 4.o functions.o 
	$(CC) -o 4.exe 4.o functions.o 

4.o : 4.c functions.h 
	$(CC) $(FLAGS) -c 4.c functions.h 

functions.o : functions.c functions.h 
	$(CC) $(FLAGS) -c functions.c 

st : 4.exe
	./4.exe

vlgr : 4.exe
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./4.exe 

clean :
	rm *.o *.exe 