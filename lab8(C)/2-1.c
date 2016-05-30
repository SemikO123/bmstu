# include  <stdio.h>

int fibon(int x)
{
    int num1 = 0;
    int num2 = 1;
    int *n;
    int *m;
    int side;
    n = &num1;
    m = &num2;
    while (num2 < x)
    {
        //printf("%d %d        |\n", num1, num2);
        side = *n + *m;
        *n = *m;
        *m = side;
        //printf("%d %d   \n", num1, num2);
    }
    if (x == num2)
    {
        //puts("fibonacci detected");
        return 1;
    }
    else
        return 0;

}

int main()
{
    int is = 1;
    int count = 0;
    int x;
    puts("Input sequence of numbers:");
    while (scanf("%d",&x) == 1)
    {
        count += fibon(x);
        //printf("%d %d\n",x,fibon(x));
    }
    printf("Amount of Fibonacci numbers: %d\n",count);

}