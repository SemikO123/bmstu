#ifndef _TREES_H_
#define _TREES_H_

typedef struct Tree
{
	char data;
	int count;
	unsigned char height;
	struct Tree *left;
	struct Tree *right;
}Tree;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Tree *from_file_to_avl(Tree *tree);
Tree *from_file_to_bst(Tree *tree);
Tree *input_to_avl(Tree *tree, char *string);
Tree *input_to_bst(Tree *tree, char *string);

Tree *add_new_tree(char data);

Tree *insert_element_bst(Tree *head, Tree *new);
Tree *insert_element_avl(Tree *head, Tree *new);

Tree *search_element(Tree *head, char data);

Tree* delete_element_avl(Tree* tr, char ch);
Tree *delete_element_bst(Tree *tr, char ch);
Tree* remove_min_elem(Tree* tr);
Tree* minimum(Tree* tr);

unsigned char height(Tree* tr);
void get_height(Tree* tr);
int baldiff(Tree* tr);
Tree* rotateright(Tree* tr);
Tree* rotateleft(Tree* tr) ;
Tree* balance(Tree* tr);
void free_all(Tree *tree);

void print_tree(Tree *head, int down, int lr);

#endif 