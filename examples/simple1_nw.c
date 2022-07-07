// $MYCLANG -fopenmp -fopenmp-targets=nvptx64 simple1_nw.c -o simple1_nw
// clang -fopenmp -fopenmp-targets=nvptx64-nvidia-cuda -Xopenmp-target -march=sm_70 simple1.c -o simple1
// LIBOMPTARGET_DEBUG=1 ./simple1_nw

#include <stdio.h>
#include <omp.h>

int main () {
    int a=100;
    printf("************************** PRAGMA 1 ************************** \n");
    #pragma omp target map(tofrom:a) nowait
    {
        a = a + 1;
        printf("Result1 %d \n", a);
    }
    printf("Result %d \n", a);

    printf("************************** PRAGMA 2 ************************** \n");
    #pragma omp target map(tofrom:a) nowait
    {
        a = a + 10;
        printf("Result2 %d \n", a);
    }
    printf("Result %d \n", a);

    printf("\n************************** TASK WAIT ************************** \n");
    #pragma omp taskwait

    printf("\n************************** SEQUENTIAL ************************** \n");
    printf("Result sequential %d \n", a);
    for(int i=0; i<100; i++) {
        a++;
    }
    printf("Result %d \n", a);
    return 0;
}
