# arr-avg-avx512
functions to compare avx512, avx and scalar

The main purpose of this is to compare the different implementation of doing an array average. 
1. Scalar
2. AVX256
3. AVX512

The codes are largely based on this Microsoft blog:
https://devblogs.microsoft.com/cppblog/accelerating-compute-intensive-workloads-with-intel-avx-512/

run script will execute a.out on all the cores of the CPU, the first argument will be how long does the program run for. 
./run.sh 200 will loop the calculation for 200s. 

To generate a.out:
 gcc -mavx512f arr_avg.c

 To get assembly output and examine to make sure we are using avx512:
  gcc -mavx512f -S arr_avg.c
