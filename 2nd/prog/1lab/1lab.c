#include <stdio.h>
#include "errors.h"
#include "functions.h"

int main(int argc, char** argv)
{
	printf("\n");
	float avrg;
	float array[N];
	int count = 0;
	FILE *file;
	if (argc != 2)
	{
		printf("Put the name of file\n");
	}
	else
	{
		file = fopen(argv[1],"r");
		if (file == NULL) 
			printf("File doesn't found\n");
		else
			switch(ReadArr(array, N, file, &count))
			{
				case EMPTYFILE:
					printf("File is empty\n");
					fclose(file);
					break;
				case BADFILE:
					printf("Can't get numbers from file\n");
					fclose(file);
					break;
				case EXCESS:
					printf("File contains other numbers which weren't included in array\n");
				case OK:
					Average(array,count, &avrg);
					printf("Average is %.3f \n",avrg);
					fclose(file);
					file = fopen("out.txt","w");
					NewArrGen(array, file, count, avrg);
					printf("Output in file out.txt\n");
					fclose(file);
					break;


			}

	}
	return 0;
}
