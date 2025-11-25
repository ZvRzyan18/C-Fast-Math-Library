#include "cfm/math.h"
#include "cfm/float_bits.h"
#include <stdint.h>

//exp(x) = exp2(x / ln2)

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

    exp(x) = exp2(x * ln(e))
*/

/*
 exponential
*/
static const double DC[6] = {
 1.3697664475809267e-02,
 5.1690358205939469e-02,
 2.4163844572498163e-01,
 6.9296612266139567e-01,
 1.0000037044659370e-00,
 1.4426950408889633e-00,
};


static const float FC[6] = {
 1.369766e-02f,
 5.169035e-02f,
 2.416384e-01f,
 6.929661e-01f,
 1.000003e-00f,
 1.442695e-00f,
};

//---------------DOUBLE------------------//

double cfm_exp(double x) {
 double mx, frac;
 uint64_t sign;
 int64_t whole;
 double_bits bits;
 
 bits.f = x * DC[5];
 sign = bits.i & 0x8000000000000000;
 bits.i = sign ? bits.i & 0x7FFFFFFFFFFFFFFF : bits.i;
 mx = bits.f;
 whole = (int64_t)mx;
 frac = mx - (double)whole;
 bits.i = (uint64_t)(1023 + whole) << 52;
 mx = ((((DC[0] * frac + DC[1]) * frac + DC[2]) * frac + DC[3]) * frac + DC[4]);
 mx = mx * bits.f;
 return sign ? 1.0 / mx : mx;
}

//---------------FLOAT------------------//

float cfm_expf(float x) {
 float mx, frac;
 uint32_t sign;
 int32_t whole;
 float_bits bits;
 
 bits.f = x * FC[5];
 sign = bits.i & 0x80000000;
 bits.i = sign ? bits.i & 0x7FFFFFFF : bits.i;
 mx = bits.f;
 whole = (int32_t)mx;
 frac = mx - (float)whole;
 bits.i = (uint32_t)(127 + whole) << 23;
 mx = ((((FC[0] * frac + FC[1]) * frac + FC[2]) * frac + FC[3]) * frac + FC[4]);
 mx = mx * bits.f;
 return sign ? 1.0f / mx : mx;
}

