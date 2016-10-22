# include  <stdio.h>
# include <math.h>

int main (void)
{
float a;
float b;
float c;
float x1;
float x2;
puts("Input a,b,c");
int e = scanf("%f %f %f",&a,&b,&c);
if (e == 3)
	{
	if (a == 0)
		{
            if (b == 0)
            {
                puts("Incorrect");
            }
            else
            {
                x1 = -c / b;
                printf("%f\n", x1);
            }
		}
	else
		{
		float D = b*b - 4*a*c;
		if (D >= 0)
			{
			if (D == 0)
				{
				x1 = x2 = -b/2/a;
				printf("%f\n",x1);
				}
			else
				{
				x1 = (-b + sqrt(D))/2/a;
				x2 = (-b - sqrt(D))/2/a;
				printf("%f %f\n",x1,x2);
				}
			}
		else
			{
			puts("Complex radiacals");
			}
		} 
	}
else
	{
	puts("Incorrect entry");
	}
}
