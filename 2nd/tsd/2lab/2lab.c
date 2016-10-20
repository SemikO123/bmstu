#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10
#define LENGTH 21

/*
Проверить правильность расстановки скобок трех типов 
(круглых, квадратных и фигурных) в выражении.
**/

struct stack_ta 
{
	char data[N];
	int size;
};

struct stack_tl
{
	char data;
	struct stack_tl *next;
};

static char *error_names[]=
{
	"Ок\n",
	"Стек пуст\n",
	"Стек переполнен\n",
	"Неверный ввод\n"
};

enum errors
{
	OK,
	STACK_UNDERFLOW,
	STACK_OWERFLOW,
	INCORRECT,
} error;


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

struct stack_tl* pop_l(struct stack_tl **head)
{
	struct stack_tl *out;
	if (!(*head))
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


void print_stack_l(struct stack_tl *head)
{
	printf("Stack#2: ");
	while (head != NULL)
	{

		printf("%c ", head->data);
		head = head->next;
	}
}

void print_stack_a(struct stack_ta *stack)
{
	printf("Stack#1 : ");
	for (int i = 0; i < stack->size; i++)
	{
		printf("%c ",stack->data[i]);
	}
	printf("\n");
}

char *stack_adress_l(struct stack_tl *head)
{
	char *p = &head->data;
	struct stack_tl **pp = &head->next;
	printf("->%p ->%p ", (void*)p, (void*)pp);
	return p;
}

char *stack_adress_a(struct stack_ta *stack)
{
	char *p = &stack->data[stack->size];
	//printf("%p\n", (void*)p);
	return p;
}

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

int filling_stack_l(struct stack_tl **head, const char *string)
{
	for (int i=0; i < strlen(string); i++)
	{
		if ((string[i] >= 'A' && string[i] <= 'Z') || (string[i] >= 'a' && string[i] <= 'z') || (strlen(string) == 0))
		{
			error = INCORRECT;
			return error;
		}
		if (string[i] == '{' || string[i] == '}' || string[i] == '[' || string[i] == ']' || string[i] == '(' || string[i] == ')')
			push_l(&*head, string[i]);
	}
	print_stack_l(*head);	
	error = OK;
	return error;
}

int filling_stack_a(struct stack_ta *stack, const char *string, char **p1, char **p2)
{
	*p1 = stack_adress_a(stack);
	for (int i=0; i < strlen(string); i++)
	{
		if ((string[i] >= 'A' && string[i] <= 'Z') || (string[i] >= 'a' && string[i] <= 'z') || (strlen(string) == 0))
		{
			error = INCORRECT;
			return error;
		}
		if (string[i] == '{' || string[i] == '}' || string[i] == '[' || string[i] == ']' || string[i] == '(' || string[i] == ')')
			push_a(stack, string[i]);
	}
	print_stack_a(stack);
	*p2 = stack_adress_a(stack);
	error = OK;
	return error;
}

int size_l(struct stack_tl **head)
{
	int size = 0;
	while(head)
	{
		size++;
		*head = (*head)->next;
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

int task_l(struct stack_tl **head)
{
	//printf("%d", size_l(&*head));
	printf("\nВыполнение задания с реализацией СПИСКОМ:\n");
	if (*head != NULL)
	{
		struct stack_tl *new = NULL;
		int i = 0;
		while (i <= size_l(&*head));
		{
			i++;
			if (new == NULL)
			{
				push_l(&new, (*head)->data);
				pop_l(&*head);
			}
			else if ((*head)->data != opposite_bracket(new->data))
			{
				push_l(&new, (*head)->data);
				pop_l(&*head);	
			}
			else
			{
				pop_l(&*head);
				pop_l(&new);
			}
			error = OK;
			print_stack_l(*head);
			print_stack_l(new);
		}
		if (new == NULL)
			printf("Скобки в выражении расставлены верно\n");
		else 
			printf("Ошибка в расстановке скобок в выражении\n");
		free_all(&new);
	}
	else
		error = INCORRECT;
	return error;


}

int task_a(struct stack_ta *stack)
{
	
	printf("\nВыполнение задания с реализацией стека МАССИВОМ:\n");
	if (stack->size != 0)
	{
		struct stack_ta stack_for_diff;
		stack_for_diff.size = 0;
		while (stack->size > 0)
		{
			if (stack_for_diff.size == 0)
			{
				push_a(&stack_for_diff, stack->data[stack->size-1]);
				pop_a(stack);
			}

			else if (stack->data[stack->size-1] != opposite_bracket(stack_for_diff.data[stack_for_diff.size-1]))
			{
				push_a(&stack_for_diff, stack->data[stack->size-1]);
				pop_a(stack);
			}
			else
			{
				
				pop_a(stack);
				pop_a(&stack_for_diff);
			}
		}
		if (stack_for_diff.size == 0)
			printf("Скобки в выражении расставлены верно\n");
		else 
			printf("Ошибка в расстановке скобок в выражении\n");
		error = OK;	
	}
	else
		error = INCORRECT;

	return error;

}

int main(void)
{

	printf("%s",error_names[error]);
	printf("\n\n\n");

	struct stack_ta stack;
	struct stack_tl *head = NULL;
	stack.size = 0;
	char *p1 = NULL, *p2 = NULL; 
	printf("Введите выражение со скобками ");
	printf("(например 1/[(5+6)*{7-6})] :");
	char string[LENGTH];
	scanf("%s", string);
	if (strlen(string) >= LENGTH-1)
	{
		error = INCORRECT;
		printf("В выражении должно быть не более %d символов\n", LENGTH-1);
		exit(INCORRECT); 
	}
	else if (filling_stack_a(&stack, string, &p1, &p2) != INCORRECT)
	{
		{
			if (filling_stack_l(&head, string) != INCORRECT)
			{
				task_l(&head);
				if (error != OK)
		        	printf("%s",error_names[error]);
			}
			task_a(&stack);
			if (error != OK)
				printf("%s",error_names[error]);
			printf("Используемая память - %d байт\n", (int)(p2-p1)+(int)sizeof(stack.size));
		}
	}
	if (error != OK)
		printf("%s",error_names[error]);
	
	return 0;
}
