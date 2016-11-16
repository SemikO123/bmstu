#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <string.h>

#define LENGTH 10


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


char *read_line1(FILE *file)
{
	int size = 2;
	int count = 0;
	int symbol;
	char *string = malloc(size * sizeof(char));
	if (!string)
		return NULL;
	else
	{
		symbol = fgetc(file);
		while (symbol != '\n')
		{
			if (count >= size)
			{
				size *= 2;
				char *new_string = malloc(size* sizeof(char));  
				if (!new_string)
					return NULL;
				else
				{
					strcpy(new_string,string);
					free(string);
					string = new_string;
				}
			}
			printf("len=%d count=%d symb=%c\n",(int)strlen(string), count, string[count-1]);
			string[count++] = symbol;
			symbol = fgetc(file);
		}
		string[count-1] = '\0';
	}
	return string;	
}

char *concat_string(char *string, const char *str)
{
	//printf("string=%d str=%d\n", strlen_f(string), strlen_f(str));
	char *result = malloc((strlen_f(string)+strlen_f(str)+1)*sizeof(char));
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
	//int string_length = 0;
	//int already_readed = 0;
	//char *result;
	int flag = 0;
	char *string = malloc(sizeof(char));
	*string = '\0';
	while (fgets(str, LENGTH, file) != NULL && flag != 1)
	{
		int count = strlen_f(str);
		// printf("str=%s//////count=%d   str[%d]=%d \n",str,count, count, str[count-1]);
		if (str[count-1] == '\n')
		{
			// printf("THE END OF THE STRING\n");
			flag = 1;
		}
		char *result = concat_string(string, str);
		printf("result=%s\n",result);
		free(string);
		string = result;
		printf("result=%s\n",string);

	}
	return string;
}

// char *change_string(const char *string, const char *old, const char *new)
// {

// }