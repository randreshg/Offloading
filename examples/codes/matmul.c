// clang -fopenmp -fopenmp-targets=nvptx64 matmul.c -o matmul
//export OMP_TARGET_OFFLOAD=MANDATORY
//clang -Xopenmp-target -march=sm_80 -fopenmp -fopenmp-targets=nvptx64  matmul.c -o matmul
//LIBOMPTARGET_DEBUG=1
// matmul.cpp: Matrix Multiplication Example using OpenMP Offloading 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <omp.h>

#define MAX 1000
int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX], C_SERIAL[MAX][MAX];

typedef int BOOL;
typedef int TYPE;

BOOL check_result(TYPE *actual, TYPE *expected, unsigned n) {
    for (unsigned i = 0; i < n; i++) {
        if(actual[i] != expected[i]) {
            printf("Value mismatch at index = %d. Expected: %d"
                   ", Actual: %d.\n", i, expected[i], actual[i]);
            return 0;
        }
    }
    return 1;
}

void __attribute__ ((noinline)) Compute()
{
  #pragma omp target teams distribute parallel for map(to: A, B) map(tofrom: C)
  {
    for (int i = 0; i < MAX; i++)
    for (int j = 0; j < MAX; j++)
    for (int k = 0; k < MAX; k++)
         C[i][j] += A[i][k] * B[k][j];
  }
}

int main() {
  for (int i = 0; i < MAX; i++)
    for (int j = 0; j < MAX; j++) {
      A[i][j] = i + j - 1;
      B[i][j] = i - j + 1;
    }
  printf("OK\n");
  for (int i = 0; i < MAX; i++)
  for (int j = 0; j < MAX; j++)
  for (int k = 0; k < MAX; k++)
       C_SERIAL[i][j] += A[i][k] * B[k][j];

  Compute();
  printf("OK\n");
  if (!check_result((int*) &C[0][0], (int*) &C_SERIAL[0][0], MAX * MAX)) {
    printf("FAILED\n");
    return 1;
  }

  printf("PASSED\n");
  return 0;
}
