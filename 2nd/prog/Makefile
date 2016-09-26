CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	FLAGS += -g3
endif

ifeq ($(mode), release)
	FLAGS += -DNDEBUG -g0
endif

test.exe : test.o
	$(CC) -o test.exe test.o

test.o : test.c
	$(CC) $(FLAGS) -c test.c

st : test.exe
	./test.exe