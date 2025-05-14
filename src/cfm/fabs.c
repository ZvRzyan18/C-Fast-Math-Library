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


double cfm_fabs(double x) {
#if defined(__aarch64__)
 __asm__ volatile(
  "fmov x0, %d[result] \n"
  "and x0, x0, #0x7FFFFFFFFFFFFFFF \n"
  "fmov %d[result], x0 \n"
  : [result] "=w" (x)
  : [input] "w" (x)
 );
 return x;
#else
	uint64_t m = (*(uint64_t*)&x) & 0x7FFFFFFFFFFFFFFF;
	return *(double*)&m;
#endif
}

float cfm_fabsf(float x) {
#if defined(__aarch64__)
 __asm__ volatile(
  "fmov w0, %s[result] \n"
  "and w0, w0, #0x7FFFFFFF \n"
  "fmov %s[result], w0 \n"
  : [result] "=w" (x)
  : [input] "w" (x)
 );
 return x;
#else
	uint32_t m = (*(uint32_t*)&x) & 0x7FFFFFFF;
	return *(float*)&m;
#endif
}