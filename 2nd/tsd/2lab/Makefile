CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	FLAGS += -g3
endif

ifeq ($(mode), release)
	FLAGS += -DNDEBUG -g0
endif

2lab.exe : 2lab.o
	$(CC) -o 2lab.exe 2lab.o

2lab.o : 2lab.c
	$(CC) $(FLAGS) -c 2lab.c

st : 2lab.exe
	./2lab.exe

rm :
	rm *.o *.exe