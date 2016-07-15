CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic -c

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
clean :
	del *.o *.exe
start : 1.exe
	1.exe