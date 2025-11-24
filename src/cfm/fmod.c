#include "cfm/math.h"
#include <stdint.h>

//TODO : implement using cpu specific instruction
#if defined(__aarch64__)

double cfm_fmod(double x, double y) {
 __asm__ volatile(
  "fdiv d3, %d[input1], %d[input2] \n"
  "frintz d3, d3 \n"
  "fmul d3, d3, %d[input2] \n"
  "fsub %d[result], %d[input1], d3 \n"
  : [result] "=w" (x)
  : [input1] "w" (x), [input2] "w" (y)
  : "d3"
 );
 return x;
}


float cfm_fmodf(float x, float y) {
 __asm__ volatile(
  "fdiv s3, %s[input1], %s[input2] \n"
  "frintz s3, s3 \n"
  "fmul s3, s3, %s[input2] \n"
  "fsub %s[result], %s[input1], s3 \n"
  : [result] "=w" (x)
  : [input1] "w" (x), [input2] "w" (y)
  : "s3"
 );
 return x;
}


#else


double cfm_fmod(double x, double y) {
 return x - cfm_trunc(x / y) * y;
}


float cfm_fmodf(float x, float y) {
 return x - cfm_truncf(x / y) * y;
}

#endif

