#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

void print_float(char znak, int *mantissa, int exponent, int len_mantissa)
{
	printf("\nРезультат умножения : ");
	int flag_null = 0;
	for (int i = 0; i < 30; i++)
		if (mantissa[i] != 0)
			flag_null = 1;
	
	if (flag_null == 1) 
	{
		printf("%c0.",znak);
		// ограничение вывода мантиссы до 30 чисел (на всякий случай)
		if (len_mantissa >= 30) 
			len_mantissa = 29;
		// [DEBUG] печать результата с незначащими нулями
		// for (int i = 0; i <= len_mantissa; i++)
		// 	printf("%d",mantissa[i]);
		// printf("\n");
		int null_mant = 0;
		// считает незначащие нули в конце
		for (int i = len_mantissa; i > 0; i--)
			if (mantissa[i] == 0)
				null_mant += 1; 
			else
				break;
		// printf("[DEBUG] незначащих нулей %d\n",null_mant);
		// печатает без незначащих нулей в конце
		int count = 0;
		for (int i=0; i <= len_mantissa-null_mant; i++)
		{
			if (count != 3)
			{
				printf("%d",mantissa[i]);
			}
			else
			{
				printf("'");
				printf("%d",mantissa[i]);
				count = 0;
			}
			count += 1;
		}
		if (exponent >= 0)
			printf("E+%d\n",exponent);
		else
			printf("E%d\n",exponent);
	}
	else 
		printf("0\n");
}

void rounding(int *array)
{
	int result[31] = {0};
	int pointer = 1;
	for (int i=30; i > 0; i--)
	{
		result[i] = (pointer + array[i-1]) % 10;
		pointer = (pointer + array[i-1]) / 10;
	}
	result[0] = pointer;
	//переприсваивание элементов полученного в функцию массива
	for (int i = 0; i < 31; i++)
		array[i] = result[i];
}

void normalize(int *array, int *result, int *exponent, int count, int *flag)
{
	int k = 0;
	int begin;
	*exponent -= *flag;
	// убирает незначащий ноль в начале (при наличии)
	if (array[0] == 0)
		begin = 1;
	else
		begin = 0;
	int last;
	if (count > 30)
	{
		// last - число, относительно которого рассматривается округление
		last = array[30];
		printf("[DEBUG INF]last = %d\n",last);
		// округление и перезапись округленной мантиссы
		if (last >= 5)
		{
			rounding(array);
			if (array[0] == 0)
				for (int i = 1; i < 31; i++)
				{	
					result[i-1] = array[i];
					*exponent += 1;
				}
			else
			{
				*exponent += 1;
				for (int i = 0; i < 30; i++)
				{
					result[i] = array[i];
					*exponent += 1;
				}
			}

		}
		// last < 5. обычная перезапись мантиссы без возможного 0 в начале
		else
		{
			while (k < 30)
			{
				result[k] = array[begin];
				begin++;
				k++;
				*exponent += 1;
			}
		}
	}
	// длина меньше 30
	else
	{
		for (int i = begin; i < count; i++)
		{
			if (k < 30)
				result[k] = array[i];
			*exponent += 1;
			k++;
		}
	}
}

void counting(const int *array_first, int first_len, const int *array_second, int second_len, int *result, int *flag)
{
	// первое число больше второго (  > float)
	int pointer;
	for (int i = second_len-1; i >= 0; i--)
	{
		pointer = 0;
		for (int j = first_len-1; j >= 0; j--)
		{
			result[i+j+1] += pointer + array_second[i]*array_first[j];
			pointer = result[i+j+1] / 10;
			result[i+j+1] %= 10;	
		}
		result[i] += pointer;
	}	
	// удаление нуля в начале, если он есть и flag = 1
	if (result[0] == 0)
	{
		for (int i = 1; i < first_len+second_len; i++)
			result[i-1] = result[i];
		result[first_len+second_len-1] = 0;
		*flag = 1;
	}
	printf("\n");


}


void float_array_generate(const char *array_char, int *array_int, int *exponent, int *counter)
{
	int flag_point=0;
	int flag_e=0;
	// подсчет количества встречающихся точек и Е
	for (int i=0; array_char[i] != '\0'; i++)
	{
		if (array_char[i] == '.')
			flag_point += 1;
		if (array_char[i] == 'E')
			flag_e += 1;
	}
	if (flag_e > 1 || flag_point > 1)
		printf("Числа введены неверно");
	else
	{
		char curr[2] = {'0','\0'};
		switch (flag_e)
		{
			case 1:
				switch (flag_point)
				{
					case 1: // есть E есть .
					{
						int i = 0;
						int flag = 0;
						int expon = 0;
						while (array_char[i] != 'E')
						{
							if (array_char[i] != '.')
								if (flag == 0)
								{
									curr[0] = array_char[i];
									array_int[*counter] = atoi(curr);
									*counter += 1;
								}
								else
								{
									curr[0] = array_char[i];
									array_int[*counter] = atoi(curr);
									*counter += 1;
									expon += 1;
								}
							else
								flag = 1;
							i++;
						}
						i++;
						char exp[6] = "";
						for (int k=0; array_char[i] != '\0'; k++)
						{
							exp[k] = array_char[i];
							i++;
						}
						*exponent = atoi(exp);
						*exponent -= expon;
						break;
					}
					case 0: // есть Е нет .
					{
						int i = 0;
						while (array_char[i] != 'E')
						{
							curr[0] = array_char[i];
							array_int[*counter] = atoi(curr);
							*counter += 1;
							i++;
						}
						i++;
						char exp[6] = "";
						for (int k=0; array_char[i] != '\0'; k++)
						{
							exp[k] = array_char[i];
							i++;
						}
						*exponent = atoi(exp);
						break;
					}
				}
				break;	
			case 0:
				switch (flag_point)
				{
					case 1: // нет E есть .
					{	
						int flag = 0;
						int i=0;
						while (array_char[i] != '\0')
						{
							if (array_char[i] != '.')
									if (flag == 0)
									{
										curr[0] = array_char[i];
										array_int[*counter] = atoi(curr);
										*counter += 1;
									}
									else
									{
										curr[0] = array_char[i];
										array_int[*counter] = atoi(curr);
										*counter += 1;
										*exponent -= 1;
									}
							else
								flag = 1;
							i++;
						}
						break;	
					}
					case 0:	// нет E нет .
					{
						int i = 0;
						while (array_char[i] != '\0')
						{
							curr[0] = array_char[i];
							array_int[*counter] = atoi(curr);
							*counter += 1;
							i++;
						}
						*exponent = 0;
						break;
					}
				}	
				break;
		}
	}
}

void integer_array_generate(const char *array_char, int *array_int, int *counter)
{
	char curr[2] = {'0','\0'};
	for (int i = 0; array_char[i] != '\0'; i++)
	{
		curr[0] = array_char[i];
		array_int[i] = atoi(curr);
		*counter += 1;
	}
}

void input_numbers(char *number, char *znak)
{
	char num[40];
	scanf("%39s", num);
	*znak = num[0];
	switch(*znak)
	{
		case '+':
			*znak = '1';
			for (int i = 0; num[i+1] != '\0'; i++)
				number[i] = num[i+1];
			break;
		case '-':
			*znak = '0';
			for (int i = 0; num[i+1] != '\0'; i++)
				number[i] = num[i+1];
			break;
		default:
			for (int i = 0; num[i] != '\0'; i++)
				number[i] = num[i];
			*znak = '1';
			break;		
	}
}