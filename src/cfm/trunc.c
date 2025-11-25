#include "cfm/math.h"
#include <stdint.h>

//TODO : implement using cpu specific instruction

#if defined(__aarch64__)
__asm__(
 ".type cfm_trunc, @function \n"

 ".global cfm_trunc \n"
 "cfm_trunc: \n"
 "frintz d0, d0 \n"
 "ret \n"
);

__asm__(
 ".type cfm_truncf, @function \n"

 ".global cfm_truncf \n"
 "cfm_truncf: \n"
 "frintz s0, s0 \n"
 "ret \n"
);

#elif (__x86_64__)

double cfm_trunc(double x) {
 __asm__ volatile (
  "movsd %[input], %%xmm0 \n"
  "roundsd $3, %%xmm0, %%xmm0 \n"
  "movsd %%xmm0, %[output]"
  : [output]"=x"(x)
  : [input] "x"(x)
  : "xmm0"
 );
 return x;
}

float cfm_truncf(float x) {
 __asm__ volatile (
  "movss %[input], %%xmm0 \n"
  "roundss $3, %%xmm0, %%xmm0 \n"
  "movss %%xmm0, %[output]"
  : [output]"=m"(x)
  : [input] "m"(x)
  : "xmm0"
 );
 return x;
}

#else

//---------------DOUBLE------------------//

double cfm_trunc(double x) {
 return (double)(int64_t)x;
}

//---------------FLOAT------------------//

float cfm_truncf(float x) {
 return (float)(int64_t)x;
}

#endif

