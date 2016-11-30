#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>

#define BADPARAMETERS -1
#define NOFILE -2
#define MEMPROBLEM -3
#define EMPTYSTRING -4
#define OK 0

char *strchr_f(char *string, int symbol);
char *strdup_f(const char *string);
int strlen_f(const char *string);

void strchr_test(char *string, int desired_symbol, char *text);
void strdup_test(char *string, char *text);

char *read_line(FILE *file, int *out_error);
char *concat_string(char *string, const char *str);
int count_of_letters(const char *string);

char *substring_in_string(char *string, const char *old);
int count_of_changings(char *string, const char *old);
char *change_string(char *string, const char *old, const char *new);

#endif // FUNCTIONS_H