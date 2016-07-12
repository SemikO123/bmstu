#include <stdio.h>
#include <math.h>
#define errempty -3
#define errnonum -4

float num;
float avrg;

int average(FILE *file,float *avrg)
{
     int count;
     float sum;
     switch(fscanf(file, "%f", &num))
     {
        case -1 :
            return errempty;
        case 0 :
            return errnonum;
     }
     sum = num;
     count = 1;
     while (fscanf(file, "%f", &num) == 1)
     {
         sum = sum + num;
         count++;
     }
     *avrg = sum/count;
     //printf("Average is %.2f\n",*avrg);
     return 0;
}

float search(FILE *file, float avrg)
{
    float minmod,uneedme;
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
