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
	FILE *file2;
	if (argc != 3)
	{
		printf("Put name of i/o files\n");
	}
	else
	{
		file = fopen(argv[1],"r");
		if (file == NULL) 
			printf("File doesn't found\n");
		else
		{
			file2 = fopen(argv[2],"w");
			switch(ReadArr(array, N, file, &count))
			{
				case EMPTYFILE:
					printf("File is empty\n");
					fprintf(file2,"File is empty\n");
					fclose(file);
					fclose(file2);
					return EMPTYFILE;
					// break;
				case BADFILE:
					printf("Can't get numbers from file\n");
					fprintf(file2,"Can't get numbers from file\n");
					fclose(file);
					fclose(file2);
					return BADFILE;
					// break;
				case EXCESS:
					printf("File contains other numbers which weren't included in array\n");
					fprintf(file2,"File contains other numbers which weren't included in array\n");
				case OK:
					Average(array,count, &avrg);
					printf("Average is %.3f \n",avrg);
					fclose(file);
					float newarr[N];
					int new_arr_count = 0;
					NewArrGen(array, count, avrg, newarr, &new_arr_count);
					ArrToFile(newarr, &new_arr_count, file2);
					printf("Look in output file\n");
					fclose(file2);
					return OK;
					// break;


			}
		}
	}
	
}
