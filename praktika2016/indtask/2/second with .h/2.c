#include <stdio.h>
#include "2.h"

int main(int argc, char** argv)
{
    FILE *file;
    float avrg;
    if (argc != 2)
    {
        fprintf(stderr, "Put the name of file as parameter of launch\n");
        return -1;
    }
    file = fopen(argv[1],"r");
    if (file == NULL)
    {
        fprintf(stderr,"File doesn't exist");
        return -2;
    }
    avrg = average(file);
    if (avrg != -1)
    {
        printf("Average is %.2f\n",avrg);
        fclose(file);
        file = fopen(argv[1],"r");
        printf("Close to average number of sequence is %.2f",search(file,avrg));
        fclose(file);
        //return 0;
    }
    else
        printf("No numbers in file");


}
