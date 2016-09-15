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
#define EMPTY -2
#define BADINPUT -3
#define OK 0

int LenOfArray(FILE *file, int *count);

int main(int argc, char **argv)
{
	FILE *file;
	if (argc != 2)
		printf("Put the name of file as parameter of launch\n");
	else
	{
		file = fopen(argv[1],"r");
		if (file == NULL)
			printf("File doesn't found\n");
		else
			int count;
			switch(LenOfArray(file,&count))
			{
				case EMPTY:
					printf("File is empty\n");
					fclose(file);
					break;
				case BADINPUT:
					printf("Can't get numbers from file\n");
					fclose(file);
					break;
				case OK:
					printf("Count of numbers=%d",count);
			}

	}
	return 0;
}

int LenOfArray(FILE *file, int *count)
{
	int num;
	switch(fscanf(file, "%f",&num))
	{
		case -1:
			err = EMPTY;
			break;
		case 0:
			err = BADINPUT;
			break;
		case 1:
			err = OK;
			*count += 1;
			while (fscanf(file, "%f", &num) == 1)
				*count += 1;
	}
	return err;
}