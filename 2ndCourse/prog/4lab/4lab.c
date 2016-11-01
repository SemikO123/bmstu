#include <stdio.h>
#include "functions.h"
#include <stdlib.h>

#define BADPARAMETERS -1
#define NOFILE -2
#define MEMPROBLEM -3
#define OK 0

char *read_line(FILE *file);

int main(int argc, char **argv)
{
	int out_error;
	FILE *file;
	if (argc != 3)
	{
		printf("\nPUt names of i/o files as parameters\n");
		out_error = BADPARAMETERS;
	}
	else
	{
		file = fopen(argv[1], "r");
		if (!file)
		{
			printf("\nInput file doesn't found\n");
			out_error = NOFILE;
		}
		else
		{
			char *string = read_line(file);
			if (string == NULL)
				out_error = MEMPROBLEM;
			else
			{
				printf("%s\n",string);
				out_error = OK;
			}
			free(string);
		}
		fclose(file);
	}
	return out_error;
}