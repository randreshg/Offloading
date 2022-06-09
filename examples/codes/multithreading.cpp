// clang multithreading.cpp -o m -fopenmp
#include <stdlib.h>

int main() {
    size_t n = 1000000000;
    double *A = (double*) malloc(n*sizeof(double));
    double *B = (double*) malloc(n*sizeof(double));
    double *C = (double*) malloc(n*sizeof(double));
    double scalar = 2;

    #pragma omp parallel for
    for (size_t i = 0; i < n; i++) {
        B[i] = 1;
        C[i] = i;
    }

    #pragma omp parallel for
    for(size_t i = 0; i < n; i++) {
        A[i] = B[i] + scalar * C[i];
    }

    free(A);
    free(B);
    free(C);

    return 0;
}