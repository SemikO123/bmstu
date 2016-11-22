#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <string.h>


char *read_line(FILE *file);
char *change_string(const char *string, const char *old, const char *new);

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
			FILE *out = fopen(argv[2], "w");
			if (!out)
			{
				printf("\nOutput file doesn't found\n");
				out_error = NOFILE;
			}
			else
			{
				printf("---------------------------\n");
				printf("Input old substring: ");
				char *old = read_line(stdin);
				printf("Input new substring: ");
				char *new = read_line(stdin);
				printf("---------------------------\n");
				while (!feof(file))
				{
					string = read_line(file);
					if (string != NULL && string[0] != 0)
					{
						printf("Current string -> %s", string);
						char *new_string = change_string(string, old, new);
						printf("New string -> %s", new_string);
						fprintf(out,"%s",new_string);
						free(new_string);	
					}
					free(string);
				}
				free(old);
				free(new);
			}
			fclose(out);
				
		}
		fclose(file);
	}
	return out_error;
}