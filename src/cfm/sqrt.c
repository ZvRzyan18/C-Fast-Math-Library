#include "cfm/math.h"
#include <stdint.h>

//TODO : implement using cpu specific instruction
#if defined(__aarch64__)

__asm__(
 ".type cfm_sqrt, @function \n"

 ".global cfm_sqrt \n"
 "cfm_sqrt: \n"
 "fsqrt d0, d0 \n"
 "ret \n"
);

__asm__(
 ".type cfm_sqrtf, @function \n"

 ".global cfm_sqrtf \n"
 "cfm_sqrtf: \n"
 "fsqrt s0, s0 \n"
 "ret \n"
);

#elif defined(__x86_64__)


double cfm_sqrt(double x) {
 __asm__ volatile (
  "sqrtsd %[in], %[out]"
  : [out] "=x" (x)
  : [in] "x" (x)
  : "xmm0"
 );
 return x;
}

float cfm_sqrtf(float x) {
 __asm__ volatile (
  "movss %[in], %%xmm0 \n"
  "sqrtss %%xmm0, %%xmm0 \n"
  "movss %%xmm0, %[out]"
  : [out] "=m" (x)
  : [in] "m" (x)
  : "xmm0"
 );
 return x;
}

#else

//---------------DOUBLE------------------//

double cfm_sqrt(double x) {
/*
 Quake III fast inv sqrt
*/
 uint64_t mx = 0x5fe6eb50c7b537a9 - (*((uint64_t*)&x) >> 1);
 const double x_half = x * 0.5;
 double f = *(double*)&mx;
 f = (f * (1.5 - (x_half * f * f)));
 f = (f * (1.5 - (x_half * f * f)));
 return x * f;
}

//---------------FLOAT------------------//

float cfm_sqrtf(float x) {
/*
 Quake III fast inv sqrt
*/
 uint32_t mx = 0x5f3759df - ((*(uint32_t*)&x) >> 1);
 const float x_half = x * 0.5f;
 float f = *(float*)&mx;
 f = (f * (1.5 - (x_half * f * f)));
 f = (f * (1.5 - (x_half * f * f)));
 return x * f;
}

#endif
