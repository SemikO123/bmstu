#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

/*
%s %o %c
Реализовать собственную версию функции snprintf, обрабатывающую указанные 
спецификаторы типа. При реализации этой функций запрещается использовать 
любые стандартные функции для обработки строк.
int snprintf ( char * s, size_t n, const char * format, ... );
*/

#define S 1
#define O 2
#define C 3

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
		n /= 10;
		i++;
	}
	return i;
}


char *to_octal(int num)
{
	int count = length_num(num);
	char *result = malloc(count+1);
	count -= 1;
	while (num != 0)
	{
		char rest = '0' + (num % 8);
		num /= 8;
		result[count--] = rest;
	}
	for (int i = 0; i < count; i++)
		result[i] = 0;
	result[count] = '\0';
	return result;

}

int my_snprintf(char *s, size_t n, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int count;
	int type;
	while (*format)
	{
		if (*format == '%')
		{
			type = get_type(*format);
			switch(type)
			{
				case S:
					char *data = va_arg(args, char*);

					break;
				case O:
					int data1 = va_arg(args, int);
					char *data = to_octal(data1);
					break;
				case C:	
					char data = va_arg(args, char);
					break;
				default:
					printf("Ты че делаешь, ублюдок?\n");
					break;
			}
		}
		else
		{
			s[count++] = *format;
		}
		format++;
	}

	va_end(args);
	return 0;
}

int main(void)
{
	char string[20];
	printf("%d",snprintf(string, 10, "int -> %d;int -> %d", 54, 100));
	printf("%s", string);
}