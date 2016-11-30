#include <stdio.h>
#include "functions.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	int out_error;
	FILE *file;
	if (argc != 3)
	{
		printf("\nPut names of i/o files as parameters\n");
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
				char *old = read_line(stdin, &out_error);
				printf("Input new substring: ");
				char *new = read_line(stdin, &out_error);
				printf("---------------------------\n");
				if (old[0] != '\n')
				{
					while (out_error != EMPTYSTRING)
					{
						string = read_line(file, &out_error); 
						if (string != NULL)
						{
							printf("Current string -> %s", string);
							char *new_string = change_string(string, old, new);
							printf("New string     -> %s\n", new_string);
							fprintf(out,"%s",new_string);
							free(new_string);	
						}
						free(string);
					}
				}
				else
					printf("Replacing empty string!\n");
				free(old);
				free(new);
			}
			fclose(out);	
		}
		fclose(file);
	}
	return out_error;
}