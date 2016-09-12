#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int ReadArr(float arr[],int n, FILE *file, int *count);
void Average(const float arr[],int n, float *avrg);
void NewArrGen(const float arr[], FILE *file, int n, float avrg);



#endif // FUNCTIONS_H