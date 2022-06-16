// $MYCLANG -fopenmp -fopenmp-targets=nvptx64 simple2_1.c -o simple2_1
// LIBOMPTARGET_DEBUG=1 ./simple2_1

#include <stdio.h>
#include <omp.h>

int main () {
    int a=100;

    printf("\n************************** PRAGMA 1************************** \n");
    #pragma omp target
    {
        a = a + 1;
        printf("Result 1 - Device: %d\n", a);
    }

    printf("\n************************** PRAGMA 2 ************************** \n");
    printf("Result 2- Host: %d\n", a);
    #pragma omp target
    {
        a = a + 1;
        printf("Result 2 - Device: %d\n", a);
    }

    printf("\n************************** PRAGMA 3 ************************** \n");
    printf("Result 3 - Host: %d\n", a);
    #pragma omp target map(tofrom: a)
    {
        a = a + 1;
        printf("Result 3 - Device: %d\n", a);
    }

    printf("\n************************** SEQUENTIAL ************************** \n");
    printf("Result Seq %d \n", a)

    for(int i=0; i<100; i++) {
        a++;
    }
    printf("Final Result %d \n", a);

    printf("\n************************** END ************************** \n");
    return 0;
}