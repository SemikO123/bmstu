#include <stdio.h>
#include "2pr.h"
#include "err.h"
#define good1 "Function 'average' works WELL\n"
#define bad1 "Function 'average' works WRONG\n"
#define good2 "Function 'search' works WELL\n"
#define bad2 "Function 'search' works WRONG\n"

int main(int argc, char** argv)
{
    FILE *file1;
    FILE *file2;
    FILE *file3;
    FILE *file4;
    float gives,avrg;
    int flag = 0;
    int code;

    float result = 5.142857;   //1 4 9 -3 6 7 12
    file1 = fopen(argv[1],"r");
    file2 = fopen(argv[2],"r");
    file3 = fopen(argv[3],"r");
    file4 = fopen(argv[4],"r");
    code = average(file1,&avrg);
    printf("Obtained      Expected\n");
    printf("%f      %f\n",avrg,result);
    if ((result != avrg) || (code != 0))
        flag = 1;

    result = 4;   //1 2 3 5 6 7
    code = average(file2,&avrg);
    printf("%f      %f\n",avrg,result);
    if ((result != avrg) || (code != 0))
        flag = 1;

    int resultcode = -3;
    code = average(file3,&avrg);
    printf("Obtained code      Expected code\n");
    printf("EMPTY FILE\n");
    printf("%d                    %d\n",resultcode,code);
    if (resultcode != code)
        flag = 1;

    resultcode = -4;
    code = average(file4,&avrg);
    printf("INCORRECT FILE\n");
    printf("%d                    %d\n",resultcode,code);
    printf("[P.S. -3 - empty file, -4 - incorrect file]\n");
    if (resultcode != code)
        flag = 1;


    if (flag == 0)
        printf(good1);
    else
        printf(bad1);

    printf("\n");

    flag = 0;
    result = 6;    //1 4 9 -3 6 7 12
    rewind(file1);
    average(file1,&avrg);
    rewind(file1);
    code = search(file1,avrg,&gives);
    printf("Obtained      Expected\n");
    printf("%f      %f\n",gives,result);
    if ((result != gives) || (code != 0))
        flag = 1;

    result = 3;    //1 2 3 5 6 7
    rewind(file2);
    average(file2,&avrg);
    rewind(file2);
    code = search(file2,avrg,&gives);
    printf("%f      %f\n",gives,result);
    if ((result != gives) || (code != 0))
        flag = 1;

    resultcode = -3;
    rewind(file3);
    average(file3,&avrg);
    rewind(file3);
    code = search(file3,avrg,&gives);
    printf("Obtained code      Expected code\n");
    printf("EMPTY FILE\n");
    printf("%d                   %d\n",resultcode,code);
    if (resultcode != code)
        flag = 1;

    resultcode = -5;
    rewind(file3);
    average(file3,&avrg);
    rewind(file3);
    float *gives1 = 0;
    code = search(file3,avrg,gives1);
    printf("BAD POINTER\n");
    printf("%d                   %d\n",resultcode,code);
    if (resultcode != code)
        flag = 1;

    resultcode = -4;
    rewind(file4);
    average(file4,&avrg);
    rewind(file4);
    code = search(file4,avrg,&gives);
    printf("INCORRECT FILE\n");
    printf("%d                   %d\n",resultcode,code);
    printf("[P.S. -3 - empty file, -4 - incorrect file, -5 - badmark]\n");
    if (resultcode != code)
        flag = 1;

    if (flag == 0)
        printf(good2);
    else
        printf(bad2);


    fclose(file1);
    fclose(file2);
    fclose(file3);
    fclose(file4);

}
