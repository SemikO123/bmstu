#include <stdio.h>
#include <stdio.h>
#include "errors.h"
#include "functions.h"

int main(int argc, char** argv)
{
	FILE *f1; // -3 -2 -1 1 2 3
	FILE *f2; // empty
	FILE *f3; // 15.2 -1 -11.34 10 8.8 -4.4 3 -5.1 1 3.33 7.6 -20
	FILE *f4; // abc 123

	float array[N];
	int count = 0;
	int result;
	int code;

	f1 = fopen(argv[1],"r");
	f2 = fopen(argv[2],"r");
	f3 = fopen(argv[3],"r");
	f4 = fopen(argv[4],"r");

	
	printf("\nFUNCTION 'READARR'\n");
	code = ReadArr(array, N, f1, &count);
	result = 0;
	printf("№  Obtained         Expected      Test\n");
	if (result == code)
		printf("1.     %d              %d           PASSED\n",code,result);
	else
		printf("1.     %d              %d           FAILED\n",code,result);

	code = ReadArr(array, N, f2, &count);
	result = -3;
	if (result == code)
		printf("2.    %d             %d           PASSED\n",code,result);
	else
		printf("2.    %d             %d           FAILED\n",code,result);

	code = ReadArr(array, N, f3, &count);
	result = -1;
	if (result == code)
		printf("3.    %d             %d           PASSED\n",code,result);
	else
		printf("3.    %d             %d           FAILED\n",code,result);

	code = ReadArr(array, N, f4, &count);
	result = -4;
	if (result == code)
		printf("4.    %d             %d           PASSED\n",code,result);
	else
		printf("4.    %d             %d           FAILED\n",code,result);

	printf("*Errors: \n 0 - Work, \n-1 - Excess data, \n-3 - Empty input, \n-4 - Bad input\n");
	fclose(f1);
	fclose(f2);
	fclose(f3);
	fclose(f4);

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

	float avrg;
	printf("\nFUNCTION 'AVERAGE'\n");
	printf("№  Obtained         Expected      Test\n");
	float res = 0;
	float arr1[6] = {-3.3,-2.2,-1.1,1.1,2.2,3.3};
	Average(arr1,6,&avrg);
	if (res == avrg)
		printf("1.  %.2f              %.2f        PASSED\n",avrg,res);
	else
		printf("1.  %.2f              %.2f        FAILED\n",avrg,res);

	res = 0.1;
	float arr2[10] = {8,7,6,8,4,-6,-4,-5,-6,-11};
	Average(arr2,10,&avrg);
	//if ((-1e-30 < res - avrg) & (res - avrg < 1e-30)) // КОСТЫЛЬ :((
	if (res == avrg)
		printf("2.  %.2f              %.2f        PASSED\n",avrg,res);
	else
		printf("2.  %.2f              %.2f        FAILED\n",avrg,res);

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

	printf("\nFUNCTION 'NEWARRGEN'\n");
	printf("№  Obtained         Expected      Test\n");
	float narr1[N];
	float resul[3] = {1.1,2.2,3.3};
	FILE *f11;
	f11 = fopen("test1.txt","w");
	NewArrGen(arr1,f11,6,0);
	count = 0;
	fclose(f11);
	f11 = fopen("test1.txt","r");
	ReadArr(narr1, N, f11, &count);
	int flag = 0;
	for (int i=0;i<count;i++)
		if (narr1[i] == resul[i])
			flag = 1;
		else
		{
			flag = 0;
			break;
		}
	if (flag == 1)
		printf("1.                                PASSED\n");
	else
		printf("1.                                FAILED\n");
	fclose(f11);


	float narr2[N];
	float resull[5] = {8,7,6,8,4};
	FILE *f12;
	f12 = fopen("test2.txt","w");
	NewArrGen(arr2,f12,10,0.1);
	count = 0;
	fclose(f12);
	f12 = fopen("test2.txt","r");
	ReadArr(narr2, N, f12, &count);
	flag = 0;
	for (int i=0;i<count;i++)
		if (narr2[i] == resull[i])
			flag = 1;
		else
		{
			flag = 0;
			break;
		}
	if (flag == 1)
		printf("2.                                PASSED\n");
	else
		printf("2.                                FAILED\n");
	fclose(f12);



}