#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void input_numbers(char *number, char *znak);
void integer_array_generate(const char *integer_num, int *integer_number, int *counter);
void float_array_generate(const char *array_char, int *array_int, int *exponent, int *counter);
int count_of_digits(int number);
void counting(const int *array_int, int int_len, const int *array_float, int float_len, int *result);


int main(void)
{
	char znak_int;
	char znak_float;
	char integer_num[30];
	char float_num[40] = {0};
	int integer_number[30] = {0};
	int float_number[30] = {0};
	int exponent = 0;

	int result[7] = {0};
	int a[3] = {5,6,7};
	int b[4] = {1,2,3,4};
	counting(b,4,a,3,result);
	for (int i = 0; i < 7; i++)
		printf("->%d \n",result[i]); 

	printf("Целое число : ");
	input_numbers(integer_num,&znak_int);
	printf("Знак = %c \nЧисло = %s\n",znak_int,integer_num);
	int count_of_dig_int = 0;
	integer_array_generate(integer_num, integer_number, &count_of_dig_int);
	printf("\n");

	printf("Вещественное число : ");
	input_numbers(float_num,&znak_float);
	//printf("float = %s\n",float_num);
	int count_of_dig_float = 0;
	float_array_generate(float_num, float_number, &exponent, &count_of_dig_float);
	if (exponent >= -99999)
	{
		printf("Знак = %c \n",znak_float);
		printf("Число = ");
		for (int i = 0; i < count_of_dig_float ;i++)
			printf("%d",float_number[i]);
		printf("\nСтепень = %d\n",exponent);
		// for (int i = 0; i < count_of_dig_float; i++)
		// 	printf("array_int[%d]=%d\n",i,float_number[i]);
	}
	else
		printf("Ошибка вычисления");

	printf("IntLen = %d, FloatLen = %d\n",count_of_dig_int, count_of_dig_float);
}

void counting(const int *array_int, int int_len, const int *array_float, int float_len, int *result)
{
	// первое число больше второго ( int > float)
	int pointer;
	for (int i = float_len-1; i >= 0; i--)
	{
		pointer = 0;
		for (int j = int_len-1; j >= 0; j--)
		{
			printf("i=%d j=%d, i+j+1=%d\n",i,j,i+j+1);
			result[i+j+1] += pointer + array_float[i]*array_int[j];
			pointer = result[i+j+1] / 10;
			result[i+j+1] %= 10;
			printf("pointer=%d, result[i+j+1]=%d\n",pointer,result[i+j+1]);	
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
			for (int i=0; i < sizeof(num)/sizeof(char); i++)
				number[i] = num[i+1];
			break;
		case '-':
			*znak = '0';
			for (int i=0; i < sizeof(num)/sizeof(char); i++)
				number[i] = num[i+1];
			break;
		default:
			for (int i=0; i < sizeof(num)/sizeof(char); i++)
				number[i] = num[i];
			*znak = '1';
			break;		
	}
}