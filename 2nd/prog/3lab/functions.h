#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

struct list
{
	int number;
	struct list *next;
};

struct list* create_new(int number);
struct list* add_next(struct list *previous, struct list *current, struct list *new_element);
struct list* add_previous(struct list *head, struct list *new_element);
struct list* add_new_element(struct list *head, int number);
void print_list(struct list *head, int flag_printto, FILE *output);
void free_all(struct list *head);

void add_previous_test(int *array, int *right, char *text, int count);
struct list *add_next_test(int *array, int *right, char *text, int count, struct list *head);
struct list *add_new_element_test(int *right, int data, char *text, int count, struct list *head);
void print_list_test(struct list *head, char *result, FILE *file, int count);


#endif // #ifndef _FUNCTIONS_H_