#include <stdio.h>
#define NOPARAM -1
#define NOFILE -2
#define ERREMPTY -3
#define ERRNONUM -4
#define BADMARK -5
#define OK 0


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
 * @param[in] file file, from which we get the sequence
 * @param[in] avrg average value of the sequence
 * @param[in] *needs the closest to average number of sequence
 * @return 0 or error
 */
int search(FILE *file, float avrg, float *needs);

int main(int argc, char** argv)
{
    float avrg,needs;
    int code;
    FILE *file;
    if (argc != 2)
    {
        //Правильность подачи файла как параметра
        fprintf(stderr, "Put the name of file as parameter of launch\n");
        code = NOPARAM;
    }
    else
    {
        file = fopen(argv[1],"r");
        if (file == NULL)  //Существование заданного файла
        {
            fprintf(stderr,"File doesn't found");
            code = NOFILE;
        }
        else
        {
            code = average(file,&avrg);
            switch(code)
            {
                case ERREMPTY:
                    fprintf(stderr,"File is empty");  //Файл пуст
                    fclose(file);
                    break;
                case BADMARK:
                    fprintf(stderr,"Bad pointer");
                    fclose(file);
                    break;
                case ERRNONUM:
                    fprintf(stderr,"Can't get numbers from file");   //Файл содержит не только числа
                    fclose(file);
                    break;
                case OK:
                    rewind(file);
                    code = search(file,avrg,&needs);
                    switch(code)
                    {
                        case ERREMPTY:
                            fprintf(stderr,"File is empty");  //Файл пуст
                            fclose(file);
                            break;
                        case BADMARK:
                            fprintf(stderr,"Bad pointer");
                            fclose(file);
                            break;
                        case ERRNONUM:
                            fprintf(stderr,"Can't get numbers from file");   //Файл содержит не только числа
                            fclose(file);
                            break;
                        case OK:
                            fprintf(stdout,"Close to average number of sequence is %.2f",needs);
                            fclose(file);
                            break;
                    }
                    break;
            }
        }

    }
    return code;
}


