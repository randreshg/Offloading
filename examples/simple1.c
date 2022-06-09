// $MYCLANG -fopenmp -fopenmp-targets=nvptx64 simple1.c -o simple1
// LIBOMPTARGET_DEBUG=1 ./simple1

#include <stdio.h>
#include <omp.h>

int main () {
    int a=100;
    printf("************************** PRAGMA 1 ************************** \n");
    #pragma omp target map(tofrom:a)
    {
        a = a + 1;
        printf("Result1 %d \n", a);
    }
    printf("Result %d \n", a);

    printf("************************** PRAGMA 2 ************************** \n");
    #pragma omp target map(tofrom:a)
    {
        a = a + 10;
        printf("Result2 %d \n", a);
    }
    printf("Result %d \n", a);
    return 0;
}
