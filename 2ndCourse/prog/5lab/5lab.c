#include <stdio.h>
#include <stdarg.h>

/*
%s %o %c
Реализовать собственную версию функции snprintf, обрабатывающую указанные 
спецификаторы типа. При реализации этой функций запрещается использовать 
любые стандартные функции для обработки строк.
int snprintf ( char * s, size_t n, const char * format, ... );
*/


int my_snprintf(char *s, size_t n, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int count;

	while (*format)
	{
		if (*format == '%')
		{
			get_type();
			va_arg(args, );
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
	snprintf(string, 10, "int %d %d", 54, 100);
	printf("%s", string);
}