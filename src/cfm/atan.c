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
/*
 # arc tangent
                     ________
 atan(x) = asin(x / √1 + x*x ) 

 • alternative (only works on positive x):
                     ________
 atan(x) = acos(1 / √1 + x*x )
*/

/*
 implementation
 
 for |x| <= 1.0
 
 atanPoly(x) = c0 * x + c1 * x² + c2 * x³....
 
 for |x| >= 1.0
 
 atan(x) pi_half - atanPoly(1.0 / x)
*/

#define ATAN_0 0.13810761856371942
#define ATAN_1 -0.33804446551765377
#define ATAN_2 -0.018287143230624005
#define ATAN_3 1.003834535410429
#define ATAN_4 -0.00010619091421120068

#define __atan(x) ((((ATAN_0 * x + ATAN_1) * x + ATAN_2) * x + ATAN_3) * x + ATAN_4)

#define ATANF_0 0.138107f
#define ATANF_1 -0.338044f
#define ATANF_2 -0.018287f
#define ATANF_3 1.003834f
#define ATANF_4 -0.000106f

#define __atanf(x) ((((ATANF_0 * x + ATANF_1) * x + ATANF_2) * x + ATANF_3) * x + ATANF_4)

double cfm_atan(double x) {
	if((*(uint64_t*)&x) & 0x8000000000000000) {
		(*(uint64_t*)&x) &= 0x7FFFFFFFFFFFFFFF;
	 if(((*(uint64_t*)&x) >> 52) >= 1023) {
	  x = 1.0 / x;
	  return -(1.57079632679489655800 - __atan(x));
	 }
	 return -__atan(x);
	}
	if(((*(uint64_t*)&x) >> 52) >= 1023) {
	 x = 1.0 / x;
	 return 1.57079632679489655800 - __atan(x);
	}
 return __atan(x);
}


float cfm_atanf(float x) {
	if((*(uint32_t*)&x) & 0x80000000) {
		(*(uint32_t*)&x) &= 0x7FFFFFFF;
	 if(((*(uint32_t*)&x) >> 23) >= 127) {
	  x = 1.0f / x;
	  return -(1.570796f - __atanf(x));
	 }
	 return -__atanf(x);
	}
	if(((*(uint32_t*)&x) >> 23) >= 127) {
	 x = 1.0f / x;
	 return 1.570796f - __atanf(x);
	}
 return __atanf(x);
}


