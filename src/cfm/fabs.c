#include "cfm/math.h"
#include "cfm/float_bits.h"
#include <stdint.h>

#if defined(__aarch64__)

//TODO : just simply use abs instruction
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

//---------------DOUBLE------------------//

double cfm_fabs(double x) {
 double_bits bits;
 bits.f = x;
 bits.i = bits.i & 0x7FFFFFFFFFFFFFFF;
 return bits.f;
}

//---------------DOUBLE------------------//

float cfm_fabsf(float x) {
 float_bits bits;
 bits.f = x;
 bits.i = bits.i & 0x7FFFFFFF;
 return bits.f;
}

#endif
