#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

struct list
{
	int number;
	struct list *next;
};

struct list *read_from_file(FILE *input, int *out_error);
struct list* create_new(int number);
struct list* add_next(struct list *previous, struct list *current, struct list *new_element);
struct list* add_previous(struct list *head, struct list *new_element);
struct list* add_new_element(struct list *head, int number);
void print_list(struct list *head, int flag_printto, FILE *output);
void free_all(struct list *head);

void add_previous_test(const int *array, const int *right, const char *text, int count);
void read_from_file_test(const char *filename, const int *right, int right_error, int count, const char *text);
struct list *add_next_test(const int *array, const int *right, const char *text, int count, struct list *head);
struct list *add_new_element_test(const int *right, int data, const char *text, int count, struct list *head);
void print_list_test(struct list *head, const char *result, FILE *file, int count);
void compare(struct list *head, int count, const int *right, const char *text);

#endif // #ifndef _FUNCTIONS_H_