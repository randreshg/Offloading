// $MYCLANG -fopenmp -fopenmp-targets=nvptx64 simple.c -o simple
// LIBOMPTARGET_DEBUG=1 ./simple

#include <stdio.h>
#include <omp.h>

int main () {
    int a = 100;
    #pragma omp target
    {
        a++;
    }

    printf("Result %d \n", a);
    return 0;
}