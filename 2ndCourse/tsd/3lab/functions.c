#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structurs.h"
#include "functions.h"

int load_table(FILE *file, int *count, book_t *books, key *key_table)
{
	while (fscanf(file, "%s", books[*count].author) != EOF && *count < MAXCOUNT)
	{
		books[*count].number = *count;
		key_table[*count].number = *count;
		fscanf(file, "%s", books[*count].title);
		fscanf(file, "%s", books[*count].publisher);
		fscanf(file, "%d", &books[*count].pages);
		key_table[*count].pages = books[*count].pages;
		fscanf(file, "%d", &books[*count].type);
		if (books[*count].type == 0)
		{
			fscanf(file, "%s", books[*count].book_type.technical.sector);
			fscanf(file, "%d", &books[*count].book_type.technical.place);
			fscanf(file, "%d", &books[*count].book_type.technical.year);
		}
		else 
		{
			if (books[*count].type == 1)
				fscanf(file, "%d", &books[*count].book_type.art.kind);
			else
			{
				printf("Incorrect load of table\n");
				return -1;
			}
		}
		(*count)++;
	}
	return 0;
}


void print_table(book_t *books, int i)
{
	if (books[i].pages)
	{			
		printf("Запись №%d.\n", i+1);
		printf("Автор: %s\n", books[i].author);
		printf("Название: %s\n", books[i].title);
		printf("Издательство: %s\n",books[i].publisher);
		printf("Страниц: %d\n", books[i].pages);
		if (books[i].type == 0)
		{
			printf("Отрасль: %s\n", books[i].book_type.technical.sector);
			printf("Отечественная/переведенная: %s\n", tech[books[i].book_type.technical.place]);
			printf("Год издания: %d\n", books[i].book_type.technical.year);
		}
		if (books[i].type == 1)
			printf("Жанр: %s\n", art[books[i].book_type.art.kind]);
		printf("-----------------------------------------\n");
	}
}

void replace_spaces(char *string)
{
	for (int i = 0; i < strlen(string); i++)
		if (string[i] == ' ')
			string[i] = '_';
}

int read_line(char *s, int n)
{
	int ch, i = 0;
	while ((ch = getchar()) != '\n' && ch != EOF)
		if (i < n - 1)
			s[i++] = ch;
	s[i] = '\0';
	return i;
}


int add_new_rec(book_t *books,key *key_table ,int *count, char *filename)
{
	printf("%s Добавление новой записи%s\n", RED, RESET);
	books[*count].number = *count;
	key_table[*count].number = *count;
	char string[N];

	fgets(string, N, stdin);
	printf("Введите автора книги: ");
	//scanf("%s", string);

	read_line(string, N);
	if (strlen(string) < N)
	{
		replace_spaces(string);
		strcpy(books[*count].author,string);
	}
	else
	{
		printf("Incorrect input\n");
		return -1;
	}

	printf("Введите название книги: ");
	//scanf("%s", string);
	read_line(string, N);
	if (strlen(string) < N)
	{
		replace_spaces(string);
		strcpy(books[*count].title,string);
	}
	else
	{
		printf("Incorrect input\n");
		return -1;
	}
	
	printf("Введите название издательства: ");
	//scanf("%s", string);
	read_line(string, N);
	if (strlen(string) < N)
	{
		replace_spaces(string);
		strcpy(books[*count].publisher,string);
	}
	else
	{
		printf("Incorrect input\n");
		return -1;
	}

	printf("Введите количество страниц в книге: ");
	int number;
	scanf("%d", &number);
	if (number > 0)
	{
		books[*count].pages = number;
		key_table[*count].pages = number;
	}
	else
	{
		printf("Incorrect input\n");
		return -1;
	}

	printf("Тип литературы: техническая(1) или художественная(2): ");
	scanf("%d", &number);
	if (number == 1 || number == 2)
	{
		books[*count].type = number-1;
		if (number == 1)
		{
			printf("Введите отрасль: ");
			scanf("%s", string);
			//read_line(string, N);
			if (strlen(string) < N)
			{
				replace_spaces(string);
				strcpy(books[*count].book_type.technical.sector,string);
			}
			else
			{
				printf("Incorrect input\n");
				return -1;
			}

			printf("Отечественная(1) или переведенная(2): ");
			int num;
			scanf("%d", &num);
			if (num == 1 || num == 2)
				books[*count].book_type.technical.place = num-1;
			else
			{
				printf("Incorrect input\n");
				return -1;
			}
			
			printf("Введите год издания: ");
			scanf("%d", &num);
			if (num > 0 && num < 2020)
				books[*count].book_type.technical.year = num;
			else
			{
				printf("Incorrect input\n");
				return -1;
			}
			
		}
		if (number == 2)
		{
			printf("Введите жанр книги - роман(1), пьеса(2), стихи(3): ");
			int num;
			scanf("%d", &num);
			if (num > 0 && num <= 3)
				books[*count].book_type.art.kind = num-1;
			else
			{
				printf("Incorrect input\n");
				return -1;
			}
		}
	}
	else
	{
		printf("Incorrect input\n");
		return -1;
	}

	FILE *file = fopen(filename, "a");
	if (books[*count].type == 0)
		fprintf(file, "%s %s %s %d %d %s %d %d\n",books[*count].author, books[*count].title, books[*count].publisher, books[*count].pages, books[*count].type, books[*count].book_type.technical.sector, books[*count].book_type.technical.place, books[*count].book_type.technical.year);
	if (books[*count].type == 1)
		fprintf(file, "%s %s %s %d %d %d\n",books[*count].author, books[*count].title, books[*count].publisher, books[*count].pages, books[*count].type, books[*count].book_type.art.kind);
	fclose(file);
	(*count)++;
	return 0;
}

