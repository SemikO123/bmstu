#include <stdio.h>

/**
 * @function counter
 * This function determines the change in the sequence of the mark
 * @param x
 * @param y
 * @return 1 if mark is changing, 0 if mark isn't changing.
 */

int counter(int x, int y);
/**
 * @function process
 * @param in
 * @param out
 * @return 0 if program can obtain the solution, -1 if it can't
 */
int process(FILE *in, FILE *out);

int main(void)
{
    process(stdin,stdout);
    return 0;

}

int process(FILE *in, FILE *out)
{
    int first,second,s;
    puts("Input numbers:");
    if (fscanf(in,"%d",&first) == 1)
    {
        s = 0;
        while(fscanf(in,"%d",&second) == 1)
        {
            //printf("f %d s %d result %d\n",first,second,counter(first,second));
            s = s + counter(first,second);
            first = second;
        }
        fprintf(out,"Mark of sequence is changing %d times",s);
        return 0;
    }
    else
    {
        fprintf(stderr,"No numbers");
        return -1;
    }
}

int counter(int x, int y)
{
    if (x*y < 0)
        return 1;
    else //x*y >= 0
    {
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
