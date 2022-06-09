// clang++ -fopenmp -fopenmp-targets=nvptx64 offloading.cpp -o offloading

#include <stdlib.h>

int main() {
    int n = 1000000000;
    double *A = (double*) malloc(n*sizeof(double));
    double *B = (double*) malloc(n*sizeof(double));
    double *C = (double*) malloc(n*sizeof(double));
    double scalar = 2;

    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        B[i] = 1;
        C[i] = i;
    }
    //Run code on the GPU using one thread
    #pragma omp target
    for (int i = 0; i < n; i++) {
        A[i] = B[i] + scalar * C[i];
    }

    free(A);
    free(B);
    free(C);

    return 0;
}