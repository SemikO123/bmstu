CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	FLAGS += -g3
endif

ifeq ($(mode), release)
	FLAGS += -DNDEBUG -g0
endif

1.exe : 1.o
	$(CC) -o 1.exe 1.o

1.o : 1.c
	$(CC) $(FLAGS) -c 1.c

st : 1.exe
	./1.exe

vlgr : 1.exe
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./1lab.exe
