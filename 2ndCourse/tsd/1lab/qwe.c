#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

int main(void)
{
	char znak_int;
	char znak_float;
	char integer_num[32] = "";
	char float_num[40] = "";
	int integer_number[30] = {0};
	int float_number[30] = {0};
	int exponent = 0;
	char znak_result;
	int flag_point=0;
	int flag_e=0;
	printf("***********************************|---------|---------|---------|\n");
	printf("Целое число (например, -11 22 +33): ");
	if (input_int_numbers(integer_num,&znak_int) == -1)
	{
		printf("Целое число введено неверно\n");
		return -1;
	}
	int count_of_dig_int = 0;
	integer_array_generate(integer_num, integer_number, &count_of_dig_int);
	if (count_of_dig_int > 30)
	{
		printf("Целое число введено неверно\n\n");
		return -1;
	}
	printf("Знак = %c \n",znak_int);
	printf("Число = ");
	for (int i = 0; i < count_of_dig_int; i++)
		printf("%d", integer_number[i]);
	printf("\n\n");
	printf("***************************************************|---------|---------|---------|\n");
	printf("Вещественное число (например +11.2E-5 .112 112.E1): ");
	if (input_float_numbers(float_num,&znak_float,&flag_point ,&flag_e) == -1)
	{
		printf("Вещественное число введено неверно\n");
		return -1;
	}
	int count_of_dig_float = 0;
	float_array_generate(float_num, float_number, &exponent, &count_of_dig_float, &flag_point, &flag_e);
	if (count_of_dig_float > 30)
	{
		printf("Вещественное число введено неверно\n\n");
		return -1;
	}
	printf("Знак = %c \n",znak_float);
	printf("Число = ");
	for (int i = 0; i < count_of_dig_float ;i++)
		printf("%d",float_number[i]);
	printf("\nСтепень = %d\n",exponent);
	
	int result[60] = {0};
	int flag = 0;
	if (count_of_dig_int > count_of_dig_float)
		counting(integer_number, count_of_dig_int, float_number, count_of_dig_float, result, &flag);
	else
		counting(float_number, count_of_dig_float, integer_number, count_of_dig_int, result, &flag);

	if (znak_int == znak_float)
		znak_result = '+';
	else 
		znak_result = '-';

	// printf("[DEBUG INF]Result of counting = ");
	// printf("%c",znak_result);
	// for (int i = 0; i < count_of_dig_int+count_of_dig_float; i++)
	// 	printf("%d",result[i]);
	// printf("E%d",exponent-flag);
	// printf("\n");

	int result_with_pointer[30] = {0};
	normalize(result, result_with_pointer, &exponent, count_of_dig_int+count_of_dig_float, &flag);
	if (exponent >= -99999 && exponent <= 99999)
		print_float(znak_result, result_with_pointer, exponent, count_of_dig_float+count_of_dig_int);
	else
		printf("Ошибка вычисления\n");

}

// ПОЧИНИТЬ ПОРЯДОК ПРИ ОКРУГЛЕНИИ
// ПРОВЕРИТЬ 100 0.01Е-99999 
// ПЕРЕНЕСТИ ВНУТРЕННЮЮ СТРУКТУРУ В ОТЧЕТЕ


