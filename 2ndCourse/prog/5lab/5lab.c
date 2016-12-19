
#include "my_snprintf.h"

/*
%s %o %c
Реализовать собственную версию функции snprintf, обрабатывающую указанные 
спецификаторы типа. При реализации этой функций запрещается использовать 
любые стандартные функции для обработки строк.
int snprintf ( char * s, size_t n, const char * format, ... );
*/

#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define PINK    "\033[1;35m"

int compare(char *str1, char *str2, int n1, int n2)
{
	if (n1 == n2)
	{
		for (int i = 0; i < n1; i++)
			if (str1[i] != str2[i])
				return 0;
		return 1;
	}
	else
		return 0;
}

void print(int n)
{
	if (n == 0)
		printf("%s%25s%s\n", RED, "FAILED", RESET);
	else
		printf("%s%25s%s\n", GREEN, "PASSED", RESET);
}

void test_octal(int num, char *answer, int n, const char *text)
{
	char *a = to_octal(num);
	printf("%15s -> %15s", text, a);
	print(compare(a, answer, n, n));
	free(a);
}

int main(void)
{
	// printf("%s\n", to_octal(100)); //144
	// printf("%s\n", to_octal(10));  //12
	// printf("%s\n", to_octal(900)); //1604
	// printf("%s\n\n", to_octal(90));//132

	char string[25], string1[25];

	printf("%s%15s %25s %25s %25s%s\n",PINK ,"","expected", "received", "TEST", RESET);

	snprintf(string, 4, "%o", 333);
	my_snprintf(string1, 4, "%o", 333);
	printf("%15s %25s %25s ","only octal", string, string1);
	print(compare(string, string1, strlen_f(string), strlen_f(string1)));

	snprintf(string, 4, "%s", "abc");
	my_snprintf(string1, 4, "%s", "abc");
	printf("%15s %25s %25s ","only string", string, string1);
	print(compare(string, string1, strlen_f(string), strlen_f(string1)));	

	snprintf(string, 2, "%c", 's');
	my_snprintf(string1, 2, "%c", 's');
	printf("%15s %25s %25s ","only char", string, string1);
	print(compare(string, string1, strlen_f(string), strlen_f(string1)));

	snprintf(string, 10, "word %s", "ab");
	my_snprintf(string1, 10, "word %s", "ab");
	printf("%15s %25s %25s ","string", string, string1);
	print(compare(string, string1, strlen_f(string), strlen_f(string1)));

	snprintf(string, 13, "str: %s", "very_long_word");
	my_snprintf(string1, 13, "str: %s", "very_long_word");
	printf("%15s %25s %25s ","string (>)", string, string1);
	print(compare(string, string1, strlen_f(string), strlen_f(string1)));

	snprintf(string, 10, "oct: %o", 123);
	my_snprintf(string1, 10, "oct: %o", 123);
	printf("%15s %25s %25s ","octal", string, string1);
	print(compare(string, string1, strlen_f(string), strlen_f(string1)));

	snprintf(string, 10, "oct: %o", 923);
	my_snprintf(string1, 10, "oct: %o", 923);
	printf("%15s %25s %25s ","octal", string, string1);
	print(compare(string, string1, strlen_f(string), strlen_f(string1)));

	snprintf(string, 10, "oct: %o", 923923);
	my_snprintf(string1, 10, "oct: %o", 923923);
	printf("%15s %25s %25s ","octal (>)", string, string1);
	print(compare(string, string1, strlen_f(string), strlen_f(string1)));

	snprintf(string, 10, "char: %c", 's');
	my_snprintf(string1, 10, "char: %c", 's');
	printf("%15s %25s %25s ","symbol", string, string1);
	print(compare(string, string1, strlen_f(string), strlen_f(string1)));

	snprintf(string, 10, "char: %c & oct: %o", 's', 123);
	my_snprintf(string1, 10, "char: %c & oct: %o", 's', 123);
	printf("%15s %25s %25s ","symb & oct (>)", string, string1);
	print(compare(string, string1, strlen_f(string), strlen_f(string1)));

	snprintf(string, 20, "char: %c & oct: %o", 's', 123);
	my_snprintf(string1, 20, "char: %c & oct: %o", 's', 123);
	printf("%15s %25s %25s ","symb & oct", string, string1);
	print(compare(string, string1, strlen_f(string), strlen_f(string1)));

	snprintf(string, 10, "%s & %c","string" , 's');
	my_snprintf(string1, 10, "%s & %c", "string" , 's');
	printf("%15s %25s %25s ","str & symb (>)", string, string1);
	print(compare(string, string1, strlen_f(string), strlen_f(string1)));

	snprintf(string, 20, "%s & %c","string" , 's');
	my_snprintf(string1, 20, "%s & %c", "string" , 's');
	printf("%15s %25s %25s ","str & symb", string, string1);
	print(compare(string, string1, strlen_f(string), strlen_f(string1)));

	snprintf(string, 20, "%s & %c & %o","abc" , 's', 567);
	my_snprintf(string1, 20, "%s & %c & %o","abc" , 's', 567);
	printf("%15s %25s %25s ","str & sym & str", string, string1);
	print(compare(string, string1, strlen_f(string), strlen_f(string1)));

	snprintf(string, 20, "symbols: %c %c %c",'a' , 'b', 'c');
	my_snprintf(string1, 20, "symbols: %c %c %c",'a' , 'b', 'c');
	printf("%15s %25s %25s ","3 symbols", string, string1);
	print(compare(string, string1, strlen_f(string), strlen_f(string1)));

	snprintf(string, 20, "%s str, %s str","first" , "second");
	my_snprintf(string1, 20, "%s str, %s str","first" , "second");
	printf("%15s %25s %25s ","2 strings (>)", string, string1);
	print(compare(string, string1, strlen_f(string), strlen_f(string1)));

	snprintf(string, 20, "%o %o %o" , 1, 111, 11111);
	my_snprintf(string1, 20, "%o %o %o" , 1, 111, 11111);
	printf("%15s %25s %25s ","3 octal num", string, string1);
	print(compare(string, string1, strlen_f(string), strlen_f(string1)));

	snprintf(string, 20, "text only");
	my_snprintf(string1, 20, "text only");
	printf("%15s %25s %25s ","nospecificators", string, string1);
	print(compare(string, string1, strlen_f(string), strlen_f(string1)));

	printf("\n------------------> Test function TO_OCTAL <------------------\n");
	test_octal(10, "12", 3,"10");
	test_octal(100, "144", 4, "100");
	test_octal(90, "132", 4,"90");
	test_octal(900, "1604", 5,"900");
	test_octal(1234, "2322", 5, "1234");
	test_octal(98765, "300715", 7, "98765");

}