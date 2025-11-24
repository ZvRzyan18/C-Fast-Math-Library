#include "cfm/math.h"
#include <stdint.h>

#define LOG2_0 -8.1615808498122383e-2
#define LOG2_1 6.4514236358772082e-1
#define LOG2_2 -2.1206751311142674
#define LOG2_3 4.0700907918522014
#define LOG2_4 -2.5128546239033371

#define __log2(x) ((((LOG2_0 * x + LOG2_1) * x + LOG2_2) * x + LOG2_3) * x + LOG2_4)

#define LOG2F_0 -8.161580e-2f
#define LOG2F_1 6.451423e-1f
#define LOG2F_2 -2.120675f
#define LOG2F_3 4.070090f
#define LOG2F_4 -2.512854f

#define __log2f(x) ((((LOG2F_0 * x + LOG2F_1) * x + LOG2F_2) * x + LOG2F_3) * x + LOG2F_4)

#define __isignificand(x) 4607182418800017408U | ((*(uint64_t*)&x) & 0x000FFFFFFFFFFFFF)
#define __isignificandf(x) 1065353216U | ((*(uint32_t*)&x) & 0x007FFFFF)

#define __ilogb(x) (((*(uint64_t*)&x) >> 52)-1023)
#define __ilogbf(x) (((*(uint32_t*)&x) >> 23)-127)

double cfm_log2(double x) {
 uint64_t mantissa;
 double mx;
 if((*(uint64_t*)&x >> 52) < 1023) { //x < 1.0
  x = 1.0 / x;
  mantissa = __isignificand(x);
  mx = *(double*)&mantissa;
  return -(__ilogb(x) + __log2(mx));
 }
 mantissa = __isignificand(x);
 mx = *(double*)&mantissa;
 return __ilogb(x) + __log2(mx);
}


float cfm_log2f(float x) {
 uint32_t mantissa;
 float mx;
 if((*(uint32_t*)&x >> 23) < 127) { //x < 1.0
  x = 1.0f / x;
  mantissa = __isignificandf(x);
  mx = *(float*)&mantissa;
  return -(__ilogbf(x) + __log2f(mx));
 }
 mantissa = __isignificandf(x);
 mx = *(float*)&mantissa;
 return __ilogbf(x) + __log2f(mx);
}

