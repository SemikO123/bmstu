#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <string.h>

#define LENGTH 11

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
	while (string[i] != '\0' && string[i] != '\n')
		i++;
		return i;	
}

char *concat_string(char *string, const char *str)
{
	//printf("String(len)=%d \nString=%s \nStr(len)=%d \nStr=%s\n", strlen_f(string),string, strlen_f(str), str);
	char *result = malloc((strlen_f(string)+strlen_f(str)+1)*sizeof(char));
	if (!result)
		return NULL;
	int k = 0;
	for (int i = 0; i < strlen_f(string); i++)
		result[k++] = string[i];
	for (int i = 0; i <= strlen_f(str); i++)
		result[k++] = str[i];
	return result;
}

char *read_line(FILE *file)
{
	char str[LENGTH];
	//printf("-------------------------BEGIN------------------\n");
	char *string = malloc(sizeof(char));
	if (string)
	{
		*string = '\0';
		while (fgets(str, LENGTH, file) != NULL)
		{
			int count = strlen_f(str);
			char *result = concat_string(string, str);
			if (result)
			{
				free(string);
				string = result;
				if (str[count] == '\n')
					break;
			}
			else
			{
				printf("Memory Error\n");
				return NULL;
			}
		}
		string[strlen_f(string)+1] = '\0';
	}
	else
	{
		printf("Memory Error\n");
		return NULL;
	}
	return string;
}

int count_of_changings(const char *string, const char *old)
{
	int changings = 0;
	for (int i = 0; i < strlen_f(string); i++)
	{
		int concurr = 0;
		for (int j = 0; j < strlen_f(old); j++)
			if (string[i+j] == old[j])
				concurr++;
		if (concurr == strlen_f(old))
		{
		    for (int t = 0; t < strlen_f(old)-1; t++, i++);
			changings++;
		}
	}
	return changings;
}

char *change_string(const char *string, const char *old, const char *new)
{
	int old_len = strlen_f(old);
	int new_len = strlen_f(new);
	int string_len = strlen_f(string);
	int changings = count_of_changings(string, old);
	char *new_string = malloc((1 + string_len - changings*(old_len - new_len))*sizeof(char));
	if (new_string)
	{
		int k = 0;
		for (int i = 0; i <= string_len; i++)
		{
			int concurr = 0;
			for (int j = 0; j < old_len; j++)
				if (string[i+j] == old[j])
						concurr++;
			if (concurr != strlen_f(old))
				new_string[k++] = string[i];
			else
			{
				for (int t = 0; t < new_len; t++)
					new_string[k++] = new[t];
				// ПОФИКСИТЬ ЭТО
				// передвигает i на столько позиций вправо, сколько символов было 
				// заменено, чтобы избежать перекрытия двух замен 
				for (int t = 0; t < strlen_f(old)-1; t++, i++);
			}
		}
		new_string[k] = '\0';
	}
	else
	{
		printf("Memory Error\n");
		return NULL;
	}

	return new_string;
}