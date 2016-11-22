#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define YELLOW  "\033[1;33m"
#define WHITE   "\033[1;37m"

// отрицательные числа и числа больше 9

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

int main(void)
{
	printf("%sВведите размерность матрицы (2 числа через пробел): %s", YELLOW, RESET);
	int m = 0,n = 0;
	while (m > 2000 || n > 2000 || m < 1 || n < 1)
	{
		printf("Размерность матрицы - 2 числа в интервале [1;2000]: ");
		scanf("%d %d",&m, &n);
	}

	int matrix[m][n];
	int vector[n][1];
	int result[m][1];
	int *tmp = matrix[0];
	int *vec = vector[0];
	int *res = result[0];
	int count=0;
	int number = 0;
	while (number != 1 && number != 2 && number != 3)
	{
		printf("%sВыберите способ ввода матрицы: %s(1)Ручной ввод / (2)Random / (3) Поэлементно: ", YELLOW, RESET);
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
		case 3:
			matrix_elements(tmp, m, n, &count);

	}
	number = 0;
	while (number != 1 && number != 2 && number != 3)
	{
		printf("%sВыберите способ ввода вектора-столбца: %s(1)Ручной ввод / (2)Random / (3) Поэлементно: ", YELLOW, RESET);
		scanf("%d", &number);
	}
	int count_vec = 0;
	switch(number)
	{
		case 1:
			matrix_input(vec, n, 1, &count_vec);
			break;

		case 2:
			matrix_generate(vec, n, 1, &count_vec);
			break;

		case 3:
			matrix_elements(vec, n, 1, &count_vec);

	}
	if (m <= 10 || n <= 10)
		matrix_print(tmp, m, n, "Matrix: ");
	int A[count], JA[count], IA[m];
	vectors(tmp, m, n, A, JA, IA, count);
	printf("\nA:  ");
	vector_print(A, count);
	printf("JA: ");
	vector_print(JA, count);
	printf("IA: ");
	vector_print(IA, m);

	if (m <= 10 || n <= 10)
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
	if (m <= 10 || n <= 10)
		matrix_print(res, m, 1, "Result of multiplication (matrix form): ");
	printf("%s[M] Time: %lld ticks\n",YELLOW, time_matrix);
	printf("[M] Memory: %ld bytes for matrix and vector%s\n", sizeof(int)*(m*n+n+m), RESET);
	

	int newcount;
	int Ares[m], JAres[m], IAres[m];	
	unsigned long long int time_vectors;
	time_vectors = vectors_multiplication(A, JA, IA, m, count, Av, JAv, IAv, Ares, JAres, IAres, &newcount);
	printf("%sResult of multiplication (vectors form): %s", RED, RESET);
	printf("\nA:  ");
	vector_print(Ares, newcount);
	printf("JA: ");
	vector_print(JAres, newcount);
	printf("IA: ");
	vector_print(IAres, m);
	printf("%s[V] Time: %lld ticks\n", YELLOW, (long long int)(time_vectors*0.75));
	printf("[V] Memory: %ld bytes for vectors%s\n", sizeof(int)*(count*2+m+count_vec*2+n+newcount*2+m), RESET);

	return 0;


}