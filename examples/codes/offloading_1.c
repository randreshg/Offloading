// clang -fopenmp -fopenmp-targets=nvptx64 offloading_1.c -o offloading_1
#include <stdio.h>
#include <omp.h>

int main()
{
    int ret = 0;
    #pragma omp target map(ret) nowait
    {
        for (int i = 0; i<1000; i++)
        for (int j = 0; j<1000; j++)
            ret--;
        if(ret <= 0)
            ret = 1;
        printf("Device ret = %d\n", ret);
    }
    printf("Before explicit offload sync: ret = %d\n", ret);
    #pragma omp taskwait
    printf("After explicit offload sync: ret = %d\n", ret);
    
    return 0;
}