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



double cfm_exp2(double x) {
 //bit hack manipulation
 if((*(uint64_t*)&x) & 0x8000000000000000) {// x < 0.0f
  *(uint64_t*)&x &= 0x7FFFFFFFFFFFFFFF;
  uint64_t out = ((uint64_t)(1023 + ((uint64_t)(x))) << 52);
  x -= (uint64_t)x;
  return 1.0 / ((*(double*)(&out)) * ((((1.3697664475809267e-2 * x + 5.1690358205939469e-2) * x + 2.4163844572498163e-1) * x + 6.9296612266139567e-1) * x + 1.000003704465937));
 }
 uint64_t out = ((uint64_t)(1023 + ((uint64_t)(x))) << 52);
 x -= (uint64_t)x;
 return (*(double*)(&out)) * ((((1.3697664475809267e-2 * x + 5.1690358205939469e-2) * x + 2.4163844572498163e-1) * x + 6.9296612266139567e-1) * x + 1.000003704465937);
}


float cfm_exp2f(float x) {
 //bit hack manipulation
 if((*(uint32_t*)&x) & 0x80000000) {// x < 0.0f
  *(uint32_t*)&x &= 0x7FFFFFFF;
  uint32_t out = ((uint32_t)(127 + ((uint32_t)(x))) << 23);
  x -= (uint64_t)x;
  return 1.0f / ((*(float*)(&out)) * ((((1.369766e-2f * x + 5.169035e-2f) * x + 2.416384e-1f) * x + 6.929661e-1f) * x + 1.000003f));
 }
 uint32_t out = ((uint32_t)(127 + ((uint64_t)(x))) << 23);
 x -= (uint64_t)x;
 return (*(float*)(&out)) * ((((1.369766e-2f * x + 5.169035e-2f) * x + 2.416384e-1f) * x + 6.929661e-1f) * x + 1.000003f);
}

