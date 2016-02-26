#include "func.h"
#include <stdio.h>
#include <omp.h>
#include <time.h>

#define N_STRING argv[1]

#ifdef AHPP_INTRINSIC
#include <emmintrin.h>
void mul_matrix(TYPE **res, TYPE **m1, TYPE **m2, size_t nmemb)
{
  for(size_t i = 0; i < nmemb; i++)
  {
    TYPE* res_line = res[i];
    for(size_t j = 0; j < nmemb; j++)
    {
      TYPE m1_value = m1[i][j];
      TYPE* m2_line = m2[j];

      __m128 v1, v2, v3;
      v1 = _mm_load1_ps(&m1_value);
      for(size_t k = sizeof(TYPE); k < nmemb; k += 2*sizeof(TYPE))
      {
        v2 = _mm_load_ps(res_line + k);
        v3 = _mm_load_ps(m2_line + k);
        v3 = _mm_mul_ps(v3, v1);
        v2 = _mm_add_ps(v2, v3);
        _mm_store_ps(res_line + k, v2);

        v2 = _mm_load_ps(res_line + k - sizeof(TYPE));
        v3 = _mm_load_ps(m2_line + k- sizeof(TYPE));
        v3 = _mm_mul_ps(v3, v1);
        v2 = _mm_add_ps(v2, v3);
        _mm_store_ps(res_line + k- sizeof(TYPE), v2);
      }
    }
  }
}
#endif

#ifdef AHPP_NO_INTRINSIC
void mul_matrix(TYPE **res, TYPE **m1, TYPE **m2, size_t nmemb)
{
  #pragma omp parallel for shared(m1, m2, res)
  for(size_t i = 0; i < nmemb; i++)
      for(size_t k = 0; k < nmemb; k++)
          for(size_t j = 0; j < nmemb; j++)
              res[i][j] += m1[i][k] * m2[k][j];
}
#endif

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
      errx(EXIT_FAILURE, "You must supply N as argument");
    }

    size_t N = convert_to_size_t(N_STRING);

    TYPE **a = alloc_matrix(N);
    TYPE **b = alloc_matrix(N);
    TYPE **c = alloc_matrix(N);

    fill_matrix(a, N);
    fill_matrix(b, N);
    fill_matrix_with_zeros(c, N);

    #ifndef _OPENMP
    clock_t start = clock();
    clock_check(start);
    #endif
    #ifdef _OPENMP
    double start = omp_get_wtime();
    #endif
    mul_matrix(c, a, b, N);
    #ifndef _OPENMP
    clock_t end = clock();
    double working_time = (double)(end - start) / CLOCKS_PER_SEC;
    #endif
    #ifdef _OPENMP
    double end = omp_get_wtime();
    double working_time = end - start;
    #endif
    printf("Working time: %g s\n", working_time);
    print_matrix(c, N);

    free_matrix(a, N);
    free_matrix(b, N);
    free_matrix(c, N);

    return 0;
}
