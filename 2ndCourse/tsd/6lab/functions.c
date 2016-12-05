#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

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

struct BinaryTree *insert_element(struct BinaryTree *head, struct BinaryTree *new)
{

	if (head == NULL)
		return new;

	int compare = strcmp(new->data, head->data);
	if (compare < 0)
		head->left = insert_element(head->left, new);
	else if (compare > 0)
		head->right = insert_element(head->right, new);

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
		{
			printf("%s %s %s\n", RED, head->data, RESET);
			head->color = 0; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		}
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

void search_words_to_same_letter(struct BinaryTree *head, char letter, int *count)
{
	if (head)
	{
		
		if (head->data[0] == letter)
		{
			head->color = 1;
			(*count)++;
		}
		search_words_to_same_letter(head->left, letter, &*count);
		search_words_to_same_letter(head->right, letter, &*count);
	}
}

unsigned long long int tick(void)
{
	unsigned long long int time = 0;
	__asm__ __volatile__ ("rdtsc" : "=A" (time));
	return time;
}

void search_words_in_file(FILE *input, char letter, int *count, char *word)
{
	while (fscanf(input, "%s", word) > 0)
	{
		if (word[0] == letter)
			(*count)++;
	}
}

void task()
{
	//FILE *input = fopen("input.txt", "r");
	FILE *input = fopen("25words.txt", "r");
	struct BinaryTree *head = NULL;
	char tmp[20];
	unsigned long long int time01, time02;
	time01 = tick();
	while (fscanf(input, "%s", tmp) > 0)
	{
		head = insert_element(head, add_new(tmp));
	}
	time02 = tick();
	printf("Время создания дерева: %lld\n", time02-time01);
	char letter;
	printf("Поиск слов на определенную букву (введите букву): ");
	scanf("%c", &letter);
	scanf("%c", &letter);
	int count = 0;
	unsigned long long int time1, time2, time3, time4;
	time1 = tick();
	search_words_to_same_letter(head, letter, &count);
	time2 = tick();
	print_tree(head, 0, 0);
	printf("%sКоличество слов на букву '%c': %d %s\n", RED, letter, count, RESET);
	rewind(input);
	int count1 = 0;
	time3 = tick();
	char word[20] = "";
	search_words_in_file(input, letter, &count1, word);
	time4 = tick();
	printf("%sВремя поиска слов на букву %c в дереве: %lld\n", RED, letter, time2-time1);
	printf("Время поиска слов на букву %c в файле: %lld%s\n", letter, time4-time3, RESET);
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
	printf("\n%sПоперечный обход графа:%s\n", RED, RESET);
	in_order(def_head);
	// обратный обход
	printf("\n%sОбратный обход графа:%s\n", RED, RESET);
	post_order(def_head);
}

void make_graph(struct BinaryTree *def_head, struct BinaryTree *parent, FILE *graph)
{
	if (def_head)
	{
		if (parent != NULL)
			fprintf(graph, "%s->%s\n",parent->data, def_head->data);
		make_graph(def_head->left, def_head, graph);
		make_graph(def_head->right, def_head, graph);
	}
}

struct BinaryTree *min(struct BinaryTree *head)
{
	if (head->left != NULL)
		return min(head->left);
	else
		return head;
}

struct BinaryTree *delete_element(struct BinaryTree *head, char *data)
{
	if (head == NULL)
		return head;
	else 
	{
		int compare = strcmp(data, head->data);
		if (compare < 0)
			head->left = delete_element(head->left, data);
		else if (compare > 0)
			head->right = delete_element(head->right, data);
		else if (head->left != NULL && head->right != NULL)
		{
			strcpy(head->data, min(head->right)->data);
			//head->data = min(head->right)->data;
			head->right = delete_element(head->right, head->right->data);
		}
		else
			if (head->left != NULL)
				head = head->left;
			else
				head = head->right;
	}
	return head;
}

void free_tree(struct BinaryTree *head)
{
	if (head == NULL)
		return;
	free_tree(head->left);
	free_tree(head->left);
	free(head);
}
