#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structurs.h"
#include "functions.h"


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


int main(int argc, char **argv)
{	
	char filename[] = "table.txt";
	FILE *table = fopen(filename, "r");
	unsigned long long int sort_keys_bubble, sort_keys_shell, sort_table_bubble, sort_table_shell;
	{
		int count_of_records = 0;
		book_t books[MAXCOUNT];
		key key_table[MAXCOUNT];
		load_table(table, &count_of_records, books, key_table);
		sort_keys_bubble = bubblesort_keys(books, key_table, &count_of_records);
	}
	rewind(table);
		{
		int count_of_records = 0;
		book_t books[MAXCOUNT];
		key key_table[MAXCOUNT];
		load_table(table, &count_of_records, books, key_table);
		sort_table_bubble = bubblesort_table(books, &count_of_records);
	}
	rewind(table);
	{
		int count_of_records = 0;
		book_t books[MAXCOUNT];
		key key_table[MAXCOUNT];
		load_table(table, &count_of_records, books, key_table);
		sort_keys_shell = shell_keys(books, key_table, &count_of_records);
	}
	rewind(table);
		{
		int count_of_records = 0;
		book_t books[MAXCOUNT];
		key key_table[MAXCOUNT];
		load_table(table, &count_of_records, books, key_table);
		sort_table_shell = shell_table(books, &count_of_records);
	}
	rewind(table);

	int count_of_records = 0;
	book_t books[MAXCOUNT];
	key key_table[MAXCOUNT];
	load_table(table, &count_of_records, books, key_table);
	int alreadysorted = 0;
	int menu;
	do
	{	
		printf("\n%sМЕНЮ:\n", YELLOW);
		printf("* 1 Вывод элементов на экран\n");
		printf("* 2 Вывод на экран элементов, упорядоченных по ключу\n");
		printf("* 3 Сортировка таблицы\n");
		printf("* 4 Добавление новой записи\n");
		printf("* 5 Удаление записи\n");
		printf("* 6 Отчет о времени сортировки и памяти\n");
		printf("* 7 Поиск записи по указанной отрасли и году\n");
		printf("* 8 Выход%s\n", RESET);
		printf("Выберите пункт меню:");
		scanf("%d", &menu);
		switch(menu)
		{
			case 1:
			{
				printf("%sСписок книг.%s\n",RED, RESET);
				printf("-----------------------------------------\n");
				for (int i = 0; i < count_of_records; i++)
					print_table(books, i);
				break;
			}
			case 2:
				printf("Sorted? %d\n", alreadysorted);
				if (!alreadysorted)
				{
					bubblesort_keys(books, key_table, &count_of_records);
					printf("%sСписок книг, отсортированный по количеству страниц.%s\n",RED, RESET);
					printf("-----------------------------------------\n");
					for (int i = 0; i < count_of_records; i++)
						print_table(books, key_table[i].number);
				}
				else
					for (int i = 0; i < count_of_records; i++)
						print_table(books, i);

				break;
			case 3:
				bubblesort_table(books, &count_of_records);
				printf("%sТаблица отсортирована.%s\n",RED,RESET);
				alreadysorted = 1;
				break;
			case 4:
				add_new_rec(books, key_table, &count_of_records, filename);
				break;
			case 5:
				del_rec(books, key_table, &count_of_records, filename);
				break;
			case 6:
				printf("%s Время.%s\n",RED,RESET);
				printf("Сортировка таблицы методом пузырька: %lld тиков\n",sort_table_bubble/10);
				printf("Сортировка таблицы методом Шелла: %lld тиков\n", sort_table_shell/10);
				printf("Сортировка таблицы ключей методом пузырька: %lld тиков\n", sort_keys_bubble/10);
				printf("Сортировка таблицы ключей методом Шелла: %lld тиков\n", sort_keys_shell/10);
				printf("%s Память.%s\n",RED,RESET);
				printf("Таблица ключей использует %ld байт памяти\n",sizeof(key)*count_of_records);
				printf("Таблица с данными использует %ld байт памяти\n",sizeof(book_t)*count_of_records);
				break;
			case 7:
				search(books, &count_of_records);
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