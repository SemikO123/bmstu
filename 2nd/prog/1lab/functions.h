#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int ReadArr(float arr[],int n, FILE *file, int *count);
void Average(const float arr[],int n, float *avrg);
void NewArrGen(const float *arr,  int n, float avrg, float *newarr, int *j);
void ArrToFile(const float *newarr, int *j, FILE *file);



#endif // FUNCTIONS_H