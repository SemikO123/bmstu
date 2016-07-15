#include <stdio.h>
#include <math.h>
#include "2pr.h"
#include "err.h"

/**
 * @function average
 * This function finds the average of the sequence of numbers
 * @param[in] file file, from which we get the sequence
 * @param[in] avrg average value of the sequence
 * @return 0 or error
 */

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

/**
 * @function search
 * This function finds number of sequence which is closest to average
 * @param[in] file file, from which we get the sequence
 * @param[in] avrg average value of the sequence
 * @param[in] *needs the closest to average number of sequence
 * @return 0 or error
 */

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

