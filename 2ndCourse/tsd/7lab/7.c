#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define PINK    "\033[1;35m"
#define WHITE   "\033[1;37m"

typedef struct Tree
{
	char data;
	int count;
	unsigned char height;
	struct Tree *left;
	struct Tree *right;
}Tree;

Tree *add_new(char data)
{
	Tree *new = malloc(sizeof(Tree));
	if (new)
	{
		new->data = data;
		new->left = NULL;
		new->right = NULL;
		new->count = 1; 
		new->height = 0;
	}
	return new;
}

void print_tree(Tree *head, int down, int lr)
{
	if (head)
	{
		print_tree(head->right, down+1, 2);
		for (int i = 0; i < down; i++)
			printf("         ");
		switch(lr)
		{
			case 0:
				printf("➙");
				break;
			case 1:
				printf("➘");
				break;
			case 2:
				printf("➚");
				break;
		}
		printf(" %c(%d)-%d\n",head->data, head->count, head->height);
		print_tree(head->left, down+1, 1);
	}
}

Tree *insert_element_bst(Tree *head, Tree *new)
{

	if (head == NULL)
		return new;

	if (new->data < head->data)
		head->left = insert_element_bst(head->left, new);
	else if (new->data > head->data)
		head->right = insert_element_bst(head->right, new);

	return head;
}

Tree *search_element(Tree *head, char data)
{
	if (head == NULL)
		return NULL;
	if (head->data == data)
		return head;
	else if (data < head->data)
		return search_element(head->left, data);
	else
		return search_element(head->right, data);
}

unsigned char height(Tree* tr)
{
	return tr ? tr->height : 0;
}

void get_height(Tree* tr)
{
	unsigned char left = height(tr->left);
	unsigned char right = height(tr->right);
	tr->height = (left>right ? left : right) + 1;
}


int baldiff(Tree* tr)
{
	return height(tr->right) - height(tr->left);
}

Tree* rotateright(Tree* tr) 
{
	Tree* p = tr->left;
	tr->left = p->right;
	p->right = tr;
	get_height(tr);
	get_height(p);
	return p;
}

Tree* rotateleft(Tree* tr) 
{
	Tree* p = tr->right;
	tr->right = p->left;
	p->left = tr;
	get_height(tr);
	get_height(p);
	return p;
}

Tree* balance(Tree* tr)
{
	get_height(tr);
	if (baldiff(tr) == 2)
	{
		if (baldiff(tr->right) < 0)
			tr->right = rotateright(tr->right);
		return rotateleft(tr);
	}
	if (baldiff(tr) == -2)
	{
		if (baldiff(tr->left) > 0)
			tr->left = rotateleft(tr->left);
		return rotateright(tr);
	}
	return tr;
}

Tree *insert_element_avl(Tree *head, Tree *new)
{

	if (head == NULL)
		return new;

	if (new->data < head->data)
		head->left = insert_element_avl(head->left, new);
	else if (new->data > head->data)
		head->right = insert_element_avl(head->right, new);

	return balance(head);
}

Tree *from_file_to_avl(Tree *tree)
{
	FILE *f = fopen("in.txt", "r");
	char ch = '.';
	while (ch != '\n')
	{
		fscanf(f, "%c", &ch);
		{
			if (ch != '\n')
			{
				Tree *find_elem = search_element(tree, ch);
				if (find_elem)
					(find_elem->count)++;
				else
					tree = insert_element_avl(tree, add_new(ch));
			}
		}
	}
	fclose(f);
	return tree;
}

Tree *from_file_to_bst(Tree *tree)
{
	FILE *f = fopen("in.txt", "r");
	char ch = '.';
	while (ch != '\n')
	{
		fscanf(f, "%c", &ch);
		if (ch != '\n')
		{
			Tree *find_elem = search_element(tree, ch);
			if (find_elem)
				(find_elem->count)++;
			else
				tree = insert_element_bst(tree, add_new(ch));
		}
	}
	fclose(f);
	return tree;
}

Tree *input_to_avl(Tree *tree, char *string)
{
	int count = strlen(string);
	for (int i = 0; i < count; i++)
	{
		Tree *find_elem = search_element(tree, string[i]);
		if (find_elem)
			(find_elem->count)++;
		else
			tree = insert_element_avl(tree, add_new(string[i]));
	}
	return tree;
}

Tree *input_to_bst(Tree *tree, char *string)
{
	int count = strlen(string);
	for (int i = 0; i < count; i++)
	{
		Tree *find_elem = search_element(tree, string[i]);
		if (find_elem)
			(find_elem->count)++;
		else
			tree = insert_element_bst(tree, add_new(string[i]));
	}
	return tree;
}

void free_all(Tree *tree)
{
	free_all(tree->left);
	free_all(tree->right);
	free(tree);
}

int main(void)
{
	int menu = -1;
	Tree *bst = NULL;
	Tree *avl = NULL;
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
				// info_to_close(hash_close close_table);
				// info_to_open(hash_open open_table);
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
				// fflush(stdin);
    //         	getchar();
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

				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 0:
				break;
		}
	}
	while (menu != 0);
}