#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

#define OK 0
#define BADPARAMETERS -1
#define NOFILE -2
#define EMPTYFILE -3
#define BADINPUT -4

struct list* initialize(int first_number);
struct list* add_next(struct list *head, int new_number);
struct list* add_previous(struct list *head, int new_number);
void print_list(struct list *head);
void free_all(struct list *head);

int main(int argc, char **argv)
{

	int out_error;
	FILE *input;
	if (argc != 4)
	{
		printf("\nPut names of i/o files and number as parameters\n");
		out_error = BADPARAMETERS;
	}
	else
	{
		input = fopen(argv[1], "r");
		if (input == NULL)
		{
			printf("\nFile doesn't found\n");
			out_error = NOFILE;
		}
		else
		{
			int int_number;
			switch (fscanf(input, "%d", &int_number))
			{
				case -1:
					printf("\nFile is empty\n");
					out_error = EMPTYFILE;
					break;
				case 0:
					printf("\nCan't get numbers from file\n");
					out_error = BADINPUT;
					break;
				case 1:
				{
					struct list *head;
					head = initialize(int_number);
					while (fscanf(input, "%d", &int_number) == 1)
					{
						for ( ; head; head = head->next)
							if (int_number <= head->number)
								head = add_previous(head, int_number);
						//head = add_next(head, int_number);
					}
					print_list(head);
					out_error = OK;
					free_all(head);
					head = NULL;
				}

			}
		}
	}
	fclose(input);
	return out_error;
}

struct list* initialize(int first_number)
{
	struct list *element = malloc(sizeof(struct list));
	if (element)
	{
		element->number = first_number;
		element->next = NULL;
	}
	return element;
}

struct list* add_next(struct list *head, int new_number)
{
	struct list *current, *new_element;
	new_element = malloc(sizeof(struct list));
	current = head->next;
	head->next = new_element;
	new_element->number = new_number;
	new_element->next = current;
	return new_element;
}

void print_list(struct list *head)
{
	printf("List: ");
	for ( ; head; head = head->next)
		printf("%d", head->number);
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


struct list* add_previous(struct list *head, int new_number)
{
	struct list *new_element;
	new_element = malloc(sizeof(struct list));
	new_element->number = new_number;
	new_element->next = head;
	return new_element;
}


