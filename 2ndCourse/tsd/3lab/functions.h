#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

int load_table(FILE *file, int *count, book_t *books, key *key_table);
void print_table(book_t *books, int i);
void replace_spaces(char *string);
int read_line(char *s, int n);
int add_new_rec(book_t *books,key *key_table ,int *count, char *filename);
int del_rec(book_t *books,key *key_table ,int *count, char *filename);
unsigned long long int tick(void);
unsigned long long int bubblesort_keys(book_t *books, key *key_table, int *count);
unsigned long long int shell_keys(book_t *books, key *key_table, int *count);
unsigned long long int bubblesort_table(book_t *books, int *count);
unsigned long long int shell_table(book_t *books, int *count);
void search(book_t *books, int *count);


#endif // _FUNCTIONS_H_