#include <stdio.h>
#include <math.h>
#define P(A, B, C) (A+B+C)/2  // подсчет полупериметра

int main(void)
{
    float a,b,c;
    float area;
    puts("Input a,b,c");
    int counter = scanf("%f %f %f",&a,&b,&c);
    // проверка ввода
    if (counter == 3)
    {
        // формула Герона вычисления площади треугольника
        area = sqrt(P(a,b,c)*(P(a,b,c)-a)*(P(a,b,c)-b)*(P(a,b,c)-c));
        printf("Area of triangle: %6.2f",area);
    }
    else
    {
        puts("Incorrect entry");
    }
}
