#ifndef _MY_SNPRINTF_H_
#define _MY_SNPRINTF_H_

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define S 1
#define O 2
#define C 3

int get_type(char specificator);
int length_num(int n);
char *to_octal(int num);
int strlen_f(const char *string);
char *strtochr(char ch, char *string);
int my_snprintf(char *s, size_t n, const char *format, ...);


#endif