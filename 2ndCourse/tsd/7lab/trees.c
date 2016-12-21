#include "trees.h"

Tree *add_new_tree(char data)
{
	Tree *new = malloc(sizeof(Tree));
	if (new)
	{
		new->data = data;
		new->left = NULL;
		new->right = NULL;
		new->count = 1; 
		new->height = 1;
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
		printf(" %c(%d)-%d\n",head->data, head->count, head->height-1);
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
	// if (tr)
	// 	printf("HEIGHT %c = %d\n", tr->data, tr->height);
	return tr ? tr->height : 0;
}

void get_height(Tree* tr)
{
	unsigned char left = height(tr->left);
	unsigned char right = height(tr->right);
	tr->height = (left>right ? left : right) + 1;
	//printf("elem %c has height %d\n", tr->data, tr->height);
}


int baldiff(Tree* tr)
{
	//printf("BalDiff right-left = %d-%d\n",  height(tr->right), height(tr->left));
	return height(tr->right) - height(tr->left);
}

Tree* rotateright(Tree* tr) 
{
	//printf("Rotate right!\n");
	Tree* p = tr->left;
	tr->left = p->right;
	p->right = tr;
	get_height(tr);
	get_height(p);
	return p;
}

Tree* rotateleft(Tree* tr) 
{
	//printf("Rotate left!\n");
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
					tree = insert_element_avl(tree, add_new_tree(ch));
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
				tree = insert_element_bst(tree, add_new_tree(ch));
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
			tree = insert_element_avl(tree, add_new_tree(string[i]));
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
			tree = insert_element_bst(tree, add_new_tree(string[i]));
	}
	return tree;
}

void free_all(Tree *tree)
{
	free_all(tree->left);
	free_all(tree->right);
	free(tree);
}

Tree* minimum(Tree* tr)
{
	if (tr->left)
		return minimum(tr->left);
	else
		return tr;
}

Tree* remove_min_elem(Tree* tr) 
{
	if( tr->left==0 )
		return tr->right;
	tr->left = remove_min_elem(tr->left);
	return balance(tr);
}

Tree* delete_element_avl(Tree* tr, char ch) 
{
	if( !tr ) 
		return 0;
	if( ch < tr->data )
		tr->left = delete_element_avl(tr->left, ch);
	else if( ch > tr->data )
		tr->right = delete_element_avl(tr->right, ch);
	else //  ch == tr->data
	{
		Tree* q = tr->left;
		Tree* r = tr->right;
		free(tr);
		if( !r ) 
			return q;
		Tree* min = minimum(r);
		min->right = remove_min_elem(r);
		min->left = q;
			return balance(min);
	}
	return balance(tr);
}

Tree *delete_element_bst(Tree *tr, char ch)
{
	if( !tr ) 
		return 0;
	if( ch < tr->data )
		tr->left = delete_element_bst(tr->left, ch);
	else if( ch > tr->data )
		tr->right = delete_element_bst(tr->right, ch);
	else //  ch == tr->data
	{
		Tree* q = tr->left;
		Tree* r = tr->right;
		free(tr);
		if( !r ) 
			return q;
		Tree* min = minimum(r);
		min->right = remove_min_elem(r);
		min->left = q;
			return min;
	}
	return tr;
}



