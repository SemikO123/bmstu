#include <stdio.h>

typedef struct list_node
{
	int data;
	struct list_node *next;
} node_t;

typedef struct 
{
	node_t *head;
} stack_t;

void push(stack_t *stack, int x)
{
	node_t *node = create(x);
	if (node)
	{
		node->next = stack->head;
		stack->head = node;
	}
}

int pop(stack_t *stack, int *x)
{
	if (!is_empty(*stack))
	{
		*x = stack->head->data;
		node_t *tmp = stack->head;
		stack->head = stack->head->next;
		free(tmp);
		return 0;
	}
	return -1;
}

int main(void)
{
	stack_t stack1 = {NULL};
	push(&stack1, 17);
	int x = 0;
	if (!pop(&stack1, 1))
		printf("%d", x);
}
