// $MYCLANG -fopenmp -fopenmp-targets=nvptx64 simple1_1.c -o simple1_1
// clang -fopenmp -fopenmp-targets=nvptx64-nvidia-cuda -Xopenmp-target -march=sm_70 simple1_1.c -o simple1_1
// LIBOMPTARGET_DEBUG=1 ./simple1_1

#include <stdio.h>
#include <omp.h>

int main () {

    int a=100;
    printf("************************** DEVICE %d ************************** \n", 0);
    printf("************************** PRAGMA 1 ************************** \n");
    #pragma omp target map(tofrom:a) device(0)
    {
        a = a + 1;
        printf("Result1 %d \n", a);
    }
    printf("Result %d \n", a);
    int b = 10;
    printf("************************** PRAGMA 2 ************************** \n");
    #pragma omp target map(tofrom:b) device(1)
    {
        b = b + 10;
        printf("Result2 %d \n", b);
    }
    printf("Result %d \n", a);
    printf("********************************************************* \n\n");
    
    return 0;
}
