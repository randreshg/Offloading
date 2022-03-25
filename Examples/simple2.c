// $MYCLANG -fopenmp -fopenmp-targets=nvptx64 simple2.c -o simple2
// LIBOMPTARGET_DEBUG=1 ./simple2

#include <stdio.h>
#include <omp.h>

int main () {
    int a=100;
    #pragma omp target nowait
    {
        a = a + 1;
        printf("Result1 %d \n", a);
    }
    // printf("-------------------------------------- Result %d \n", a);
    // #pragma omp target
    // {
    //     a = a + 1;
    //     printf("Result2 %d \n", a);
    // }
    printf("-------------------------------------- Result %d \n", a);
    for(int i=0; i<100; i++) {
        a++;
    }
    printf("-------------------------------------- Result %d \n", a);
    #pragma omp taskwait
    return 0;
}