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

//implemented using asin and sqrt

#define ASIN_0 0.13819359277748702
#define ASIN_1 0.094813956277301839
#define ASIN_2 0.014298809020222956
#define ASIN_3 0.99902850272887345
#define ASIN_4 1.0488947775378894e-05

#define __asin(x) ((((ASIN_0 * x + ASIN_1) * x + ASIN_2) * x + ASIN_3) * x + ASIN_4)

#define ASINF_0 0.138193f
#define ASINF_1 0.094813f
#define ASINF_2 0.014298f
#define ASINF_3 0.999028f
#define ASINF_4 1.048894e-05f

#define __asinf(x) ((((ASINF_0 * x + ASINF_1) * x + ASINF_2) * x + ASINF_3) * x + ASINF_4)

double cfm_atan(double x) {
 if((*(uint64_t*)&x) & 0x8000000000000000) {
  x = (x / -cfm_sqrt(1.0 + x * x)); //TODO : x = (x * -inv_sqrt(1.0 + x*x));
  if(x > 0.5) {
   x = cfm_sqrt((1.0 - x) * 0.5);
   return -(1.57079632679489655800 - 2.0 * __asin(x));
  } 
  return -__asin(x);
 }
 x = (x / cfm_sqrt(1.0 + x * x)); //TODO : x = (x * inv_sqrt(1.0 + x*x));
 if(x > 0.5) {
  x = cfm_sqrt((1.0 - x) * 0.5);
  return 1.57079632679489655800 - 2.0 * __asin(x);
 }
 return __asin(x);
}


float cfm_atanf(float x) {
 if((*(uint32_t*)&x) & 0x80000000) {
  x = (x / -cfm_sqrtf(1.0f + x * x)); //TODO : x = (x * -inv_sqrt(1.0 + x*x));
  if(x > 0.5f) {
   x = cfm_sqrtf((1.0f - x) * 0.5f);
   return -(1.570796f - 2.0f * __asinf(x));
  } 
  return -__asinf(x);
 }
 x = (x / cfm_sqrtf(1.0f + x * x)); //TODO : x = (x * inv_sqrt(1.0 + x*x));
 if(x > 0.5f) {
  x = cfm_sqrtf((1.0f - x) * 0.5f);
  return 1.570796f - 2.0f * __asinf(x);
 } 
 return __asinf(x);
}

