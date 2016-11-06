#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define WHITE   "\033[1;37m"
#define N 100
#define MAXCOUNT 40

/*
Создать таблицу, содержащую не менее 40-ка записей (тип – запись с вариантами). 
Упорядочить данные в ней по возрастанию ключей, где ключ – любое невариантное поле 
по выбору программиста), используя:  а) саму таблицу, б) массив ключей (возможность 
бавления и удаления записей в ручном режиме обязательна)

Ввести список литературы, содержащий фамилию автора, название книги, 
издательство, количество страниц,  вид литературы (0: техническая – отрасль, 
отечественная(0), переводная(1), год издания; 1: художественная – роман(0), пьеса(1),
стихи(2)). 
Вывести список всей переводной лит-ры по указанной отрасли с годом издания не 
позднее указанного.
*/

typedef struct
{
	int number;
	char author[N];
	char title[N];
	char publisher[N];
	int pages;
	int type;
	union 
	{
		struct
		{
			char sector[N];
			int place;
			int year;
		} technical;
		struct 
		{
			int kind;
		} art;
	} book_type;
} book_t;

typedef struct 
{
	int number;
	int pages;
} key;

static char *tech[] = 
{
	"Отечественная", 
	"Переведенная"
};

static char *art[] = 
{
	"Роман",
	"Пьеса",
	"Стихи"
};

int load_table(FILE *file, int *count, book_t *books)
{
	while (fscanf(file, "%s", books[*count].author) != EOF && *count < MAXCOUNT)
	{
		books[*count].number = *count;
		fscanf(file, "%s", books[*count].title);
		fscanf(file, "%s", books[*count].publisher);
		fscanf(file, "%d", &books[*count].pages);
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


void print_table(book_t *books, int *count)
{
	printf("-----------------------------------------\n");
	int i = 0;
	while (i < *count)
	{
		if (books[i].pages)
		{			
		printf("Запись №%d.\n",i+1);
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
		i++;
		}
	}
}

void replace_spaces(char *string)
{
	for (int i = 0; i < strlen(string); i++)
		if (string[i] == ' ')
			string[i] = '_';
}


int add_new_rec(book_t *books, int *count, char *filename)
{
	printf("%s Добавление новой записи%s\n", RED, RESET);
	books[*count].number = *count;
	printf("Введите автора книги (вместо пробелов '_'): ");
	char string[N];
	scanf("%s", string);
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

	printf("Введите название книги (вместо пробелов '_'): ");
	scanf("%s", string);
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
	
	printf("Введите название издательства (вместо пробелов '_'): ");
	scanf("%s", string);
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
		books[*count].pages = number;
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
			printf("Введите отрасль (вместо пробелов '_'): ");
			scanf("%s", string);
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

int main(int argc, char **argv)
{	
	char filename[] = "table.txt";
	FILE *table = fopen(filename, "r");
	int count_of_records = 0;
	book_t books[MAXCOUNT];
	load_table(table, &count_of_records, books);
	int menu;
	do
	{	
		printf("\n%sМЕНЮ:\n", YELLOW);
		printf("* 1 Вывод таблицы на экран \n");
		printf("* 2 Упорядочивание таблицы по ключам\n");
		printf("* 3 Сортировка таблицы\n");
		printf("* 4 Добавление новой записи\n");
		printf("* 5 Удаление записи\n");
		printf("* 6 Отчет о времени сортировки\n");
		printf("* 7 Поиск записи по указанной отрасли и году\n");
		printf("* 8 Выход%s\n", RESET);


		printf("Выберите пункт меню:");
		scanf("%d", &menu);
		switch(menu)
		{
			case 1:
				print_table(books, &count_of_records);
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				add_new_rec(books, &count_of_records, filename);
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				fclose(table);
				return 0;
			default:
				printf("%sВведите номер выбранного пункта меню!%s\n",RED, RESET);
				break;
		}
	}
	while (menu != 8);

}