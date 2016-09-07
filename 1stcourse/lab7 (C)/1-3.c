#include <stdio.h>

int main(void)
{
    int x;
    int summa;
    int t = 0;
    puts("Input numbers:");
    if (scanf("%d\n", &x) == 1)
    {
        if (x % 2 == 1)
        {
            summa = x;
            t = 1;
        }
        else
            summa = 0;
    }
    else
    {
        puts("Wrong input");
        return 0;
    }

    while (scanf("%d\n", &x) == 1)
    {
        if (x % 2 == 1)
        {
            summa += x;
            t += 1;
        }
    }
    if (t > 0)
        printf("Sum of the odd numbers: %d\n",summa);
    else
        puts("No odd numbers");


}

