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
	while (string[i] != '\0')
		i++;
		return i;	
}

char *concat_string(char *string, const char *str)
{
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

char *read_line(FILE *file, int *out_error)
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
				if (str[count-1] == '\n')
					break;
			}
			else
			{
				*out_error = MEMPROBLEM;
				return NULL;
			}
		}
		if (strlen_f(string) == 0)
			{
				*out_error = EMPTYSTRING;
				return NULL;
			}
	}
	else
	{
		*out_error = MEMPROBLEM;
		return NULL;
	}
	*out_error = OK;
	return string;
}

int count_of_letters(const char *string)
{
	return string[strlen_f(string)-1] == '\n' ? strlen_f(string)-1 : strlen_f(string);
}

char *substring_in_string(char *string, const char *old)
{
	for (int i = 0; i < strlen_f(string); i++)
	{
		int concurr = 0;
		for (int j = 0; j < count_of_letters(old); j++)
		{
			if (string[i+j] == old[j])
				concurr++;
			else
				break;
			if (concurr == count_of_letters(old))
				return string + i;
		}
	}
	return NULL;

}

int count_of_changings(char *string, const char *old)
{
	int changings = 0;
	char *ptr = string;
	while (ptr)
	{
		ptr = substring_in_string(ptr, old);
		if (ptr)
		{
			changings++;
			ptr += count_of_letters(old);
		}
	}
	return changings;
}


char *change_string(char *string, const char *old, const char *new)
{
	int old_len = count_of_letters(old);
	int new_len = count_of_letters(new);
	int string_len = strlen_f(string);
	int changings = count_of_changings(string, old);
	// printf("COUNT = %d\n", changings);
	int length = string_len - changings*(old_len - new_len);
	char *new_string = malloc((1 + length)*sizeof(char));
	if (new_string)
	{
		char *ptr = string, *lptr = string;
		char *new_ptr = new_string;
		while (ptr)
		{
			ptr = substring_in_string(ptr, old);
			if (ptr)
			{
				memcpy(new_ptr, lptr, ptr-lptr);
				new_ptr += ptr-lptr;
				memcpy(new_ptr, new, count_of_letters(new));
				new_ptr += count_of_letters(new);
				ptr += count_of_letters(old);
				lptr = ptr;
			}	
			else
				memcpy(new_ptr, lptr, strlen_f(lptr));
		}
		new_string[length] = '\0';
	}
	else
		return NULL;

	return new_string;
}