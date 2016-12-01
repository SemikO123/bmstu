#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

/*
Написать программу для работы с матрицами, которая реализует сложение матриц, 
умножение матриц и вычисление обратной матрицы методом элементарных преобразований.
Исходные матрицы читаются из файла, результирующие матрицы записываются в файл. 
Один файл содержит одну матрицу. Количество строк и столбцов матрицы указывается 
в первой строчке файла. Имена файлов и выполняемая операция указывается через 
параметры командной строки.
*/

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
					printf("++++++++ ADDITION ++++++++\n");
					if (m1 != m2 || n1 != n2)
						printf("Matrix can not be folded!\n");
					else
					{
						double **matrix1 = allocate_memory(n1, m1);
						double **matrix2 = allocate_memory(n2, m2);
						if (!matrix1 || !matrix2)
						{
							printf("Memory problem\n");
							return MEMORYPROBLEM;
						}
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
						FILE *out = fopen(argv[4], "w");
						print_to_file(n1, m1, result, out);
						fclose(out);
						free(matrix1);
						free(matrix2);
						free(result);
					}
					break;
				case 'x':
					printf("++++++++ MULTIPLICATION ++++++++\n");
					if (m1 != n2)
						printf("Matrix can not multiply!\n");
					else
					{
						double **matrix1 = allocate_memory(n1, m1);
						double **matrix2 = allocate_memory(n2, m2);
						if (!matrix1 || !matrix2)
						{
							printf("Memory problem\n");
							return MEMORYPROBLEM;
						}
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
						FILE *out = fopen(argv[4], "w");
						print_to_file(n1, m2, result, out);
						fclose(out);
						free(matrix1);
						free(matrix2);
						free(result);
					}
					break;
				case '-':
					printf("++++++++ INVERSE MATRIX ++++++++\n");
					if (m1 != n1)
						printf("Inverse matrix can not be obtained\n");
					else
					{
						double **matrix1 = allocate_memory(n1, m1);
						if (!matrix1)
						{
							printf("Memory problem\n");
							return MEMORYPROBLEM;
						}
						matrix1 = filling_matrix(n1, m1, matrix1, first);
						printf("Matrix:\n");
						print_matrix(n1,m1, matrix1);
						double **result = allocate_memory(n1, m1);
						result = inverse(n1, matrix1, result);
						if (result)
						{
							printf("Inverse matrix:\n");
							print_matrix(n1, m2, result);
							FILE *out = fopen(argv[4], "w");
							print_to_file(n1, m2, result, out);
							fclose(out);
						}
						else
							printf("Could not find the inverse matrix\n");
						free(matrix1);
						free(result);
					}
					break;
				default:
					printf("Invalid operation!\n");
					return BADOPERATION;
			}
		}
		fclose(first);
		fclose(second);
	}
	return OK;
}