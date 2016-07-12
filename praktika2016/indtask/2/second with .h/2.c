#include <stdio.h>
#include "2pr.h"
#include "err.h"

float avrg;

/**
 * @function average
 * This function finds the average of the sequence of numbers
 * @param[in] file file, from which we get the sequence
 * @param[in] avrg average value of the sequence
 * @return 0 or error
 */
int average(FILE *file, float *avrg);

/**
 * @function search
 * This function finds number of sequence which is closest to average
 * @param file file, from which we get the sequence
 * @param avrg average value of the sequence
 * @return the closest to average number of sequence
 */
float search(FILE *file, float avrg);

int main(int argc, char** argv)
{
    FILE *file;
    if (argc != 2)   //Правильность подачи файла как параметра
    {
        fprintf(stderr, "Put the name of file as parameter of launch\n");
        return -1;
    }
    file = fopen(argv[1],"r");
    if (file == NULL)  //Существование заданного файла
    {
        fprintf(stderr,"File doesn't found");
        return -1;
    }
    switch(average(file,&avrg))
    {
        case errempty:
            fprintf(stderr,"File is empty");  //Файл пуст
            fclose(file);
            return -1;
            break;
        case errnonum:
            fprintf(stderr,"Can't get numbers from file");   //Файл содержит не только числа
            fclose(file);
            return -1;
            break;
       case 0:
            rewind(file);
            fprintf(stdout,"Close to average number of sequence is %.2f",search(file,avrg));
            fclose(file);
            return 0;

    }
}

