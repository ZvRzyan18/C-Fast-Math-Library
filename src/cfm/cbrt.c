#include "cfm/math.h"
#include <stdint.h>

// cbrt(x) = exp2((1.0/3.0) * log2(x));

#define CBRT_EXPONENT 0.333333333333333333333
#define CBRTF_EXPONENT 0.333333f


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

#define EXP2_0 1.3697664475809267e-2
#define EXP2_1 5.1690358205939469e-2
#define EXP2_2 2.4163844572498163e-1
#define EXP2_3 6.9296612266139567e-1
#define EXP2_4 1.000003704465937

#define __exp2(x) ((((EXP2_0 * x + EXP2_1) * x + EXP2_2) * x + EXP2_3) * x + EXP2_4)

#define EXP2F_0 1.369766e-2f
#define EXP2F_1 5.169035e-2f
#define EXP2F_2 2.416384e-1f
#define EXP2F_3 6.929661e-1f
#define EXP2F_4 1.000003f

#define __exp2f(x) ((((EXP2F_0 * x + EXP2F_1) * x + EXP2F_2) * x + EXP2F_3) * x + EXP2F_4)

#define __isignificand(x) 4607182418800017408U | ((*(uint64_t*)&x) & 0x000FFFFFFFFFFFFF)
#define __isignificandf(x) 1065353216U | ((*(uint32_t*)&x) & 0x007FFFFF)

#define __ilogb(x) (((*(uint64_t*)&x) >> 52)-1023)
#define __ilogbf(x) (((*(uint32_t*)&x) >> 23)-127)

double cfm_cbrt(double x) {
 uint64_t m;
 double mx;
 //log2 implementation
 if((*(uint64_t*)&x >> 52) < 1023) { //x < 1.0
  x = 1.0 / x;
  m = __isignificand(x);
  mx = *(double*)&m;
  x = -CBRT_EXPONENT * (__ilogb(x) + __log2(mx));
 } else {
  m = __isignificand(x);
  mx = *(double*)&m;
  x = CBRT_EXPONENT * (__ilogb(x) + __log2(mx));
 }
 //exp2 implementation
 if((*(uint64_t*)&x) & 0x8000000000000000) {// x < 0.0f
  *(uint64_t*)&x &= 0x7FFFFFFFFFFFFFFF;
  m = ((uint64_t)(1023 + ((uint64_t)(x))) << 52);
  x -= (uint64_t)x;
  return 1.0 / ((*(double*)(&m)) * __exp2(x));
 }
 m = ((uint64_t)(1023 + ((uint64_t)(x))) << 52);
 x -= (uint64_t)x;
 return (*(double*)(&m)) * __exp2(x);
}


float cfm_cbrtf(float x) {
 uint32_t m;
 float mx;
 //log2 implementation
 if((*(uint32_t*)&x >> 23) < 127) { //x < 1.0
  x = 1.0f / x;
  m = __isignificandf(x);
  mx = *(float*)&m;
  x = -CBRTF_EXPONENT * (__ilogbf(x) + __log2f(mx));
 } else {
  m = __isignificandf(x);
  mx = *(float*)&m;
  x = CBRTF_EXPONENT * (__ilogbf(x) + __log2f(mx));
 }
 //exp2 implementation
 if((*(uint32_t*)&x) & 0x80000000) {// x < 0.0f
  *(uint32_t*)&x &= 0x7FFFFFFF;
  m = ((uint32_t)(127 + ((uint32_t)(x))) << 23);
  x -= (uint64_t)x;
  return 1.0f / ((*(float*)(&m)) * __exp2f(x));
 }
 m = ((uint32_t)(127 + ((uint64_t)(x))) << 23);
 x -= (uint64_t)x;
 return (*(float*)(&m)) * __exp2f(x);
}

