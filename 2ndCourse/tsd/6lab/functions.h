#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

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

struct BinaryTree
{
	char data[N];
	struct BinaryTree *left;
	struct BinaryTree *right;
	int color;
};

struct BinaryTree *add_new(char *data);
struct BinaryTree *insert_element(struct BinaryTree *head, struct BinaryTree *new);
void print_tree(struct BinaryTree *head, int down, int lr);
struct BinaryTree *search_element(struct BinaryTree *head, const char *data);
void search_words_to_same_letter(struct BinaryTree *head, char letter, int *count);
unsigned long long int tick(void);
void search_words_in_file(FILE *input, char letter, int *count, char *word);
void task();
void pre_order(struct BinaryTree *def_head);
void in_order(struct BinaryTree *def_head);
void post_order(struct BinaryTree *def_head);
void tree_traversal(struct BinaryTree *def_head);
void make_graph(struct BinaryTree *def_head, struct BinaryTree *parent, FILE *graph);
struct BinaryTree *min(struct BinaryTree *head);
struct BinaryTree *delete_element(struct BinaryTree *head, char *data);
void free_tree(struct BinaryTree *head);
#endif