#include <stdio.h>
#include <stdlib.h>
#define N 3

/*
Проверить правильность расстановки скобок трех типов 
(круглых, квадратных и фигурных) в выражении.
**/

struct stack_t 
{
	char data[N];
	int size;
};

static char *error_names[]=
{
	"OK\n",
	"STACK UNDERFLOW\n",
	"STACK OWERFLOW\n"
};

enum errors
{
	OK,
	STACK_UNDERFLOW,
	STACK_OWERFLOW,
} error;


void push(struct stack_t *stack, char value)
{
	if (stack->size >= N)
		error = STACK_OWERFLOW;
	else
	{
		error = OK;
		stack->data[stack->size] = value;
		stack->size++;
	}
}

int pop(struct stack_t *stack)
{
	if (stack->size <= 0)
	{
		error = STACK_UNDERFLOW;
		return error;
	}
	else
	{
		error = OK;
		stack->size--;
		return stack->data[stack->size];
	}
}

void print_stack(struct stack_t *stack)
{
	printf("Stack : ");
	for (int i = 0; i < stack->size; i++)
	{
		printf("%c ",stack->data[i]);
	}
	printf("\n");
}

int main(void)
{
	struct stack_t stack;
	stack.size = 0;

	push(&stack, 'w');
	print_stack(&stack);
	push(&stack, 'q');
	print_stack(&stack);
	pop(&stack);
	print_stack(&stack);
	push(&stack, 'r');
	print_stack(&stack);
	push(&stack, 's');
	print_stack(&stack);
	push(&stack, 'd');
	pop(&stack);
	print_stack(&stack);
	printf("%s",error_names[error]);

}
