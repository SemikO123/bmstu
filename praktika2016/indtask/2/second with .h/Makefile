CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	FLAGS += -g3
endif

ifeq ($(mode), release)
	FLAGS += -DNDEBUG -g0
endif

2.exe : 2.o func.o
	$(CC) -o $@ $^
2.o : 2.c 2pr.h err.h
	$(CC) $(FLAGS) -c 2.c
func.o : func.c 2pr.h err.h
	$(CC) $(FLAGS) -c func.c
clean :
	del *.o *.exe
start : 2.exe
	2.exe input.txt