#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

int main(void)
{
	printf("Тесты на некорректный ввод\n");
	char str1[] = "++1";
	char znak_int1;
	if (input_int_numbers(str1,&znak_int1) == -1)
		printf("%s --> PASSED\n",str1);
	else
		printf("%s --> FALLED\n",str1);

}