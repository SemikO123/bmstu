#ifndef FUNC_H
#define FUNC_H

void input_numbers(char *number, char *znak);
void integer_array_generate(const char *integer_num, int *integer_number, int *counter);
void float_array_generate(const char *array_char, int *array_int, int *exponent, int *counter);
int count_of_digits(int number);
void counting(const int *array_int, int int_len, const int *array_float, int float_len, int *result,  int *flag);
void normalize(int *array, int *result, int *exponent, int count, int *flag);
void print_float(char znak, int *mantissa, int exponent, int len_mantissa);
void rounding(int *array);

#endif // FUNC_H