#include "cfm/math.h"
#include "cfm/float_bits.h"
#include <stdint.h>

/*
 exponential base 2
*/

/*

 
                exponential growth

                        /
                       |
                      /   
                     |
                    /
                ---*  <- point exactly to one
              __
    _______---      <- negative values are always below one

    exp2(x) = exp(x * ln(2))
*/
/*
 approximation : f(x) = exp2(x) for [0, 0.5]
*/
static const double DC[5] = {
 0.1145799711195791e-01,
 0.5467185395011767e-01,
 0.2403778499718522e-00,
 0.6931375989500995e-00,
 1.0000000969209102e-00
};



static const float FC[5] = {
 0.11457997e-01f,
 0.54671853e-01f,
 0.24037784e-00f,
 0.69313759e-00f,
 1.00000009e-00f
};

//---------------DOUBLE------------------//

double cfm_exp2(double x) {
 double mx, a;
	double_bits bits;
 int64_t whole;

 if(cfm_fabs(x) < 0.5) {
 	a = x;
  return (((DC[0] * a + DC[1]) * a + DC[2]) * a + DC[3]) * a + DC[4];
 }
	a = x;
 whole = (int64_t)(a - 0.5);
 a = a - ((double)whole);
 bits.i = (uint64_t)((int64_t)(1023 + whole) << 52);
 mx = (((DC[0] * a + DC[1]) * a + DC[2]) * a + DC[3]) * a + DC[4];
 return bits.f * mx;
}

//---------------FLOAT------------------//

float cfm_exp2f(float x) {
 float mx, a;
	float_bits bits;
 int32_t whole;

 if(cfm_fabsf(x) < 0.5f) {
 	a = x;
  return (((FC[0] * a + FC[1]) * a + FC[2]) * a + FC[3]) * a + FC[4];
 }
	a = x;
 whole = (int32_t)(a - 0.5f);
 a = a - ((float)whole);
 bits.i = (uint32_t)((int32_t)(127 + whole) << 23);
 mx = (((FC[0] * a + FC[1]) * a + FC[2]) * a + FC[3]) * a + FC[4];
 return bits.f * mx;
}

