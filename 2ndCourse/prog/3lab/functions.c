#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "functions.h"
#include "errors.h"


struct list *read_from_file(FILE *input, int *out_error)
{
	int int_number;
	switch (fscanf(input, "%d", &int_number))
	{
		case -1:
			printf("File is empty\n");
			*out_error = EMPTYFILE;
			break;
		case 0:
			printf("Can't get numbers from file\n");
			*out_error = BADINPUT;
			break;
		case 1:
		{
			*out_error = OK;
			struct list *head = create_new(int_number);
			if (head)
			{
				while (fscanf(input, "%d", &int_number) == 1)			
					head = add_new_element(head, int_number);
				printf("List:   ");
				print_list(head, 0, NULL);
				return head;
			}
			else 
				*out_error = MEMORYPROBLEM;
		}
	}
	return NULL;
}

/*
* @function create_new
* This function creates new element of list
* @param[in] number data for element
* @return new_element link to element of list
**/
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

/*
* @function add_previous
* This function puts the link of 'new_element' to 'head'
* @param[in] head element, in front of which puts new element
* @param[in] new_element element, which puts after 'head'
* @return link to new_element
**/
struct list* add_previous(struct list *head, struct list *new_element)
{
	if (new_element)
		new_element->next = head;
	return new_element;
}

/*
* @function add_next
* This function puts the 'new_element' after 'previous' and before 'current' 
* @param[in] current element, in front of which puts new element
* @param[in] new_element element, which puts after 'current'
* @param[in] previous element, after which puts new element 
* @return link to new_element
**/
struct list* add_next(struct list *previous, struct list *current, struct list *new_element)
{
	if (new_element)
	{
		new_element->next = current;
		previous->next = new_element;
	}
	return new_element;
}

/*
* @function print_list
* This function prints the list or puts the data to file
* @param[in] head the link to first element
* @param[in] flag_printto 0 to print on screen, 1 to print on screen and to file
* @param[in] file 
**/
void print_list(struct list *head, int flag_printto, FILE *file)
{
	struct list *current;
	for (current = head ; current; current = current->next)
		printf("%d ", current->number);
	printf("\n");
	if (flag_printto == 1)
	{
		// fprintf(file, "List: ");
		for ( ; head; head = head->next)
			fprintf(file, "%d ", head->number);
		fprintf(file, "\n");
	}
}

/*
* @function free_all
* This function frees all memory of list
* @param[in] head the link to the first element of list
**/
void free_all(struct list *head)
{
    struct list *next;
    for ( ; head; head = next)
    {
        next = head->next;
        free(head);
    }
}

/*
* @function add_new_element
* This function searches place for new element and puts new element to it
* @param[in] head link to the first element
* @param[in] number data for element
* @return head
**/
struct list* add_new_element(struct list *head, int number)
{
	assert(head);
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




