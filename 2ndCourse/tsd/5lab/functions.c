#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"


void matrix_generate(int *matrix, int m, int n, int *count)
{
	printf("Процент нулей (для генерации матрицы): ");
	int procent;
	int nullorno;
	scanf("%d", &procent);
	procent/=10;
	srand(time(NULL));	
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
		{
			nullorno = rand()%10;
			if (nullorno < procent)
				*(matrix + n*i + j) = 0;
			else
			{
				*(matrix + n*i + j) = rand()%10;
				if (*(matrix + n*i + j) != 0)
				{
					//printf("num=%d count=%d\n", *(matrix + n*i + j), *count);
					*count+=1;
				}
			}
		}

	//printf("c=%d\n", *count);
}

void matrix_print(int *matrix, int m, int n, char *text)
{
	printf("%s%s%s\n", RED, text, RESET);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			if (*(matrix+n*i+j) == 0)
				printf("%3d ", *(matrix+n*i+j));
			else
				printf("%s%3d %s", RED, *(matrix+n*i+j), RESET);

		printf("\n");
	}
}

void vector_print(int *vector, int count)
{
	for (int i = 0; i < count; i++)
		printf("%d ", vector[i]);
	printf("\n");
}

void vectors(const int *matrix, int m, int n, int *A, int *JA, int *IA, int count)
{
	int k=0;
	int flag = 0, first = 0;
	for (int i = 0; i < m; i++)
	{
		flag = 0;
		first = 0;
		for (int j = 0; j < n; j++)
		{
			if (*(matrix + n*i + j) != 0)
			{
				A[k] = *(matrix + n*i + j);
				JA[k] = j;
				k++;
				if (!first)
				{
					IA[i] = k-1;
					first = 1;
				}
			}
			else
			{
				flag += 1;
			}
			
		}
		if (flag == n)
		{
			IA[i] = -1;
		}
	}
}


void matrix_input(int *matrix, int m, int n, int *count)
{
	for (int i = 0; i < m; i++)
	{
		printf("Ввод %d строки из %d символов: ", i+1, n);
		for (int j = 0; j < n; j++)
			scanf("%d", &*(matrix+n*i+j));
	}
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (*(matrix+n*i+j) != 0)
				(*count)++;
}

void matrix_elements(int *matrix, int m, int n, int *count)
{
	int num;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (*(matrix+n*i+j) != 0)
				*(matrix+n*i+j) = 0;
	do
	{
		printf("Введите (1) чтобы добавить элемент, (0) чтобы закончить ввод: ");
		scanf("%d", &num);
		if (num != 1)
			break;
		printf("Введите i-строку, j-столбец для ввода и значение: ");
		int i, j, elem;
		scanf("%d %d %d", &i, &j, &elem);
		if (i < m && j < n)
		{
			*(matrix+n*i+j) = elem;
			printf("%d %d %d\n", elem, *(matrix+n*i+j), *count);
			(*count)++;
		}
	}
	while (num == 1);
}

unsigned long long int tick(void)
{
	unsigned long long int time = 0;
	__asm__ __volatile__ ("rdtsc" : "=A" (time));
	return time;
}

unsigned long long int matrix_multiplication(const int *matrix, const int *vector, int *result, int m, int n, int count_matr, int count_vec)
{
	unsigned long long int time1, time2;
	time1 = tick();
	int res = 0;
	for (int j = 0; j < m; j++)
			*(result + j) = 0;
	int k = 0;
	for (int i = 0; i < m; i++)
	{
		res = 0;
		for (int j = 0; j < n; j++)
			res += *(matrix + n*i + j) * *(vector + j);
			//*(result + k) += *(matrix + n*i + j) * *(vector + j);
		*(result+k) = res;
		k++;
	}
	time2 = tick();
	return time2-time1;
}

unsigned long long int vectors_multiplication(int *A, int *JA, int *IA, int m, int count, int *Av, int *JAv, int *IAv, int *Ares, int *JAres, int *IAres, int *newcount)
{
	int notnull = 0;
	unsigned long long int time1, time2;
	*newcount = m;
	for (int i = 0; i < m; i++)
		IAres[i] = 0;
	time1 = tick();
	for (int i = 0; i < m; i++)
		if (IA[i] != -1)
		{
			int result = 0;
			if (i == m-1)
			{
				for (int j = IA[i]; j < count; j++)
					if (IAv[JA[j]] != -1)
					{
						//printf("%d * %d\n", A[j],Av[IAv[JA[j]]]);
						result += A[j]*Av[IAv[JA[j]]];
					}
				if (result != 0)
				{
					IAres[i] = notnull;
					Ares[notnull] = result;
					JAres[notnull++] = 0; 
				}
				else
				{
					IAres[i] = -1;
					(*newcount)--;
				}
			}
			else
			{
				if (IA[i+1] != -1)
				{
					for (int j = IA[i]; j < IA[i+1]; j++)
						if (IAv[JA[j]] != -1)
						{
							//printf("%d * %d\n", A[j],Av[IAv[JA[j]]]);
							result += A[j]*Av[IAv[JA[j]]];
						}
					if (result != 0)
					{
						IAres[i] = notnull;
						Ares[notnull] = result;
						JAres[notnull++] = 0; 
					}
					else
					{
						IAres[i] = -1;
						(*newcount)--;
					}
				}
				else
				{
					int t = 1;
					int gran;
					while (IA[i+t] == -1 )
						t++;
					if (i+t >= m)
						gran = count;
					else
						gran = IA[i+t];
					//printf("-1POWER granica=%d\n",gran);
					for (int j = IA[i]; j < gran; j++)
						if (IAv[JA[j]] != -1)
						{
							//printf("%d * %d\n", A[j],Av[IAv[JA[j]]]);
							result += A[j]*Av[IAv[JA[j]]];
						}
					if (result != 0)
					{
						IAres[i] = notnull;
						Ares[notnull] = result;
						JAres[notnull++] = 0; 
					}
					else
					{
						IAres[i] = -1;
						(*newcount)--;
					}
				}
			}
		}
		else
		{
			IAres[i] = -1;
			(*newcount)--;
		}
	time2 = tick();
	return time2-time1;
}
