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

//remainder(x, y) = x - round(x / y) * y

#if defined(__aarch64__)

double cfm_drem(double x, double y) {
 __asm__ volatile(
  "fdiv d3, %d[input1], %d[input2] \n"
  "frintn d3, d3 \n"
  "fmul d3, d3, %d[input2] \n"
  "fsub %d[result], %d[input1], d3 \n"
  : [result] "=w" (x)
  : [input1] "w" (x), [input2] "w" (y)
  : "d3"
 );
 return x;
}

float cfm_dremf(float x, float y) {
 __asm__ volatile(
  "fdiv s3, %s[input1], %s[input2] \n"
  "frintn s3, s3 \n"
  "fmul s3, s3, %s[input2] \n"
  "fsub %s[result], %s[input1], s3 \n"
  : [result] "=w" (x)
  : [input1] "w" (x), [input2] "w" (y)
  : "s3"
 );
 return x;
}

#else

double cfm_drem(double x, double y) {
 return x - cfm_round(x / y) * y;
}


float cfm_dremf(float x, float y) {
 return x - cfm_roundf(x / y) * y;
}

#endif

