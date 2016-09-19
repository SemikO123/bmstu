#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 30

void input_numbers(char *number, char *znak);
int float_update(char *float_num, char *float_number, int *exponent);


int main(void)
{
	char integer_number[N+1];
	char znak_int;
	char float_num[2*N+9];
	char float_number[N+2];
	char znak_float;
	int exponent = 0;

	printf("Целое число : ");
	input_numbers(integer_number,&znak_int);
	printf("ZNAK=%c INT=%s\n",znak_int,integer_number);	
	
	printf("Вещественное число : ");
	input_numbers(float_num,&znak_float);
	//printf("ZNAK=%c FLOAT=%s\n",znak_float,float_num);

	if (float_update(float_num,float_number,&exponent) == -1)
	{
		printf("Числа введены неправильно\n");
	}
	else
		printf("ZNAK=%c MANTISSA=%s EXPONENT=%d\n",znak_float,float_number,exponent);



}

void input_numbers(char *number, char *znak)
{
	char num[2*N+9];
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

int float_update(char *float_num, char *float_number, int *exponent)
{
	int flag_point=0;
	int flag_e=0;
	char float_numberr[2*N+1];
	for (int i=0; i < N+12; i++)
	{
		if (float_num[i] == '.')
			flag_point += 1;
		if (float_num[i] == 'E')
			flag_e += 1;
	}
	if (flag_e > 1 || flag_point > 1)
		return -1;
	char exp[6];
	switch(flag_e)
	{
		case 1:
			switch(flag_point)
			{
				case 1:
				{
					int i = 0;
					while (float_num[i] != 'E') 
					{
						float_numberr[i] = float_num[i];
						i++;
					}
					//printf("float number = %s\n",float_numberr);
					i++;
					for (int k=0; k < 6; k++)
					{
						exp[k] = float_num[i];
						i++;
					}
					*exponent = atoi(exp);
					//printf("exp = %d\n",*exponent);
					i = 0;
					while (float_numberr[i] != '.')
						i++;
					char t;
					for (int k = i; k > 0;k--)
					{
						t = float_numberr[k];
						float_numberr[k] = float_numberr[k-1];
						float_numberr[k-1] = t;
						*exponent += 1;
					}
					for (int i=0; i < strlen(float_numberr)-1; i++)
						if (float_numberr[i] == '.' && float_numberr[i+1] == '0')
						{
							t = float_numberr[i];
							float_numberr[i] = float_numberr[i+1];
							float_numberr[i+1] = t;
							*exponent -= 1;
						}
					switch(float_numberr[0])
					{
						case '0':
						{
							int i=0;
							while (float_numberr[i] == '0' && float_numberr[i+1] != '.')
								++i;
							int k = 0;
							for (; i < strlen(float_numberr); i++)
							{
								float_number[k] = float_numberr[i];
								k++;
							}
							break;
						}
						case '.':
						{
							int k = 1;
							float_number[0] = '0';
							for (int i=0; i < strlen(float_numberr); i++)
							{
								float_number[k] = float_numberr[i];
								k++;
							}
							break;
						}
					}
					//printf("float number = %s\n",float_number);
					//printf("exp = %d\n",*exponent);
					break;
				}
				case 0:
				{
					int i = 0;
					while (float_num[i] != 'E') 
					{
						float_numberr[i] = float_num[i];
						i++;
					}
					//printf("float number = %s\n",float_numberr);
					i++;
					for (int k=0; k < 6; k++)
					{
						exp[k] = float_num[i];
						i++;
					}
					*exponent = atoi(exp);
					//printf("exp = %d\n",*exponent);
					i = 0;

					float_number[0] = '0';
					float_number[1] = '.';
					int k = 2;
					for (int i=0; i < strlen(float_numberr); i++)
					{
						float_number[k] = float_numberr[i];
						k++;
						*exponent += 1;
					}
					break;
				}
			}
			break;
		case 0:
			switch(flag_point)
			{
				case 1:
				{

					int i = 0;
					while (float_num[i] != '.')
						i++;
					char t;
					for (int k = i; k > 0;k--)
					{
						t = float_num[k];
						float_num[k] = float_num[k-1];
						float_num[k-1] = t;
						*exponent += 1;
					}
					for (int i=0; i < strlen(float_num)-1; i++)
						if (float_num[i] == '.' && float_num[i+1] == '0')
						{
							t = float_num[i];
							float_num[i] = float_num[i+1];
							float_num[i+1] = t;
							*exponent -= 1;
						}
					switch(float_num[0])
					{
						case '0':
						{
							int i=0;
							while (float_num[i] == '0' && float_num[i+1] != '.')
								++i;
							int k = 0;
							for (; i < strlen(float_num); i++)
							{
								float_number[k] = float_num[i];
								k++;
							}
							break;
						}
						case '.':
						{
							int k = 1;
							float_number[0] = '0';
							for (int i=0; i < strlen(float_num); i++)
							{
								float_number[k] = float_num[i];
								k++;
							}
							break;
						}
					}
					//printf("float number = %s\n",float_number);
					//printf("exp = %d\n",*exponent);
					break;
				}

				case 0:
				{
					float_number[0] = '0';
					float_number[1] = '.';
					int k = 2;
					for (int i=0; i < strlen(float_num); i++)
					{
						float_number[k] = float_num[i];
						k++;
						*exponent += 1;
					}
					break;
				}
			}
			break;

	}

	return 0;
}

// void rounding()





