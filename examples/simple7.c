// $MYCLANG -fopenmp -fopenmp-targets=nvptx64 simple7.c -o simple7
// LIBOMPTARGET_DEBUG=1 ./simple7

#include <stdio.h>
#include <omp.h>
#define N 10

//MULTIPLE DEVICES
int test_map_device() {
   int num_dev = omp_get_num_devices(), sum[num_dev], errors = 0;
   int *h_matrix = (int *) malloc(num_dev*N*sizeof(int));

   for(int dev = 0; dev < num_dev; ++dev) {
      #pragma omp target data map(from: h_matrix[dev*N:N]) device(dev)
      {
         #pragma omp target map(from: h_matrix[dev*N:N]) device(dev)
         {
            for(int i = 0; i < N; ++i)
               h_matrix[dev*N + i] = dev;
         } // end target
      } //end target data
   }

   //Checking results
   errors = 0;
   for(int dev = 0; dev < num_dev; ++dev) {
      sum[dev] = h_matrix[dev*N + 0];
      for(int i = 1; i < N; ++i)
         sum[dev] += h_matrix[dev*N + i];
      errors |= (dev * N != sum[dev]);
   }
   return errors;
}


int main () {
   printf("TEST DONE: %d\n", test_map_device());
   return 0;
}