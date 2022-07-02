// $MYCLANG -fopenmp -fopenmp-targets=nvptx64 simple3.c -o simple3
// LIBOMPTARGET_DEBUG=1 ./simple3

#include <stdio.h>
#include <omp.h>

int main () {
   #pragma omp parallel
   {
      int a = omp_get_thread_num();
      #pragma omp target device(0)
      {
         printf("Result1 %d \n", a);
      }
   }
   return 0;
}