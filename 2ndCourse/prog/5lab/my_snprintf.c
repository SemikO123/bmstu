#include "my_snprintf.h"

int get_type(char specificator)
{
	if (specificator == 's')
		return S;
	if (specificator == 'o')
		return O;
	if (specificator == 'c')
		return C;
	return 0;
}

int length_num(int n)
{
	int i = 0;
	while (n != 0)
	{
		n /= 8;
		i++;
	}
	return i;
}


char *to_octal(unsigned int num)
{
	int count = length_num(num);
	// char *result = malloc(count+2);
	char *result = malloc(count+1);
	int i = 0;
	while (num != 0)
	{
		char rest = '0' + (num % 8);
		num /= 8;
		result[i++] = rest;
	}
	for (int j = 0; j < i/2; j++)
	{
		char tmp = result[j];
		result[j] = result[i-j-1];
		result[i-j-1] = tmp; 
	}
	if (i == count)
		result[count] = '\0';
	// else
	// 	result[count+1] = '\0';
	return result;

}

int strlen_f(const char *string)
{
	int i = 0;
	while (string[i] != '\0')
		i++;
		return i;	
}

// char *strtochr(char ch, char *string)
// {
// 	string[0] = ch;
// 	string[1] = '\0';
// 	return string;
// }



int my_snprintf(char *s, size_t n, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int count = 0;
	int type;
	int flag = 1;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			//printf("->%c\n", *format);
			char *data;
			type = get_type(*format);
			switch(type)
			{
				case S:
				{
					data = va_arg(args, char*);
					int string_length = strlen_f(data);
					for (int i = 0; i < string_length; i++)
					{
						if (count < n-1)
							s[count++] = data[i];
						else
						{
							flag = 0;
							count++;	
						}
					}
					break;
				}
				case O:
				{
					unsigned int data1 = va_arg(args, unsigned int);
					data = to_octal(data1);
					int string_length = strlen_f(data);
					for (int i = 0; i < string_length; i++)
					{
						if (count < n-1)
							s[count++] = data[i];	
						else
						{
							flag = 0;
							count++;
						}
					}
					free(data);
					break;
				}
				case C:
				{	
					char data2 = va_arg(args, int);
					if (count < n -1)
					{
						s[count++] = data2;
					}
					else
					{
						flag = 0;
						count++;
					}
					break;
				}
				// default:
				// 	s[count++] = '%';
				// 	s[count++] = *format;
				// 	break;
			}
		}
		else
		{
			if (count < n-1)
				s[count++] = *format;
			else
			{
				flag = 0;
				count++;
			}
		}
		format++;
	}
	//printf("ENDcount=%d\n", count);
	if (flag == 1)
		s[count] = '\0';
	else
		s[n-1] = '\0';

	va_end(args);
	return count;
}