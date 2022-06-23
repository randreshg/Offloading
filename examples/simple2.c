// $MYCLANG -fopenmp -fopenmp-targets=nvptx64 simple2.c -o simple2
// LIBOMPTARGET_DEBUG=1 ./simple2

#include <stdio.h>
#include <omp.h>

int main () {
    int a=100;

    printf("\n************************** PRAGMA 1************************** \n");
    #pragma omp target
    {
        a = a + 1;
        printf("Result1 %d \n", a);
    }

    printf("\n************************** PRAGMA 2 ************************** \n");
    printf("Result %d \n", a);
    #pragma omp target
    {
        for(int i = 0; i<1000000; i++)
            a = a + 1;
        printf("Result2 %d \n", a);
    }

    // printf("\n************************** SEQUENTIAL ************************** \n");
    // printf("Result %d \n", a);
    // for(int i=0; i<100; i++) {
    //     a++;
    // }
    // printf("Result %d \n", a);
    
    
    printf("\n************************** END ************************** \n");
    return 0;
}