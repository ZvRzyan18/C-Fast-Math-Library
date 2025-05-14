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

double cfm_atan(double x) {
 if((*(uint64_t*)&x) & 0x8000000000000000) {
 	(*(uint64_t*)&x) &= 0x7FFFFFFFFFFFFFFF;
  x = (x / cfm_sqrt(1.0 + x * x));
  if(x > 0.5) {
   x = cfm_sqrt((1.0 - x) * 0.5);
   return -(1.57079632679489655800 - 2.0 * ((((0.13819359277748702 * x + 0.094813956277301839) * x + 0.014298809020222956) * x + 0.99902850272887345) * x + 1.0488947775378894e-05));
  } 
  return -((((0.13819359277748702 * x + 0.094813956277301839) * x + 0.014298809020222956) * x + 0.99902850272887345) * x + 1.0488947775378894e-05);
 }
 x = (x / cfm_sqrt(1.0 + x * x));
 if(x > 0.5) {
  x = cfm_sqrt((1.0 - x) * 0.5);
  return 1.57079632679489655800 - 2.0 * ((((0.13819359277748702 * x + 0.094813956277301839) * x + 0.014298809020222956) * x + 0.99902850272887345) * x + 1.0488947775378894e-05);
 }
 return ((((0.13819359277748702 * x + 0.094813956277301839) * x + 0.014298809020222956) * x + 0.99902850272887345) * x + 1.0488947775378894e-05);
}


float cfm_atanf(float x) {
 if((*(uint32_t*)&x) & 0x80000000) {
  (*(uint32_t*)&x) &= 0x7FFFFFFF;
  x = (x / cfm_sqrtf(1.0f + x * x));
  if(x > 0.5f) {
   x = cfm_sqrtf((1.0f - x) * 0.5f);
   return -(1.570796f - 2.0f *  ((((0.138193f * x + 0.094813f) * x + 0.014298f) * x + 0.999028f) * x + 1.048894e-05f));
  } 
 return -((((0.138193f * x + 0.094813f) * x + 0.014298f) * x + 0.999028f) * x + 1.048894e-05f);
 }
 x = (x / cfm_sqrtf(1.0f + x * x));
 if(x > 0.5f) {
  x = cfm_sqrtf((1.0f - x) * 0.5f);
  return 1.570796f - 2.0f *  ((((0.138193f * x + 0.094813f) * x + 0.014298f) * x + 0.999028f) * x + 1.048894e-05f);
 } 
 return ((((0.138193f * x + 0.094813f) * x + 0.014298f) * x + 0.999028f) * x + 1.048894e-05f);
}

