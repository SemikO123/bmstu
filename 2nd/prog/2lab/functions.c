#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "errors.h"

int len_of_array(FILE *file, int *count)
{
	int num;
	int error;
	switch(fscanf(file, "%d", &num))
	{
		case -1:
			error = EMPTY;
			break;
		case 0:
			error = BADINPUT;
			break;
		case 1:
			error = OK;
			*count += 1;
			while (fscanf(file, "%d", &num) == 1)
				*count += 1;
	}
	return error;
}

int *array_generate(int *count)
{
	int *array = NULL;
	if (*count)
	{
		array = malloc(*count * sizeof(int));
	}
	return array;

}

int array_filling(int *begin, int *end, FILE *file)
{
	if (begin == end) // никогда не произойдет
	{
		printf("Length of array = 0"); 
		return EMPTY; 
	}
	else
		for (int *current = begin; current < end; current++)
			fscanf(file,"%d", &*current);

		return OK;
}

int counting(int *begin, int *end, int *min)
{
	if (end - begin == 1)
		return ONEELEMENT;
	*min = *(begin) * *(begin + 1);
	//printf("min %d %d\n", *begin, *(begin+1));
	for (int *current = begin + 1; current < end - 1; current++)
	{
		//printf("%d %d\n",*current,*(current+1));
		if (*current * *(current + 1) < *min)
			*min = *current * *(current + 1); 
	}
	return OK;

}