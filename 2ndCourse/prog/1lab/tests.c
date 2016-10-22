#include <stdio.h>
#include <stdio.h>
#include "errors.h"
#include "functions.h"


int main(int argc, char **argv)
{
	FILE *f1; 
	f1 = fopen("test1.txt", "w");
	printf("\nFUNCTIONS 'read_array' and 'array_to_file'\n");
	printf("№                                 Test\n");
	float array1[5] = { -5,6.5,1,0,11.222 };
	float newarr[NT];
	int count = 0;
	int cnt = 5;
	array_to_file(array1, &cnt, f1);
	fclose(f1);
	f1 = fopen("test1.txt", "r");
	read_array(newarr, NT, f1, &count);
	int flag = 0;
	for (int i = 0; i < count;i++)
		if (array1[i] == newarr[i])
			flag = 1;
		else
		{
			flag = 0;
			break;
		}
	if (flag == 1)
		printf("1.                                PASSED\n");
	else
		printf("1.                                FAILED\n");
	fclose(f1);

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

	printf("\nFUNCTION 'new_array_generate'\n");
	printf("№                                 Test\n");
	float in_arr[5] = { -1,2,3,-4,5 };
	float test_avrg = 1.0;
	float out_arr_good[3] = { 2,3,5 };
	float out_arr[NT];
	int cnt_out_arr = 0;
	new_array_generate(in_arr, 5, test_avrg, out_arr, &cnt_out_arr);
	flag = 0;
	for (int j = 0; j < 3; j++)
	{
		if (out_arr[j] == out_arr_good[j])
			flag = 1;
		else
		{
			flag = 0;
			break;
		}
	}
	if (flag == 1)
		printf("1.                                PASSED\n");
	else
		printf("1.                                FAILED\n");

	float in_arr1[6] = { 2.345,2.456,-1.12,-3.666,2.28,12.22 };
	float test_avrg1 = 2.419166667;
	float out_arr_good1[2] = { 2.456,12.22 };
	float out_arr1[NT];
	int cnt_out_arr1 = 0;
	new_array_generate(in_arr1, 6, test_avrg1, out_arr1, &cnt_out_arr1);
	flag = 0;
	for (int j = 0; j < 2; j++)
	{
		if (out_arr1[j] == out_arr_good1[j])
			flag = 1;
		else
		{
			flag = 0;
			break;
		}
	}
	if (flag == 1)
		printf("2.                                PASSED\n");
	else
		printf("2.                                FAILED\n");

	float in_arr2[6] = { 1,2,3,4,5,6};
	float test_avrg2 = 0;
	float out_arr_good2[6] = {1,2,3,4,5,6};
	float out_arr2[NT];
	int cnt_out_arr2 = 0;
	new_array_generate(in_arr2, 6, test_avrg2, out_arr2, &cnt_out_arr2);
	flag = 0;
	for (int j = 0; j < 6; j++)
	{
		if (out_arr2[j] == out_arr_good2[j])
			flag = 1;
		else
		{
			flag = 0;
			break;
		}
	}
	if (flag == 1)
		printf("3.равен исходному                 PASSED\n");
	else
		printf("3.равен исходному                 FAILED\n");


	float in_arr3[6] = { 1,2,3,4,5,6};
	float test_avrg3 = 7;
	int cnt_out_arr3_good = 0;
	float out_arr3[NT];
	int cnt_out_arr3 = 0;
	new_array_generate(in_arr3, 6, test_avrg3, out_arr3, &cnt_out_arr3);
	if (cnt_out_arr3 == cnt_out_arr3_good)
		printf("4.пустой массив                   PASSED\n");
	else
		printf("4.пустой массив                   FAILED\n");



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

	float avrg;
	float eps = 1e-10;
	printf("\nFUNCTION 'count_average'\n");
	printf("№  Obtained         Expected      Test\n");
	float res = 0;
	float arr1[6] = { -3.3,-2.2,-1.1,1.1,2.2,3.3 };
	count_average(arr1, 6, &avrg);
	if ((-eps < res - avrg) & (res - avrg < eps))
		printf("1.  %.2f              %.2f        PASSED\n", avrg, res);
	else
		printf("1.  %.2f              %.2f        FAILED\n", avrg, res);

	res = 0.1;
	float arr2[10] = { 8,7,6,8,4,-6,-4,-5,-6,-11 };
	count_average(arr2, 10, &avrg);
	if ((-eps < res - avrg) & (res - avrg < eps)) // КОСТЫЛЬ :((
		printf("2.  %.2f              %.2f        PASSED\n", avrg, res);
	else
		printf("2.  %.2f              %.2f        FAILED\n", avrg, res);
}