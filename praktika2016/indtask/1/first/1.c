#include <stdio.h>
#define errempty -1
#define errnonum -2

int s;

/**
 * @brief counter
 * This function determines the change in the sequence of the mark between two numbers X and Y
 * @param[in] x
 * @param[in] y
 * @return 1 if mark is changing, 0 if mark isn't changing.
 */
int counter(int x, int y);

/**
 * @brief process
 * This function shows the result
 * @param[in] in
 * @param[in] s count of mark changing
 * @return 0 or error
 */
int process(FILE *in,int *s);


int main(void)
{
    switch(process(stdin,&s))
    {
        case 0:
            fprintf(stdout,"Mark of sequence is changing %d times",s);
            break;
        case errempty:
            fprintf(stderr,"Empty input");
            break;
        case errnonum:
            fprintf(stderr,"Can't get the numbers");
            break;
    }
    return 0;
}

int process(FILE *in,int *s)
{
    int first,second;
    puts("Input numbers:");
    switch (fscanf(in,"%d",&first))
    {
        case -1:
            return errempty;
        case 0:
            return errnonum;
    }
    *s = 0;
    while(fscanf(in,"%d",&second) == 1)
    {
        //printf("f %d s %d result %d\n",first,second,counter(first,second));
        *s = *s + counter(first,second);
        first = second;
    }
    return 0;

}

int counter(int x, int y)
{
    if (x*y < 0)
        return 1;
    else //x*y >= 0
    {
        //assert(x*y != 0)
        if (x*y > 0)
            return 0;
        else
        {
            if ((x==0 && y<0)==1 || (y==0 && x<0)==1)
                    return 1;
            else
                return 0;
        }
    }
}
