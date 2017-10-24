/*****试验double与float的性能差异*****/
/*  Author  : Renleilei              */
/*  Date    : 2017/10/24             */
/*  Version : 1.00                   */
/*  Function: 使用100M的数据测试性能 */
/*************************************/

#include <x86intrin.h> 
#include <stdio.h> 
#include <time.h>

#define SIZE 100000000

typedef float F_TYPE; 
typedef unsigned long long int uint64;
 
double sum_double_avx(const double* pbuf, uint64 cntbuf)
{
    double s = 0;
    uint64 nBlockWidth = 4;
    uint64 cntBlock = cntbuf / nBlockWidth;
    uint64 cntRem = cntbuf % nBlockWidth;
    __m256d xfdSum = _mm256_setzero_pd();
    __m256d xfdLoad;    
    const double* p = pbuf;
    const double* q;
    //AVX      
    for(uint64 i=0; i<cntBlock; ++i)
    {     
 	    xfdLoad = _mm256_load_pd(p);
        xfdSum  = _mm256_add_pd(xfdSum, xfdLoad);
   	    p += nBlockWidth;    
    }
     
    q = (const double*)&xfdSum;
    s = q[0] + q[1] + q[2] + q[3];
    for(uint64 i=0; i<cntRem; ++i)
    {
    	s += p[i];
    }
     
    return s;
}

float sum_single_avx(const float* pbuf, uint64 cntbuf)
{    
	  float s = 0;
	  uint64 nBlockWidth = 8;
	  uint64 cntBlock = cntbuf / nBlockWidth;
	  uint64 cntRem = cntbuf % nBlockWidth;
	  __m256 yfsSum = _mm256_setzero_ps();
	  __m256 yfsLoad;
	  const float* p = pbuf;
	  const float* q;
	  //AVX
	  for(uint64 i=0; i<cntBlock; ++i)
	  {
	  	  yfsLoad = _mm256_load_ps(p);
	  	  yfsSum  = _mm256_add_ps(yfsSum, yfsLoad);
	  	  p += nBlockWidth;
	  }
	  
	  q = (const float*)&yfsSum;
	  s = q[0] + q[1] + q[2] + q[3] + q[4] + q[5] + q[6] + q[7];
	  for(uint64 i=0; i<cntRem; ++i)
	  {
	  	  s += p[i];
	  }
	  
	  return s;
} 

int main()
{    
	 F_TYPE* array = (F_TYPE*)malloc(sizeof(F_TYPE) * SIZE);
	 if(array == NULL)
         exit(-1);
	  
	 F_TYPE sum = 0;
	 for(uint64 i = 0; i < SIZE; i++)
	 {
	     array[i] = (F_TYPE)0.01;
	 }
	  
	 if(sizeof(F_TYPE) == sizeof(double))
	//     printf("sum = %f\n", sum_double_avx(array, SIZE));
		 printf("double");
	 else
	     printf("sum = %f\n", sum_single_avx(array, SIZE));
	  	
	 free(array);
	 return 0;
}
