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
	
	printf("FUNCTION 'READARR'\n");
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

	fclose(f1);
	fclose(f2);
	fclose(f3);
	fclose(f4);

	float avrg;
	printf("FUNCTION 'AVERAGE'\n");
	printf("№  Obtained         Expected      Test\n");
	float res = 0;
	float arr1[6] = {-3.3,-2.2,-1.1,1.1,2.2,3.3};
	Average(arr1,6,&avrg);
	if (res == avrg)
		printf("1.  %.2f              %.2f      PASSED\n",avrg,res);
	else
		printf("1.  %.2f              %.2f      FAILED\n",avrg,res);

	res = 0.2;
	float arr2[10] = {8,7,6,8,4,-6,-4,-5,-6,-10};
	Average(arr2,10,&avrg);
	if ((-1e-30 < res - avrg) & (res - avrg < 1e-30)) // КОСТЫЛЬ :((
		printf("2.  %.2f              %.2f      PASSED\n",avrg,res);
	else
		printf("2.  %.2f              %.2f      FAILED\n",avrg,res);


	float narr1[3];
	int m=0;
	printf("FUNCTION 'NEWARRGEN'\n");
	printf("№  Obtained         Expected      Test\n");
	float resul[3] = {1.1,2.2,3.3};
	NewArrGen(arr1,narr1,6,&m,0);
	int flag = 0;
	for (int i=0;i<m;i++)
		if (narr1[i] == resul[i])
			flag = 1;
		else
		{
			flag = 0;
			break;
		}
	if (flag == 1)
		printf("1.                               PASSED\n");
	else
		printf("1.                               FAILED\n");


}