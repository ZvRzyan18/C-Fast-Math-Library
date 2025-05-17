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
 ".type cfm_sqrt, @function \n"

 ".global cfm_sqrt \n"
 "cfm_sqrt: \n"
 "fsqrt d0, d0 \n"
 "ret \n"
);

__asm__(
 ".type cfm_sqrtf, @function \n"

 ".global cfm_sqrtf \n"
 "cfm_sqrtf: \n"
 "fsqrt s0, s0 \n"
 "ret \n"
);

#elif defined(__x86_64__)


double cfm_sqrt(double x) {
 __asm__ volatile (
  "sqrtsd %[in], %[out]"
  : [out] "=x" (x)
  : [in] "x" (x)
  : "xmm0"
 );
 return x;
}

float cfm_sqrtf(float x) {
 __asm__ volatile (
  "movss %[in], %%xmm0 \n"
  "sqrtss %%xmm0, %%xmm0 \n"
  "movss %%xmm0, %[out]"
  : [out] "=m" (x)
  : [in] "m" (x)
  : "xmm0"
 );
 return x;
}

#else

double cfm_sqrt(double x) {
/*
 Quake III fast inv sqrt
*/
 uint64_t mx = 0x5fe6eb50c7b537a9 - (*((uint64_t*)&x) >> 1);
 const double x_half = x * 0.5;
 double f = *(double*)&mx;
 f = (f * (1.5 - (x_half * f * f)));
 f = (f * (1.5 - (x_half * f * f)));
 return x * f;
}


float cfm_sqrtf(float x) {
/*
 Quake III fast inv sqrt
*/
 uint32_t mx = 0x5f3759df - ((*(uint32_t*)&x) >> 1);
 const float x_half = x * 0.5f;
 float f = *(float*)&mx;
 f = (f * (1.5 - (x_half * f * f)));
 f = (f * (1.5 - (x_half * f * f)));
 return x * f;
}

#endif
