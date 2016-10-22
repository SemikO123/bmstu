#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <string.h>



int main(void)
{
	char string[] = "This is a very very short string!"; 
	char string1[1] = "";
	printf("\n-----> Test function 'strchr' <-----\n");
	int desired_symbol = 'v';
	strchr_test(string, desired_symbol, "Test #1 (found)           ");
	desired_symbol = 0;
	strchr_test(string, desired_symbol, "Test #2 (symbol = 0)      ");
	desired_symbol = 'w';
	strchr_test(string, desired_symbol, "Test #3 (doesn't found)   ");
	desired_symbol = '\0';
	strchr_test(string, desired_symbol, "Test #4 (end of string)   ");
	desired_symbol = 'f';
	strchr_test(string1, desired_symbol, "Test #5 (empty string)    ");

	printf("\n-----> Test function 'strdup' <-----\n");
	strdup_test(string, "Test #1                   ");
	strdup_test(string1, "Test #2 (empty string)    ");
}

void strchr_test(char *string, int desired_symbol, char *text)
{
	char *address_from_func, *address_from_std;
	address_from_func = strchr_f(string, desired_symbol);
	address_from_std = strchr(string, desired_symbol);
	//printf("%d <- ",(int)(address_from_std-string+1));
	if (address_from_std == address_from_func)
		printf("%s PASSED\n", text);
	else
		printf("%s FAILED\n", text);
	
}

void strdup_test(char *string, char *text)
{
	char *duplicate_from_func, *duplicate_from_std;
	duplicate_from_func = strdup_f(string);
	duplicate_from_std = strdup(string);
	int count_f = strlen_f(duplicate_from_func);
	int count_s = strlen_f(duplicate_from_std);
	int flag;
	if (count_f == count_s)
	{
		flag = 1;
		for (int i = 0; i < count_f; i++)
		if (duplicate_from_func[i] != duplicate_from_std[i])
			flag = 0;	
	}
	else
		flag = 0;
	if (flag == 1)
			printf("%s PASSED\n", text);
		else
			printf("%s FAILED\n", text);

	free(duplicate_from_func);
	free(duplicate_from_std);

}