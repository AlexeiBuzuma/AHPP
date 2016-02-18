#include "func.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <omp.h>

void raise_memory_error()
{
    err(EXIT_FAILURE, "Memory error!");
}

TYPE *alloc_array(size_t nmemb)
{
    TYPE *arr = (TYPE*)aligned_alloc (16, nmemb * sizeof(TYPE));
    if(arr == NULL)
        raise_memory_error();

    return arr;
}

char *alloc_string(size_t nmemb)
{
  char* str = (char*)calloc(nmemb, sizeof(char));
  if(str == NULL)
    raise_memory_error();
  return str;
}

TYPE **alloc_matrix(size_t nmemb)
{
    TYPE **arr = (TYPE**)malloc(sizeof(TYPE *) * nmemb);
    if(NULL == arr)
        raise_memory_error();

    for (size_t i = 0; i < nmemb; i++)
    {
        arr[i] = alloc_array(nmemb);
        if (NULL == arr[i])
            raise_memory_error();
    }

    return arr;
}

void free_matrix(TYPE **arr, size_t nmemb)
{
    if(NULL == arr)
        return;

    for(size_t i = 0; i < nmemb; i++)
    {
        if(NULL == arr[i])
            raise_memory_error();

        free(arr[i]);

        if(NULL == arr[i])
            raise_memory_error();

    }
}

void fill_matrix(TYPE **matrix, size_t nmemb)
{
  for(size_t i = 0; i < nmemb; i++)
    for(size_t j = 0; j < nmemb; j++)
        matrix[i][j] = (i + j)/(TYPE)nmemb;
}

void fill_matrix_with_zeros(TYPE **matrix, size_t nmemb)
{
  for(size_t i = 0; i < nmemb; i++)
    for(size_t j = 0; j < nmemb; j++)
        matrix[i][j] = 0;
}

void print_matrix(TYPE **matrix, size_t nmemb)
{
    for(size_t i = 0; i < nmemb; i++ )
    {
        for(size_t j = 0; j < nmemb; j++)
            printf("%g ", matrix[i][j]);
        puts("");
    }
}

size_t convert_to_size_t(char* str)
{
  char* endptr = alloc_string(strlen(str));
  size_t n = strtoll(str, &endptr, 10);
  if (0 == strcmp(endptr, "\0"))
    return n;
  else
    errx(EXIT_FAILURE, "Failed to convert N to size_t");
}
