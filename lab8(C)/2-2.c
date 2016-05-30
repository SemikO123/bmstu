#include <stdio.h>

void swap(float *x, float *y)
{
    float z = *x;
    *x = *y;
    *y = z;
}

int main(void)
{
    float a = 0.1;
    float b = 0.2;
    printf("a=%f b=%f\n",a,b);
    swap(&a,&b);
    printf("a=%f b=%f\n",a,b);

}