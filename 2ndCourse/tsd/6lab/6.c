#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>



#define N 20
#define REITERATION -1

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
};

struct BinaryTree *add_new(char *data)
{
	struct BinaryTree *new = malloc(sizeof(struct BinaryTree));
	if (new)
	{
		strcpy(new->data, data);
		new->left = NULL;
		new->right = NULL;
	}
	return new;
}

struct BinaryTree *insert_element(struct BinaryTree *head, struct BinaryTree *new)
{
	if (head == NULL)
		return new;

	int compare = strcmp(new->data, head->data);
	if (compare < 0)
		head->left = insert_element(head->left, new);
	else
		head->right = insert_element(head->right, new);

	return head;
}

void print_tree(struct BinaryTree *head, int down)
{
	if (head)
	{
		print_tree(head->right, down+1);
		for (int i = 0; i < down; i++)
			printf("           ");
		printf("%s\n",head->data);
		print_tree(head->left, down+1);
	}

}

int main(void)
{
	FILE *input = fopen("input.txt", "r");
	struct BinaryTree *head = NULL;
	char tmp[20];
	while (fscanf(input, "%s", tmp) > 0)
	{
		//printf("len=%d slovo=%s", (int)strlen(tmp), tmp);
		head = insert_element(head, add_new(tmp));
	}
	print_tree(head, 0);
	fclose(input);	
}