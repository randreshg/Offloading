// $MYCLANG -fopenmp -fopenmp-targets=nvptx64 simple3.c -o simple3
// LIBOMPTARGET_DEBUG=1 ./simple3

#include <stdio.h>
#include <omp.h>

int main () {
    int a=100;
   
   printf("\n************************** TARGET DATA MAP ************************** \n");
   #pragma omp target data map(tofrom: a)
   {
      printf("\n************************** PRAGMA 1************************** \n");
      printf("Result 1 - %d \n", a);
      #pragma omp target
      {
         //a = a + 1;
         printf("Result1 %d \n", 0);
      }
      
      printf("\n************************** PRAGMA 2 ************************** \n");
      printf("Result 2 - %d \n", a);
      #pragma omp target
      {
         a = a + 1;
         printf("Result2 %d \n", a);
      }

      printf("\n************************** PRAGMA 3 ************************** \n");
      printf("Result 3 - %d \n", a);
      #pragma omp target map(tofrom: a)
      {
         a = a + 1;
         printf("Result3 %d \n", a);
      }
      #pragma omp target update from(a)
      printf("\n************************** SEQUENTIAL ************************** \n");
      printf("Result sequential %d \n", a);
      for(int i=0; i<100; i++) {
         a++;
      }
      printf("Result %d \n", a);
      printf("\n************************** TASK WAIT ************************** \n");
      //#pragma omp taskwait
   }
   printf("\n************************** RESULT ************************** \n");
   printf("Result final %d \n", a);

   return 0;
}