#include <stdio.h>
#include "2pr.h"
#include "err.h"
#define good1 "Function 'average' works well\n"
#define bad1 "Function 'average' works wrong\n"
#define good2 "Function 'search' works well\n"
#define bad2 "Function 'search' works wrong\n"

int main(int argc, char** argv)
{
    FILE *file1;
    FILE *file2;
    float gives;
    float avrg;
    int flag = 0;

    float result = 5.142857;   //1 4 9 -3 6 7 12
    file1 = fopen(argv[1],"r");
    file2 = fopen(argv[2],"r");
    average(file1,&avrg);
    //printf("%f and %f\n",avrg,result);
    if (result != avrg)
        flag = 1;

    result = 4;   //1 2 3 5 6 7
    average(file2,&avrg);
    //printf("%f and %f\n",avrg,result);
    if (result != avrg)
        flag = 1;

    if (flag == 0)
        puts(good1);
    else
        puts(bad1);

    flag = 0;
    result = 6;    //1 4 9 -3 6 7 12
    rewind(file1);
    average(file1,&avrg);
    rewind(file1);
    gives = search(file1,avrg);
    //printf("%f and %f\n",gives,result);
    if (result != gives)
        flag = 1;

    result = 3;    //1 2 3 5 6 7
    rewind(file2);
    average(file2,&avrg);
    rewind(file2);
    gives = search(file2,avrg);
    //printf("%f and %f\n",gives,result);
    if (result != gives)
        flag = 1;

    if (flag == 0)
        puts(good2);
    else
        puts(bad2);



    fclose(file1);
    fclose(file2);



}
