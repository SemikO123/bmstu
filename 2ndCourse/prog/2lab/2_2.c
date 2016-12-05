#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <math.h>

#define NOFILENAME -1
#define NOFILE -2
#define MEMORYPROBLEM -3
#define OK 0
/*
Написать программу, которая упорядочивает массив.
Данные в массив считываются из файла (можно и нужно взять функцию чтения массива 
из предыдущей лабораторной работы). Полученный после сортировки массив записывается 
в файл. Возможно, что перед сортировкой элементы массива могут быть отфильтрованы 
с помощью функции-фильтра. Функция-фильтр работает следующим образом:
определяет количество элементов массива, которые удовлетворяют заданному условию;
выделяет память под соответствующее количество элементов;
копирует элементы, удовлетворяющие условию, из старого массива в новый.
Функция сортировки реализуется универсальной (т.е. имеет одинаковый прототип 
с функцией qsort из стандартной библиотеки (stdlib.h)).
Все параметры (имена файлов, необходимость фильтрации) передаются 
через аргументы командной строки. Для функции сортировки и функции-фильтра 
реализуются модульные тесты (отдельный проект).
Функция-фильтр - расположенные между минимальным и максимальным элементами массива.
Алгоритм сортировки - Модифицированная сортировка пузырьком III. Идеи первой и 
второй модифицированной сортировки пузырьком объединяются.
*/


int main(int argc, char **argv)
{
	int out_error = OK;
	FILE *file;
	if (argc != 4)
	{
		printf("\nPut the names of i/o files and filter as parameter of launch\n");
		out_error = NOFILENAME;
	}
	else
	{
		file = fopen(argv[1], "r");
		if (file == NULL)
		{
			printf("\nInput file doesn't found\n");
			out_error = NOFILE;
		}
		else
		{
			int count_of_numbers = 0, count = 0, out_error = 0;
			int *array;
			if (array_generate(file, &count_of_numbers, &array) == 0)
			{
				char *num;
				int filter = strtol(argv[3], &num, 10);
				if (*num)
					printf("Doesn't found the filter parameter\n");
				else
				{
					switch(filter)
					{
						case 1:
							{
								int *new_array = filter_array(array, array+count_of_numbers, &count, &out_error);
								if (!new_array)
								{
									printf("Array is empty!\n");
									return OK;
								}

								if (out_error == MEMORYPROBLEM)
								{
									printf("Memory problem!\n");
									return MEMORYPROBLEM;
								}
								free(array);
								array = new_array;
								count_of_numbers = count;
							}
						case 0:
							{
								printf("Array:        ");
								print_array(array, count_of_numbers);
								my_sort(array, count_of_numbers, sizeof(int), compare_int);
								printf("\nSorted array: ");
								print_array(array, count_of_numbers);
								printf("\n");
								FILE *out = fopen(argv[2], "w");
								if (!out)
								{
									printf("Output file doesn't found!\n");
									out_error = NOFILE;
								}
								else
									print_to_file(out, array, count_of_numbers);
								fclose(out);
								free(array);
								break;
							}
						default:
							printf("\nPut 1(use filter) or 0(don't use filter) as fourth parameter of launch\n");
							break;

					}
				}
			}
		}
	}
	return out_error;
}
