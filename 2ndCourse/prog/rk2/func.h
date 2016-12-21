#ifndef _FUNC_H_
#define _FUNC_H_

struct list
{
	int num;
	struct list *next;
};

struct list *add_new(int number);
struct list* add_next(struct list *head, struct list *new_element);
void free_all(struct list *head);
struct list *multipl(struct list *first, struct list *second);
void print_list(struct list *head);

#endif 