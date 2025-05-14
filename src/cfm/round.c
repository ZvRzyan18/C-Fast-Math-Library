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

double cfm_round(double x) {
#if defined(__aarch64__)
 //aarch64 frintn instruction
 __asm__ volatile(
  "frintn %d[result], %d[input]\n"
  : [result] "=w" (x)
  : [input] "w" (x)
 );
 return x;
#else
	if(*(uint64_t*)&x & 0x8000000000000000) {
 	if((-x - (int64_t)-x) >= 0.5)
 	 return (double)(((int64_t)x)-1);
 return (double)((int64_t)x);
	}
	if((x - (int64_t)x) > 0.5)
 	return (double)(((uint64_t)x)+1);
 return (double)((uint64_t)x);
#endif
}


float cfm_roundf(float x) {
#if defined(__aarch64__)
 //aarch64 frintn instruction
 __asm__ volatile(
  "frintn %s[result], %s[input]\n"
  : [result] "=w" (x)
  : [input] "w" (x)
 );
 return x;
#else
	if(*(uint32_t*)&x & 0x80000000) {
 	if((-x - (int64_t)-x) >= 0.5f)
 	 return (float)(((int64_t)x)-1);
 return (float)((int64_t)x);
	}
	if((x - (int64_t)x) > 0.5)
 	return (float)(((uint64_t)x)+1);
 return (float)((uint64_t)x);
#endif
}

