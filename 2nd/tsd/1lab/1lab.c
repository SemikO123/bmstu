#include <stdio.h>
#define N 30
#define M 3

// int main(void)
// {
// 	char a[N];
// 	int i=0;
// 	printf("Input numbers separating with space: ");
// 	if ((scanf("%c", &a[i]) == 1) && (a[i] == '-'))
// 	{
// 		a[i] = '0';
// 		i = 1;
// 	}
// 	else 
// 	{
// 		a[i+1] = a[i];
// 		a[i] = '1';
// 		i = 2;
// 	}
// 	while ((scanf("%c",&a[i]) == 1) && (a[i] >= '0' && a[i] <= '9'))
// 		i++;
// 	for (int k=0;k<i;k++)
// 		printf("%c %d\n", a[k],k);

// 	char b[N];
// 	i = 0;

// }

int main(void)
{
	char a[M] = {1,2,3};
	char b[M] = {2,3,4};
	char c[M+M] = {0};
	char d[N] = {0};
	int t,per;
	for (int i=M-1; i>=0; i--)
	{
		t=M;
		per = 0;
		for (int j=M-1; j>=0; j--)
		{
			//printf("j=%d, i=%d\n",j,i);
			per += b[j]*a[i];
			//printf("b[j]=%c, a[i]=%c\n",b[j],a[i]);
			c[t] = per % 10;
			t-=1;
			per = (int)(per/10);
			if (t == 0)
				c[t] = per;
			//printf("c[%d]=%c, per=%d\n",t+1,c[t+1],per);
		}
		int co;
		for (co=0;co<M+1;co++)
			printf("%d",c[co]);
		for (int w=i;w<M-1;w++)
		{
			c[co+w] = 0;
			printf("%d",c[co+w]);
		}
		printf("sizeof=%d\n",(int)(sizeof(c)/sizeof(c[0])));
		int k = sizeof(c)/sizeof(c[0]);
		int num = 0;
		while (k>0)
		{
			d[N-k] += c[num];
			num += 1;
			k -= 1;
		}
		// В ДАННЫЙ МОМЕНТ В С ХРАНИТСЯ НУЖНОЕ СЛАГАЕМОЕ ПОРАЗРЯДНО
		printf("\n");

	}
	for (int y=0;y<N;y++)
		printf("%d ",d[y]);
}








