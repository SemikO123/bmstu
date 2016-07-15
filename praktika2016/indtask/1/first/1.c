#include <stdio.h>
#define ERREMPTY -1
#define ERRNONUM -2
#define OK 0


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
    int s;
    int err;
    switch(process(stdin,&s))
    {
        case OK:
            fprintf(stdout,"Mark of sequence is changing %d times",s);
            err = OK;
            break;
        case ERREMPTY:
            err = ERREMPTY;
            fprintf(stderr,"Empty input");
            break;
        case ERRNONUM:
            err = ERRNONUM;
            fprintf(stderr,"Can't get the numbers");
            break;
    }
    return err;
}

int process(FILE *in,int *s)
{
    int err;
    int first,second;
    puts("Input numbers:");
    switch (fscanf(in,"%d",&first))
    {
        case -1:
            err = ERREMPTY;
            break;
        case 0:
            err = ERRNONUM;
            break;
        case 1:
            err = OK;
            *s = 0;
            while(fscanf(in,"%d",&second) == 1)
            {
                //printf("f %d s %d result %d\n",first,second,counter(first,second));
                *s = *s + counter(first,second);
                first = second;
            }
            break;
    }
    return err;
}

int counter(int x, int y)
{
    int code;
    if (x*y < 0)
        code = 1;
    else //x*y >= 0
    {
        //assert(x*y != 0)
        if (x*y > 0)
            code = 0;
        else
        {
            if ((x==0 && y<0)==1 || (y==0 && x<0)==1)
                code = 1;
            else
                code = 0;
        }
    }
    return code;
}
