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

double **filling_matrix(int n, int m, double **matrix, FILE *file)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			fscanf(file, "%lf", &matrix[i][j]);
	return matrix;
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
			printf("Размерность первой матрицы - %d на %d\n", n1, m1);
			fscanf(second, "%d %d", &n2, &m2);
			printf("Размерность второй матрицы - %d на %d\n", n2, m2);
			switch(operation) 
			{
				case '+':
					printf("Сложение\n");
					if (m1 != m2 || n1 != n2)
						printf("Матрицы сложить нельзя!\n");
					else
					{
						double **matrix1 = allocate_memory(n1, m1);
						double **matrix2 = allocate_memory(n2, m2);
						matrix1 = filling_matrix(n1, m1, matrix1, first);
						matrix2 = filling_matrix(n2, m2, matrix2, second); 
						print_matrix(n1,m1, matrix1);
						print_matrix(n2,m2, matrix2);	
						double **result = allocate_memory(n1, m1);
						result = addition(n1, m1, matrix1, matrix2);
						free(matrix1);
						free(matrix2);
						free(result);
					}
					break;
				case 'x':
					printf("Умножение\n");
					if (m1 != n2)
						printf("Матрицы перемножить нельзя!\n");
					else
					{
					}
					break;
				case '-':
					printf("Обратная\n");
					break;
				default:
					return BADOPERATION;
			}
		}
	}
}