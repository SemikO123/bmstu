#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "functions.h"
#include "errors.h"

struct list* create_new(int number)
{
	struct list *new_element = malloc(sizeof(struct list));
	if (new_element)
	{
		new_element->number = number;
		new_element->next = NULL;
	}
	return new_element;
}


struct list* add_previous(struct list *head, struct list *new_element)
{
	if (new_element)
		new_element->next = head;
	return new_element;
}

struct list* add_next(struct list *previous, struct list *current, struct list *new_element)
{
	if (new_element)
	{
		new_element->next = current;
		previous->next = new_element;
	}
	return new_element;
}

void print_list(struct list *head, int flag_printto, FILE *file)
{
	struct list *current;
	printf("List: ");
	for (current = head ; current; current = current->next)
		printf("%d ", current->number);
	printf("\n");
	if (flag_printto == 1)
	{
		fprintf(file, "List: ");
		for ( ; head; head = head->next)
			fprintf(file, "%d ", head->number);
		fprintf(file, "\n");
	}

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

struct list* add_new_element(struct list *head, int number)
{
	struct list *new, *previous, *current;
	new = create_new(number);
	if (new)
	{
		if (new->number <= head->number)
		{
			head = add_previous(head, new);
			return head;
		}
		else
		{
			previous = head;
			for (current = head->next; current; current = current->next)
			{
				if (new->number <= current->number)
				{
					previous = add_next(previous, current, new);
					return head;
				}
				previous = previous->next;
			}
			if (previous->next == NULL)
				previous = add_next(previous, current, new); 
		}
	}	
	return head;
}




