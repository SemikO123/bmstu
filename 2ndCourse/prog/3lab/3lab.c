#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "functions.h"
#include "errors.h"

int main(int argc, char **argv)
{

	int out_error;
	FILE *input;
	if (argc != 4)
	{
		printf("\nPut names of i/o files and number as parameters\n");
		out_error = BADPARAMETERS;
	}
	else
	{
		input = fopen(argv[1], "r");
		if (!input)
		{
			printf("\nInput file doesn't found\n");
			out_error = NOFILE;
		}
		else
		{
			struct list *head = NULL;
			int error;
			head = read_from_file(input, &error);
			if (error == OK)
			{
				if (strtol(argv[3], NULL, 10) == 0 && argv[3][0] != '0')
				{
					printf("Bad number as parameter\n");
					out_error = BADPARAMETERS;
				}
				else
				{
					int adding_number = strtol(argv[3], NULL, 0);
					printf("add %d \n", adding_number);
					head = add_new_element(head, adding_number);
					FILE *output;
					output = fopen(argv[2], "w");
					if (!output)
					{
						printf("Output file doesn't found\n");
						out_error = NOFILE;
					}
					else
					{
						printf("Result: ");
						print_list(head, 1, output);
						out_error = OK;
					}
					fclose(output);
				}
			}
			free_all(head);
			head = NULL; 	
		}
		fclose(input);
	}
	return out_error;
}



