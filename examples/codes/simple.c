#include <stdio.h>
#include <omp.h>



int main () {
    int a;
    int*ptr = &a;
    printf("host %d %x\n",*ptr, (unsigned int)ptr); //0
    #pragma omp target //nowait //1
    {
        #pragma omp teams
        {
        a++;
        }
    } //0
    #pragma omp target //nowait //1
    {
        #pragma omp teams
        {
        a++;
        }
    } //2



    #pragma omp enter data map(to:a) //1
        #pragma omp target //nowait //2
        {
            #pragma omp teams
            {
            a++;
            }
        } //1
        #pragma omp target //nowait //2
        {
            #pragma omp teams
            {
            a++;
            }
        } //1
        #pragma omp target //nowait //2
        {
            #pragma omp teams
            {
            a++;
            a++;
            a++;
            a++;
            a++;
            }
        }//1
    #pragma omp exit data map(from:a) //1
    printf("hola"); //0
    fflush(stdout);
    
    return 0;
}