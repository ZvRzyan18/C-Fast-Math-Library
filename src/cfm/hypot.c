/*
 MIT License

 Copyright (c) 2025 ZvRzyan18

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include "cfm/math.h"
#include <stdint.h>

//TODO : implement using cpu specific instruction

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
 );
 return x;
}

#else 

double cfm_hypot(double x, double y) {
 return cfm_sqrt(x * x + y * y);
}


float cfm_hypotf(float x, float y) {
 return cfm_sqrtf(x * x + y * y);
}

#endif

