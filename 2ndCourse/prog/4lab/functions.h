#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#define BADPARAMETERS -1
#define NOFILE -2
#define MEMPROBLEM -3
#define OK 0

char *strchr_f(char *string, int symbol);
char *strdup_f(const char *string);
int strlen_f(const char *string);

void strchr_test(char *string, int desired_symbol, char *text);
void strdup_test(char *string, char *text);




#endif // FUNCTIONS_H