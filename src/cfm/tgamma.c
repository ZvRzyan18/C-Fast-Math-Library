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

//https://www.rskey.org/CMS/the-library/?view=article&id=11
//https://compbio.mit.edu/dlcoal/pub/dlcoal/src/spidir/gamma.cpp
//Lanczos approximation to the gamma function

//tgamma(x) = exp(lgamma(x))

double cfm_tgamma(double x) {
 // sqrt(tau) = 2.50662827463100024161
 if(*(uint64_t*)&x & 0x8000000000000000) { // x < 0.0
  *(uint64_t*)&x &= 0x7FFFFFFFFFFFFFFF;
  return -(3.14159265358979323846 / (cfm_sin(3.14159265358979323846 * x) * ((1.000000000190015 + 76.18009172947146 / (x + 1.0) + -86.50532032941677 / (x + 2.0) + 24.01409824083091 / (x + 3.0) + -1.231739572450155 / (x + 4.0) + 1.208650973866179e-3 / (x + 5.0) + -5.395239384953e-6 / (x + 6.0)))
  * 2.50662827463100024161 / x * cfm_pow(x + 5.5, x + 0.5) * cfm_exp(-x - 5.5)));
 }
 return ((1.000000000190015 + 76.18009172947146 / (x + 1.0) + -86.50532032941677 / (x + 2.0) + 24.01409824083091 / (x + 3.0) + -1.231739572450155 / (x + 4.0) + 1.208650973866179e-3 / (x + 5.0) + -5.395239384953e-6 / (x + 6.0)))
  * 2.50662827463100024161 / x * cfm_pow(x + 5.5, x + 0.5) * cfm_exp(-x - 5.5);
}


float cfm_tgammaf(float x) {
 if(*(uint32_t*)&x & 0x80000000) { // x < 0.0
  *(uint32_t*)&x &= 0x7FFFFFFF;
  return -(3.141592f / (cfm_sin(3.141592f * x) * ((1.000000f + 76.180091f / (x + 1.0f) + -86.505320f / (x + 2.0f) + 24.014098f / (x + 3.0f) + -1.231739f / (x + 4.0f) + 1.208650e-3f / (x + 5.0f) + -5.395239e-6f / (x + 6.0f)))
  * 2.506628f / x * cfm_powf(x + 5.5f, x + 0.5f) * cfm_expf(-x - 5.5f)));
 }
 return ((1.000000f + 76.180091f / (x + 1.0f) + -86.505320f / (x + 2.0f) + 24.014098f / (x + 3.0f) + -1.231739f / (x + 4.0f) + 1.208650e-3f / (x + 5.0f) + -5.395239e-6f / (x + 6.0f)))
  * 2.506628f / x * cfm_powf(x + 5.5f, x + 0.5f) * cfm_expf(-x - 5.5f);
}


