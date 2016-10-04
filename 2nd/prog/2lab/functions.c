#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "errors.h"


/**
* @function len_of_array
* This function counts length of array and allocates the memory
* @param[in] file file with numbers
* @param[out] count count of numbers in file
* @param[out] array array without numbers (for allocating memory)
* @return error code of error 
*/
int len_of_array(FILE *file, int *count, int **array)
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
			if (*count)
			{
				*array = malloc(*count * sizeof(int));
				if (*array)
					error = OK;
				else
					error = MEMORYPROBLEM;
			}
	}
	return error;
}

/**
* @function array_filling
* This function puts numbers from file to array
* @param[in] first element's pointer
* @param[in] end after last element's pointer
* @param[in] file file with numbers
* @return code of error
*/
int array_filling(int *begin, int *end, FILE *file)
{
	if (begin == end)
	{
		//printf("Length of array = 0 "); 
		return EMPTY; 
	}
	else
	{
		int tmp;
		for (int *current = begin; current < end; current++)
			if (fscanf(file, "%d", &tmp) == 1)
				*current = tmp;
			else
				return BADINPUT;
			//fscanf(file,"%d", current);
	}
	return OK;
}


/**
* @function counting
* This function searches min(x[0]*x[1],x[1]*x[2],x[2]*x[3],...
* @param[in] first element's pointer
* @param[in] end after last element's pointer
* @param[out] min minimum value (result)
* @return code of error
*/
int counting(int *begin, int *end, int *min)
{
	if (end - begin == 1)
		return ONEELEMENT;
	int *curr_prev = begin;
	int *curr_next = begin + 1;
	*min = *(curr_prev) * *(curr_next);
	//printf("1 = %d, 2 = %d \n", *curr_prev, *curr_next);
	while (curr_next < end - 1)
	{
		curr_prev = curr_next;
		curr_next = curr_prev + 1;
		//printf("1 = %d, 2 = %d \n", *curr_prev, *curr_next);
		if (*(curr_prev) * *(curr_next) < *min)
			*min = *(curr_prev) * *(curr_next);
	}
	return OK;

}