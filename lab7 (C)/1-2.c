# include  <stdio.h>
# include <math.h>

int main(void)
{
float x;
float eps;
puts("Input x and eps");
int e = scanf("%f %f",&x,&eps);
	if (e == 2)
	{
		float t = x;
		int count = 1;
		float exp1 = 1;
		while (t > eps)
		{
			exp1 += t;
			count += 1;
			t *= x;
			t /= count;
		}
		puts("\n");
		printf("The value of the sum of series: %f\n", exp1);
		printf("The exact exponential value: %f\n", exp(x));
		if (exp1 > exp(x))
			puts("exp > exp0");
		else
			puts("exp < exp0");


	}
	else
		puts("Incorrect input");
}