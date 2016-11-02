#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "func.h"

struct list *new(char *word)
{
	// printf("WORD %s\n", word);
	struct list *list = malloc(sizeof(struct list));
	if (list)
	{
		list->data = word;
		list->next = NULL;
	}
	return list;
}

struct list *add(struct list *head, struct list *new)
{
	if (new)
		new->next = head;
	return new;
}

void free_list(struct list *head)
{
	struct list *curr;
	for (; head; head = curr)
	{
		curr = curr->next;
		free(head);
	}
}

void print_list(struct list *head, FILE *out)
{
	//puts("bitch");
	//printf("vnutri %s\n", head->data);
	struct list *current;
	for (current = head; current; current = current->next)
	{
		// printf("%s",current->data);
		fprintf(out, "%s ", current->data);
	}
	printf("\n");
}

