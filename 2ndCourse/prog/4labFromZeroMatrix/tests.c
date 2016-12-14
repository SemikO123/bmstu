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
	test(compare(result, n, m, rightresult), text);
	free(result);
	free(matrix1);
	free(matrix2);
}

void test_multiplication(FILE *f1, FILE *f2, double **rightresult, int n, int k, int m, const char *text)
{
	double **matrix1 = allocate_memory(n, k);
	double **matrix2 = allocate_memory(k, m);
	matrix1 = filling_matrix(n, k, matrix1, f1);
	matrix2 = filling_matrix(k, m, matrix2, f2);
	double **result = allocate_memory(n, m);
	result = multiplication(n, k, m, matrix1, matrix2, result);
	test(compare(result, n, m, rightresult), text);
	free(result);
	free(matrix1);
	free(matrix2);
}

void test_inverse(FILE *file, double **rightresult, int n, int work, const char* text)
{
	double **matrix = allocate_memory(n, n);
	matrix = filling_matrix(n, n, matrix, file);
	double **result = allocate_memory(n, n);
	result = inverse(n, matrix, result);
	if (result)
		test(compare(result, n, n, rightresult), text);
	else
		if (work == 0)
			test(1, text);
		else
			test(0, text);
	free(result);
	free(matrix);
}

int main(void)
{
	printf("--------> Test function 'Addition' <--------\n");
	FILE *m1 = fopen("tests/a1_1.txt", "r");
	FILE *m2 = fopen("tests/a1_2.txt", "r");
	double **resultt = allocate_memory(2, 2);
	resultt[0][0] = 6;
	resultt[0][1] = 15;
	resultt[1][0] = 10;
	resultt[1][1] = -24;
	test_addition(m1, m2, resultt, 2, 2, "#1 2 matrix 2*2      ");
	fclose(m1);
	fclose(m2);
	free(resultt);

	m1 = fopen("tests/a2_1.txt", "r");
	m2 = fopen("tests/a2_2.txt", "r");
	resultt = allocate_memory(4, 2);
	resultt[0][0] = 10;
	resultt[0][1] = 10;
	resultt[1][0] = -10;
	resultt[1][1] = -10;
	resultt[2][0] = 10;
	resultt[2][1] = 10;
	resultt[3][0] = -10;
	resultt[3][1] = -10;
	test_addition(m1, m2, resultt, 4, 2, "#2 2 matrix 4*2      ");
	fclose(m1);
	fclose(m2);
	free(resultt);	

	m1 = fopen("tests/a3_1.txt", "r");
	m2 = fopen("tests/a3_2.txt", "r");
	resultt = allocate_memory(3, 4);
	resultt[0][0] = 7;
	resultt[0][1] = 9;
	resultt[0][2] = 3;
	resultt[0][3] = 13;
	resultt[1][0] = -4;
	resultt[1][1] = -7;
	resultt[1][2] = -5;
	resultt[1][3] = -6;
	resultt[2][0] = 1;
	resultt[2][1] = 10;
	resultt[2][2] = 10;
	resultt[2][3] = 10;
	test_addition(m1, m2, resultt, 3, 4, "#3 2 matrix 3*4      ");
	fclose(m1);
	fclose(m2);
	free(resultt);

	printf("-----> Test function 'Multiplication' <-----\n");
	m1 = fopen("tests/m1_1.txt", "r");
	m2 = fopen("tests/m1_2.txt", "r");
	resultt = allocate_memory(2, 2);
	resultt[0][0] = 46;
	resultt[0][1] = 57;
	resultt[1][0] = 8;
	resultt[1][1] = 14;
	test_multiplication(m1, m2, resultt, 2, 2, 2, "#1 2 matrix 2*2      ");
	fclose(m1);
	fclose(m2);
	free(resultt);

	m1 = fopen("tests/m2_1.txt", "r");
	m2 = fopen("tests/m2_2.txt", "r");
	resultt = allocate_memory(2, 4);
	resultt[0][0] = 26;
	resultt[0][1] = 38;
	resultt[0][2] = 50;
	resultt[0][3] = 62;
	resultt[1][0] = 44;
	resultt[1][1] = 65;
	resultt[1][2] = 86;
	resultt[1][3] = 107;
	test_multiplication(m1, m2, resultt, 2, 3, 4, "#2 matrix 2*3 and 3*4");
	fclose(m1);
	fclose(m2);
	free(resultt);

	m1 = fopen("tests/m3_1.txt", "r");
	m2 = fopen("tests/m3_2.txt", "r");
	resultt = allocate_memory(3, 1);
	resultt[0][0] = 0;
	resultt[0][1] = -14;
	resultt[0][2] = -70;
	test_multiplication(m1, m2, resultt, 3, 4, 1, "#3 matrix 3*4 and 4*1");
	fclose(m1);
	fclose(m2);
	free(resultt);

	printf("--------> Test function 'Inverse' <---------\n");
	m1 = fopen("tests/i1.txt", "r");
	resultt = allocate_memory(3, 3);
	resultt[0][0] = -7.0/12.0;
	resultt[0][1] = -1.0/12.0;
	resultt[0][2] = 19.0/6.0;
	resultt[1][0] = 1.0/6.0;
	resultt[1][1] = 1.0/6.0;
	resultt[1][2] = -1.0/3.0;
	resultt[2][0] = 5.0/12.0;
	resultt[2][1] = -1.0/12.0;
	resultt[2][2] = -11.0/6.0;
	test_inverse(m1, resultt, 3, 1, "#1 matrix 3*3        ");
	fclose(m1);

	m1 = fopen("tests/i2.txt", "r");
	test_inverse(m1, resultt, 3, 0, "#2 determinant = 0   ");
	fclose(m1);
	free(resultt);

	m1 = fopen("tests/i3.txt", "r");
	resultt = allocate_memory(4, 4);
	resultt[0][0] = 8.0/3.0;  resultt[2][0] = -4.0/9.0;
	resultt[0][1] = -7.0/3.0; resultt[2][1] = 5.0/9.0;
	resultt[0][2] = -4.5;     resultt[2][2] = 17.0/18.0;
	resultt[0][3] = 10.0/3.0; resultt[2][3] = -5.0/9.0;
	resultt[1][0] = 1.0/9.0;  resultt[3][0] = 0;
	resultt[1][1] = 1.0/9.0;  resultt[3][1] = 0;
	resultt[1][2] = 1.0/18.0; resultt[3][2] = 1.0/6.0;
	resultt[1][3] = -1.0/9.0; resultt[3][3] = 0;
	test_inverse(m1, resultt, 4, 1, "#3 zeros on diagonal ");
	fclose(m1);
	free(resultt);


}