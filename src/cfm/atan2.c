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

//atan(y, x) = atan(y/x)

double cfm_atan2(double y, double x) {
 if (y < 0.0 && x < 0.0)
  return cfm_atan(y / x) - 3.14159265358979323846;
 else if(y > 0.0 && x < 0.0)
  return cfm_atan(y / x) + 3.14159265358979323846;
 return cfm_atan(y / x);
}

float cfm_atan2f(float y, float x) {
 if (y < 0.0f && x < 0.0f)
  return cfm_atanf(y / x) - 3.141592f;
 else if(y > 0.0f && x < 0.0f)
  return cfm_atanf(y / x) + 3.141592f;
 return cfm_atanf(y / x);
}
