#include <stdio.h>

/**
 * @function average
 * This function finds the average of the sequence of numbers
 * @param file
 * @return average of sequence
 */
float average(FILE *file);

/**
 * @function search
 * This function finds number of sequence which is closest to average
 * @param file
 * @param avrg
 * @return the closest to average number of sequence
 */

float search(FILE *file, float avrg);

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
        rewind(file);
        printf("Close to average number of sequence is %.2f",search(file,avrg));
        fclose(file);
        //return 0;
    }
    else
        printf("No numbers in file");


}
