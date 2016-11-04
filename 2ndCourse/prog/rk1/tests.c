#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void test(int flag, const char *text)
{
	if (flag)
		printf("%s PASSED\n", text);
	else
		printf("%s FAILED\n", text);
}

void length_test(const char *string, int result, const char *text)
{
	int count = length(string);
	if (count == result)
		test(1, text);
	else
		test(0, text);
}

void get_word_test(const char *string, int begin, const char *result, const char *text)
{
	char *word = get_word(string+begin);
	int flag = 1;
	if (strlen(word) == strlen(result))
	{
		for (int i = 0; i < strlen(word); i++)
			if (word[i] != result[i])
				flag = 0;
	}
	else
		flag = 0;
	test(flag, text);
	free(word);
}

int main(void)
{
	printf(" * TEST FUNCTION 'LENGTH' *\n");
	length_test("abcdef", 6, "Test #1         ");
	length_test("", 0, "Test #2 (empty) ");

	printf("\n * TEST FUNCTION 'GET_WORD' *\n");
	get_word_test("abc def", 0, "abc", "Test #1        ");
	get_word_test("abc defg", 4, "defg", "Test #2        ");
	get_word_test("", 0, "", "Test #3 (empty)");

	printf("\n * TEST FUNCTION ''*\n");

}