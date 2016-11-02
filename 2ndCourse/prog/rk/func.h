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
void print_list(struct list *head, FILE *out);
//struct list *take_words(FILE *f);