// $MYCLANG -fopenmp -fopenmp-targets=nvptx64 -march=sm70 simple.c -o simple
// LIBOMPTARGET_DEBUG=1 ./simple

#include <stdio.h>
#include <omp.h>

int main () {
    int a[3] = {0, 0, 0};
    #pragma omp target map(to:a)
    {
        a[0] = 10;
        printf("Result in target %d \n", a[0]);
    }


    printf("Result %d \n", a[0]);
    return 0;
}