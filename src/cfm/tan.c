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
 # tangent
 
              c0 * x + c1 * x² + c2 * x³...
 tanPoly(x) = ___________________________
              j0 * x + j1 * x² + j2 * x³...
 
 just basically:
           sin(x)
 tan(x) = ________
           cos(x)
*/

/*
 ARM Neon Optimized Calculation
*/

#if defined(__aarch64__) && defined(__ARM_NEON)

#include "__aarch64_tan.h"

#define __tan1 __neon_tan1
#define __tan2 __neon_tan2
#define __tan3 __neon_tan3
#define __tan4 __neon_tan4
#define __tan5 __neon_tan5
#define __tan6 __neon_tan6
#define __tan7 __neon_tan7
#define __tan8 __neon_tan8

#define __tanf1 __neon_tanf1
#define __tanf2 __neon_tanf2
#define __tanf3 __neon_tanf3
#define __tanf4 __neon_tanf4
#define __tanf5 __neon_tanf5
#define __tanf6 __neon_tanf6
#define __tanf7 __neon_tanf7
#define __tanf8 __neon_tanf8

#else

/*
 float64
*/
#define __tan1(x) \
          ((((0.028419240510851106 * x + -0.20266577327037072) * x + 0.019080842223381331) * x + 0.99642139497886761) * x + 0.00000062377991903727) / \
  	       ((((0.028419240510851106 * x + 0.024102418851388162) * x + -0.51522912260478604) * x + 0.0032202099707060541) * x + 0.99989227622008092);

#define __tan2(x) \
 	        ((((0.028419240510851106 * x + -0.15446093556759441) * x + -0.20807910376841424) * x + 1.3596838236791193) * x + -0.1968404310997216) / \
          ((((-2.8419240510851105e-2 * x + 3.8122912768935326e-1) * x - 1.3948507907160879) * x + 1.0042835118007021) * x + 5.5948009821321672e-1);

#define __tan3(x) \
          ((((-0.028419240510851103 * x + 0.55979248210833576) * x + -3.6120807228733334) * x + 8.6488594332797177) * x + -6.1102813795057216) / \
          ((((-2.8419240510851109e-2 * x + 3.3302428998657699e-1) * x - 9.4053089873249697e-1) * x - 4.2944494317606792e-1) * x + 2.0743658093284209);

#define __tan4(x) \
 	        ((((-0.028419240510851113 * x + 0.51158764440555959) * x + -2.9306008848979479) * x + 5.4310209345087541) * x + -1.0354793094431121) / \
          ((((2.84192405108511e-2 * x - 7.3835583652731825e-1) * x + 6.6707706386951177) * x - 2.4580830872428483e+1) * x + 3.0950983305259838e+1);

#define __tan5(x) \
 	        -((((0.028419240510851106 * x + -0.20266577327037072) * x + 0.019080842223381331) * x + 0.99642139497886761) * x + 0.00000062377991903727) / \
  	        ((((0.028419240510851106 * x + 0.024102418851388162) * x + -0.51522912260478604) * x + 0.0032202099707060541) * x + 0.99989227622008092);

#define __tan6(x) \
          -((((0.028419240510851106 * x + -0.15446093556759441) * x + -0.20807910376841424) * x + 1.3596838236791193) * x + -0.1968404310997216) / \
           ((((-2.8419240510851105e-2 * x + 3.8122912768935326e-1) * x - 1.3948507907160879) * x + 1.0042835118007021) * x + 5.5948009821321672e-1);

#define __tan7(x) \
         -((((-0.028419240510851103 * x + 0.55979248210833576) * x + -3.6120807228733334) * x + 8.6488594332797177) * x + -6.1102813795057216) / \
          ((((-2.8419240510851109e-2 * x + 3.3302428998657699e-1) * x - 9.4053089873249697e-1) * x - 4.2944494317606792e-1) * x + 2.0743658093284209);

#define __tan8(x) \
         -((((-0.028419240510851113 * x + 0.51158764440555959) * x + -2.9306008848979479) * x + 5.4310209345087541) * x + -1.0354793094431121) / \
          ((((2.84192405108511e-2 * x - 7.3835583652731825e-1) * x + 6.6707706386951177) * x - 2.4580830872428483e+1) * x + 3.0950983305259838e+1);

/*
 float32 
*/
#define __tanf1(x) \
 	        ((((0.0284192f * x + -0.2026657f) * x + 0.0190808f) * x + 0.9964213f) * x + 0.0000006f) / \
          ((((0.0284192f * x + 0.0241024f) * x + -0.5152291f) * x + 0.0032202f) * x + 0.9998922f);

