#ifndef FUNCTIONS_H
#define FUNCTIONS_H


// part 1
int len_of_array(FILE *file, int *count);
int array_filling(int *begin, int *end, FILE *file);
int array_generate(FILE *file, int *count, int **array);
int counting(int *begin, int *end, int *min);

void len_of_array_test(int right_count, int right_code, FILE *file, char *string);
void array_filling_test(int *right_array, int count, int right_code, FILE *file, char *string);
void counting_test(int right_result, int right_code, int count, int *array, char *string);

// part 2
typedef int (*compare_t)(const void *, const void *);

void minmax_search(int *begin, int *end, int **min, int **max);
int *filter_array(int *begin, int *end, int *count, int *out_error);

int compare_int(const void *a, const void *b);
void swap(void *a, void *b, size_t size);
void my_sort(void *base, size_t num, size_t size, compare_t compare);

void print_array(int *array, int count);
void print_to_file(FILE *file, int *array, int count);

#endif // FUNCTIONS_H