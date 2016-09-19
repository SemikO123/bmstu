#include <stdio.h>
#define N 30

int read(char *mass)
{
	int i=0;
	while ((scanf("%c",&mass[i])) != '\0')
		i++;
	return i;
}


int main(void)
{
	char mass[N];
	printf("MASS=%s",mass);
	int i = sizeof(mass)/sizeof(char);
	printf("N=%d",read(mass));
}

