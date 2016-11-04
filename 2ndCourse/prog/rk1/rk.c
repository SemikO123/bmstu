#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

// Вариант 3 Задача 2

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		printf("Bad parameters with names of file");
		return BADPARAMETERS;
	}
	else
	{
		FILE *in = fopen(argv[1],"r");
		if (in)
		{
			struct list *head = take_words(in);
			FILE *out = fopen(argv[2], "w");
			if (out)
			{
				print_list(head, out);
				// print_list(head, stdout);
				printf("\nYou can find result in 'out.txt'\n");
			}
			else
			{
				printf("Output file doesn't found");
				return NOFILE;
			}
			free_list(head);
			fclose(out);
		}
		else 
		{
			printf("Input file doesn't found");
			return NOFILE;
		}
		fclose(in);
	}
	return OK;
}