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

#endif // #ifndef _FUNCTIONS_H_