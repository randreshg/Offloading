//https://www.ibm.com/docs/en/xl-c-and-cpp-linux/13.1.5?topic=parallelization-pragma-omp-target-data

double *array = (double*)malloc(sizeof(double)*N);
// Target data region
#pragma omp target data map(from: array[0:N])
{
  // The first target region
  #pragma omp target map(tofrom: array[0:N])
  {
     for (int i=0; i<N; i++)array[i] = double(i) / N;
  }
  // The second target region
  #pragma omp target map(tofrom: array[0:N])
  {
     for (int i=0; i<N; i++) array[i] = 1.0 / array[i];
  }
}
for (int i=0; i<N; i++) sum += array[i];