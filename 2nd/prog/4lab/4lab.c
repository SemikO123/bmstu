#include <stdio.h>
#include "functions.h"
#include <stdlib.h>

int main(int argc, char **argv)
{
	char string[] = "This is a very short string!"; 
	char *symbol;
	int desired_symbol = 'v';
	symbol = strchr(string, desired_symbol);
	printf("String: %s\n\n",string);
	if (symbol != NULL)
		printf("'%c' found on %d place\n", desired_symbol, (int)(symbol-string+1));
	else
		printf("Didn't find '%c' in string!\n", desired_symbol);


	char *duplicate;
	duplicate = strdup(string);
	printf("Copy of string: %s\n", duplicate);
	free(duplicate);
}