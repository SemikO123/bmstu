#include <stdio.h>

void swap(float *x, float *y);

int main(void)
{
    float a = 0.1;
    float b = 0.2;
    printf("a=%.1f b=%.1f\n",a,b);
    swap(&a,&b);
    printf("a=%.1f b=%.1f\n",a,b);
}

void swap(float *x, float *y)
{
    float z = *x;
    *x = *y;
    *y = z;
}

