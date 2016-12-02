#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"

#define RESET   "\033[0m"
#define GRAY     "\033[1;30m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"

#define EPS 0.0001

double fmax(double a, double b)
{
	return (a < b) ? b : a; 
}

void test(int flag, const char *text)
{
	if (flag == 0)
		printf("TEST %s %sFAILED%s\n", text, RED, RESET);
	else
		printf("TEST %s %sPASSED%s\n", text, GREEN, RESET);
}

int compare(double **matrix1, int n, int m, double **matrix2)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			if (fabs(matrix2[i][j]-matrix1[i][j]) <= EPS*(fmax(fabs(matrix2[i][j]),fabs(matrix1[i][j]))))
				;
			else
				return 0;
	return 1;
}

void test_addition(FILE *f1, FILE *f2, double **rightresult, int n, int m, const char *text)
{
	double **matrix1 = allocate_memory(n, m);
	double **matrix2 = allocate_memory(n, m);
	matrix1 = filling_matrix(n, m, matrix1, f1);
	matrix2 = filling_matrix(n, m, matrix2, f2);
	double **result = allocate_memory(n, m);
	result = addition(n, m, matrix1, matrix2, result);
	print_matrix(n,m, result);
	test(compare(result, n, m, rightresult), text);
	free(result);
	free(matrix1);
	free(matrix2);
}

int main(void)
{
	// double **filling_matrix(int n, int m, double **matrix, FILE *file);
	// double **add_identity_matrix(int n, double **matrix);
	// double **copy(int n, int m, double **matrix, double **new_matrix);
	// double **transformation(int n, int m, double **matrix);
	// double **inverse(int n, double **matrix, double **result);
	// double **addition(int n, int m, double **matrix1, double **matrix2, double **result);
	// double **multiplication(int n, int t, int m, double **matrix1, double **matrix2, double **result);
	printf("Test function 'Addition'\n");
	FILE *m1 = fopen("tests/a1_1.txt", "r");
	FILE *m2 = fopen("tests/a1_2.txt", "r");
	double **result_a1 = allocate_memory(2, 2);
	result_a1[0][0] = 6;
	result_a1[0][1] = 15;
	result_a1[1][0] = 10;
	result_a1[1][1] = -24;
	test_addition(m1, m2, result_a1, 2, 2, "2 matrix 2*2");
	fclose(m1);
	fclose(m2);
	free(result_a1);

}