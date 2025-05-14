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

double cfm_scalbn(double x, int _exp) {
	uint64_t exponent = ((((*(int64_t*)&x) & 0x7FFFFFFFFFFFFFFF) >> 52) + _exp) << 52;
	uint64_t mantissa = ((*(uint64_t*)&x) & 0x000FFFFFFFFFFFFF);
 uint64_t sign_bit = ((*(uint64_t*)&x) & 0x8000000000000000) << 63;
 uint64_t value = sign_bit | exponent | mantissa;
 return *(double*)&value;
}

float cfm_scalbnf(float x, int _exp) {
	uint32_t exponent = ((((*(int32_t*)&x) & 0x7FFFFFFF) >> 23) + _exp) << 23;
	uint32_t mantissa = ((*(uint32_t*)&x) & 0x007FFFFF);
 uint64_t sign_bit = ((*(uint32_t*)&x) & 0x80000000) << 31;
 uint32_t value = sign_bit | exponent | mantissa;
 return *(float*)&value;
}

