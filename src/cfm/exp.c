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

//exp(x) = exp2(x / ln2)

#define INV_LN2 1.44269504088896338700
#define INV_LN2F 1.442695f


#define EXP2_0 1.3697664475809267e-2
#define EXP2_1 5.1690358205939469e-2
#define EXP2_2 2.4163844572498163e-1
#define EXP2_3 6.9296612266139567e-1
#define EXP2_4 1.000003704465937

#define __exp2(x) ((((EXP2_0 * x + EXP2_1) * x + EXP2_2) * x + EXP2_3) * x + EXP2_4)

#define EXP2F_0 1.369766e-2f
#define EXP2F_1 5.169035e-2f
#define EXP2F_2 2.416384e-1f
#define EXP2F_3 6.929661e-1f
#define EXP2F_4 1.000003f

#define __exp2f(x) ((((EXP2F_0 * x + EXP2F_1) * x + EXP2F_2) * x + EXP2F_3) * x + EXP2F_4)


double cfm_exp(double x) {
 x *= INV_LN2;
 if((*(uint64_t*)&x) & 0x8000000000000000) {// x < 0.0f
  *(uint64_t*)&x &= 0x7FFFFFFFFFFFFFFF;
  uint64_t out = ((uint64_t)(1023 + ((uint64_t)(x))) << 52);
  x -= (uint64_t)x;
  return 1.0 / ((*(double*)(&out)) * __exp2(x));
 }
 uint64_t out = ((uint64_t)(1023 + ((uint64_t)(x))) << 52);
 x -= (uint64_t)x;
 return (*(double*)(&out)) * __exp2(x);
}


float cfm_expf(float x) {
	x *= INV_LN2F;
 if((*(uint32_t*)&x) & 0x80000000) {// x < 0.0f
  *(uint32_t*)&x &= 0x7FFFFFFF;
  uint32_t out = ((uint32_t)(127 + ((uint32_t)(x))) << 23);
  x -= (uint64_t)x;
  return 1.0f / ((*(float*)(&out)) * __exp2f(x));
 }
 uint32_t out = ((uint32_t)(127 + ((uint64_t)(x))) << 23);
 x -= (uint64_t)x;
 return (*(float*)(&out)) * __exp2f(x);
}

