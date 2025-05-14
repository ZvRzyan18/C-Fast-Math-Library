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

#ifndef CFM_MATH_H
#define CFM_MATH_H

/*
 math constants
*/
#define CFM_PI		     3.141592653589793
#define CFM_PI_2	   	1.570796326794896
#define CFM_PI_4	   	0.785398163397448
#define CFM_1_PI	   	0.318309886183790
#define CFM_2_PI	   	0.636619772367581
#define CFM_E		      2.718281828459045
#define CFM_LOG2E  		1.442695040888963
#define CFM_LOG10E  	0.434294481903251
#define CFM_LN2		    0.693147180559945
#define CFM_LN10	   	2.302585092994045
#define CFM_2_SQRTPI	1.128379167095512
#define CFM_SQRT2		  1.414213562373095
#define CFM_SQRT1_2	 0.707106781186547

#define CFM_NAN cfm_nan()
#define CFM_INFINITY cfm_inf();

#ifdef __cplusplus
extern "C" {
#endif

/*
 math functions
*/

double cfm_inf();
float cfm_inff();

double cfm_nan();
float cfm_nanf();

double cfm_fabs(double x);
float cfm_fabsf(float x);

double cfm_trunc(double x);
float cfm_truncf(float x);

double cfm_floor(double x);
float cfm_floorf(float x);

double cfm_ceil(double x);
float cfm_ceilf(float x);

double cfm_round(double x);
float cfm_roundf(float x);

double cfm_sqrt(double x);
float cfm_sqrtf(float x);

double cfm_sin(double x);
float cfm_sinf(float x);

double cfm_cos(double x);
float cfm_cosf(float x);

double cfm_tan(double x);
float cfm_tanf(float x);

void cfm_sincos(double x, double* _s, double* _c);
void cfm_sincosf(float x, float* _s, float* _c);

double cfm_asin(double x);
float cfm_asinf(float x);

double cfm_acos(double x);
float cfm_acosf(float x);

double cfm_atan(double x);
float cfm_atanf(float x);

double cfm_atan2(double y, double x);
float cfm_atan2f(float y, float x);

double cfm_log2(double x);
float cfm_log2f(float x);

double cfm_exp2(double x);
float cfm_exp2f(float x);

double cfm_cbrt(double x);
float cfm_cbrtf(float x);

double cfm_pow(double x, double y);
float cfm_powf(float x, float y);

double cfm_exp(double x);
float cfm_expf(float x);

double cfm_log(double x);
float cfm_logf(float x);

double cfm_tgamma(double x);
float cfm_tgammaf(float x);

double cfm_lgamma(double x);
float cfm_lgammaf(float x);

double cfm_fmod(double x, double y);
float cfm_fmodf(float x, float y);

double cfm_frexp(double x, int* _exp);
float cfm_frexpf(float x, int* _exp);

double cfm_ldexp(double x, int _exp);
float cfm_ldexpf(float x, int _exp);

double cfm_logb(double x);
float cfm_logbf(float x);

int cfm_ilogb(double x);
int cfm_ilogbf(float x);

double cfm_hypot(double x, double y);
float cfm_hypotf(float x, float y);

double cfm_fma(double x, double y, double z);
float cfm_fmaf(float x, float y, float z);

double cfm_sinh(double x);
float cfm_sinhf(float x);

double cfm_cosh(double x);
float cfm_coshf(float x);

double cfm_tanh(double x);
float cfm_tanhf(float x);

double cfm_asinh(double x);
float cfm_asinhf(float x);

double cfm_acosh(double x);
float cfm_acoshf(float x);

double cfm_atanh(double x);
float cfm_atanhf(float x);

double cfm_erf(double x);
float cfm_erff(float x);

double cfm_erfc(double x);
float cfm_erfcf(float x);

double cfm_copysign(double x, double sign);
float cfm_copysignf(float x, float sign);

double cfm_significand(double x);
float cfm_significandf(float x);

double cfm_drem(double x, double y);
float cfm_dremf(float x, float y);

double cfm_scalb(double x, double _exp);
float cfm_scalbf(float x, float _exp);

double cfm_scalbn(double x, int _exp);
float cfm_scalbnf(float x, int _exp);

double cfm_fdim(double x, double y);
float cfm_fdimf(float x, float y);

#ifdef __cplusplus
}
#endif

#endif
