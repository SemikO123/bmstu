#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trees.h"

/*
построить хеш-таблицу по указанным данным. Сравнить эффективность поиска в 
сбалансированном двоичном дереве, в двоичном дереве поиска и в хеш-таблице 
(используя открытую и закрытую адресацию). Вывести на экран деревья и хеш-таблицы. 
Подсчитать среднее количество сравнений для поиска данных в указанных структурах. 
Произвести реструктуризацию хеш-таблицы, если среднее количество сравнений больше 
указанного. Оценить эффективность использования этих структур (по времени и памяти) 
для поставленной задачи. Оценить эффективность поиска в хеш-таблице при различном 
количестве коллизий и при различных методах  их разрешения.

0. Сбалансировать дерево (задача №6) после удаления повторяющихся букв. 
Вывести его на экран в виде дерева. Составить хеш-таблицу, содержащую буквы 
(хеш - по количеству различных букв) и количество их вхождений во введенной строке. 
ывести таблицу на экран. Осуществить поиск введенной буквы в двоичном дереве поиска,
в сбалансированном дереве и в хеш-таблице. Сравнить время поиска, объем памяти и 
количество сравнений при использовании различных структур данных. 
*/

#define LIMIT_COLLISIONS 10
#define ADD_SIZE 5

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define PINK    "\033[1;35m"
#define WHITE   "\033[1;37m"

typedef struct Hash_op
{
	struct Hash_op *next;
	char data;
	int count;
} Hash_op;

typedef struct Hash_Open_Table
{
	int size;
	int collisions;
	Hash_op *tbl;
} Hash_Open_Table;


Hash_Open_Table *restucture_hashO(Hash_Open_Table *table);

int hash(char ch, int key)
{
	return (int)ch % key;
}

Hash_op *add_to_end(Hash_op *head, Hash_op *node, int *collis)
{
	if (!head)
		return node;
	Hash_op *current = head;
	for (; current->next; current = current->next)
		;
	current->next = node;
	(*collis) = 1;
	return head;
}

Hash_Open_Table *add_new_hashO(Hash_Open_Table *table, char ch)
{
	if (!table)
		return NULL;
	while (table->collisions >= LIMIT_COLLISIONS)
		table = restucture_hashO(table);
	int num = hash(ch, table->size);
	int collis = 0;
	Hash_op *res = malloc(sizeof(Hash_op));
	if (res)
	{
		res->next = NULL;
		res->data = ch;
	}
	else
		return NULL;
	table->tbl[num].next = add_to_end(table->tbl[num].next, res, &collis);
	table->collisions += collis;
	return table;
}

Hash_op *new_hash_o_elem(int size)
{
	Hash_op *result = malloc(sizeof(Hash_op)*size);
	if (!result)
		for (int i = 0; i < size; i++)
		{
			result[i].next = NULL;
			result[i].data = '0';
			result[i].count = 1;
		}
	return result;
}

Hash_Open_Table *new_open_hash(int size)
{
	Hash_Open_Table *table = malloc(sizeof(Hash_Open_Table));
	table->size = size;
	table->tbl = new_hash_o_elem(table->size);
	table->collisions = 0;
	return table;
}

Hash_Open_Table *restucture_hashO(Hash_Open_Table *table)
{
	if (!table)
		return NULL;
	printf("Реструктуризация хеш-таблицы. Размер увеличен на %d\n", ADD_SIZE);
	Hash_Open_Table *new_table = new_open_hash(table->size + ADD_SIZE);
	for (int i = 0; i < table->size; i++)
		if (!table->tbl[i].next)
		{
			Hash_op *current = table->tbl[i].next;
			for (; current; current = current->next)
				new_table = add_new_hashO(new_table, current->data);
		}
	return new_table;
}


Hash_op *search_in_HashO(Hash_Open_Table *table, char ch)
{
	if (!table)
		return NULL;
	int num = hash(ch, table->size);
	Hash_op *current = table->tbl[num].next;
	for (; current; current = current->next)
		if (current->data == ch)
			return current;
	return NULL;
}

Hash_Open_Table *from_file_to_hashO(Hash_Open_Table *table)
{
	FILE *f = fopen("in.txt", "r");
	table = new_open_hash(5);
	char ch = '.';
	while (ch != '\n')
	{
		fscanf(f, "%c", &ch);
		if (ch != '\n')
		{
			Hash_op *find_elem = search_in_HashO(table, ch);
			if (find_elem)
				(find_elem->count)++;
			else
				table = add_new_hashO(table, ch);
		}
	}
	fclose(f);
	return table;
}