int del_rec(book_t *books,key *key_table ,int *count, char *filename)
{
	printf("%s Удаление записи%s\n", RED, RESET);
	printf("Введите номер записи (от 1 до %d), которую вы хотите удалить: ", *count);
	int number;
	scanf("%d", &number);
	number--;
	if (number > 0 && number < *count)
	{
		int i = 0;
		while (i < *count)
		{
			if (books[i].number == number) 
			{
				for (int j = i; j < *count; j++)
				{
					books[j] = books[j+1];
					key_table[j] = key_table[j+1];
				}
				(*count)--;
			}
			i++;
		}
	}
	else
		printf("Нет такой записи\n");
	return 0;
}

unsigned long long int tick(void)
{
	unsigned long long int time = 0;
	__asm__ __volatile__ ("rdtsc" : "=A" (time));
	return time;
}

unsigned long long int bubblesort_keys(book_t *books, key *key_table, int *count)
{
	unsigned long long int time1, time2;
	time1 = tick();
	for (int i = 0; i < *count; i++)
		for (int j = *count - 1; j > i; j--)
			if (key_table[j].pages < key_table[j-1].pages)
			{
				key tmp = key_table[j];
				key_table[j] = key_table[j-1];
				key_table[j-1] = tmp;
			}
	time2 = tick();
	return time2-time1;
}

unsigned long long int shell_keys(book_t *books, key *key_table, int *count)
{
	unsigned long long int time1, time2;
	time1 = tick();
	for (int mid = *count / 2; mid > 0; mid /= 2)
		for (int i = mid; i < *count; i++)
			for (int j = i - mid; (j >= 0) && (key_table[j+mid].pages < key_table[j].pages); j -= mid)
			{
				key tmp = key_table[j];
				key_table[j] = key_table[j+mid];
				key_table[j+mid] = tmp;
			}
	time2 = tick();
	return time2-time1;
}

unsigned long long int bubblesort_table(book_t *books, int *count)
{
	unsigned long long int time1, time2;
	time1 = tick();
	for (int i = 0; i < *count; i++)
		for (int j = *count-1; j > i; j--)
			if (books[j].pages < books[j-1].pages)
			{
				book_t tmp = books[j];
				books[j] = books[j-1];
				books[j-1] = tmp;
			}
	time2 = tick();
	return time2-time1;
}

unsigned long long int shell_table(book_t *books, int *count)
{
	unsigned long long int time1, time2;
	time1 = tick();
	for (int mid = *count / 2; mid > 0; mid /= 2)
		for (int i = mid; i < *count; i++)
			for (int j = i - mid; (j >= 0) && (books[j+mid].pages < books[j].pages); j -= mid)
			{
				book_t tmp = books[j];
				books[j] = books[j+mid];
				books[j+mid] = tmp;
			}
	time2 = tick();
	return time2-time1;
}

void search(book_t *books, int *count)
{
	printf("Введите отрасль технической литературы: ");
	char sector[N];
	scanf("%s", sector);
	printf("Введите год издания: ");
	int year;
	scanf("%d", &year);
	printf("%sСписок книг отрасли '%s' года издания не позже %d%s\n",RED, sector, year,RESET);
	for (int i = 0; i < *count; i++)
	{
		if (strcmp(books[i].book_type.technical.sector, sector) == 0 && books[i].book_type.technical.year <= year && books[i].book_type.technical.place == 1)
			print_table(books, i);
	}

}

