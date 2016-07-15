#include <stdio.h>
#include "2pr.h"
#include "err.h"
#include "function.h"

int main(int argc, char** argv)
{
    int a,b,sum;
    printf("Input 2 numbers:");
    scanf("%d %d",&a,&b);
    summa(a,b,&sum);
    printf("Summa = %d\n",sum);
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
                case ERRNONUM:
                    fprintf(stderr,"Can't get numbers from file");   //Файл содержит не только числа
                    fclose(file);
                    break;
                case BADMARK:
                    fprintf(stderr,"Bad pointer");
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
                        case ERRNONUM:
                            fprintf(stderr,"Can't get numbers from file");   //Файл содержит не только числа
                            fclose(file);
                            break;
                        case BADMARK:
                            fprintf(stderr,"Bad pointer");
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


