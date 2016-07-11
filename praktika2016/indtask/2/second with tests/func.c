#include <stdio.h>
#include <math.h>
#include "2.h"
float num;

float average(FILE *file)
{
     int count;
     float sum;
     if (fscanf(file, "%f", &num) == 1)
     {
         sum = num;
         count = 1;
         while (fscanf(file, "%f", &num) == 1)
         {
             sum = sum + num;
             count++;
         }
         return sum/count;
     }
     else
         return -1;

}

float search(FILE *file, float avrg)
{
    float minmod,uneedme;
    if (fscanf(file, "%f", &num) == 1)
    {
        minmod = fabs(num-avrg);
        uneedme = num;
        while (fscanf(file, "%f", &num) == 1)
            if (fabs(num-avrg) < minmod)
            {
                minmod = fabs(num-avrg);
                uneedme = num;
            }
        return uneedme;
    }
    else
        return -1;

}
