#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int ReadArr(float arr[],int n, FILE *file, int *count);
void Average(const float arr[],int n, float *avrg);
void NewArrGen(const float arr[], float newarr[], int n, int *j, float avrg);



#endif // FUNCTIONS_H