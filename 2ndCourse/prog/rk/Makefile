CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic -ggdb

1.exe : 1.o func.o
	$(CC) -o 1.exe 1.o func.o	
func.o : func.c func.h
	$(CC) $(FLAGS) -c func.c
1.o : 1.c
	$(CC) $(FLAGS) -c 1.c
st : 1.exe
	./1.exe input.txt output.txt
rm : 
	del *.o *.exe

