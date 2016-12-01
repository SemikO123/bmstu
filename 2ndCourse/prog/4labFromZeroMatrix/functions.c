#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"


void print_to_file(int n, int m, double **matrix, FILE *file)
{
	fprintf(file, "%d %d\n", n, m);
	for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
        	if (matrix[i][j] - (int)matrix[i][j] == 0)
        		fprintf(file, "%8d", (int)matrix[i][j]);
        	else
            	fprintf(file, " %7.4f", matrix[i][j]);
        }
        fprintf(file,"\n");
    }
}

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
        		printf("%8d", (int)matrix[i][j]);
        	else
            	printf(" %7.4f", matrix[i][j]);
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

double **transformation(int n, int m, double **matrix)
{
	for (int i = 0; i < n; i++)
	{
		if (matrix[i][i] == 0)
			return NULL;
		for (int j = m-1; j >= 0; j--)
			matrix[i][j] /= matrix[i][i];
		for (int j = 0; j < n; j++)
			if (j != i)
				for (int k = m-1; k >= 0; k--)
					matrix[j][k] -= matrix[j][i]*matrix[i][k];
	}
	return matrix;
}

double **get_result(int n, double **matrix, double **result)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			result[i][j] = matrix[i][j+n];
	return result;
}

double **inverse(int n, double **matrix, double **result)
{
	double **big_matrix = allocate_memory(n, 2*n);
	if (big_matrix)
	{
		big_matrix = copy(n, n, matrix, big_matrix);
		big_matrix = add_identity_matrix(n, big_matrix);
		big_matrix = transformation(n, 2*n, big_matrix);
		if (big_matrix)
			result = get_result(n, big_matrix, result);
		else
			result = NULL;
		free(big_matrix);
		return result;
	}
	else
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
