#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define WHITE   "\033[1;37m"

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

void matrix_print(int *matrix, int m, int n, char *text)
{
	printf("%s%s%s\n", RED, text, RESET);
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
				//printf("num=%d, stolb=%d\n", *(matrix + n*i + j), j);
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

unsigned long long int tick(void)
{
	unsigned long long int time = 0;
	__asm__ __volatile__ ("rdtsc" : "=A" (time));
	return time;
}

unsigned long long int matrix_multiplication(const int *matrix, const int *vector, int *result, int m, int n, int count_matr, int count_vec)
{
	unsigned long long int time1, time2;
	for (int j = 0; j < m; j++)
			*(result + j) = 0;
	int k = 0;
	time1 = tick();
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			*(result + k) += *(matrix + n*i + j) * *(vector + j);
		k++;
	}
	time2 = tick();
	return time2-time1;
}

int main(void)
{

	printf("%sВведите размерность матрицы (2 числа через пробел): %s", YELLOW, RESET);
	int m,n;
	scanf("%d %d",&m, &n);
	int matrix[m][n];
	int vector[m][1];
	int result[m][1];
	int *tmp = matrix[0];
	int *vec = vector[0];
	int *res = result[0];
	int count=0;
	int number = 0;
	while (number != 1 && number != 2)
	{
		printf("%sВыберите способ ввода матрицы: %s(1)Ручной ввод / (2)Random: ", YELLOW, RESET);
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
	number = 0;
	while (number != 1 && number != 2)
	{
		printf("%sВыберите способ ввода вектора-столбца: %s(1)Ручной ввод / (2)Random: ", YELLOW, RESET);
		scanf("%d", &number);
	}
	int count_vec = 0;
	switch(number)
	{
		case 1:
			matrix_input(vec, n, 1,&count_vec);
			break;

		case 2:
			matrix_generate(vec, n, 1 ,&count_vec);
			break;

	}
	matrix_print(tmp, m, n, "Matrix: ");
	int A[count], JA[count], IA[n];
	vectors(tmp, m, n, A, JA, IA, count);
	printf("\nA:  ");
	vector_print(A, count);
	printf("JA: ");
	vector_print(JA, count);
	printf("IA: ");
	vector_print(IA, m);

	matrix_print(vec, n, 1, "Vector: ");
	int Av[count_vec], JAv[count_vec], IAv[n];
	vectors(vec, n, 1, Av, JAv, IAv, count_vec);
	printf("\nA:  ");
	vector_print(Av, count_vec);
	printf("JA: ");
	vector_print(JAv, count_vec);
	printf("IA: ");
	vector_print(IAv, n);

	unsigned long long int time_matrix;
	time_matrix = matrix_multiplication(tmp, vec, res, m, n, count, count_vec);
	matrix_print(res, m, 1, "Result of multiplication (matrix form): ");
	printf("Time %lld\n", time_matrix);

	return 0;


}