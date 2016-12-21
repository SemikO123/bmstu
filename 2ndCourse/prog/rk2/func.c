#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

struct list *add_new(int number)
{
	struct list *elem = malloc(sizeof(struct list));
	if (elem)
	{
		elem->num = number;
		elem->next = NULL;
	}
	return elem;
}


struct list* add_next(struct list *head, struct list *new_element)
{
	if (head)
	{
		struct list *current = head;
		while (current->next)
			current = current->next;
		current->next = new_element;
	}
	else
	{
		head = new_element;
	}
	return head;
}

void free_all(struct list *head)
{
    struct list *next;
    for ( ; head; head = next)
    {
        next = head->next;
        free(head);
    }
}


struct list *multipl(struct list *first, struct list *second)
{
	struct list *result = NULL;
	int flag = 0;
	while (first && second)
	{
		int sum = first->num + second->num + flag;
		//printf("%d   ",sum);
		if (sum < 10)
		{
			struct list *new = add_new(sum);
			result = add_next(result, new);
			flag = 0;
		}
		else
		{
			struct list *new = add_new(sum % 10);
			result = add_next(result, new);
			flag = 1;
		}
		first = first->next;
		second = second->next;
	}
	if (flag == 1 && !first && !second)
	{
		struct list *new = add_new(1);
		result = add_next(result, new);
		flag = 0;
	}
		while (first && !second)
		{
			int number = first->num + flag;
			if (number > 9)
			{
				number %= 10;
				flag = 1;
			}
			else
				flag = 0;
			struct list *new = add_new(number);
			//struct list *new = add_new(first->num + flag);
			result = add_next(result, new);
			first = first->next;
		}
		while (second && !first)
		{
			int number = second->num + flag;
			if (number > 9)
			{
				number %= 10;
				flag = 1;
			}
			else
				flag = 0;
			struct list *new = add_new(number);
			result = add_next(result, new);
			second = second->next;
			flag = 0;
		}
	return result;
}


void print_list(struct list *head)
{
	struct list *current;
	for (current = head ; current; current = current->next)
		printf("%d ", current->num);
	printf("\n");
}
