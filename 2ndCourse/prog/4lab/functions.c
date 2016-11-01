#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <string.h>

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


char *read_line(FILE *file)
{
	int size = 2;
	int count = 0;
	int symbol;
	char *string = malloc(2 * sizeof(char));
	if (!string)
		return NULL;
	else
	{
		symbol = fgetc(file);
		while (symbol != EOF)
		{
			if (count >= size)
			{
				size *= 2;
				char *new_string = malloc(size* sizeof(char)); // СПРОСИТЬ 
				if (!new_string)
					return NULL;
				else
				{
					strcpy(new_string,string);
					free(string);
					string = new_string;
				}
			}
			string[count++] = symbol;
			symbol = fgetc(file);
		}
		string[count-1] = '\0';
	}
	return string;	
}

// char *change_string(const char *string, const char *old, const char *new)
// {
// 	int i = 0;
// 	while (string[i] != '\0')
// 	{
// 		int flag = 0;
// 		for (int j = 0; j < strlen(old); j++)
// 			if (string[i] == old[j])
// 			{
// 				flag = 1;
// 				i++;
// 			}
// 			else
// 			{
// 				flag = 0;
// 				break;
// 			}
// 		if (flag == 1)
// 			for (int j == 0; j < strlen(new); j++)
// 				new_string[i++] = new[j];
// 		else
// 		{
// 			new_string[i] = string[i];
// 			i++;
// 		}
// 	}
// }