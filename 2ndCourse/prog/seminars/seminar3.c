Семинар 3

Правильно ли проинициализирована строка name? почему?
char name[] = {'f','e','s','s'};   // + '\0'
char name1[] = "fess";
char name2[5] = {'f','e','s','s'};

Что напечатает следующая программа?
#include <stdio.h>
int main(void)
{
	char note[] = "1234567890 abcd.";
	char *ptr = note;
	puts(ptr);        // 1234567890 abcd.
	puts(++ptr);      // 234567890 abcd.
	note[7] = '\0';
	puts(note);       // 1234567
	puts(++ptr);      // 34567
	return 0;
}

Что напечатает следующая программа?
#include <stdio.h>
#include <string.h>
int main(void)
{
	char food[] = "Yummy";
	char *ptr;
	ptr = food + strlen(food);
	while (--ptr >= food)
		puts(ptr);       
	return 0;
}
//y
//my
//mmy
//ummy
//Yummy

#include <stdio.h>
char *pr(char *str)
{
	char *pe = str;
	while (*pe)
		putchar(*pe++);
	do
	{
		putchar(*--pe);
	}
	while (pe-str);
	return pe;
}

X = pr("Xo Xo Xo!");
Что при этом выводится на печать?
// Xo Xo Xo!!oX oX oX

Какой тип должна иметь переменная X?
// char *

Что означает *--pe? Чем отличается от --*pe?
// *--pe - разыменование указателя на предыдущий элемент массива
// --*pe - значение элемента на 1 меньше

#include <stdio.h>
char *pr(char *str)
{
	char *pe = str;
	while (*pe)
		putchar(*pe++);
	do
	{
		putchar(*pe--);
	}
	while (pe-str);
	return pe;
}

// Xo Xo Xo!(\0)oX oX o

Что произойдет если функции будет передана пустая строка в качестве аргумента?
// бесконечный цикл с мусором

#include <stdio.h>
#include <string.h>
int main(void)
{
	char str_a[40] = "e is ";
	char str_b[40] = "My nam";
	const char *quote = "Ymmy.";
	strcat(str_a, quote); // e is Ymmy.
	strcat(str_b, str_a); // My name is Ymmy.
	puts(str_b);          // My name is Ymmy.
	return 0;
}

если 
str_a[40];
// My nam(мусор)Ymmy.

