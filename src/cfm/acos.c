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
 # arc cosine
 • for x between [0, 0.5] (4 degree polynomial)
 acosPoly(x) = c0 * x + c1 * x² + c2 * x³ + c3 * x⁴....
 acos(x) = acosPoly(x)
 
 • for x between [0.5, 1.0]
                                ____________
 acos(x) = pi - 2.0 * acosPoly(√ (1 - x) / 2)
*/

double cfm_acos(double x) {
 if((*(uint64_t*)&x) & 0x8000000000000000) {
  (*(uint64_t*)&x) &= 0x7FFFFFFFFFFFFFFF;
  if(x > 0.5) {
   x = cfm_sqrt((1.0 - x) * 0.5);
   return 2.0 * ((((-1.3819359277748702e-1 * x - 9.4813956277301838e-2) * x - 1.4298809020222956e-2) * x - 9.9902850272887342e-1) * x + 1.5707858378471212);
  }
  return 3.14159265358979323846 - ((((-1.3819359277748702e-1 * x - 9.4813956277301838e-2) * x - 1.4298809020222956e-2) * x - 9.9902850272887342e-1) * x + 1.5707858378471212);
 }
 if(x > 0.5) {
  x = cfm_sqrt((1.0 - x) * 0.5);
  return 3.14159265358979323846 - 2.0 * ((((-1.3819359277748702e-1 * x - 9.4813956277301838e-2) * x - 1.4298809020222956e-2) * x - 9.9902850272887342e-1) * x + 1.5707858378471212);
 } 
 return ((((-1.3819359277748702e-1 * x - 9.4813956277301838e-2) * x - 1.4298809020222956e-2) * x - 9.9902850272887342e-1) * x + 1.5707858378471212);
}


float cfm_acosf(float x) {
 if((*(uint32_t*)&x) & 0x80000000) {
  (*(uint32_t*)&x) &= 0x7FFFFFFF;
  if(x > 0.5f) {
   x = cfm_sqrtf((1.0f - x) * 0.5f);
   return 2.0f * ((((-1.381935e-1f * x - 9.481395e-2f) * x - 1.429880e-2f) * x - 9.990285e-1f) * x + 1.570785f);
  }
  return 3.141592f - ((((-1.381935e-1f * x - 9.481395e-2f) * x - 1.429880e-2f) * x - 9.990285e-1f) * x + 1.570785f);
 }
 if(x > 0.5f) {
  x = cfm_sqrtf((1.0f - x) * 0.5f);
  return 3.141592f - 2.0f * ((((-1.381935e-1f * x - 9.481395e-2f) * x - 1.429880e-2f) * x - 9.990285e-1f) * x + 1.570785f);
 } 
 return ((((-1.381935e-1f * x - 9.481395e-2f) * x - 1.429880e-2f) * x - 9.990285e-1f) * x + 1.570785f);
}

