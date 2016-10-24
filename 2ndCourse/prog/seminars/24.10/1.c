#include <stdio.h>
#include <stdlib.h>

struct list_node
{
	int num;
	struct list_node *next;
	struct list_node *prev;
};

struct list_node* create_node(int n)
{
	struct list_node *p = malloc(sizeof(struct list_node));
	if (p)
	{
		p->num = n;
		p->next = NULL;
		p->prev = NULL;
	}
	return p;
}

struct list_node* add_node(struct list_node *head, struct list_node *elem) 
{
	if (!head)
	{
		head = elem;
		head->prev = elem;
		head->next = elem;	
		return head; 
	}
	else
	{
		elem->next = head->next;
		head->next = elem;
		elem->prev = head;
		elem->next->prev = elem;
		return elem; // head = elem
	}
}

struct list_node* del_node(struct list_node *head)
{
	if (head->next == head->prev && head->next == head)
	{
		free(head);
		return NULL;
	}
	else
	{
		head->next->prev = head->prev;
		head->prev->next = head->next;
		struct list_node *tmp = head->next;
		free(head);
		return tmp; 
	}
}

void print_node(struct list_node *head)
{
	if (head)
	{
		struct list_node *current = head;
		do
		{
			printf("%d ", current->num);
			current = current->next;
		}
		while (current != head);
		printf("\n");
	}
	else
		printf("Empty list!\n");	
}

int main(void)
{
	int n, m;
	printf("Количество воинов: ");
	scanf("%d", &n);
	printf("m = ");
	scanf("%d", &m);
	struct list_node *head = NULL, *new;
	for (int i = 1; i <= n; i++)
	{
		new = create_node(i);
		head = add_node(head, new);
	} 
	head = head->next;
	print_node(head);

	for (int i = 1; i < n; i++)
	{
		for (int i = 1; i < m; i++)
			head = head->next;
		head = del_node(head);
	}
	printf("Ответ: %d\n", head->num);
	while (head != NULL)
	{
		head = del_node(head);
	}

}