#include <stdio.h>
#include "2.h"

int main(int argc, char** argv)
{
    FILE *file;
    float gives,avrg;

    float result = 5.142857;   //1 4 9 -3 6 7 12
    file = fopen(argv[1],"r");
    gives = average(file);
    printf("%f and %f\n",gives,result);
    if (result == gives)
        puts("Function average works well\n");
    else
        puts("Function average works wrong\n");
    fclose(file);

    result = 0;   //-2 2
    file = fopen(argv[2],"r");
    gives = average(file);
    printf("%f and %f\n",gives,result);
    if (result == gives)
        puts("Function average works well\n");
    else
        puts("Function average works wrong\n");
    fclose(file);

    result = 6;    //1 4 9 -3 6 7 12
    file = fopen(argv[1],"r");
    avrg = average(file);
    fclose(file);
    file = fopen(argv[1],"r");
    gives = search(file,avrg);
    printf("%f and %f\n",gives,result);
    if (result == gives)
        puts("Function search works well\n");
    else
        puts("Function search works wrong\n");
    fclose(file);

    result = -2;    //-2 2
    file = fopen(argv[2],"r");
    avrg = average(file);
    fclose(file);
    file = fopen(argv[2],"r");
    gives = search(file,avrg);
    printf("%f and %f\n",gives,result);
    if (result == gives)
        puts("Function search works well\n");
    else
        puts("Function search works wrong\n");
    fclose(file);



}
