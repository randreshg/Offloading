// $MYCLANG -fopenmp -fopenmp-targets=nvptx64 simple6.c -o simple6
// LIBOMPTARGET_DEBUG=1 ./simple6

#include <stdio.h>
#include <omp.h>
#define N 100

// TASK GRAPH DEPENDECIES
int test_task_device() {
    double sum = 0.0;
    double *h_array = (double *) malloc(N * sizeof(double));
    double *in_1 = (double *) malloc(N * sizeof(double));
    double *in_2 = (double *) malloc(N * sizeof(double));

    #pragma omp task depend(out: in_1) shared(in_1)
    {
        for(int i = 0; i < N; ++i)
            in_1[i] = 1;
    }

    #pragma omp task depend(out: in_2) shared(in_2)
    {
        for(int i = 0; i < N; ++i)
            in_2[i] = 2;
    }

    #pragma omp target enter data nowait \
        map(alloc: h_array[0:N]) map(to: in_1[0:N]) \
        map(to: in_2[0:N]) depend(out: h_array) \
        depend(in: in_1) depend(in: in_2)

    #pragma omp target nowait depend(inout: h_array)
    {
        for(int i = 0; i < N; ++i)
            h_array[i] = in_1[i] * in_2[i];
    }

    #pragma omp target exit data nowait \
        map(from: h_array[0:N]) depend(inout: h_array)

    #pragma omp task depend(in: h_array) shared(sum, h_array)
    {
        for(int i = 0; i < N; ++i)
            sum += h_array[i];
    }

    #pragma omp taskwait
    int errors = 2.0*N != sum;
    return errors;
}


int main () {
   printf("TEST: %d\n", test_task_device());
   return 0;
}

