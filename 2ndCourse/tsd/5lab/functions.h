#ifndef _FUNCTIONS_H_
#define _FUNCTIONS_H_

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define WHITE   "\033[1;37m"

void matrix_generate(int *matrix, int m, int n, int *count);
void matrix_print(int *matrix, int m, int n, char *text);
void vector_print(int *vector, int count);
void vectors(const int *matrix, int m, int n, int *A, int *JA, int *IA, int count);
void matrix_input(int *matrix, int m, int n, int *count);
unsigned long long int tick(void);
unsigned long long int matrix_multiplication(const int *matrix, const int *vector, int *result, int m, int n, int count_matr, int count_vec);
unsigned long long int vectors_multiplication(int *A, int *JA, int *IA, int m, int count, int *Av, int *JAv, int *IAv, int *Ares, int *JAres, int *IAres, int *newcount);


#endif // _FUNCTIONS_H_