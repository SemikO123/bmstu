#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
Разреженная (содержащая много нулей) матрица хранится в форме 3-х объектов:
     - вектор A содержит значения ненулевых элементов;
     - вектор JA содержит номера столбцов для элементов вектора A;
     - связный список IA, в элементе Nk которого находится номер компонент
в A и JA, с которых начинается описание строки Nk матрицы A.

1. Смоделировать операцию умножения  матрицы и вектора-столбца, хранящихся 
в этой форме, с получением результата в той же форме.
2. Произвести операцию умножения, применяя  стандартный алгоритм работы с матрицами.
3. Сравнить время выполнения операций и объем памяти при использовании 
этих 2-х алгоритмов при различном проценте заполнения матриц.
*/



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
					*count+=1;
			}
		}
}

void matrix_print(int *matrix, int m, int n)
{
	printf("Matrix:\n");
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%3d ", *(matrix+n*i+j));
		printf("\n");
	}
}

void vectors(int *matrix, int m, int n, int *A, int *JA, int *IA, int count)
{
	int k=0;
	for (int i = 0; i < m; i++)
	{
		int flag = 0, first = 0;
		for (int j = 0; j < n; j++)
		{
			if (*(matrix + n*i + j) != 0)
			{
				A[k] = *(matrix + n*i + j);
				JA[k] = j;
				if (!first)
				{
					IA[i] = k;
					first = 1;
				}
				k++;
			}
			else
				flag += 1;
			
		}
		if (flag == n)
			IA[i] = -1;
	}
	//printf("count=%d k=%d\n", count, k);
}

void vector_print(int *vector, int count)
{
	for (int i = 0; i < count; i++)
		printf("%d ", vector[i]);
	printf("\n");
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

int main(void)
{

	printf("Введите размерность матрицы (через пробел): ");
	int m,n;
	scanf("%d %d",&m, &n);
	int matrix[m][n];
	int *tmp = matrix[0];
	int count=0;
	int number = 0;
	while (number != 1 && number != 2)
	{
		printf("Выберите способ ввода матрицы: (1)Ручной ввод / (2)Random: ");
		scanf("%d", &number);
	}

	switch(number)
	{
		case 1:
			matrix_input(tmp,m,n,&count);
			break;

		case 2:
			matrix_generate(tmp, m, n ,&count);
			break;

	}
	matrix_print(tmp, m, n);
	int A[count];
	int JA[count];
	int IA[n];
	vectors(tmp, m, n, A, JA, IA, count);
	printf("\nA:  ");
	vector_print(A, count);
	printf("JA: ");
	vector_print(JA, count);
	printf("IA: ");
	vector_print(IA, m);



	return 0;


}