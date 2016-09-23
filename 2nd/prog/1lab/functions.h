#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int read_array(float arr[],int n, FILE *file, int *count);
void count_average(const float arr[],int n, float *avrg);
void new_array_generate(const float *arr,  int n, float avrg, float *newarr, int *j);
void array_to_file(const float *newarr, int *j, FILE *file);



#endif // FUNCTIONS_H