#include "cfm/math.h"
#include <stdint.h>

#if defined(__aarch64__)

double cfm_fabs(double x) {
 __asm__ volatile(
  "fmov x0, %d[result] \n"
  "and x0, x0, #0x7FFFFFFFFFFFFFFF \n"
  "fmov %d[result], x0 \n"
  : [result] "=w" (x)
  : [input] "w" (x)
  : "x0"
 );
 return x;
}

float cfm_fabsf(float x) {
 __asm__ volatile(
  "fmov w0, %s[result] \n"
  "and w0, w0, #0x7FFFFFFF \n"
  "fmov %s[result], w0 \n"
  : [result] "=w" (x)
  : [input] "w" (x)
  : "w0"
 );
 return x;
}

#else

double cfm_fabs(double x) {
 uint64_t m = (*(uint64_t*)&x) & 0x7FFFFFFFFFFFFFFF;
 return *(double*)&m;
}

float cfm_fabsf(float x) {
 uint32_t m = (*(uint32_t*)&x) & 0x7FFFFFFF;
 return *(float*)&m;
}

#endif
