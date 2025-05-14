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

double cfm_log2(double x) {
 uint64_t mantissa;
 double mx;
 if((*(uint64_t*)&x >> 52) < 1023) { //x < 1.0
	 x = 1.0 / x;
	 mantissa = 4607182418800017408U | ((*(uint64_t*)&x) & 0x000FFFFFFFFFFFFF);
	 mx = *(double*)&mantissa;
  return -((((*(uint64_t*)&x) >> 52)-1023) + ((((-8.1615808498122383e-2 * mx + 6.4514236358772082e-1) * mx - 2.1206751311142674) * mx + 4.0700907918522014) * mx - 2.5128546239033371));
 }
 mantissa = 4607182418800017408U | ((*(uint64_t*)&x) & 0x000FFFFFFFFFFFFF);
 mx = *(double*)&mantissa;
 return (((*(uint64_t*)&x) >> 52)-1023) + ((((-8.1615808498122383e-2 * mx + 6.4514236358772082e-1) * mx - 2.1206751311142674) * mx + 4.0700907918522014) * mx - 2.5128546239033371);
}


float cfm_log2f(float x) {
 uint32_t mantissa;
 float mx;
 if((*(uint32_t*)&x >> 23) < 127) { //x < 1.0
	 x = 1.0f / x;
  mantissa = 1065353216U | ((*(uint32_t*)&x) & 0x007FFFFF);
	 mx = *(float*)&mantissa;
  return -((((*(uint32_t*)&x) >> 23)-127) + ((((-8.161580e-2f * mx + 6.451423e-1f) * mx - 2.120675f) * mx + 4.070090f) * mx - 2.512854f));
 }
 mantissa = 1065353216U | ((*(uint32_t*)&x) & 0x007FFFFF);
 mx = *(float*)&mantissa;
 return (((*(uint32_t*)&x) >> 23)-127) + ((((-8.161580e-2f * mx + 6.451423e-1f) * mx - 2.120675f) * mx + 4.070090f) * mx - 2.512854f);
}

