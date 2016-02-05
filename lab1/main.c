#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <errno.h>

#define N 5
#define TYPE double


void raise_memory_error()
{
    perror("Memory error");
    exit(EXIT_FAILURE);
}

TYPE * alloc_array(size_t nmemb)
{
    TYPE *arr = (TYPE*)malloc(sizeof(TYPE) * nmemb);
    if(arr == NULL)
        raise_memory_error();

    return arr;
}

TYPE **alloc_matrix(size_t nmemb)
{
    TYPE **arr = (TYPE**)malloc(sizeof(TYPE *) * nmemb);
    if(NULL == arr)
        raise_memory_error();

    for (int i = 0; i < nmemb; i++)
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

    for(int i = 0; i < nmemb; i++)
    {
        if(NULL == arr[i])
            raise_memory_error();

        free(arr[i]);

        if(NULL == arr[i])
            raise_memory_error();

    }
}

void randomize_matrix(TYPE **matrix, size_t nmemb)
{
    for(int i = 0; i < nmemb; i++)
        for(int j = 0; j < nmemb; j++)
            matrix[i][j] = (TYPE)rand()/(TYPE)RAND_MAX;
}


void print_matrix(TYPE **matrix, size_t nmemb)
{
    for(int i = 0; i < nmemb; i++ )
    {
        for(int j = 0; j < nmemb; j++)
            printf("%f ", matrix[i][j]);
        puts("");
    }
}

void mul_matrix(TYPE **res, TYPE **m1, TYPE **m2, size_t nmemb)
{
    for(int i = 0; i < nmemb; i++)
        for(int j = 0; j < nmemb; j++)
            for(int k = 0; k < nmemb; k++)
                res[i][j] += m1[i][k] * m2[k][j];
}

int main(void)
{
    srand(time(NULL));
    // time()

    TYPE **a = alloc_matrix(N);
    TYPE **b = alloc_matrix(N);
    TYPE **c = alloc_matrix(N);


    // print_matrix(a, N);
    // puts("");
    // print_matrix(b, N);
    // puts("");
    // print_matrix(c, N);
    // puts("");

    randomize_matrix(a, N);
    randomize_matrix(b, N);
    randomize_matrix(c, N);
    //
    // print_matrix(a, N);
    // puts("");
    // print_matrix(b, N);
    // puts("");
    // print_matrix(c, N);
    // puts("");

    mul_matrix(c, a, b, N);

    print_matrix(c, N);

    free_matrix(a, N);
    free_matrix(b, N);
    free_matrix(c, N);

    return 0;
}
