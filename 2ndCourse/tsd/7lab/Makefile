CC := gcc
FLAGS := -g -std=c99 -Wall -Werror -pedantic 

ifeq ($(mode), debug)
	FLAGS += -g6
endif

ifeq ($(mode), release)
	FLAGS += -DNDEBUG -g0
endif

main.exe : main.o tree.o htable.o htable_open.o 
	$(CC) -o main.exe main.o tree.o htable.o htable_open.o 

main.o : main.c htable.h tree.h
	$(CC) $(FLAGS) -c main.c

tree.o : tree.c htable.h tree.h
	$(CC) $(FLAGS) -c tree.c

htable.o : htable.c htable.h tree.h
	$(CC) $(FLAGS) -c htable.c

htable_open.o : main.c htable.h tree.h
	$(CC) $(FLAGS) -c htable_open.c



st : main.exe
	./main.exe

rm :
	rm *.o *.exe
