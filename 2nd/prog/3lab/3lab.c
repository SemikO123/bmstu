#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "functions.h"
#include "errors.h"

int main(int argc, char **argv)
{

	//int out_error;
	FILE *input;
	if (argc != 4)
	{
		printf("\nPut names of i/o files and number as parameters\n");
		return BADPARAMETERS;
	}
	else
	{
		input = fopen(argv[1], "r");
		if (input == NULL)
		{
			printf("\nInput file doesn't found\n");
			return NOFILE;
		}
		else
		{
			int int_number;
			switch (fscanf(input, "%d", &int_number))
			{
				case -1:
					printf("\nFile is empty\n");
					return EMPTYFILE;
				case 0:
					printf("\nCan't get numbers from file\n");
					return BADINPUT;
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
							return BADPARAMETERS;
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
								return NOFILE;
							}
							else
								print_list(head, 1, output);
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
	return OK;
}



