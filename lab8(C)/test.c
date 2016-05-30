#include <stdio.h>


int main(void)
{
    int x = 1;
    int y = 2;
    int z;
    int *a;
    int *b;
    int t = 8;
    a = &x;
    b = &y;
    while (y <= 21)
    {
        printf("%d %d |\n",x, y);
        z = *a + *b;
        printf("%d\n", z);
        *a = *b;
        printf("%d\n", x);
        *b = z;
        printf("%d\n", y);
        printf("%d %d   \n", x, y);
        if (t == y) {
            puts("piupiupiu");
            return 1;
        }
    }




}