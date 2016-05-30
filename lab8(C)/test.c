#include <stdio.h>

int main(void)
{
    int a = 5;
    int *p = &a;
    int **n = &p;
    *&a = 17;
    printf("%d\n", **n);
    printf("%d", a);
}