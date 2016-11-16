#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <string.h>


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
			char *string;
			do
			{
				
				string = read_line(file);
				printf("ETO STROKA = %s", string);	
			}
			while (string != NULL);
				
		}
		fclose(file);
	}
	return out_error;
}