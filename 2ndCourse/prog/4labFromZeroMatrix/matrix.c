#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BADPARAMETERS -1
#define NOFILE -2
#define BADOPERATION -3

/*
Написать программу для работы с матрицами, которая реализует сложение матриц, 
умножение матриц и вычисление обратной матрицы методом элементарных преобразований.
Исходные матрицы читаются из файла, результирующие матрицы записываются в файл. 
Один файл содержит одну матрицу. Количество строк и столбцов матрицы указывается 
в первой строчке файла. Имена файлов и выполняемая операция указывается через 
параметры командной строки.
*/

double **allocate_memory(int n, int m)
{
	double **data = malloc(n*sizeof(double*) + n*m*sizeof(double));
	if (!data)
		return NULL;
	for (int i = 0; i < n; i++)
		data[i] = (double*)((char*)data+n*sizeof(double*)+i*m*sizeof(double));
	return data;
} 

void print_matrix(int n, int m, double **matrix)
{
	for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
        	if (matrix[i][j] - (int)matrix[i][j] == 0)
        		printf("%6d", (int)matrix[i][j]);
        	else
            	printf(" %5.2f", matrix[i][j]);
        }
        printf("\n");
    }
}

double **add_identity_matrix(int n, double **matrix)
{
	for (int i = 0; i < n; i++)
		for (int j = n; j < 2*n; j++)
			if (j-i == n)
				matrix[i][j] = 1;
			else
				matrix[i][j] = 0;
	return matrix;
}

double **copy(int n, int m, double **matrix, double **new_matrix)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			new_matrix[i][j] = matrix[i][j];
	return new_matrix;
}

double **inverse(int n, double **matrix, double **result)
{
	double **big_matrix = allocate_memory(n, 2*n);
	big_matrix = copy(n, n, matrix, big_matrix);
	big_matrix = add_identity_matrix(n, big_matrix);
	print_matrix(n, 2*n, big_matrix);
	return NULL;
}

double **addition(int n, int m, double **matrix1, double **matrix2, double **result)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			result[i][j] = matrix1[i][j] + matrix2[i][j];
	return result;
}

double **multiplication(int n, int t, int m, double **matrix1, double **matrix2, double **result)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			result[i][j] = 0;
			for (int k = 0; k < t; k++)
				result[i][j] += matrix1[i][k]*matrix2[k][j];
		}
	return result;
}


double **filling_matrix(int n, int m, double **matrix, FILE *file)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			fscanf(file, "%lf", &matrix[i][j]);
	return matrix;
}

int main(int argc, char **argv)
{
	if (argc != 5)
	{
		printf("Put i/o filenames and operation as arguments\n");
		return BADPARAMETERS;
	}
	else
	{
		FILE *first = fopen(argv[1], "r");
		FILE *second = fopen(argv[2], "r");
		if (!first || !second)
		{
			printf("Input file doesn't found!\n");
			return NOFILE;
		}
		else
		{
			int operation;
			if (strlen(argv[3]) == 1)
				operation = argv[3][0];
			else
				return BADOPERATION;

			int n1,m1, n2, m2;
			fscanf(first, "%d %d", &n1, &m1);
			printf("Dimension of the first matrix - %d by %d\n", n1, m1);
			fscanf(second, "%d %d", &n2, &m2);
			printf("Dimension of the second matrix - %d by %d\n", n2, m2);
			switch(operation) 
			{
				case '+':
					printf("ADDITION\n");
					if (m1 != m2 || n1 != n2)
						printf("Matrix can not be folded!\n");
					else
					{
						double **matrix1 = allocate_memory(n1, m1);
						double **matrix2 = allocate_memory(n2, m2);
						matrix1 = filling_matrix(n1, m1, matrix1, first);
						matrix2 = filling_matrix(n2, m2, matrix2, second); 
						printf("First matrix:\n");
						print_matrix(n1,m1, matrix1);
						printf("Second matrix:\n");
						print_matrix(n2,m2, matrix2);	
						double **result = allocate_memory(n1, m1);
						result = addition(n1, m1, matrix1, matrix2, result);
						printf("Result matrix:\n");
						print_matrix(n1,m1, result);
						free(matrix1);
						free(matrix2);
						free(result);
					}
					break;
				case 'x':
					printf("MULTIPLICATION\n");
					if (m1 != n2)
						printf("Matrix can not multiply!\n");
					else
					{
						double **matrix1 = allocate_memory(n1, m1);
						double **matrix2 = allocate_memory(n2, m2);
						matrix1 = filling_matrix(n1, m1, matrix1, first);
						matrix2 = filling_matrix(n2, m2, matrix2, second); 
						printf("First matrix:\n");
						print_matrix(n1,m1, matrix1);
						printf("Second matrix:\n");
						print_matrix(n2,m2, matrix2);
						double **result = allocate_memory(n1, m2);
						result = multiplication(n1, m1, m2, matrix1, matrix2, result);
						printf("Result matrix:\n");
						print_matrix(n1, m2, result);
						free(matrix1);
						free(matrix2);
						free(result);
					}
					break;
				case '-':
					printf("INVERSE MATRIX\n");
					if (m1 != n1)
						printf("Inverse matrix can not be obtained\n");
					else
					{
						double **matrix1 = allocate_memory(n1, m1);
						matrix1 = filling_matrix(n1, m1, matrix1, first);
						printf("Matrix:\n");
						print_matrix(n1,m1, matrix1);
						double **result = allocate_memory(n1, m1);
						result = inverse(n1, matrix1, result);
						// printf("Inverse matrix:\n");
						// print_matrix(n1, m2, result);
						free(matrix1);
						free(result);
					}
					break;
				default:
					return BADOPERATION;
			}
		}
		fclose(first);
		fclose(second);
	}
}