#define __tanf2(x) \
 	        ((((0.0284192f * x + -0.1544609f) * x + -0.2080791f) * x + 1.3596838f) * x + -0.1968404f) / \
          ((((-2.8419240e-2f * x + 3.8122912e-1f) * x - 1.3948507f) * x + 1.0042835f) * x + 5.5948009e-1f);

#define __tanf3(x) \
          ((((-0.0284192f * x + 0.5597924f) * x + -3.6120807f) * x + 8.6488594f) * x + -6.1102813f) / \
          ((((-2.8419240e-2f * x + 3.3302428e-1f) * x - 9.4053089e-1f) * x - 4.2944494e-1f) * x + 2.0743658f);

#define __tanf4(x) \
 	        ((((-0.0284192f * x + 0.5115876f) * x + -2.9306008f) * x + 5.4310209f) * x + -1.0354793f) / \
          ((((2.8419240e-2f * x - 7.3835583e-1f) * x + 6.6707706f) * x - 2.4580830e+1f) * x + 3.0950983e+1f);

#define __tanf5(x) \
 	       -((((0.0284192f * x + -0.2026657f) * x + 0.0190808f) * x + 0.9964213f) * x + 0.0000006f) / \
          ((((0.0284192f * x + 0.0241024f) * x + -0.5152291f) * x + 0.0032202f) * x + 0.9998922f);

#define __tanf6(x) \
 	       -((((0.0284192f * x + -0.1544609f) * x + -0.2080791f) * x + 1.3596838f) * x + -0.1968404f) / \
          ((((-2.8419240e-2f * x + 3.8122912e-1f) * x - 1.3948507f) * x + 1.0042835f) * x + 5.5948009e-1f);

#define __tanf7(x) \
         -((((-0.0284192f * x + 0.5597924f) * x + -3.6120807f) * x + 8.6488594f) * x + -6.1102813f) / \
          ((((-2.8419240e-2f * x + 3.3302428e-1f) * x - 9.4053089e-1f) * x - 4.2944494e-1f) * x + 2.0743658f);

#define __tanf8(x) \
 	       -((((-0.0284192f * x + 0.5115876f) * x + -2.9306008f) * x + 5.4310209f) * x + -1.0354793f) / \
          ((((2.8419240e-2f * x - 7.3835583e-1f) * x + 6.6707706f) * x - 2.4580830e+1f) * x + 3.0950983e+1f);



#endif



double cfm_tan(double x) {
 int64_t inv_quad = 0;
 if((*(uint64_t*)&x) & 0x8000000000000000) {
  (*(uint64_t*)&x) &= 0x7FFFFFFFFFFFFFFF;
  inv_quad = 1 << 5;
 }
 
 if((*(uint64_t*)&x) > 0x401921fb54442d18)
  x = x - (int64_t)(x * 0.15915494309189534561) * 6.28318530717958623200;

 //Padé approximants
 switch((int64_t)(x * 0.636619772367581382432888403855) | inv_quad) {
 	case 0:
 	 return __tan1(x);
 	break;
 	case 1:
 	 return __tan2(x);
 	break;
 	case 2:
 	 return __tan3(x);
 	break;
 	case 3:
 	 return __tan4(x);
 	break;
  // negative x
 	case 32:
 	 return __tan5(x);
  break;
  case 33:
   return __tan6(x);
  break;
  case 34:
   return __tan7(x);
  break;
  case 35:
   return __tan8(x);
  break;
 }
 return 0;
}


float cfm_tanf(float x) {
 int32_t inv_quad = 0;
 if((*(uint32_t*)&x) & 0x80000000) {
  (*(uint32_t*)&x) &= 0x7FFFFFFF;
  inv_quad = 1 << 5;
 }
 
 if((*(uint32_t*)&x) > 0x40c90fdb)
  x = x - (int32_t)(x * 0.1591549f) * 6.2831853f;

 //Padé approximants
 switch((int32_t)(x * 0.6366197f) | inv_quad) {
 	case 0:
 	 return __tanf1(x);
 	break;
 	case 1:
 	 return __tanf2(x);
 	break;
 	case 2:
 	 return __tanf3(x);
 	break;
 	case 3:
 	 return __tanf4(x);
 	break;
  // negative x
 	case 32:
 	 return __tanf5(x);
 	break;
 	case 33:
 	 return __tanf6(x);
 	break;
 	case 34:
 	 return __tanf7(x);
 	break;
 	case 35:
 	 return __tanf8(x);
 	break;
 }
 return 0;
}

