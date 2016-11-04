#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

struct list *new(char *word)
{
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
		free(head->data);
		curr = head->next;
		free(head);
	}
}

int length(const char *string)
{
	int count = 0;
	while (!strchr(" \0\n", *string))
	{
		count++;
		string++;
	}	
	return count;
}

void print_list(struct list *head, FILE *out)
{
	struct list *current;
	for (current = head; current; current = current->next)
	{
		//printf("word=%s, length=%d\n", current->data, length(current->data));
		for (int i = 0; i < length(current->data); i++)
			fprintf(out, "%c", current->data[i]);
		fprintf(out, " ");
	}
}

char *get_word(const char *string)
{
	int count = length(string);
	char *word = malloc((count+1)*sizeof(char));
	for (int i = 0; i < count; i++)
	{
		if (string[i] != '\n') // костыль (последнее слово в строке содержит \n)
			word[i] = string[i];
	}
	word[count] = '\0';
	return word;
}

struct list *take_words(FILE *f)
{
	struct list *head = NULL;
	char string[N+1];
	while (fgets(string, N+1, f) != NULL)
	{
		printf("\n * STRING = %s * LEN = %d\n", string, (int)strlen(string));
		int length = strlen(string);
		int flag = 1;
		for (int i = 0; i < length; i++)
		{
			if (strchr(" \0\n", string[i]))
				flag = 1;
			else
				if (flag)
				{
					char *new_word = get_word(string+i);
					head = add(head, new(new_word));	
					printf("Current word: %s\n", head->data);
					flag = 0;
				}
		}
	}
	return head;			
}
