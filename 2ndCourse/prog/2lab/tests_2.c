#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include <math.h>

#define RESET   "\033[0m"
#define GRAY     "\033[1;30m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"

struct addr
{
	char name[10];
	char street[15];
	int house;
};

void test(int flag, const char *text)
{
	if (flag == 0)
		printf("TEST %s %sFAILED%s\n", text, RED, RESET);
	else
		printf("TEST %s %sPASSED%s\n", text, GREEN, RESET);
}
//*********************************************************//
//                      comporators                        //
int compare_chr(const void *a, const void *b)
{
	const char *x = a;
	const char *y = b;
	return *x-*y;
}


int compare_struct(const void *a, const void *b)
{
	const struct addr *x = a;
	const struct addr *y = b;
	//printf("-> %d -> %d \n", x->house, y->house);
	return x->house - y->house;
}
//**********************************************************//

int compare_arrays(int *array1, int *array2, int count)
{
	for (int i = 0; i < count; i++)
		if (array1[i] != array2[i])
			return 0;
	return 1;
}

void test_filter(int *array, int count_in_array, int *right_result, int right_count, const char *text)
{
	int new_count = 0;
	int err_code = 0;
	int *result = filter_array(array, array+count_in_array, &new_count, &err_code);
	if (new_count == right_count)
	{
		if (new_count == 0)
			test(1, text);
		else
			test(compare_arrays(result, right_result, new_count), text);
	}
	else
		test(0, text);
}


int main(void)
{
	printf("--------> Test for filter-function <--------\n");
	{
		int arr[8] = {-1, 5, -5, 4, 8, -2, 11, 7};
		int res[3] = {4, 8, -2};
		test_filter(arr, 8, res, 3,"#1 situation ..MIN..MAX..      ");
	}	
	{
		int arr[9] = {33, 61, 100, 5, 7, 11, 0, 45, 11};
		int res[3] = {5, 7, 11};
		test_filter(arr, 9, res, 3,"#2 situation ..MAX..MIN..      ");
	}	
	{
		int arr[6] = {0, 1, 2, 3, 4, 5};
		int res[4] = {1, 2, 3, 4};
		test_filter(arr, 6, res, 4,"#3 situation   MIN..MAX        ");
	}
	{
		int arr[7] = {7, 6, 5, 4, 3, 2, 1};
		int res[5] = {6, 5, 4, 3, 2};
		test_filter(arr, 7, res, 5,"#4 situation   MAX..MIN        ");
	}
	{
		int arr[4] = {10, 5, 15, 10};
		int res[1] = {0}; // не будет использоваться
		test_filter(arr, 4, res, 0,"#5 situation ..MINMAX..        ");
	}
	{
		int arr[6] = {5,4,8,2,5,6};
		int res[1] = {0}; // не будет использоваться
		test_filter(arr, 6, res, 0,"#6 situation ..MAXMIN..        ");
	}
	{
		int arr[6] = {5,4,5,2,1,3};
		int res[3] = {4,5,2}; 
		test_filter(arr, 6, res, 3,"#7 situation ..MAX.MAX..MIN..  ");
	}
	{
		int arr[8] = {5, 0, 4, 3, 0, 5, 8, 9};
		int res[5] = {4, 3, 0, 5, 8}; 
		test_filter(arr, 8, res, 5,"#8 situation ..MAX.MAX..MIN..  ");
	}


	printf("\n---------> Test for sort-function <---------\n");
	{
		int arr[5] = {5,3,4,2,6};
		int res[5] = {2,3,4,5,6};
		my_sort(arr, 5, sizeof(int), compare_int);
		test(compare_arrays(arr, res, 5), "#1 int: no repetitive elements ");
	}
	{
		int arr[6] = {4,2,4,2,3,3};
		int res[6] = {2,2,3,3,4,4,};
		my_sort(arr, 6, sizeof(int), compare_int);
		test(compare_arrays(arr, res, 6), "#2 int: repetitive elements    ");
	}
	{
		int arr[6] = {-1,-2,-3,4,5,6};
		int res[6] = {-3,-2,-1,4,5,6};
		my_sort(arr, 6, sizeof(int), compare_int);
		test(compare_arrays(arr, res, 6), "#3 int: poz+ and neg- elements ");
	}
	{
		int arr[5] = {1,1,1,1,1};
		my_sort(arr, 6, sizeof(int), compare_int);
		test(compare_arrays(arr, arr, 6), "#4 int: same elements          ");
	}
	{
		char arr[6] = {'b','k','s','t','a','u'};
		char res[6] = {'a','b','k','s','t','u'};
		my_sort(arr, 6, sizeof(char), compare_chr);
		int flag = 1;
		for (int i = 0; i < 6; i++)
			if (arr[i] != res[i])
				flag = 0;
		test(flag, "#5 char: usual situation       ");
	}
	{
		struct addr arr[5] = 
		{
			{"Tom", "Grant Ave", 5},
			{"Mary","Aviation St", 7},
			{"Bett","Knob Hill",2},
			{"John","Ripley Ave",11},
			{"Frank","Palos Verdes",6}
		};
		struct addr res[5] = 
		{
			{"Bett","Knob Hill",2},
			{"Tom", "Grant Ave", 5},
			{"Frank","Palos Verdes",6},
			{"Mary","Aviation St", 7},
			{"John","Ripley Ave",11}
		};
		my_sort(arr, 5, sizeof(struct addr), compare_struct);
		int flag = 1;
		for (int i = 0; i < 5; i++)
			if (res[i].house != arr[i].house)
				flag = 0;
		test(flag, "#6 structure: usual situation  ");
		}

}