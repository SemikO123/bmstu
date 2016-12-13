#include <stdio.h>
#include <stdlib.h>

/*
Задана система двусторонних дорог. Для каждой пары городов найти длину 
кратчайшего пути между ними.
*/

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define PINK    "\033[1;35m"
#define WHITE   "\033[1;37m"

#define INF 10000

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

int main(void)
{
	int menu = -1;
	int **matrix = NULL;
	int **matr = NULL;
	int count;
	do
	{
		printf("%sМеню работы с графами:\n", YELLOW);
		printf("(1) Загрузка графа из файла\n");
		printf("(2) Задание графа вручную\n");
		printf("(3) Печать графа\n");
		printf("%s(4) Длина кратчайшего пути между каждой парой городов\n", GREEN);
		printf("%s(5) Длины кратчайшего пути из одного города до других\n", YELLOW);
		printf("(6) Вывод на экран матрицы кратчайших расстояний\n");
		printf("(7) Проверка связности графа\n");
		printf("(8) Построение минимального остовного дерева\n");
		printf("(0) Завершение работы%s\n",RESET);
		printf("Введите пункт меню: ");
		scanf("%d", &menu);
		switch(menu)
		{
			case 1:
			{
				FILE *in = fopen("in.txt", "r");
				fscanf(in,"%d", &count);
				matrix = allocate_memory(count, count);
				matrix = filling_matrix(in, matrix, count);
				printf("Матрица достижимости:\n");
				print_matrix(matrix, count, 2);
				printf("Матрица стоимостей:\n");
				print_matrix(matrix, count,1);
				fclose(in);
				break;
			}
			case 2:
			{
				printf("Количество вершин: ");
				scanf("%d", &count);
				matrix = allocate_memory(count, count);
				for (int i = 0; i < count; i++)
					for (int j = 0; j < count; j++)
						matrix[i][j] = 0;
				int a, b, rasst;
				printf("%sВвод данных.%s Для завершения введите отрицательные числа.\n", PINK, RESET);
				do
				{
					printf("Введите через пробел номера двух вершин (<=%d) и расстояние между ними: ", count);
					scanf("%d %d %d", &a, &b, &rasst);
					if (a <= count && a > 0 && b <= count && b > 0 && rasst > 0)
					{
						matrix[a-1][b-1] = rasst;
						matrix[b-1][a-1] = rasst;
						//printf("[%d][%d] = %d", a-1,b-1,rasst);
					}
					else 
						if (a < 0)
							break;
						else
							printf("%sНеверный ввод%s\n", RED, RESET);
				}
				while (a > -1);
				printf("Матрица достижимости:\n");
				print_matrix(matrix, count, 2);
				printf("Матрица стоимостей:\n");
				print_matrix(matrix, count,1);
				break;
			}
			case 3:
				if (matrix == NULL)
					printf("Загрузите матрицу из файла(1) или задайте вручную(2)!\n");
				else
				{
					get_graph(matrix, count);
					system("/bin/bash /home/irina/Документы/bmstu/2ndCourse/tsd/8lab/file.sh");
				}
				break;
			case 4:
				if (!matrix)
					printf("Загрузите матрицу из файла(1) или задайте вручную(2)!\n");
				else
				{
					printf("%s| Город 1 | Город 2 | Кратчайшее расстояние |\n", WHITE);
					for (int i = 0; i < count; i++)
					{
						int *min_rasst = malloc(sizeof(int)*count);
						min_rasst = dijkstra(count, matrix, i, min_rasst);
						for (int j = i+1; j < count; j++)
						{
							printf("+—————————+—————————+———————————————————————+\n");
							if (min_rasst[j] != INF)
								printf("|  %2d     |   %2d    |         %3d           |\n", i+1, j+1, min_rasst[j]);
							else
								printf("|  %2d     |   %2d    |           %s∞%s           | %s\n", i+1, j+1, RED, RESET, RESET);
						}
					}
					printf("+—————————+—————————+———————————————————————+\n");
				}
				break;
			case 5:
			{
				if (!matrix)
					printf("Загрузите матрицу из файла(1) или задайте вручную(2)!\n");
				else
				{
					int v0;
					printf("Введите номер начальной вершины(город): ");
					scanf("%d", &v0);
					v0 -= 1;
					int *min_rasst = malloc(sizeof(int)*count);
					// int already_used[count];
					min_rasst = dijkstra(count, matrix, v0, min_rasst);
					for (int i = 0; i < count; i++)
						if (v0 != i)
						{
							if (min_rasst[i] == INF)
								printf("%s  Из города %d нельзя попасть в город %d               \n%s",PINK, v0+1, i+1, RESET);
							else
								printf("%s  Кратчайшее расстояние между городами %d и %d - %3d  \n%s",PINK, v0+1, i+1, min_rasst[i], RESET);
						}
					free(min_rasst);
				}
				break;
			}
			case 6:
				printf("%sМатрица достижимости (Алгоритм Флойда — Уоршелла): %s\n", PINK, RESET);
				matr = allocate_memory(count, count);
				matr = floyd_warshall(count, matrix, matr);
				for (int i = 0; i < count; i++)
					for (int j = 0; j < count; j++)
						if (matr[i][j] == INF)
							matr[i][j] = 0;
				print_matrix(matr, count, 1);
				free(matr);
				break;
			case 7:
				switch(connected_graph(matr, matrix, count))
				{
					case 0:
						printf("%s   Граф несвязный%s\n", PINK, RESET);
						break;
					case 1:
						printf("%s   Граф связный%s\n", PINK, RESET);
						break;
				}
				free(matr);
				break;
			case 8:
			{
				if (connected_graph(matr, matrix, count) == 0)
					printf("%sНе удаётся построить\n%s",RED, RESET);
				else
				{
					int *result = malloc(count*sizeof(int));
					int v0;
					printf("Введите начальную вершину: ");
					scanf("%d", &v0);
					result = prim(matrix, result, count, v0-1);
					printf("%sМинимальное остовное дерево: \n%s", PINK, RESET);
					for (int i = 0; i < count; i++)
						if (i != count-1)
							printf("%d -> ", result[i]+1);
						else
							printf("%d\n", result[i]+1);
					get_graph_prim(count, matrix, result);
					system("/bin/bash /home/irina/Документы/bmstu/2ndCourse/tsd/8lab/file.sh");
					free(result);
				}
				break;
			}
			case 0:
				free(matrix);
				break;
			default:
				printf("Пункт меню выбран неверно!\n");
				break;
		}
		
	}
	while (menu != 0);
}
