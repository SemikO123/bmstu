#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "functions.h"
#include "errors.h"

int main(void)
{
	printf("------> Test function 'add_previous' <------\n");
	int adding1[6] = {5,3,4,2,3,1};
	int right_answer1[6] = {1,3,2,4,3,5};
	add_previous_test(adding1, right_answer1, "Test #1 (5 3 4 2 3 1)->(1 3 2 4 3 5)", 6);

	int adding2[1] = {1};
	int right_answer2[1] = {1};
	add_previous_test(adding2, right_answer2, "Test #2 (1)->(1)                    ", 1);

	printf("\n--------> Test function 'add_next' <--------\n");
	int adding3[5] = {1,2,3,5,6};
	int right_answer3[5] = {1,2,3,5,6};
	struct list *head = NULL;
	head = add_next_test(adding3, right_answer3, "Test #1 (1 2 3 5 6)->(1 2 3 5 6)    ", 5, head);

	printf("\n---->  Test function 'add_new_element' <----\n");
	int right_answer4[6] = {1,2,3,4,5,6};	
	head = add_new_element_test(right_answer4, 4, "Test #1 (+element '4' in the middle)", 6, head);
	int right_answer5[7] = {0,1,2,3,4,5,6};
	head = add_new_element_test(right_answer5, 0, "Test #2 (+element '0' in the begin) ", 7, head);
	int right_answer6[8] = {0,1,2,3,4,5,6,7};
	head = add_new_element_test(right_answer6, 7, "Test #3 (+element '7' in the end)   ", 8, head);

	printf("\n------>  Test function 'print_list' <-------\n");
	char result[] = "List: 0 1 2 3 4 5 6 7";
	int count_of_symbols = 21;
	FILE *file = fopen("test.txt", "w");
	printf("Test #1. Result: ");
	print_list_test(head, result, file, count_of_symbols);
	free_all(head);
}

void print_list_test(struct list *head, char *result, FILE *file, int count)
{
	print_list(head, 1, file);
	fclose(file);
	file = fopen("test.txt", "r");
	char symbol;
	int i = 0, counter = 0;
	while (fscanf(file, "%c", &symbol) == 1)
	{
		if (symbol == result[i])
		{
			counter += 1;
		}
		i++;
	}
	if (counter == count)
		printf("                                     PASSED\n");
	else
		printf("                                     FAILED\n");
	fclose(file);
}

struct list *add_new_element_test(int *right, int data, char *text, int count, struct list *head)
{
	head = add_new_element(head, data);
	int flag = 1;
	struct list *current = head;
	for (int i = 0; i < count; i++)
	{
		if (current->number != right[i])
			flag = 0;
		current = current->next;
	}
	if (flag == 1)
		printf("%s PASSED\n", text);
	else
		printf("%s FAILED\n", text);
	return head;	
}

void add_previous_test(int *array, int *right, char *text, int count)
{
	struct list *head = NULL, *current, *new;
	for (int i = 0; i < count; i++)
	{
		new = create_new(array[i]);
		head = add_previous(head, new);
	}
	int flag = 1;
	current = head;
	for (int i = 0; i < count; i++)
	{
		if (current->number != right[i])
			flag = 0;
		current = current->next;
	}
	if (flag == 1)
		printf("%s PASSED\n", text);
	else
		printf("%s FAILED\n", text);
	free_all(head);
}

struct list *add_next_test(int *array, int *right, char *text, int count, struct list *head)
{
	struct list *current, *previous, *new;
	for (int i = 0; i < count; i++)
	{
		if (!head)
		{
			previous = create_new(array[i]);
			head = previous;
		}
		else
		{
			new = create_new(array[i]);
			if (previous)
				previous = add_next(previous, NULL, new);
		}
	}
	int flag = 1;
	current = head;
	for (int i = 0; i < count; i++)
	{
		if (current->number != right[i])
			flag = 0;
		current = current->next;
	}
	if (flag == 1)
		printf("%s PASSED\n", text);
	else
		printf("%s FAILED\n", text);
	return head;
}