void print_open_hash(const Hash_Open_Table *table)
{
    if (table == NULL)
        return;
    printf("Collisions: %d\n", table->collisions);
    for (int i = 0; i < table->size; i++)
    {
        if (table->tbl[i].next != NULL)
        {
            printf("%5d)", i);
            for (Hash_op *cur = table->tbl[i].next; cur; cur = cur->next)
                printf("%c ", cur->data);
            puts("");
        }
    }
}

int main(void)
{
	int menu = -1;
	Tree *bst = NULL;
	Tree *avl = NULL;
	Hash_Open_Table *open_tbl = NULL;
	do
	{
		printf("%sМЕНЮ:\n", YELLOW);
		printf("(1) Загрузить информацию из файла\n");
		printf("(2) Ввести информацию с клавиатуры\n");
		printf("(3) Вывести на экран деревья и хеш-таблицы\n");
		printf("(4) Добавить элемент (букву)\n");
		printf("(5) Удалить элемент (букву)\n");
		printf("(6) Найти введенный элемент (букву)\n");
		printf("(7) Сравнить поиск элемента в разных структрах\n");
		printf("(0) Завершение работы программы%s\n", RESET);
		printf("Выберите пункт меню: ");
		scanf("%d", &menu);
		fflush(stdin);
        getchar();
		switch(menu)
		{
			case 1:
			{
				bst = NULL;
				avl = NULL;
				bst = from_file_to_bst(bst);
				if (bst)
					printf("%sBST создано!%s\n", PINK, RESET);
				avl = from_file_to_avl(avl);
				if (avl)
					printf("%sAVL создано!%s\n", PINK, RESET);
				open_tbl = from_file_to_hashO(open_tbl);
				if (open_tbl)
					printf("%sOpenHashTable создано!%s\n", PINK, RESET);
				// info_to_open(hash_open open_table);
				// fflush(stdin);
    //         	getchar();
				break;
			}
			case 2:
				printf("Введите строку, из букв которой будут сгенерированы структуры:\n");
				char string[100];
				bst = NULL;
				avl = NULL;
				scanf("%s", string);
				bst = input_to_bst(bst, string);
				if (bst)
					printf("%sBST создано!%s\n", PINK, RESET);

				avl = input_to_avl(avl, string);
				if (avl)
					printf("%sAVL создано!%s\n", PINK, RESET);

				fflush(stdin);
            	getchar();
				break;
			case 3:
				if (bst)
				{
					printf("%sBinary Search Tree\n%s", RED, RESET);
					print_tree(bst, 0, 0);
				}
				else
					printf("%sBST doesn't found!%s\n", PINK, RESET);

				if (avl)
				{
					printf("%sSelf-Balancing Binary Search Tree\n%s", RED, RESET);
					print_tree(avl, 0, 0);
				}
				else
					printf("%sAVL doesn't found!%s\n", PINK, RESET);

				if (open_tbl)
				{
					printf("%sOpen Hash Table \n%s", RED, RESET);
					print_open_hash(open_tbl);
				}
				else
					printf("%sOHT doesn't found!%s\n", PINK, RESET);

				break;
			case 4:
			{
				printf("Введите элемент (букву), который нужно добавить: ");
				char ch;
				scanf("%c", &ch);
				//bst
				Tree *find_elem = search_element(bst, ch);
				if (find_elem)
					(find_elem->count)++;
				else
					bst = insert_element_bst(bst, add_new_tree(ch));
				printf("%sЭлемент добавлен в BST!\n%s", PINK, RESET);
				//avl
				Tree *find_elem1 = search_element(avl, ch);
				if (find_elem1)
					(find_elem1->count)++;
				else
					avl = insert_element_avl(avl, add_new_tree(ch));
				printf("%sЭлемент добавлен в AVL!\n%s", PINK, RESET);
				break;
			}
			case 5:
			{
				printf("Введите элемент (букву), который нужно удалить: ");
				char ch;
				scanf("%c", &ch);
				//bst
				bst = delete_element_bst(bst, ch);
				printf("%sЭлемент удален из BST!\n%s", PINK, RESET);
				//avl
				avl = delete_element_avl(avl, ch);
				printf("%sЭлемент удален из AVL!\n%s", PINK, RESET);
				break;
			}
			case 6:
				break;
			case 0:
				break;
		}
	}
	while (menu != 0);
}