#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct BinaryTree
{
	int data;
	struct BinaryTree *left;
	struct BinaryTree *right;
	struct BinaryTree *father;
};

struct BinaryTree *new(int data)
{
	struct BinaryTree *new = malloc(sizeof(struct BinaryTree));
	new->data = data;
	new->left = NULL;
	new->right = NULL;
	new->father = NULL;
	return new;
}

void Make_Binary_Tree(BinaryTree** Node, int n){
  BinaryTree** ptr;//вспомогательный указатель
  srand(time(NULL)*1000);
  while (n > 0) {
    ptr = Node;
    while (*ptr != NULL) {
      if ((double) rand()/RAND_MAX < 0.5) 
        ptr = &((*ptr)->Left);
      else ptr = &((*ptr)->Right);
    }
    (*ptr) = new BinaryTree();
    cout << "Введите значение ";
    cin >> (*ptr)->Data;
    n--;
  }
}

struct BinaryTree *make_tree(struct BinaryTree *head; struct BinaryTree *new)
{
	struct BinaryTree *tmp = head;
	while (tmp != NULL)
	{
		if (tmp->left != NULL)
			if (tmp->right != NULL)
				tmp = tmp->left;
			else
			{
				
			}
		else
		{
			tmp->left = new;
			new->father = tmp;
		}

	}


}

int main(void)
{
	struct BinaryTree *head = new(5);
	printf("%d\n", head->data);
	free(head);
	printf("QQQQQQQQ!");
}