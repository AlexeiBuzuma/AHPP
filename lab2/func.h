#include <stdlib.h>
#include <err.h>
#pragma once
#define TYPE double
void raise_memory_error();
TYPE *alloc_array(size_t nmemb);
char *alloc_string(size_t nmemb);
TYPE **alloc_matrix(size_t nmemb);
void free_matrix(TYPE **arr, size_t nmemb);
void fill_matrix(TYPE **matrix, size_t nmemb);
void fill_matrix_with_zeros(TYPE **matrix, size_t nmemb);
void print_matrix(TYPE **matrix, size_t nmemb);
size_t convert_to_size_t(char* str);

void mul_matrix(TYPE **res, TYPE **m1, TYPE **m2, size_t nmemb);

#define clock_check(clocks) if (-1 == clocks) {\
    err(EXIT_FAILURE, "Clock error");\
  }
