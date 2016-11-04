CC := gcc
FLAGS := -std=c99 -Wall -Werror -pedantic 

rk.exe : rk.o functions.o
	$(CC) -o $@ $^

tests.exe : tests.o functions.o
	$(CC) -o $@ $^

%.o : %.c *.h
	$(CC) $(FLAGS) -c $<

st : rk.exe 
	./rk.exe in.txt out.txt

stt : tests.exe
	./tests.exe

clean : 
	rm *.exe *.o

