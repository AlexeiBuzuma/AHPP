#include <stdint.h>
#include <errno.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define ACCESS_NUMBER           500
#define MATRIX_ACCESS_NUMBER    5000

#define TYPE int

double investigate_time_of_passing_through_array(size_t block_size, size_t offset, size_t n)
{
	if(0 == block_size || 0 == offset)
	{
		return -1;
	}

    uint8_t *data = calloc(offset * n, sizeof(uint8_t));
    if(NULL == data)
    {
        perror("Memory error");
        return -1;
    }

    size_t line_length = block_size / n;
    size_t index;
    clock_t start;
    double result_time;

    start = clock();
    for(size_t test_number = 0; test_number < ACCESS_NUMBER; test_number++)
    {
        for(size_t i = 0; i < line_length; i++)
        {
            for(size_t j = 0; j < n; j++)
            {
                index = n*offset + j;
                data[j] = i;
            }      
        }
    }
    result_time = (double)(clock() - start) / CLOCKS_PER_SEC;
    result_time /= ACCESS_NUMBER;

    free(data);

    return result_time;
}

void raise_memory_error()
{
    perror("Memory error");
    exit(EXIT_FAILURE);
}

TYPE *alloc_array(int size)
{
    TYPE *arr = (TYPE*)calloc(size, sizeof(TYPE));
    if(arr == NULL)
        raise_memory_error();

    return arr;
}

TYPE ** alloc_matrix(int size)
{
    TYPE **arr = (TYPE**)malloc(sizeof(TYPE *) * size);
    if(NULL == arr)
        raise_memory_error();

    for (int i = 0; i < size; i++)
    {
        arr[i] = alloc_array(size);
        if (NULL == arr[i])
            raise_memory_error();
    }

    return arr;
}

void process_element(TYPE *element)
{
    *element += 13;
}

void free_matrix(TYPE **arr, int size)
{
    if(NULL == arr)
        return;

    for(int i = 0; i < size; i++)
    {
        if(NULL == arr[i])
            raise_memory_error();

        free(arr[i]);

        if(NULL == arr[i])
            raise_memory_error();

    }
}

double processing_of_double_pointer_matrix(int size_of_matrix, int is_logging)
{   
    TYPE **matrix = alloc_matrix(size_of_matrix);

    FILE *processing_matrix_result = fopen("matrix_processing_result.log", "w");
    if(NULL == processing_matrix_result)
    {
        perror("File error");
        exit(EXIT_FAILURE);
    }

    srand(time(NULL));

    int i = 0, j = 0;
    double all_time = 0;
    clock_t start;

    for(int k = 0; k < MATRIX_ACCESS_NUMBER; k++)
    {
        i = rand() % size_of_matrix;
        j = rand() % size_of_matrix;

        start = clock();
        process_element(&matrix[i][j]);
        all_time += (double)(clock() - start) / CLOCKS_PER_SEC;

        if(1 == is_logging)
        {
            fprintf(processing_matrix_result, "%d %d\n", i, j);
        }
        
    }

    free_matrix(matrix, size_of_matrix);
    fclose(processing_matrix_result);

    return all_time;
}