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

#if defined(__aarch64__)

__asm__(
 ".type cfm_floor, @function \n"

 ".global cfm_floor \n"
 "cfm_floor: \n"
 "frintm d0, d0 \n"
 "ret \n"
);

__asm__(
 ".type cfm_floorf, @function \n"

 ".global cfm_floorf \n"
 "cfm_floorf: \n"
 "frintm s0, s0 \n"
 "ret \n"
);

#elif (__x86_64__)

double cfm_floor(double x) {
 __asm__ volatile (
  "movsd %[input], %%xmm0 \n"
  "roundsd $1, %%xmm0, %%xmm0 \n"
  "movsd %%xmm0, %[output]"
  : [output]"=x"(x)
  : [input] "x"(x)
  : "xmm0"
 );
 return x;
}

float cfm_floorf(float x) {
 __asm__ volatile (
  "movss %[input], %%xmm0 \n"
  "roundss $1, %%xmm0, %%xmm0 \n"
  "movss %%xmm0, %[output]"
  : [output]"=m"(x)
  : [input] "m"(x)
  : "xmm0"
 );
 return x;
}

#else

double cfm_floor(double x) {
 if(*(uint64_t*)&x & 0x8000000000000000) {
  return (double)(((int64_t)x)-1);
 }
 return (double)(uint64_t)x;
}


float cfm_floorf(float x) {
 if(*(uint32_t*)&x & 0x80000000) {
  return (float)(((int64_t)x)-1);
 }
 return (float)(uint64_t)x;
}

#endif


