#include "cfm/math.h"
#include <stdint.h>

//TODO : implement using cpu specific instruction
#if defined(__aarch64__)

__asm__(
//".p2align	2 \n"
 ".type cfm_round, @function \n"

 ".global cfm_round \n"
 "cfm_round: \n"
 "frintn d0, d0 \n"
 "ret \n"
);

__asm__(
 ".type cfm_roundf, @function \n"

 ".global cfm_roundf \n"
 "cfm_roundf: \n"
 "frintn s0, s0 \n"
 "ret \n"
);

#elif (__x86_64__)

double cfm_round(double x) {
 __asm__ volatile (
  "movsd %[input], %%xmm0 \n"
  "roundsd $0, %%xmm0, %%xmm0 \n"
  "movsd %%xmm0, %[output]"
  : [output]"=x"(x)
  : [input] "x"(x)
  : "xmm0"
 );
 return x;
}

float cfm_roundf(float x) {
 __asm__ volatile (
  "movss %[input], %%xmm0 \n"
  "roundss $0, %%xmm0, %%xmm0 \n"
  "movss %%xmm0, %[output]"
  : [output]"=m"(x)
  : [input] "m"(x)
  : "xmm0"
 );
 return x;
}


#else

//---------------DOUBLE------------------//

double cfm_round(double x) {
 if(*(uint64_t*)&x & 0x8000000000000000) {
  if((-x - (int64_t)-x) >= 0.5)
   return (double)(((int64_t)x)-1);
 return (double)((int64_t)x);
 }
 if((x - (int64_t)x) > 0.5)
  return (double)(((uint64_t)x)+1);
 return (double)((uint64_t)x);
}

//---------------FLOAT------------------//

float cfm_roundf(float x) {
 if(*(uint32_t*)&x & 0x80000000) {
  if((-x - (int64_t)-x) >= 0.5f)
   return (float)(((int64_t)x)-1);
 return (float)((int64_t)x);
 }
 if((x - (int64_t)x) > 0.5)
  return (float)(((uint64_t)x)+1);
 return (float)((uint64_t)x);
}

#endif

