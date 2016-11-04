#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#define BADPARAMETERS -1
#define NOFILE -2
#define OK 0

#define N 100

struct list
{
	char *data;
	struct list *next;
};

struct list *new(char *word);
struct list *add(struct list *head, struct list *new);
void free_list(struct list *head);
int length(const char *string);
void print_list(struct list *head, FILE *out);
char *get_word(const char *string);
struct list *take_words(FILE *f);

#endif //_FUNCTIONS_H_