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
			while ((*count < n) && (fscanf(file, "%f",&arr[*count]) == 1))
				*count += 1;
			if (fscanf(file, "%f", &num) == 1)
				priznak = EXCESS;
	//printf("N=%d\n",*count);
	}
	return priznak;
}

void Average(const float arr[],int n, float *avrg)
{
	int i;
	float sum=0;
	for (i=0; i<n; i++)
		sum += arr[i];
	*avrg = sum/n;

}

/* Получает исходный массив, файловая переменная, количество элементов в исходном 
массиве, значение среднего арифметического */
void NewArrGen(const float arr[], FILE *file, int n, float avrg)
{
	int j=0;
	float newarr[N];
	for (int i=0;i<n;i++)
		if (arr[i] > avrg)
		{
			newarr[j] = arr[i];
			// for (int k=0;k<n;k++)
			// 	printf("%f ",newarr[k]);
			fprintf(file, "%.3f \n", newarr[j]);
			j+=1;

		}
}

