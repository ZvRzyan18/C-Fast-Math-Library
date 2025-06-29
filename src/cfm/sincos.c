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
 ARM Neon Optimized Calculation
*/
#if defined(__aarch64__) && defined(__ARM_NEON)

#include "__aarch64_sincos.h"
/*
 we prefer to use assembly since it minimize the overhead of <arm_neon.h>
 interface
*/
#define __sincos1 __neon_sincos1
#define __sincos2 __neon_sincos2
#define __sincos3 __neon_sincos3
#define __sincos4 __neon_sincos4
#define __sincos5 __neon_sincos5
#define __sincos6 __neon_sincos6
#define __sincos7 __neon_sincos7
#define __sincos8 __neon_sincos8

#define __sincosf1 __neon_sincosf1
#define __sincosf2 __neon_sincosf2
#define __sincosf3 __neon_sincosf3
#define __sincosf4 __neon_sincosf4
#define __sincosf5 __neon_sincosf5
#define __sincosf6 __neon_sincosf6
#define __sincosf7 __neon_sincosf7
#define __sincosf8 __neon_sincosf8


#else

/*
 float64 default implementation
*/

//interval [0, pi/2]
#define __sincos1(x, _s, _c) \
 	 *_s = ((((0.028419240510851106 * x + -0.20266577327037072) * x + 0.019080842223381331) * x + 0.99642139497886761) * x + 0.00000062377991903727); \
  	*_c = ((((0.028419240510851106 * x + 0.024102418851388162) * x + -0.51522912260478604) * x + 0.0032202099707060541) * x + 0.99989227622008092);

//interval [pi/2, pi]
#define __sincos2(x, _s, _c) \
 	 *_s = ((((0.028419240510851106 * x + -0.15446093556759441) * x + -0.20807910376841424) * x + 1.3596838236791193) * x + -0.1968404310997216); \
   *_c = ((((-2.8419240510851105e-2 * x + 3.8122912768935326e-1) * x - 1.3948507907160879) * x + 1.0042835118007021) * x + 5.5948009821321672e-1);

//interval [pi, pi+(pi/2)]
#define __sincos3(x, _s, _c) \
   *_s = ((((-0.028419240510851103 * x + 0.55979248210833576) * x + -3.6120807228733334) * x + 8.6488594332797177) * x + -6.1102813795057216); \
   *_c = ((((-2.8419240510851109e-2 * x + 3.3302428998657699e-1) * x - 9.4053089873249697e-1) * x - 4.2944494317606792e-1) * x + 2.0743658093284209);

//interval [pi+(pi/2), tau]
#define __sincos4(x, _s, _c) \
 	 *_s = ((((-0.028419240510851113 * x + 0.51158764440555959) * x + -2.9306008848979479) * x + 5.4310209345087541) * x + -1.0354793094431121); \
   *_c = ((((2.84192405108511e-2 * x - 7.3835583652731825e-1) * x + 6.6707706386951177) * x - 2.4580830872428483e+1) * x + 3.0950983305259838e+1);

//interval [0, -(pi/2)]
#define __sincos5(x, _s, _c) \
 	 *_s = -((((0.028419240510851106 * x + -0.20266577327037072) * x + 0.019080842223381331) * x + 0.99642139497886761) * x + 0.00000062377991903727); \
  	*_c = ((((0.028419240510851106 * x + 0.024102418851388162) * x + -0.51522912260478604) * x + 0.0032202099707060541) * x + 0.99989227622008092);

//interval [-(pi/2), -pi]
#define __sincos6(x, _s, _c) \
   *_s = -((((0.028419240510851106 * x + -0.15446093556759441) * x + -0.20807910376841424) * x + 1.3596838236791193) * x + -0.1968404310997216); \
   *_c = ((((-2.8419240510851105e-2 * x + 3.8122912768935326e-1) * x - 1.3948507907160879) * x + 1.0042835118007021) * x + 5.5948009821321672e-1);

//interval [-pi, -(pi+(pi/2))]
#define __sincos7(x, _s, _c) \
   *_s = -((((-0.028419240510851103 * x + 0.55979248210833576) * x + -3.6120807228733334) * x + 8.6488594332797177) * x + -6.1102813795057216); \
   *_c = ((((-2.8419240510851109e-2 * x + 3.3302428998657699e-1) * x - 9.4053089873249697e-1) * x - 4.2944494317606792e-1) * x + 2.0743658093284209);

//interval [-(pi+(pi/2)), -tau]
#define __sincos8(x, _s, _c) \
   *_s = -((((-0.028419240510851113 * x + 0.51158764440555959) * x + -2.9306008848979479) * x + 5.4310209345087541) * x + -1.0354793094431121); \
   *_c = ((((2.84192405108511e-2 * x - 7.3835583652731825e-1) * x + 6.6707706386951177) * x - 2.4580830872428483e+1) * x + 3.0950983305259838e+1);


/*
 float32 default implementation
*/
//interval [0, pi/2]
#define __sincosf1(x, _s, _c) \
 	 *_s = ((((0.0284192f * x + -0.2026657f) * x + 0.0190808f) * x + 0.9964213f) * x + 0.0000006f); \
   *_c = ((((0.0284192f * x + 0.0241024f) * x + -0.5152291f) * x + 0.0032202f) * x + 0.9998922f);

