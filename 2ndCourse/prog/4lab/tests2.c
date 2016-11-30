#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <string.h>

#define RESET   "\033[0m"
#define GRAY     "\033[1;30m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"

void test(int flag, const char *text)
{
	if (flag == 0)
		printf("TEST %s %sFAILED%s\n", text, RED, RESET);
	else
		printf("TEST %s %sPASSED%s\n", text, GREEN, RESET);
}

int compare(const char *result, const char *rightresult)
{
	int flag = 1;
	if (strlen_f(result) == strlen_f(rightresult))
	{
		for (int i = 0; i < strlen(result); i++)
			if(result[i] != rightresult[i])
				flag = 0;
	}
	else
		flag = 0;
	return flag;	
}

void test_concat(char *string1, const char *string2, const char *rightresult, const char *text)
{
	char *result = concat_string(string1, string2);
	test(compare(result, rightresult), text);
	free(result);
}

void test_read(const char *filename, const char *rightresult , int error, const char *text)
{
	int err;
	FILE *file = fopen(filename, "r");
	char *result = read_line(file, &err);
	if (err == error)
	{
		if (err == OK)
			test(compare(result, rightresult), text);
		else if (err == EMPTYSTRING && error == EMPTYSTRING)
			test(1, text);
	}
	free(result);
	fclose(file);
}

void test_changings(char *string, const char *substring, int right, const char *text)
{
	int result = count_of_changings(string, substring);
	if (result == right)
		test(1, text);
	else
		test(0, text);
}

void test_replace(char *string, const char *old, const char *new, const char *rightresult, const char *text)
{
	char *result = change_string(string, old, new);
	test(compare(result, rightresult), text);
	free(result);
}

int main(void)
{
	printf("-------Test function 'concat_string'-------\n");
	test_concat("", "", "", "#1 two empty strings      ");
	test_concat("aaa", "", "aaa", "#2 second empty string    ");
	test_concat("", "aaa", "aaa", "#3 first empty string     ");
	test_concat("aaa", "bbb", "aaabbb","#4 two strings            ");

	printf("\n-------Test function 'read_line'-----------\n");
	test_read("file1.txt", "", EMPTYSTRING,"#1 empty file             ");
	test_read("file2.txt", "aaa bbb ccccc\n", OK, "#2 not empty file         ");

	printf("\n---Test function 'count_of_changings'------\n");
	test_changings("", "aaa", 0, "#1 empty initial string   ");
	test_changings("aaa", "aaa", 1, "#2 string = substring     ");
	test_changings("aaaaabaaaa", "aaa", 2, "#3 overlap                ");
	test_changings("aaabaaaaaabbb", "aaa", 3, "#4 ordinary situation     ");

	printf("\n------Test function 'change_string'--------\n");
	test_replace("aaaaaaabbaaaaaaa","bb","A","aaaaaaaAaaaaaaa","#1 len(old) > len(new)   ");
	test_replace("aaaaaaabbaaaaaaa","bb","AA","aaaaaaaAAaaaaaaa","#2 len(old) = len(new)   ");
	test_replace("aaaaaaabbaaaaaaa","bb","AAAA","aaaaaaaAAAAaaaaaaa","#3 len(old) < len(new)   ");
	test_replace("abcdefgh","z","xyz","abcdefgh","#4 old doesn't found     ");
	test_replace("","aa","O","","#5 empty string          ");
	test_replace("aabaabaab","a","","bbb","#6 empty new             ");
	test_replace("abc","0","W","abc","#7 old = 0               ");
	printf("%s        symbols replaces where\n%s", GRAY, RESET);
	test_replace("abc def","a","W","Wbc def","#8    1      1      begin ");
	test_replace("abc def","ab","W","Wc def","#9    2      1      begin ");
	test_replace("aaaabca aaa","b","W","aaaaWca aaa","#10   1      1      middle");
	test_replace("aaaabca aaa","abc","W","aaaWa aaa","#11   3      1      middle");
	test_replace("abc efg","g","W","abc efW","#12   1      1      end   ");
	test_replace("abc efg","fg","W","abc eW","#13   2      1      end   ");
	test_replace("aaa aaab ba aabb","a","W","WWW WWWb bW WWbb","#14   1      9      begin ");
	test_replace("aaa aaab ba aabb","aa","W","Wa Wab ba Wbb","#15   2      3      begin ");
	test_replace("babaacd","a","W","bWbWWcd","#16   1      3      middle");
	test_replace("babc abc aaba","abc","W","bW W aaba","#17   3      2      middle");
	test_replace("abc def defdef","f","W","abc deW deWdeW","#18   1      3      end   ");
	test_replace("abc def defde","de","W","abc Wf WfW","#19   2      3      end   ");
	printf("%s* old - old substring to replace,\n  new - new substring instead of the old substring\n%s",GRAY, RESET);

}