#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

void print_float(char znak, int *mantissa, int exponent, int len_mantissa)
{
	printf("%c0.",znak);
	for (int i=2; i <= len_mantissa; i++)
		printf("%d",mantissa[i]);
	if (exponent >= 0)
		printf("E+%d\n",exponent);
	else
		printf("E%d\n",exponent);
}

void normalize(int *array, int *result, int *exponent, int count)
{
	result[0] = 0;
	result[1] = -1;
	int k = 2;
	int begin;
	if (array[0] == 0)
		begin = 1;
	else
		begin = 0;
	for (int i = begin; i < count; i++)
	{
		if (k < 32)
			result[k] = array[i];
		*exponent += 1;
		k++;
	}
}

void counting(const int *array_first, int first_len, const int *array_second, int second_len, int *result)
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
}


void float_array_generate(const char *array_char, int *array_int, int *exponent, int *counter)
{
	int flag_point=0;
	int flag_e=0;
	for (int i=0; i < strlen(array_char); i++)
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
		char curr[1] = {0};
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
						char exp[5];
						for (int k=0; k < 6; k++)
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
						char exp[5];
						for (int k=0; k < 6; k++)
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
						while (i < strlen(array_char))
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
						while (i < strlen(array_char))
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

int count_of_digits(int number) 
{
    int count = (number == 0) ? 1 : 0;
    while (number != 0) 
    {
        count++;
        number /= 10;
    }
    return count;
}


void integer_array_generate(const char *array_char, int *array_int, int *counter)
{
	char curr[1];
	for (int i = 0; i < strlen(array_char); i++)
	{
		curr[0] = array_char[i];
		array_int[i] = atoi(curr);
		*counter += 1;
	}
}

void input_numbers(char *number, char *znak)
{
	char num[40];
	scanf("%s", num);
	*znak = num[0];
	switch(*znak)
	{
		case '+':
			*znak = '1';
			for (int i = 0; i < sizeof(num)/sizeof(char); i++)
				number[i] = num[i+1];
			break;
		case '-':
			*znak = '0';
			for (int i = 0; i < sizeof(num)/sizeof(char); i++)
				number[i] = num[i+1];
			break;
		default:
			for (int i = 0; i < sizeof(num)/sizeof(char); i++)
				number[i] = num[i];
			*znak = '1';
			break;		
	}
}