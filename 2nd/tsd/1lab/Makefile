CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	FLAGS += -g3
endif

ifeq ($(mode), release)
	FLAGS += -DNDEBUG -g0
endif

1lab.exe : 1lab.o 
	$(CC) -o  1lab.exe 1lab.o 

1lab.o : 1lab.c
	$(CC) $(FLAGS) -c 1lab.c

st : 1lab.exe
	./1lab.exe

rm : 
	rm *.o *.exe

