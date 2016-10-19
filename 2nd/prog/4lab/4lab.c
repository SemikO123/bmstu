#include <stdio.h>
#include "functions.h"
#include <stdlib.h>

#define BADPARAMETERS -1
#define NOFILE -2

int main(int argc, char **argv)
{
	FILE *file;
	if (argv != 4)
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
			
		}
	}
}