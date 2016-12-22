#ifndef TISD_LAB_6
#define TISD_LAB_6


typedef struct tree_node
{
    int info;
    int count;
    unsigned char height;
    struct tree_node *left;
    struct tree_node *right;
} tree_node;

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define PINK    "\033[1;35m"
#define WHITE   "\033[1;37m"

#define panic(A)            \
do                          \
{                           \
    fprintf(stderr, A);     \
    putc('\n',stderr);      \
}                           \
while(0)


unsigned long long int tick(void);
unsigned int hash(int info, int key);
tree_node* create_node(int info);
tree_node* insert(tree_node *tree, tree_node *node);
tree_node *bst_insert(tree_node *tree, tree_node *node, int *count);
tree_node* bst_remove_tree(tree_node* p, int k);
tree_node *bst_read_tree_from_file(FILE *f, int *count);
tree_node *lookup(tree_node *tree, int info);
void apply_in(tree_node *tree, void (*f)(tree_node*, void*), void *arg);
void apply_post(tree_node *tree, void (*f)(tree_node*, void*), void *arg);
void apply_pre(tree_node *tree, void (*f)(tree_node*, void*), void *arg);
void to_dot(tree_node *tree, void *param);
void export_to_dot(FILE *f, const char *tree_name, tree_node *tree);
void free_tree(tree_node *tree);
void free_node(tree_node *tree, void *param);
tree_node *read_tree_from_file(FILE *f);
tree_node* remove_tree(tree_node* p, int k);
tree_node* removemin(tree_node* p);
tree_node* findmin(tree_node* p);
void level_apply(int *levels, tree_node *tree, int index);
int *count_levels(tree_node *tree, int *n);
void print_array(int *arr, int n);
//void print_tree(tree_node *tree, int elem);
void print_node(tree_node *tree, void *arg);
// void print_node_to_file(const tree_node *tree, void *param);
// void print_tree_to_file(FILE *f, const tree_node *tree);
unsigned char height(tree_node* p);
int bfactor(tree_node* p);
void fixheight(tree_node* p);
tree_node* rotateright(tree_node* p);
tree_node* rotateleft(tree_node* q);
tree_node* balance(tree_node* p);
void show_count(void);
void zero_count_made(void);
int get_count_made(void);
#endif // TISD_LAB_6
