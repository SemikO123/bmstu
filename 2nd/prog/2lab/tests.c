#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#include "errors.h"

int main(void)
{
	printf("\n==> TEST FUNCTION 'len_of_array' <==\n");
	FILE *file = fopen("tests/empty.txt", "r");
	len_of_array_test(-1, EMPTY, file, "EMPTY FILE");
	fclose(file);

	file = fopen("tests/badfile.txt", "r");
	len_of_array_test(-1, BADINPUT, file, " BAD FILE ");
	fclose(file);

	file = fopen("tests/4numbers.txt", "r");
	len_of_array_test(4, OK, file, "4 numbers ");
	fclose(file);

	file = fopen("tests/30numbers.txt", "r");
	len_of_array_test(30, OK, file, "30 numbers");
	fclose(file);



	printf("\n==> TEST FUNCTION 'array_filling' <==\n");
	file = fopen("tests/empty.txt", "r");
	int r_arr1[1];
	array_filling_test(r_arr1,0, EMPTY, file, "EMPTY FILE");
	fclose(file);

	file = fopen("tests/badfile.txt", "r");
	array_filling_test(r_arr1, 1, BADINPUT, file, " BAD FILE ");
	fclose(file);

	file = fopen("tests/4numbers.txt", "r");
	int r_arr2[4] = {-1,1,-1,1};
	array_filling_test(r_arr2,4, OK, file, "4 numbers ");
	fclose(file);

	file = fopen("tests/30numbers.txt", "r");
	int r_arr3[30] = {10, -36, 89, -22, 43, 73, 78, 79, -23, -83, 80, 70, -94, 97, 38, -96, -84, 29, 19, -71, 95, -34, 50, 59, 55, -92, -63, -56, 91, -3};
	array_filling_test(r_arr3,30, OK, file, "30 numbers");
	fclose(file);



	printf("\n==> TEST FUNCTION 'counting' <==\n");
	int arr_1[1] = {5};
	counting_test(-1, ONEELEMENT, 1, arr_1, "ONE ELEMENT");

	int arr_2[5] = {4, -20, 3, 20, -1};
	counting_test(-80, OK, 5, arr_2, "    #1     ");

	int arr_3[6] = {-1, -1, 20, 0, -1, -1};
	counting_test(-20, OK, 6, arr_3, "    #2     ");

	int arr_4[4] = {8,6,4,2};
	counting_test(8, OK, 4, arr_4, "    #3     ");



}

void len_of_array_test(int right_count, int right_code, FILE *file, char *string)
{
	int count = 0;
	switch (len_of_array(file, &count))
	{
		case EMPTY:
			if (right_code == EMPTY)
				printf("Test %s passed\n",string);
			else
				printf("Test %s failed\n",string);
			break;
		case BADINPUT:
			if (right_code == BADINPUT)
				printf("Test %s passed\n",string);
			else
				printf("Test %s failed\n",string);
			break;
		case OK:
			if (right_code == OK && count == right_count)
				printf("Test %s passed\n",string);
			else
				printf("Test %s failed\n",string);
			break;
	}
}

void array_filling_test(int *right_array, int count, int right_code, FILE *file, char *string)
{
	int *array;
	array = malloc(count * sizeof(int));
	switch (array_filling(array, array + count, file))
	{
		case EMPTY:
			if (right_code == EMPTY)
				printf("Test %s passed\n",string);
			else
				printf("Test %s failed\n", string);
			break;
		case BADINPUT:
			if (right_code == BADINPUT)
				printf("Test %s passed\n",string);
			else
				printf("Test %s failed\n", string);
			break;
		case OK:
		{
			int flag = 1;
			for (int i = 0; i < count; i++)
				if (array[i] != right_array[i])
					flag = 0;
			if (flag == 1)
				printf("Test %s passed\n", string);
			else
				printf("Test %s failed\n", string);
			break;
		}
	}
	free(array);

}

void counting_test(int right_result, int right_code, int count, int *array, char *string)
{
	int result;
	switch(counting(array, array + count, &result))
	{
		case ONEELEMENT:
			if (right_code == ONEELEMENT)
				printf("Test %s passed\n",string);
			else
				printf("Test %s failed\n", string);
			break;
		case OK:
			if (right_code == OK && result == right_result)
				printf("Test %s passed\n",string);
			else
			{
				printf("Test %s failed\n", string);
				printf("   expectation: %d\n",right_result);
				printf("   reality: %d\n",result);
			}
			break;
	}
}