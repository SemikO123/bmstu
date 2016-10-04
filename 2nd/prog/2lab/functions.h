#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int len_of_array(FILE *file, int *count, int **array);
int array_filling(int *begin, int *end, FILE *file);
int counting(int *begin, int *end, int *min);

void len_of_array_test(int right_count, int right_code, FILE *file, char *string);
void array_filling_test(int *right_array, int count, int right_code, FILE *file, char *string);
void counting_test(int right_result, int right_code, int count, int *array, char *string);

#endif // FUNCTIONS_H