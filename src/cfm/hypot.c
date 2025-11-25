#include "cfm/math.h"
#include <stdint.h>


//TODO : implement using cpu specific instruction

/*
 hypot
                     • (x, y) 
                    /|
                   / |
  hypothenuse ->  /  |
                 /   | -> B-side
                /__  |
               /   | |
               •-------
                 ^
                A-side
 
  hypothenuse = sqrt(A^2 + B^2) (pythagorean theorem)
  
*/


/*
 hypot(x, y) = sqrt(x * x + y * y)
 
 or :
 
 hypot(x, y) = sqrt(dot())
*/

#if defined(__aarch64__)

double cfm_hypot(double x, double y) {
 __asm__ volatile(
  "fmul d3, %d[input1], %d[input1] \n"
  "fmul d4, %d[input2], %d[input2] \n"
  "fadd d3, d3, d4 \n"
  "fsqrt %d[result], d3 \n"
  : [result] "=w" (x)
  : [input1] "w" (x), [input2] "w" (y)
  : "d3", "d4"
 );
 return x;
}


float cfm_hypotf(float x, float y) {
 __asm__ volatile(
  "fmul s3, %s[input1], %s[input1] \n"
  "fmul s4, %s[input2], %s[input2] \n"
  "fadd s3, s3, s4 \n"
  "fsqrt %s[result], s3 \n"
  : [result] "=w" (x)
  : [input1] "w" (x), [input2] "w" (y)
  : "s3", "s4"
 );
 return x;
}

#else 

//---------------DOUBLE------------------//

double cfm_hypot(double x, double y) {
 return cfm_sqrt(x * x + y * y);
}

//---------------FLOAT------------------//

float cfm_hypotf(float x, float y) {
 return cfm_sqrtf(x * x + y * y);
}

#endif

