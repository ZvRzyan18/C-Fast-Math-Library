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

// TODO : implement cpu specific instruction
#if defined(__aarch64__)

__asm__ (
 ".type cfm_fma, @function \n"

 ".global cfm_fma \n"
 "cfm_fma: \n"
 "fmadd d0, d0, d1, d2 \n"
 "ret \n"
);

__asm__ (
 ".type cfm_fmaf, @function \n"

 ".global cfm_fmaf \n"
 "cfm_fmaf: \n"
 "fmadd s0, s0, s1, s2 \n"
 "ret \n"
);

#else 

double cfm_fma(double x, double y, double z) {
 return x * y + z;
}

float cfm_fmaf(float x, float y, float z) {
 return x * y + z;
}

#endif

