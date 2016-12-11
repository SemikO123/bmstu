#include <stdio.h>
#include <stdlib.h>

/*
Реализовать алгоритмы обработки графовых структур: поиск различных путей, 
проверка связности, построение остовых деревьев минимальной стоимости.
Задана система двусторонних дорог. Найти два города и соединяющий их путь, 
который проходит через каждую из дорог системы только один раз
*/

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
	fprintf(graph, "digraph G{\n");
	for (int i = 0; i < count; i++)
		for (int j = 0; j < count; j++)
			if (matrix[i][j] != 0)
				fprintf(graph, "%d->%d\n", i, j);
	fprintf(graph, "}");
	fclose(graph);
}

int *dijkstra(int count, int **matrix, int v0, int *min_rasst)
{
	int already_used[count];
	int min_ind, min, tmp;
	for (int i = 0; i < count; i++)
	{
		min_rasst[i] = 10000;
		already_used[i] = 1;
	}
	min_rasst[v0] = 0;
	do
	{
		min_ind = 10000;
		min = 10000;
		for (int i = 0; i < count; i++)
		{
			if (already_used[i] == 1 && min_rasst[i] < min)
			{
				min = min_rasst[i];
				min_ind = i;
			}
		}
		if (min_ind != 10000)
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
	while (min_ind < 10000);
	return min_rasst;
}

int main(void)
{
	int menu = -1;
	int **matrix;
	int count;
	do
	{
		printf("Меню работы с графами:\n");
		printf("(1) Загрузка графа из файла\n");
		printf("(2) Задание графа вручную\n");
		printf("(3) Печать графа\n");
		printf("(4) Поиск пути из одной вершины до остальных\n");
		printf("(5) ?\n");
		printf("(6) Проверка связности графа\n");
		printf("(7) Построение остовых деревьев минимальной стоимости\n");
		printf("(8) Задание лабораторной работы\n");
		printf("(0) Завершение работы\n");
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
				printf("Количество вершин:");
				scanf("%d", &count);
				matrix = allocate_memory(count, count);
				for (int i = 0; i < count; i++)
					for (int j = 0; j < count; j++)
					{
						// if (i == j)
						// 	matrix[i][j] = 0;
						// else
						// {
							printf("Введите вес ребра между %d и %d вершинами или 0, если ребра нет: ",i,j);
							scanf("%d", &matrix[i][j]);
						// }
					}
				printf("Матрица достижимости:\n");
				print_matrix(matrix, count, 2);
				printf("Матрица стоимостей:\n");
				print_matrix(matrix, count,1);
				break;
			}
			case 3:
				get_graph(matrix, count);
				system("/bin/bash /home/irina/Документы/bmstu/2ndCourse/tsd/8lab/file.sh");
				break;
			case 4:
			{
				int v0;
				printf("Введите начальную вершину: ");
				scanf("%d", &v0);
				int *min_rasst = malloc(sizeof(int)*count);
				// int already_used[count];
				min_rasst = dijkstra(count, matrix, v0, min_rasst);
				for (int i = 0; i < count; i++)
					printf("%d ", min_rasst[i]);
				break;
			}
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			case 0:
				break;
			default:
				printf("Пункт меню выбран неверно!\n");
				break;
		}
		
	}
	while (menu != 0);
}
