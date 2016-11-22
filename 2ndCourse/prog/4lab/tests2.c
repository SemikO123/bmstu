#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <string.h>

void test(int flag, const char *text)
{
	if (flag == 0)
		printf("TEST %s FAILED\n", text);
	else
		printf("TEST %s PASSED\n", text);
}

void test_concat(char *string1, const char *string2, const char *rightresult, const char *text)
{
	int flag = 1;
	char *result = concat_string(string1, string2);
	if (strlen(result) == strlen(rightresult))
	{
		for (int i = 0; i < strlen(result); i++)
			if(result[i] != rightresult[i])
				flag = 0;
	}
	else
		flag = 0;
	test(flag, text);
	free(result);
}

void test_read(const char *filename, const char *rightresult ,const char *text)
{
	int flag = 1;
	FILE *file = fopen(filename, "r");
	char *result = read_line(file);
	if (strlen(result) == strlen(rightresult))
	{
		for (int i = 0; i < strlen(result); i++)
			if(result[i] != rightresult[i])
				flag = 0;
	}
	else
		flag = 0;
	test(flag, text);
	free(result);
	fclose(file);
}

void test_changings(const char *string, const char *substring, int right, const char *text)
{
	int result = count_of_changings(string, substring);
	if (result == right)
		test(1, text);
	else
		test(0, text);
}

int main(void)
{
	printf("-------Test function 'concat_string'-------\n");
	test_concat("", "", "", "two empty strings    ");
	test_concat("aaa", "", "aaa", "second empty string  ");
	test_concat("", "aaa", "aaa", "first empty string   ");
	test_concat("aaa", "bbb", "aaabbb","two strings          ");

	printf("\n-------Test function 'read_line'-----------\n");
	test_read("file1.txt", "", "empty file           ");
	test_read("file2.txt", "aaa bbb ccccc\n", "not empty file       ");

	printf("\n---Test function 'count_of_changings'------\n");
	test_changings("", "aaa", 0, "empty initial string ");
	test_changings("aaa", "aaa", 1, "string = substring   ");
	test_changings("aaaaabaaaa", "aaa", 2, "overlap              ");
	test_changings("aaabaaaaaabbb", "aaa", 3, "ordinary situation   ");

	printf("\n---Test function 'change_string'------\n");



}