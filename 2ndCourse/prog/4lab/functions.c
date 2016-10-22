#include <stdio.h>
#include "functions.h"
#include <stdlib.h>

/*Функция strchr выполняет поиск первого вхождения символа symbol 
* в строку string. Возвращает указатель на первое вхождение символа в строке.
**/ 
char *strchr_f(char *string, int symbol)
{
	for (int i = 0; i <= strlen_f(string); i++)
		if (string[i] == symbol)
			return string + i;	
	return NULL;
}

/*Функция strdup дублирует строку, на которую указывает аргумент str. 
* Память под дубликат строки выделяется с помощью функции malloc, и по окончанию 
* работы с дубликатом должна быть очищена с помощью функции free.
**/
char *strdup_f(const char *string)
{
	int i = strlen_f(string);
	char *new_string;
	new_string = malloc((i+1)*sizeof(char));
	if (new_string)
	{
		for (int i=0; string[i] != '\0'; i++)
			new_string[i] = string[i];
		new_string[i+1] = '\0';
		return new_string;
	}
	else
		return NULL;
}

int strlen_f(const char *string)
{
	int i = 0;
	while (string[i] != '\0')
		i++;
		return i;	
}


// int read_string(char *string, FILE *file)
// {
// 	char symbol;
// 	while (fscanf(file, "%c", &symbol) != EOF)
// 	{
// 		printf("%c",symbol;)	
// 	}
// }