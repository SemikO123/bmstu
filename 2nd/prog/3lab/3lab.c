#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
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
			int int_number;
			switch (fscanf(input, "%d", &int_number))
			{
				case -1:
					printf("\nFile is empty\n");
					out_error = EMPTYFILE;
					break;
				case 0:
					printf("\nCan't get numbers from file\n");
					out_error = BADINPUT;
					break;
				case 1:
				{
					struct list *head = NULL;
					head = create_new(int_number);
					if (head)
					{
						while (fscanf(input, "%d", &int_number) == 1)			
							head = add_new_element(head, int_number);

						print_list(head, 0, NULL);

						int adding_number;
						if (atoi(argv[3]) == 0 && argv[3][0] != '0')
						{
							printf("Bad number as parameter\n");
							out_error = BADPARAMETERS;
						}
						else
						{
							adding_number = atoi(argv[3]);
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
								print_list(head, 1, output);
								out_error = OK;
							}
							fclose(output);
						}
						free_all(head);
						head = NULL; 
					}
				}
			}
			fclose(input);
		}
	}
	return out_error;
}



