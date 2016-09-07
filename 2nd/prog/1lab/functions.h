#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int ReadArr(float arr[],int n, FILE *file, int *count);
int Average(const float arr[],int n, float *avrg);
int NewArrGen(const float arr[], float newarr[], int n, int *j, float avrg);

#endif // FUNCTIONS_H