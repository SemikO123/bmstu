#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>



#define N 20
#define REITERATION -1
#define LENGTH 100

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define WHITE   "\033[1;37m"

/*
Обход дерева, включение,  исключение и поиск узлов.
2. Построить двоичное дерево поиска, в вершинах которого находятся слова из 
текстового файла. Вывести его на экран в виде дерева. Определить количество 
вершин дерева, содержащих слова, начинающиеся на указанную букву. Выделить 
эти вершины цветом. Сравнить время поиска начинающихся на указанную букву слов 
в дереве и в файле. \
*/

struct BinaryTree
{
	char data[N];
	struct BinaryTree *left;
	struct BinaryTree *right;
	int color;
};

struct BinaryTree *add_new(char *data)
{
	struct BinaryTree *new = malloc(sizeof(struct BinaryTree));
	if (new)
	{
		strcpy(new->data, data);
		new->left = NULL;
		new->right = NULL;
		new->color = 0; 
	}
	return new;
}

struct BinaryTree *insert_element(struct BinaryTree *head, struct BinaryTree *prev, struct BinaryTree *new, FILE *graph)
{

	if (head == NULL)
	{
		if (prev != NULL)
			fprintf(graph, "%s -> %s \n", prev->data, new->data);
		return new;
	}

	int compare = strcmp(new->data, head->data);
	if (compare < 0)
		head->left = insert_element(head->left, head, new, graph);
	else
		head->right = insert_element(head->right, head, new, graph);

	return head;
}

void print_tree(struct BinaryTree *head, int down, int lr)
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
		if (head->color == 0)
			printf(" %s\n",head->data);
		if (head->color == 1)
			printf("%s %s %s\n", RED, head->data, RESET);
		print_tree(head->left, down+1, 1);
	}
}

struct BinaryTree *search_element(struct BinaryTree *head, const char *data)
{
	if (head == NULL)
		return NULL;

	int compare = strcmp(data, head->data);
	if (compare == 0)
		return head;
	else if (compare < 0)
		return search_element(head->left, data);
	else
		return search_element(head->right, data);
}

// ─ ╰╶ ╭╶ 
// └  ˩ ˥
// │

void task()
{
	FILE *input = fopen("input.txt", "r");
	struct BinaryTree *head = NULL;
	char tmp[20];
	while (fscanf(input, "%s", tmp) > 0)
	{
		head = insert_element(head, NULL, add_new(tmp), NULL);
	}
	print_tree(head, 0, 0);
	fclose(input);
}

void pre_order(struct BinaryTree *def_head)
{
	if (def_head)
	{
		printf("%s ", def_head->data);
		pre_order(def_head->left);
		pre_order(def_head->right);
	}	
}

void in_order(struct BinaryTree *def_head)
{
	if (def_head)
	{
		in_order(def_head->left);
		printf("%s ", def_head->data);
		in_order(def_head->right);
	}	
}

void post_order(struct BinaryTree *def_head)
{
	if (def_head)
	{
		post_order(def_head->left);
		post_order(def_head->right);
		printf("%s ", def_head->data);
	}	
}

void tree_traversal(struct BinaryTree *def_head)
{
	// прямой обход
	printf("%sПрямой обход графа:%s\n", RED, RESET);
	pre_order(def_head);
	// поперечный обход
	printf("%sПоперечный обход графа:%s\n", RED, RESET);
	in_order(def_head);
	// обратный обход
	printf("%sОбратный обход графа:%s\n", RED, RESET);
	post_order(def_head);
}




int main(void)
{	
	int menu = -1;
	struct BinaryTree *def_head = NULL;
	FILE *graph = fopen("graph.gv", "w");
	fprintf(graph, "digraph G{\n");
	do
	{
		printf("%sМеню работы с бинарным деревом:\n",YELLOW);
		printf("(1) Добавить элемент (слово) в дерево\n");
		printf("(2) Удалить элемент (слово) из дерева\n");
		printf("(3) Поиск узла\n");
		printf("(4) Печать дерева\n");
		printf("(5) Обход дерева\n");
		printf("(6) Выполнение задания лабораторной работы\n");
		printf("(0) Завершение работы программы%s\n",RESET);
		printf("Выберите пункт меню: ");
		scanf("%d", &menu);
		switch(menu)
		{
			case 1:
				printf("Введите информацию для узла: ");
				char data[20];
				scanf("%s", data);
				def_head = insert_element(def_head, NULL, add_new(data), graph);
				printf("%sЭлемент %s добавлен%s\n", RED, data, RESET);
				break;	
			case 2:
				break;
			case 3:
				printf("Введите информацию, которую нужно найти: ");
				char data1[20];
				scanf("%s", data1);
				struct BinaryTree *element = search_element(def_head, data1);
				if (element == NULL)
					printf("%s Не найдено%s\n", RED, RESET);
				else
				{	
					element->color = 1;
					print_tree(def_head, 0, 0);
					element->color = 0;
				}
				break;
			case 4:
				if (def_head == NULL)
					printf("%s Дерево пусто\n %s", RED, RESET);
				else
					print_tree(def_head, 0, 0);
				break;
			case 5:
				if (def_head == NULL)
					printf("%s Дерево пусто\n %s", RED, RESET);
				else
					tree_traversal(def_head);
				break;
			case 6:
				task();
				break;
			case 0:
				break;
			default:
				printf("Пункт меню выбран неверно\n");
				break;
		}
	}
	while (menu != 0); 
	fprintf(graph, "}");
	fclose(graph);



}