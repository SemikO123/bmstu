#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

int main(void)
{
	int first, second;
	struct list *n1 = NULL, *n2 = NULL;
	printf("First number: ");
	scanf("%d", &first);
	while (first != 0)
	{
		int letter = first % 10;
		first /= 10;
		struct list *new = add_new(letter);
		n1 = add_next(n1, new);
	}
	print_list(n1);
	printf("\nSecond number: ");
	scanf("%d", &second);
	while (second != 0)
	{
		int letter = second % 10;
		second /= 10;
		struct list *new = add_new(letter);
		n2 = add_next(n2, new);
	}
	print_list(n2);

	struct list *result = multipl(n1,n2);
	printf("\nResult: ");
	print_list(result);

	//free_all(n1);
	//free_all(n2);
	//free_all(result);
	
	
}