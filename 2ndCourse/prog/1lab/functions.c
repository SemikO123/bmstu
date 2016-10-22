#include <stdio.h>
#include <assert.h>
#include "errors.h"
#include "functions.h"


/**
 * @function read_array
 * This function reads numbers from file and puts it to array
 * @param[in] arr array of numbers from file
 * @param[in] n max count of numbers
 * @param[in] file file with numbers 
 * @param[out] count real count of numbers in array
 * @return priznak error code 
 */
int read_array(float arr[], int n, FILE *file, int *count)
{
	int priznak;
	float num;
	switch (fscanf(file, "%f", &arr[*count]))
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
			while ((*count < n) && (fscanf(file, "%f", &arr[*count]) == 1))
				*count += 1;
			if ((fscanf(file, "%f", &num) == 1) && (*count == n))
				priznak = EXCESS;
			// assert(*count > 0);

			
	//printf("N=%d\n",*count);
	}
	return priznak;
}

/**
* @function count_average
* This function counts average of numbers in array
* @param[in] arr array with numbers
* @param[in] n count of numbers in array
* @param[out] avrg average of numbers
*/
void count_average(const float arr[], int n, float *avrg)
{
	assert( n > 0);
	int i;
	float sum = 0;
	for (i = 0; i < n; i++)
		sum += arr[i];
	*avrg = sum / n;
}

/**
* function new_array_generate
* This function generates new array with numbers from 1st array
* @param[in] arr array with numbers
* @param[in] n count of numbers in array
* @param[in] avrg average of numbers
* @param[out] newarr new array with numbers from 1st array
* @param[out] j count of numbers in new array
*/
void new_array_generate(const float *arr, int n, float avrg, float *newarr, int *j)
{
	*j = 0;
	for (int i = 0;i < n;i++)
		if (arr[i] > avrg)
		{
			newarr[*j] = arr[i];
			*j += 1;
		}
}

/**
* @function array_to_file
* This function puts numbers from new array to new file
* @param[in] newarr array with numbers
* @param[in] j count of numbers in array
* @param[out] file file with numbers
*/
void array_to_file(const float *newarr, int *j, FILE *file)
{
	for (int i = 0; i < *j; i++)
	{
		fprintf(file, "%.3f \n", newarr[i]);
	}
}

