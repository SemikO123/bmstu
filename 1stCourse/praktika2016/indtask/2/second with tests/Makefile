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
tests.exe : tests.o func.o
	$(CC) -o $@ $^
%.o : %.c *.h
	$(CC) $(FLAGS) -c $<
clean :
	del *.o *.exe
start : 2.exe
	2.exe input.txt
starttests : tests.exe
	tests.exe in1.txt in2.txt in3.txt in4.txt