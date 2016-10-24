#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "functions.h"

char opposite_bracket(char bracket)
{
	if (bracket == '{')
		return '}';
	if (bracket == '}')
		return '{';
	if (bracket == '[')
		return ']';
	if (bracket == ']')
		return '[';
	if (bracket == '(')
		return ')';
	if (bracket == ')')
		return '(';
	return 0;
}

void push_a(struct stack_ta *stack, char value)
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

int pop_a(struct stack_ta *stack)
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

void print_stack_a(struct stack_ta *stack)
{
	printf("%s* Cтек: %s", YELLOW,    RESET);
	for (int i = 0; i < stack->size; i++)
		printf("%c ",stack->data[i]);
	//printf("\n");
	printf("\nВывести адреса элементов стека? (y/n): ");
	char answer[2];
	scanf("%s", answer);
	if (*answer == 'y')
	{	
		printf("%s* Адреса элементов стека: %s", YELLOW,    RESET);
		for (int i = 0; i < stack->size; i++)
		{
			char *p = &stack->data[i];
			printf("%p ",(void*)p);
		}
		printf("\n");
	}

}

char *stack_adress_a(struct stack_ta *stack)
{
	char *p = &stack->data[stack->size];
	return p;
}

int filling_stack_a(struct stack_ta *stack, const char *string, int *size)
{
	int error_code;
	for (int i=0; i < strlen(string); i++)
	{
		if ((string[i] >= 'A' && string[i] <= 'Z') || (string[i] >= 'a' && string[i] <= 'z') || (strlen(string) == 0))
		{
			error_code = INCORRECT;
			return error_code;
		}
		if (string[i] == '{' || string[i] == '}' || string[i] == '[' || string[i] == ']' || string[i] == '(' || string[i] == ')')
			push_a(stack, string[i]);
	}
	*size = stack->size;
	//print_stack_a(stack);
	error_code = OK;
	return error_code;
}

int task_a(struct stack_ta *stack)
{
	//printf("size=%d", stack->size);
	if (stack->size != 0)
	{
		//print_stack_a(stack);
		struct stack_ta stack_for_diff;
		stack_for_diff.size = 0;
		if (stack->data[stack->size-1] == '{' || stack->data[stack->size-1] == '(' || stack->data[stack->size-1] == '[')
			error = OKFAIL;
		else
		{
			while (stack->size > 0)
			{
				if (stack_for_diff.size == 0)
					push_a(&stack_for_diff, stack->data[stack->size-1]);
				else if (stack->data[stack->size-1] != opposite_bracket(stack_for_diff.data[stack_for_diff.size-1]))
					push_a(&stack_for_diff, stack->data[stack->size-1]);
				else
					pop_a(&stack_for_diff);
				pop_a(stack);
			}
			if (stack_for_diff.size == 0)
				error = OKPASS;
			else 
				error = OKFAIL;
			//error = OK;	
		}
	}
	else
		error = INCORRECT;

	return error;

}



void push_l(struct stack_tl **head, char data)
{
	struct stack_tl *new = NULL;
	new = malloc(sizeof(struct stack_tl));
	if (new != NULL)
	{
		new->next = *head;
		new->data = data;
		*head = new;
		error = OK;
	}
	else
		error = STACK_OWERFLOW;
}


struct stack_tl* pop_l(struct stack_tl **head)
{
	struct stack_tl *out;
	if ((*head) != NULL)
	{
		out = *head;
		*head = (*head)->next;
		return out;
	} 
	else
	{
		error = STACK_UNDERFLOW;
		return NULL;
	}
}




void print_stack_l(struct stack_tl *head)
{
	printf("%s* Стек: %s", YELLOW,    RESET);
	struct stack_tl *current;
	for (current = head; current; current = current->next)	
		printf("%c ", current->data);
	//printf("\n");
	printf("\nВывести адреса элементов стека? (y/n): ");
	char answer[2];
	scanf("%s", answer);
	if (*answer == 'y')
	{
		printf("%s* Адреса элементов стека: %s", YELLOW,    RESET);
		for (current = head; current; current = current->next)
		{
			char *p = &current->data;
			printf("%p ", (void*)p);
		}
		printf("\n");
	}
}



char *stack_adress_add(struct stack_tl *head, char **array, int *count)
{
	char *p = &head->data;
	//struct stack_tl **pp = &head->next;
	//printf("dd=%p ddd=%p %d\n", (void*)p,(void*)pp, (int)sizeof(head->next));

	array[*count] = p;
	(*count)++;
	return p;
}

char *stack_adr_l(struct stack_tl *head)
{
	char *p = &head->data;
	return p;
}

void stack_adress_del(struct stack_tl *head, char **array, int *count)
{
	array[*count] = NULL;
	(*count)--;
}



int filling_stack_l(struct stack_tl **head, const char *string)
{
	int error_code;
	for (int i=0; i < strlen(string); i++)
	{
		if ((string[i] >= 'A' && string[i] <= 'Z') || (string[i] >= 'a' && string[i] <= 'z') || (strlen(string) == 0))
		{
			error_code = INCORRECT;
			return error_code;
		}
		if (string[i] == '{' || string[i] == '}' || string[i] == '[' || string[i] == ']' || string[i] == '(' || string[i] == ')')
			push_l(&*head, string[i]);
	}
	//print_stack_l(*head);	
	error_code = OK;
	return error_code;
}



int size_l(struct stack_tl *head)
{
	int size = 0;
	struct stack_tl *current = head; 
	while(current)
	{
		size++;
		current = current->next;
	}
	return size;
}

void free_all(struct stack_tl **head)
{
    struct stack_tl *next;
    for ( ; *head; *head = next)
    {
        next = (*head)->next;
        free(*head);
    }
}

void task_l(struct stack_tl *head, char **array_free)
{
	int count = 0;
	if (head != NULL)
	{
		if (head->data == '{' || head->data == '[' || head->data == '(')
			error = OKFAIL;
		else
		{
			struct stack_tl *new = NULL;
			while (head)
			{
				if (new == NULL)
				{
					push_l(&new, head->data);
				}
				else if (head->data != opposite_bracket(new->data))
				{
					push_l(&new, head->data);
				}
				else
				{
					pop_l(&new);
				}
				stack_adress_add(head, array_free, &count);
				pop_l(&head);
			}
			if (new == NULL)
				error = OKPASS;
			else 
				error = OKFAIL;
			free_all(&new);
		}
	}
	else
		error = INCORRECT;
}
