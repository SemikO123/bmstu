CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	FLAGS += -g3
endif

ifeq ($(mode), release)
	FLAGS += -g0 -DNDEBUG
endif

2.exe : 2.o func.o
	$(CC) -o $@ $^
2.o : 2.c
	$(CC) $(FLAGS) -c 2.c
func.o : func.c
	$(CC) $(FLAGS) -c func.c
clean :
	del *.o *.exe
start : 2.exe
	2.exe input.txt