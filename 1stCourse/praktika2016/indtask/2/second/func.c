#include <stdio.h>
#include <math.h>
#define ERREMPTY -3
#define ERRNONUM -4
#define BADMARK -5
#define OK 0


int average(FILE *file,float *avrg)
{
    int code;
    if ((file == NULL) || (avrg == NULL))
        code = BADMARK;
    else
    {
         float sum,num,count;
         switch(fscanf(file, "%f", &num))
         {
            case -1 :
                code = ERREMPTY;
                break;
            case 0 :
                code = ERRNONUM;
                break;
            case 1 :
                code = OK;
                sum = num;
                count = 1;
                while (fscanf(file, "%f", &num) == 1)
                {
                    sum = sum + num;
                    count++;
                }
                *avrg = sum/count;
                //printf("Average is %.2f\n",*avrg);
         }
    }
    return code;
}

int search(FILE *file, float avrg, float *needs)
{
    int code;
    if ((file == NULL) || (needs == NULL))
        code = BADMARK;
    else
    {
        float minmod,num;
        switch(fscanf(file, "%f", &num))
        {
            case -1 :
                code = ERREMPTY;
            case 0 :
                code = ERRNONUM;
            case 1 :
                code = OK;
                minmod = fabs(num-avrg);
                *needs = num;
                while (fscanf(file, "%f", &num) == 1)
                    if (fabs(num-avrg) < minmod)
                    {
                        minmod = fabs(num-avrg);
                        *needs = num;
                    }
        }
    }
    return code;
}
