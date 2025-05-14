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

// cbrt(x) = exp2((1.0/3.0) * log2(x));

double cfm_cbrt(double x) {
 uint64_t m;
 double mx;
 //log2 implementation
 if((*(uint64_t*)&x >> 52) < 1023) { //x < 1.0
	 x = 1.0 / x;
	 m = 4607182418800017408U | ((*(uint64_t*)&x) & 0x000FFFFFFFFFFFFF);
	 mx = *(double*)&m;
  x = -0.333333333333333333333 * (((((*(uint64_t*)&x) >> 52)-1023) + ((((-8.1615808498122383e-2 * mx + 6.4514236358772082e-1) * mx - 2.1206751311142674) * mx + 4.0700907918522014) * mx - 2.5128546239033371)));
 } else {
  m = 4607182418800017408U | ((*(uint64_t*)&x) & 0x000FFFFFFFFFFFFF);
  mx = *(double*)&m;
  x = 0.333333333333333333333 * ((((*(uint64_t*)&x) >> 52)-1023) + ((((-8.1615808498122383e-2 * mx + 6.4514236358772082e-1) * mx - 2.1206751311142674) * mx + 4.0700907918522014) * mx - 2.5128546239033371));
 }
 //exp2 implementation
 if((*(uint64_t*)&x) & 0x8000000000000000) {// x < 0.0f
  *(uint64_t*)&x &= 0x7FFFFFFFFFFFFFFF;
  m = ((uint64_t)(1023 + ((uint64_t)(x))) << 52);
  x -= (uint64_t)x;
  return 1.0 / ((*(double*)(&m)) * ((((1.3697664475809267e-2 * x + 5.1690358205939469e-2) * x + 2.4163844572498163e-1) * x + 6.9296612266139567e-1) * x + 1.000003704465937));
 }
 m = ((uint64_t)(1023 + ((uint64_t)(x))) << 52);
 x -= (uint64_t)x;
 return (*(double*)(&m)) * ((((1.3697664475809267e-2 * x + 5.1690358205939469e-2) * x + 2.4163844572498163e-1) * x + 6.9296612266139567e-1) * x + 1.000003704465937);
}


float cfm_cbrtf(float x) {
 uint32_t m;
 float mx;
 //log2 implementation
 if((*(uint32_t*)&x >> 23) < 127) { //x < 1.0
	 x = 1.0f / x;
  m = 1065353216U | ((*(uint32_t*)&x) & 0x007FFFFF);
	 mx = *(float*)&m;
  x = -0.333333f * (((((*(uint32_t*)&x) >> 23)-127) + ((((-8.161580e-2f * mx + 6.451423e-1f) * mx - 2.120675f) * mx + 4.070090f) * mx - 2.512854f)));
 } else {
  m = 1065353216U | ((*(uint32_t*)&x) & 0x007FFFFF);
  mx = *(float*)&m;
  x = 0.333333f * ((((*(uint32_t*)&x) >> 23)-127) + ((((-8.161580e-2f * mx + 6.451423e-1f) * mx - 2.120675f) * mx + 4.070090f) * mx - 2.512854f));
 }
 //exp2 implementation
 if((*(uint32_t*)&x) & 0x80000000) {// x < 0.0f
  *(uint32_t*)&x &= 0x7FFFFFFF;
  m = ((uint32_t)(127 + ((uint32_t)(x))) << 23);
  x -= (uint64_t)x;
  return 1.0f / ((*(float*)(&m)) * ((((1.369766e-2f * x + 5.169035e-2f) * x + 2.416384e-1f) * x + 6.929661e-1f) * x + 1.000003f));
 }
 m = ((uint32_t)(127 + ((uint64_t)(x))) << 23);
 x -= (uint64_t)x;
 return (*(float*)(&m)) * ((((1.369766e-2f * x + 5.169035e-2f) * x + 2.416384e-1f) * x + 6.929661e-1f) * x + 1.000003f);
}