//interval [pi/2, pi]
#define __sincosf2(x, _s, _c) \
 	 *_s = ((((0.0284192f * x + -0.1544609f) * x + -0.2080791f) * x + 1.3596838f) * x + -0.1968404f); \
   *_c = ((((-2.8419240e-2f * x + 3.8122912e-1f) * x - 1.3948507f) * x + 1.0042835f) * x + 5.5948009e-1f);

//interval [pi, pi+(pi/2)]
#define __sincosf3(x, _s, _c) \
   *_s = ((((-0.0284192f * x + 0.5597924f) * x + -3.6120807f) * x + 8.6488594f) * x + -6.1102813f); \
   *_c = ((((-2.8419240e-2f * x + 3.3302428e-1f) * x - 9.4053089e-1f) * x - 4.2944494e-1f) * x + 2.0743658f);

//interval [pi+(pi/2), tau]
#define __sincosf4(x, _s, _c) \
 	 *_s = ((((-0.0284192f * x + 0.5115876f) * x + -2.9306008f) * x + 5.4310209f) * x + -1.0354793f); \
   *_c = ((((2.8419240e-2f * x - 7.3835583e-1f) * x + 6.6707706f) * x - 2.4580830e+1f) * x + 3.0950983e+1f);

//interval [0, -(pi/2)]
#define __sincosf5(x, _s, _c) \
 	 *_s = -((((0.0284192f * x + -0.2026657f) * x + 0.0190808f) * x + 0.9964213f) * x + 0.0000006f); \
   *_c = ((((0.0284192f * x + 0.0241024f) * x + -0.5152291f) * x + 0.0032202f) * x + 0.9998922f);

//interval [-(pi/2), -pi]
#define __sincosf6(x, _s, _c) \
 	 *_s = -((((0.0284192f * x + -0.1544609f) * x + -0.2080791f) * x + 1.3596838f) * x + -0.1968404f); \
   *_c = ((((-2.8419240e-2f * x + 3.8122912e-1f) * x - 1.3948507f) * x + 1.0042835f) * x + 5.5948009e-1f);

//interval [-pi, -(pi+(pi/2))]
#define __sincosf7(x, _s, _c) \
   *_s = -((((-0.0284192f * x + 0.5597924f) * x + -3.6120807f) * x + 8.6488594f) * x + -6.1102813f); \
   *_c = ((((-2.8419240e-2f * x + 3.3302428e-1f) * x - 9.4053089e-1f) * x - 4.2944494e-1f) * x + 2.0743658f);

//interval [-(pi+(pi/2)), -tau]
#define __sincosf8(x, _s, _c) \
 	 *_s = -((((-0.0284192f * x + 0.5115876f) * x + -2.9306008f) * x + 5.4310209f) * x + -1.0354793f); \
   *_c = ((((2.8419240e-2f * x - 7.3835583e-1f) * x + 6.6707706f) * x - 2.4580830e+1f) * x + 3.0950983e+1f);


#endif


void cfm_sincos(double x, double* _s, double* _c) {
 int64_t inv_quad = 0;
 if((*(uint64_t*)&x) & 0x8000000000000000) {
  (*(uint64_t*)&x) &= 0x7FFFFFFFFFFFFFFF; // x = |x|
  inv_quad = 1 << 5;
 }
 
 if((*(uint64_t*)&x) > 0x401921fb54442d18) //x > tau
  x = x - (int64_t)(x * 0.15915494309189534561) * 6.28318530717958623200;

 switch((int64_t)(x * 0.636619772367581382432888403855) | inv_quad) {
 	case 0:
 	 __sincos1(x, _s, _c);
 	break;
 	case 1:
 	 __sincos2(x, _s, _c);
 	break;
 	case 2:
 	 __sincos3(x, _s, _c);
 	break;
 	case 3:
 	 __sincos4(x, _s, _c);
 	break;
  // negative x
 	case 32:
 	 __sincos5(x, _s, _c);
  break;
  case 33:
   __sincos6(x, _s, _c);
  break;
  case 34:
   __sincos7(x, _s, _c);
  break;
  case 35:
   __sincos8(x, _s, _c);
  break;
 }
}


void cfm_sincosf(float x, float* _s, float* _c) {
 int32_t inv_quad = 0;
 if((*(uint32_t*)&x) & 0x80000000) {
  (*(uint32_t*)&x) &= 0x7FFFFFFF; // x = |x|
  inv_quad = 1 << 5;
 }
 
 if((*(uint32_t*)&x) > 0x40c90fdb) // x > tau
  x = x - (int32_t)(x * 0.1591549f) * 6.2831853f;

 switch((int32_t)(x * 0.6366197f) | inv_quad) {
 	case 0:
 	 __sincosf1(x, _s, _c);
 	break;
 	case 1:
 	 __sincosf2(x, _s, _c);
 	break;
 	case 2:
 	 __sincosf3(x, _s, _c);
 	break;
 	case 3:
 	 __sincosf4(x, _s, _c);
 	break;
  // negative x
 	case 32:
 	 __sincosf5(x, _s, _c);
 	break;
 	case 33:
 	 __sincosf6(x, _s, _c);
 	break;
 	case 34:
 	 __sincosf7(x, _s, _c);
 	break;
 	case 35:
 	 __sincosf8(x, _s, _c);
 	break;
 }
}

