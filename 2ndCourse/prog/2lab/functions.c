#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "errors.h"


int array_generate(FILE *file, int *count, int **array)
{
	int error_code;
	int count_of_numbers = 0;
	switch (len_of_array(file, &count_of_numbers))
	{
		case EMPTY:
			//printf("\nFile is empty\n");
			fclose(file);
			error_code = EMPTY;
			break;
		case BADINPUT:
			//printf("\nCan't get numbers from file\n");
			fclose(file);
			error_code = BADINPUT;
			break;
		case OK:
			//printf("\nCount of numbers = %d\n", count_of_numbers);
			rewind(file);
			if (count)
			{
				*array = malloc(count_of_numbers * sizeof(int));
				if (*array)
					error_code = array_filling(*array, *array + count_of_numbers, file);
				else
					error_code = MEMORYPROBLEM;
			}
			*count = count_of_numbers;
			fclose(file);
	}
	return error_code;
}

/**
* @function len_of_array
* This function counts length of array and allocates the memory
* @param[in] file file with numbers
* @param[out] count count of numbers in file
* @param[out] array array without numbers (for allocating memory)
* @return error code of error 
*/
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

/**
* @function array_filling
* This function puts numbers from file to array
* @param[in] first element's pointer
* @param[in] end after last elem/ent's pointer
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

void minmax_search(int *begin, int *end, int **min, int **max)
{
	*min = begin;
	*max = begin;
	for (int *curr = begin; curr < end; curr++)
	{
		if (*curr < **min)
			*min = curr;
		if (*curr > **max)
			*max = curr;
	}
}


int *filter_array(int *begin, int *end, int *count, int *out_error)
{
	int *min, *max;
	minmax_search(begin, end, &min, &max);
	if (abs(max-min) > 1)
	{
		int *left, *right;
		if (max > min)
		{
			left = min;
			right = max;
		}
		else
		{
			left = max;
			right = min;
		}
		left++;
		*count = right-left;
		int *new_array = malloc(*count*sizeof(int));
		if (new_array)
		{
			int i = 0;
			for (int *curr = left; curr < right; curr++)
				*(new_array + i++) = *curr;
		}
		else
			*out_error = MEMORYPROBLEM;
		*out_error = OK;
		return new_array;
	}
	else
	{
		*count = 0;
		return NULL;
	}
}

void print_array(int *array, int count)
{
	for (int i = 0; i < count; i++)
		printf("%d ", *(array+i));
}


int compare_int(const void *a, const void *b)
{
	const int *x = a;
	const int *y = b;
	return *x-*y;
}

void swap(void *a, void *b, size_t size)
{
	char *x = a;
	char *y = b;
	for (int i = 0; i < size; i++)
	{
		char tmp = *x;
		*(x++) = *y;
		*(y++) = tmp;
	}
}

void my_sort(void *base, size_t num, size_t size, compare_t compare)
{
	char *left = base;
	char *right = (char *)base + size*(num-1);
	int flag = 1;
	while (left < right && flag == 1)
	{
		flag = 0;
		for (char *i = left; i < right; i += size)
		{
			if(compare(i, i + size) > 0)
			{
				swap(i, i + size, size);
				flag = 1;
			}
		}
		right -= size;
		for (char *i = right; i > left; i -= size)
		{
			if (compare(i - size, i) > 0)
			{
				swap(i - size, i, size);
				flag = 1;
			}
		}
		left += size;
	}
}

void print_to_file(FILE *file, int *array, int count)
{
	for (int i = 0; i < count; i++)
		fprintf(file, "%d ", *(array+i));
}
