#include <stdio.h>
#include "errors.h"
#include "functions.h"

// Получает массив, размер массива, указатель фактическое количество элементов
// Возвращает код ошибки обработки файла или признак об избыточности чисел в нем
int ReadArr(float arr[],int n, FILE *file, int *count)
{
	int priznak;
	float num;
	switch(fscanf(file,"%f",&arr[*count]))
	{
		case -1:
			priznak = EMPTYFILE;
			break;
		case 0:
			priznak = BADFILE;
			break;
		case 1:
			priznak = OK;
			*count += 1;
			while ((fscanf(file, "%f",&arr[*count]) == 1) & (*count < n))
				*count += 1;
			if (fscanf(file, "%f", &num) == 1)
				priznak = EXCESS;
	}
	return priznak;
}

int Average(const float arr[],int n, float *avrg)
{
	int i;
	float sum;
	for (i=0; i<n; i++)
		sum += arr[i];
	*avrg = sum/n;
	return 0;
}

/* Получает исходный массив, новый массив(пустой), количество элементов в исходном
массиве, количество элементов в новом массиве, значение среднего арифметического */
int NewArrGen(const float arr[], float newarr[], int n, int *j, float avrg)
{
	int i;
	for (i=0;i<n;i++)
		if (arr[i] > avrg)
		{
			newarr[*j] = arr[i];
			*j+=1;
		}
	return 0;
}
