#include <stdio.h>

int main(void)
{
int x;
int count = 1;
int t = 0;
int summa = 0;
    puts("Input numbers:");
    while (count != 0)
    {
        count = scanf("%d\n", &x);
        if (count != 0)
        {
            t += 1;
            if (t % 2 == 1)
                summa += x;
        }
    }
    printf("Sum of the odd numbers: %d\n",summa);

}

