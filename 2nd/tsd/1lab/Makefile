CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic

ifeq ($(mode), debug)
	FLAGS += -g3
endif

ifeq ($(mode), release)
	FLAGS += -DNDEBUG -g0
endif

qwe.exe : qwe.o func.o
	$(CC) -o  qwe.exe qwe.o func.o

qwe.o : qwe.c func.h
	$(CC) $(FLAGS) -c qwe.c func.h

func.o : func.c func.h
	$(CC) $(FLAGS) -c func.c func.h

st : qwe.exe
	./qwe.exe

rm : 
	rm *.o *.exe



