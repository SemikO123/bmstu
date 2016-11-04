#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(void)
{
	printf(" * TEST FUNCTION 'LENGTH' *\n");
	length_test("abcdef", 6, "Test #1         ");
	length_test("", 0, "Test #2 (empty) ");

	printf("\n * TEST FUNCTION 'GET_WORD' *\n");
	get_word_test("abc def", 0, "abc", "Test #1        ");
	get_word_test("abc defg", 4, "defg", "Test #2        ");
	get_word_test("", 0, "", "Test #3 (empty)");

	printf("\n * TEST FUNCTION 'TAKE_WORDS' *\n");
	FILE *file = fopen("t1.txt", "r");
	take_words_test("abc bcd cde ",3, "Test #1        " , file);
	fclose(file);
	file = fopen("t2.txt", "r");
	take_words_test("", 0, "Test #2 (empty)", file);
	fclose(file);


}


//*******************************************************************************


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


int size(struct list *head)
{
	int size = 0;
	struct list *current = head; 
	while(current)
	{
		size++;
		current = current->next;
	}
	return size;
}

void take_words_test(const char *result, int count, const char *text, FILE *file)
{
	struct list *head = take_words(file);
	int flag = 1;
	if (size(head) == count)
	{
		FILE *out = fopen("o1.txt", "w");
		print_list(head, out);
		fclose(out);
		out = fopen("o1.txt", "r");
		char string[N] = "";
		fgets(string, N, out);
		if (strlen(string) == strlen(result))
		{
			for (int i = 0; i < strlen(string); i++)
				if (string[i] != result[i])
					flag = 0;
		}
		else
			flag = 0;
		fclose(out);
	}
	else
		flag = 0;
	test(flag, text);
	free_list(head);
}
