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

double cfm_trunc(double x) {
#if defined(__aarch64__)
 //aarch64 frintz instruction
 __asm__ volatile(
  "frintz %d[result], %d[input]\n"
  : [result] "=w" (x)
  : [input] "w" (x)
 );
 return x;
#else
	return (double)(int64_t)x;
#endif
}

float cfm_truncf(float x) {
#if defined(__aarch64__)
 //aarch64 frintz instruction
 __asm__ volatile(
  "frintz %s[result], %s[input]\n"
  : [result] "=w" (x)
  : [input] "w" (x)
 );
 return x;
#else
	return (float)(int64_t)x;
#endif
}
