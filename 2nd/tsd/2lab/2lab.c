#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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
	"Скобки в выражении расставлены верно\n",
	"Ошибка в расстановке скобок в выражении\n",
	"Стек пуст\n",
	"Стек переполнен\n",
	"Неверный ввод\n"
};

enum errors
{
	OK,
	OKPASS,
	OKFAIL,
	STACK_UNDERFLOW,
	STACK_OWERFLOW,
	INCORRECT,
} error;

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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10
#define LENGTH 21


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
	printf("* Cтек: ");
	for (int i = 0; i < stack->size; i++)
		printf("%c ",stack->data[i]);
	printf("\n* Адреса элементов стека: ");
	for (int i = 0; i < stack->size; i++)
	{
		char *p = &stack->data[i];
		printf("%p ",(void*)p);
	}
	printf("\n");

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
	printf("* Стек: ");
	struct stack_tl *current;
	for (current = head; current; current = current->next)	
		printf("%c ", current->data);
	printf("\n* Адреса элементов стека: ");
	for (current = head; current; current = current->next)
	{
		char *p = &current->data;
		printf("%p ", (void*)p);
	}
	printf("\n");
}



char *stack_adress_l(struct stack_tl *head, char **array, int *count)
{
	char *p = &head->data;
	//struct stack_tl **pp = &head->next;
	//printf("dd=%p ddd=%p %d\n", (void*)p,(void*)pp, (int)sizeof(head->next));
	array[*count] = p;
	(*count)++;

	return p;
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
			stack_adress_l(head, array_free, &count);
			pop_l(&head);
		}
		if (new == NULL)
			error = OKPASS;
		else 
			error = OKFAIL;
		free_all(&new);
	}
	else
		error = INCORRECT;
}


int main(void)
{
	struct stack_ta stack;
	stack.size = 0;
	struct stack_tl *head = NULL;
	printf("Введите выражение со скобками ");
	printf("(например 1/[(5+6)*{7-6})]) :");
	char string[LENGTH];
	scanf("%s", string);
	if (strlen(string) >= LENGTH-1)
	{
		error = INCORRECT;
		printf("В выражении должно быть не более %d символов\n", LENGTH-1);
		exit(INCORRECT); 
	}
	else
	{
		char *array_free[N];
		int time1 = clock();
		if (filling_stack_l(&head, string) != INCORRECT)
		{
			printf("\nВыполнение задания с реализацией стека СПИСКОМ:\n");
			print_stack_l(head);
			task_l(head, array_free);
			printf("%s",error_names[error]);
			printf("* Используемая память - %d байт\n", (int)(size_l(head)*sizeof(struct stack_tl)));
			printf("* Времени потребовалось - %d тактов\n", time1);
			printf("* Cвободные области: \n");
			for (int i = 0; i < size_l(head); i++)
				printf("       %p \n", (void*)array_free[i]);

		}
		printf("_________________________________________________________\n");
		int time2 = clock();
		int size = 0;
		if (filling_stack_a(&stack, string, &size) != INCORRECT)
		{
			printf("\nВыполнение задания с реализацией стека МАССИВОМ:\n");
			print_stack_a(&stack);
			task_a(&stack);
			printf("%s",error_names[error]);
			printf("* Используемая память - %d байт\n", size+(int)sizeof(stack.size));
			printf("* Времени потребовалось - %d тактов\n", time2);
		}
		else
			printf("%s",error_names[INCORRECT]);

		
	}
	free_all(&head);
	
	return 0;
}
