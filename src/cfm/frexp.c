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

double cfm_frexp(double x, int* _exp) {
	*_exp = ((((*(int64_t*)&x) & 0x7FFFFFFFFFFFFFFF) >> 52)-1023) + 1;
	uint64_t mantissa = 4607182418800017408U | ((*(uint64_t*)&x) & 0x000FFFFFFFFFFFFF);
	return *(double*)&mantissa * 0.5;
}


float cfm_frexpf(float x, int* _exp) {
	*_exp = ((((*(int32_t*)&x) & 0x7FFFFFFF) >> 23)-127) + 1;
	uint32_t mantissa = 1065353216U | ((*(uint32_t*)&x) & 0x007FFFFF);
	return *(float*)&mantissa * 0.5f;
}

