#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define N 100
#define LENGTH 1000
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define WHITE   "\033[1;37m"

struct stack_ta 
{
	char data[N];
	int size;
};

struct stack_tl
{
	char data;
	struct stack_tl *next;
};

enum errors
{
	OK,
	OKPASS,
	OKFAIL,
	STACK_UNDERFLOW,
	STACK_OWERFLOW,
	INCORRECT,
} error;

char opposite_bracket(char bracket);

void push_a(struct stack_ta *stack, char value);
int pop_a(struct stack_ta *stack);
void print_stack_a(struct stack_ta *stack);
char *stack_adress_a(struct stack_ta *stack);
int filling_stack_a(struct stack_ta *stack, const char *string, int *size);
int task_a(struct stack_ta *stack);

void push_l(struct stack_tl **head, char data);
struct stack_tl* pop_l(struct stack_tl **head);
void print_stack_l(struct stack_tl *head);
char *stack_adress_add(struct stack_tl *head, char **array, int *count);
char *stack_adr_l(struct stack_tl *head);
void stack_adress_del(struct stack_tl *head, char **array, int *count);
int filling_stack_l(struct stack_tl **head, const char *string);
int size_l(struct stack_tl *head);
void task_l(struct stack_tl *head, char **array_free);

void free_all(struct stack_tl **head);
#endif // FUNCTIONS_H

