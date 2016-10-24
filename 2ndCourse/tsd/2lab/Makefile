CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	FLAGS += -g3
endif

ifeq ($(mode), release)
	FLAGS += -DNDEBUG -g0
endif

work.exe : work.o functions.o
	$(CC) -o work.exe work.o functions.o

2lab.exe : 2lab.o functions.o
	$(CC) -o 2lab.exe 2lab.o functions.o

work.o : work.c functions.h
	$(CC) $(FLAGS) -c work.c

2lab.o : 2lab.c functions.h
	$(CC) $(FLAGS) -c 2lab.c

functions.o : functions.c functions.h
	$(CC) $(FLAGS) -c functions.c

work : work.exe
	./work.exe

st : 2lab.exe
	./2lab.exe #< test.txt

vlgr : 2lab.exe
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./2lab.exe 

rm :
	rm *.o *.exe