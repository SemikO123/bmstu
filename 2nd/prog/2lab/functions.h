#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int len_of_array(FILE *file, int *count);
int *array_generate(int *count);
int array_filling(int *begin, int *end, FILE *file);
int counting(int *begin, int *end, int *min);

#endif // FUNCTIONS_H