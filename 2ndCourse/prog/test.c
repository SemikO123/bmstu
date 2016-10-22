#include <stdio.h>
#include <stdlib.h>

int main(void)
{
int i = 10;
int j = 14;
int k;
int *p = &i;
int *q = &j;
printf("1. %d %d %d\n",i,j,k);
*p+=1;
printf("2. %d %d %d\n",i,j,k);
p = &k;
printf("3. %d %d %d\n",i,j,k);
*p = *q;
printf("4. %d %d %d\n",i,j,k);
p = q;
printf("5. %d %d %d\n",i,j,k);
*p = *q;	
printf("6. %d %d %d\n",i,j,k);

int arr[10] = {9,8,7,6,5,4,3,2,1,0};
printf("\n%d\n",arr[0]);
printf("%d\n",*arr);
printf("%d\n",*arr+2);
printf("%d\n",*(arr+2));
// printf("%p\n",arr);
// printf("%p\n",&arr[2]);
// printf("%p\n",arr+2);

}