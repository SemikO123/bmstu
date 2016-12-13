#include "functions.h"

int **allocate_memory(int n, int m)
{
	int **data = malloc(n*sizeof(int*) + n*m*sizeof(int));
	if (!data)
		return NULL;
	for (int i = 0; i < n; i++)
		data[i] = (int*)((char*)data+n*sizeof(int*)+i*m*sizeof(int));
	return data;
} 

int **filling_matrix(FILE *file, int **matrix, int count)
{
	for (int i = 0; i < count; i++)
		for (int j = 0; j < count; j++)
			fscanf(file, "%d", &matrix[i][j]);
	return matrix;
}

void print_matrix(int **matrix, int count, int flag)
{
	switch(flag)
	{
		case 1:
			for (int i = 0; i < count; i++)
			{
				for (int j = 0; j < count; j++)
				{
					if (matrix[i][j] == 0)
						printf("   ∞");
					else
						printf("%4d",matrix[i][j]);
				}
				printf("\n");
			}
			break;
		case 2:
			for (int i = 0; i < count; i++)
			{
				for (int j = 0; j < count; j++)
				{
					if (matrix[i][j] != 0)
						printf("   1");
					else
						printf("%4d", matrix[i][j]);
				}
				printf("\n");
			}
			break;
	}
}

void get_graph(int **matrix, int count)
{
	FILE *graph = fopen("graph.gv", "w");
	fprintf(graph, "graph G{\n");
	for (int i = 0; i < count; i++)
	{
		fprintf(graph,"%d\n", i+1);
		for (int j = i; j < count; j++)
			if (matrix[i][j] != 0)
				fprintf(graph, "%d -- %d [label=%d]\n", i+1, j+1, matrix[i][j]);
	}
	fprintf(graph, "}");
	fclose(graph);
}

void get_graph_prim(int count, int **matrix, int *vector)
{
	FILE *graph = fopen("graph.gv", "w");
	fprintf(graph, "graph G{\n");
	for (int i = 0; i < count; i++)
	{
		for (int j = i; j < count; j++)
			if (matrix[i][j] != INF)
				fprintf(graph, "%d -- %d [label=%d]\n", i+1, j+1, matrix[i][j]);
	}
	for (int i = 0; i < count-1; i++)
	{
		fprintf(graph, "%d -- %d [color=blue]\n", vector[i]+1, vector[i+1]+1);
	}
	fprintf(graph, "}");
	fclose(graph);
}

int *dijkstra(int count, int **matrix, int v0, int *min_rasst)
{
	int already_used[count];
	int min_ind, min, tmp;
	for (int i = 0; i < count; i++)
	{
		min_rasst[i] = INF;
		already_used[i] = 1;
	}
	min_rasst[v0] = 0;
	do
	{
		min_ind = INF;
		min = INF;
		for (int i = 0; i < count; i++)
		{
			if (already_used[i] == 1 && min_rasst[i] < min)
			{
				min = min_rasst[i];
				min_ind = i;
			}
		}
		if (min_ind != INF)
		{
			for (int i = 0; i < count; i++)
			{
				if (matrix[min_ind][i] > 0)
				{
					tmp = min+matrix[min_ind][i];
					if (tmp < min_rasst[i])
						min_rasst[i] = tmp; 
				}
				
			}
			already_used[min_ind] = 0;
		}
	}
	while (min_ind < INF);
	return min_rasst;
}

int minimum(int a, int b)
{
	return (a < b) ? a : b;
}

int **floyd_warshall(int n, int **matrix, int **matr)
{
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (matrix[i][j] != 0)
				matr[i][j] = matrix[i][j];
			else
				matr[i][j] = INF;
	for (int k = 0; k < n; k++)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				matr[i][j] = minimum(matr[i][j], matr[i][k]+matr[k][j]);
	for (int i = 0; i < n; i++)
	{
		matr[i][i] = 0;
	}

	return matr;
}

int connected_graph(int **matr, int **matrix, int count)
{
	matr = allocate_memory(count, count);
	matr = floyd_warshall(count, matrix, matr);
	for (int i = 0; i < count; i++)
		for (int j = 0; j < count; j++)
			if (matr[i][j] == INF)
				return 0;
	return 1;
}

int firstzero(int *mass, int n)
{
	for (int i = 0; i < n; i++)
		if (mass[i] == 0)
			return i;
	return -1;
}

int *prim(int **matrix, int *result, int count, int v0)
{
	// printf("\nresult = ");
	// for (int i = 0; i < count; i++)
	// 	printf("%d", result[i]);
	// printf("\nalready = ");
	// for (int i = 0; i < count; i++)
	// 	printf("%d", already_used[i]);
	for (int i = 0; i < count; i++)
		for (int j = 0; j < count; j++)
			if (matrix[i][j] == 0)
				matrix[i][j] = INF;
	int *already_used = malloc(count* sizeof(int));
	for (int i = 0; i < count; i++)
		already_used[i] = 0;
	already_used[v0] = 1;

	result[0] = v0;
	for (int i = 1; i < count; i++)
	{
		int min = matrix[v0][firstzero(already_used, count)];
		result[i] = firstzero(already_used,count);
		for (int j = 0; j < count; j++)
			if (matrix[v0][j] < min && already_used[j] == 0)
			{
				min = matrix[v0][j];
				result[i] = j;
			}
		v0 = result[i];
		already_used[v0] = 1;
	}
	return result;		
}

