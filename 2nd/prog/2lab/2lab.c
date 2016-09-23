/* 
Написать программу, которая считывает из текстового файла целые числа в массив 
и выполняет обработку этого массива (см. распределение вариантов).
Память под массив выделяется динамически. Число элементов в массиве 
определяется в первом проходе по текстовому файлу, во время второго прохода 
числа считываются в массив. Имя файла передается через параметры командной строки.
Вычислить значение min(x[0]*x[1], x[1]*x[2],x[2]*x[3], ...,
 x[n-3]*x[n-2], x[n-2]*x[n-1]), где x[i] - элементы массива x из n элементов 
 */

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "errors.h"


int main(int argc, char **argv)
{
	int out_error;
	FILE *file;
	if (argc != 2)
	{
		printf("\nPut the name of file as parameter of launch\n");
		out_error = NOFILENAME;
	}
	else
	{
		file = fopen(argv[1], "r");
		if (file == NULL)
		{
			printf("\nFile doesn't found\n");
			out_error = NOFILE;
		}
		else
		{
			int count_of_numbers = 0;
			switch (len_of_array(file, &count_of_numbers))
			{
				case EMPTY:
					printf("\nFile is empty\n");
					fclose(file);
					out_error = EMPTY;
					break;
				case BADINPUT:
					printf("\nCan't get numbers from file\n");
					fclose(file);
					out_error = BADINPUT;
					break;
				case OK:
					printf("\nCount of numbers = %d\n", count_of_numbers);
					int *array = array_generate(&count_of_numbers);
					if (array == NULL)
					{
						printf("MEMORY PROBLEM");
						out_error = MEMORYPROBLEM;
						free(array);
					}
					else
					{
						rewind(file);
						array_filling(array, array + count_of_numbers, file);
						fclose(file);
						int min;
						switch (counting(array, array + count_of_numbers, &min))
						{
							case ONEELEMENT:
								printf("Array has only one element\n");
								free(array);
								out_error = ONEELEMENT;
								break;
							case OK:
								printf("Minimum of x[0]*x[1], x[1]*x[2]... = %d\n", min);
								out_error = OK;
								free(array);
						}
					}						
			}
		}
	}
	//printf("ERROR = %d\n",out_error);
	return out_error;
}


