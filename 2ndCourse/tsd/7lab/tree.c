#include "tree.h"

static int node_count = 0;
static size_t counts_made = 0;


unsigned long long int tick(void)
{
    unsigned long long int time = 0;
    __asm__ __volatile__ ("rdtsc" : "=A" (time));
    return time;
}

unsigned int hash(int info, int key)
{
    //printf("info = %d key = %d\n", info, key);
    return (unsigned int) info % key;
}

tree_node *create_node(int info)
{
    tree_node *node = malloc(sizeof(tree_node));
    if (node)
    {
        node->info = info;
        node->count = 1;
        node->height = 1;
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}


tree_node *lookup(tree_node *tree, int info)
{
    counts_made++;
    if (tree == NULL)
        return NULL;

    if (info == tree->info)
        return tree;
    else if (info < tree->info)
        return lookup(tree->left, info);
    else
        return lookup(tree->right, info);
}

void zero_count_made(void)
{
    counts_made = 0;
}

void show_count(void)
{
    printf("%d\n", (int)counts_made);
}

int get_count_made(void)
{
    return (int)counts_made;
}
void apply_in(tree_node *tree, void (*f)(tree_node*, void*), void *arg)
{
    if (tree == NULL)
        return;

    // pre-order
    // f(tree, arg);
    apply_in(tree->left, f, arg);
    // in-order
    f(tree, arg);
    apply_in(tree->right, f, arg);
    // post-order
    // f(tree, arg);
}

void apply_post(tree_node *tree, void (*f)(tree_node*, void*), void *arg)
{
    if (tree == NULL)
        return;

    // pre-order
    // f(tree, arg);
    apply_post(tree->left, f, arg);
    // in-order
    // f(tree, arg);
    apply_post(tree->right, f, arg);
    // post-order
    f(tree, arg);
}


void print_node(tree_node *tree, void *arg)
{
    //FILE *f = fopen("data.txt", "a");
    printf("On element: %d, adr:, count:%d\n", tree->info, /*tree,*/ tree->count);
}

void apply_pre(tree_node *tree, void (*f)(tree_node*, void*), void *arg)
{
    if (tree == NULL)
        return;

    f(tree, arg);
    apply_pre(tree->left, f, arg);
    apply_pre(tree->right, f, arg);
}


void free_node(tree_node *tree, void *param)
{
    if (!tree)
        free(tree);
    tree = NULL;
}

void free_tree(tree_node *tree)
{
    if (!tree)
        apply_post(tree, free_node, NULL);
}

tree_node *insert(tree_node *tree, tree_node *node)
{
    node_count++;
    if (tree == NULL)
        return node;
    
    if (node->info == tree->info)
    {
        tree->count++;
        free(node);
    }
    else if (node->info < tree->info)
        tree->left = insert(tree->left, node);
    else
        tree->right = insert(tree->right, node);
    //puts("insert done");
    return balance(tree);
}

tree_node *bst_insert(tree_node *tree, tree_node *node, int *count)
{
    node_count++;
    if (tree == NULL)
        return node;
    (*count)++;
    if (node->info == tree->info)
    {
        tree->count++;
        free(node);
    }
    else if (node->info < tree->info)
        tree->left = insert(tree->left, node);
    else
        tree->right = insert(tree->right, node);
    //puts("insert done");
    return tree;
}

tree_node *read_tree_from_file(FILE *f)
{
    rewind(f);
    int tmp;
    tree_node *tree = NULL;
    while (fscanf(f, "%d", &tmp) == 1)
    {
        tree_node *cur = create_node(tmp);
        tree = insert(tree, cur);
    }
    return tree;
}
tree_node *bst_read_tree_from_file(FILE *f, int *count)
{
    rewind(f);
    int tmp;
    tree_node *tree = NULL;
    while (fscanf(f, "%d", &tmp) == 1)
    {
        tree_node *cur = create_node(tmp);
        tree = bst_insert(tree, cur, count);
    }
    return tree;
}

tree_node* findmin(tree_node* p)
{
	return p->left?findmin(p->left):p;
}

tree_node* removemin(tree_node* p) 
{
	if( p->left==0 )
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}

tree_node* remove_tree(tree_node* p, int k) 
{
	if( !p ) return 0;
	if( k < p->info )
		p->left = remove_tree(p->left,k);
	else if( k > p->info )
		p->right = remove_tree(p->right,k);
	else //  k == p->info
	{
		tree_node* q = p->left;
		tree_node* r = p->right;
		free(p);
		if( !r ) return q;
		tree_node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}

tree_node* bst_remove_tree(tree_node* p, int k) 
{
	if( !p ) return 0;
	if( k < p->info )
		p->left = remove_tree(p->left,k);
	else if( k > p->info )
		p->right = remove_tree(p->right,k);
	else //  k == p->info
	{
		tree_node* q = p->left;
		tree_node* r = p->right;
		free(p);
		if( !r ) return q;
		tree_node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return min;
	}
	return p;
}

void level_apply(int *levels, tree_node *tree, int index)
{
    if (tree != NULL)
    {
        levels[index]++;
        level_apply(levels, tree->left, index+1);
        level_apply(levels, tree->right, index+1);
    }
}

int *count_levels(tree_node *tree, int *n)
{
    int *levels = malloc(sizeof(int) * node_count);
    *n = node_count;
    for (int i = 0; i < *n; i++)
        levels[i] = 0;
    level_apply(levels, tree, 0);
    return levels;
}

void print_array(int *arr, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] != 0)
            printf("level %d: %d\n", i, arr[i]);
    }
}

unsigned char height(tree_node* p)
{
	return p ? p->height : 0;
}

int bfactor(tree_node* p)
{
	return height(p->right) - height(p->left);
}

void fixheight(tree_node* p)
{
	unsigned char hl = height(p->left);
	unsigned char hr = height(p->right);
	p->height = (hl>hr ? hl : hr) + 1;
	//printf("elem %d has height %d\n", p->info, p->height);
}

tree_node* rotateright(tree_node* p) 
{
	tree_node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}

tree_node* rotateleft(tree_node* q) 
{
	tree_node* p = q->right;
	q->right = p->left;
	p->left = q;
	fixheight(q);
	fixheight(p);
	return p;
}

tree_node* balance(tree_node* p)
{
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p; 
}
