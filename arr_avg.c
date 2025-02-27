#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include <immintrin.h>


//static const int length = 1024*8;
#define length 1024*1024*8
//#define PRINT_TYPE(var) printf("Type of " #var " is %s\n", #typeof(var))
#define PRINT_SIZE(var) printf("Size of " #var " is %zu bytes\n", sizeof(var))



static float a[length] = {0};


float scalarAverage() {
  float sum = 0.0;
  for (int j = 0; j < length; ++j) {
    sum += a[j];
  }

//  PRINT_SIZE(sum);

//  printf ("sum is %f, length is %d, average is %f\n", sum, length,  sum/((float) length));
  return  sum/((float) length);
}


float avxAverage () {
  __m256 sumx8 = _mm256_setzero_ps();
  for (int j = 0; j < length; j = j + 8) {
    sumx8 = _mm256_add_ps(sumx8, _mm256_loadu_ps(&(a[j])));
  }
//  PRINT_SIZE(sumx8);
  float sum = sumx8[0] + sumx8[1] +  sumx8[2] + sumx8[3] +  sumx8[4] + sumx8[5] +  sumx8[6] + sumx8[7];
//  float sum = sumx8.m256_f32[0] + sumx8.m256_f32[1] +  sumx8.m256_f32[2] + sumx8.m256_f32[3] +  sumx8.m256_f32[4] + sumx8.m256_f32[5] +  sumx8.m256_f32[6] + sumx8.m256_f32[7];
//  float sum = 0;
  return sum/((float) length);
}


float avx512AverageKernel() {
  __m512 sumx16 = _mm512_setzero_ps();
  for (int j = 0; j < length; j = j + 16) {
    sumx16 = _mm512_add_ps(sumx16, _mm512_loadu_ps(&(a[j])));
  }
  float sum = _mm512_reduce_add_ps (sumx16);
  return sum/((float) length);
}


int main()
{
	//Seed the random number generator
	srand(time(NULL));

	for (int i=0; i<length; ++i) {
		a[i] = (float)rand() /RAND_MAX;
//		printf ("a[%d] is %f\n", i, a[i]);

	}

//	float scalar_average = scalarAverage();
//	float avx_average = avxAverage();
	float avx512_average = avx512AverageKernel();

//	printf("The scalar average is: %f\n", scalar_average);
//	printf("The avx average is: %f\n", avx_average);
//	printf("The avx512 average is: %f\n", avx512_average);

  	return 0;

}

