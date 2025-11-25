#include "cfm/math.h"
#include "cfm/float_bits.h"
#include <stdint.h>

/*
 arc cosine
          • (x, y) = normalized value
         /|
        / |
       /  |
      /   |
     /__  |
    /   | |
   •-------
   ^
  angle
 
  angle = acos(x)
*/
/*
 # arc cosine
 • for x between [0, 0.5] (4 degree polynomial)
 acosPoly(x) = c0 * x + c1 * x² + c2 * x³ + c3 * x⁴....
 acos(x) = acosPoly(x)
 
 • for x between [0.5, 1.0]
                                ____________
 acos(x) = pi - 2.0 * acosPoly(√ (1 - x) / 2)
*/

static const double DC[5] = {
 7.7426018886311967e-02,
 2.6132143752749238e-02,
 7.7127028227080299e-02,
 1.6662925962529435e-01,
 1.5707963267948965e-00,
};

static const float FC[5] = {
 7.74260188e-02f,
 2.61321437e-02f,
 7.71270282e-02f,
 1.66629259e-01f,
 1.57079632e-00f,
};

//---------------DOUBLE------------------//

double cfm_acos(double x) {
 double x2, mx;
 uint32_t hi;
 double_bits bits;
 bits.f = x;
 bits.i = (bits.i & 0x8000000000000000) ? bits.i & 0x7FFFFFFFFFFFFFFF : bits.i;
 hi = bits.f > 0.5;
 bits.f = hi ? cfm_sqrt((1.0 - bits.f) * 0.5) : bits.f;
 mx = bits.f;
 x2 = mx * mx;
 mx = mx + (mx * x2) * (((DC[0] * x2 + DC[1]) * x2 + DC[2]) * x2 + DC[3]);
 mx = hi ? DC[4] - (mx + mx) : mx;
 return DC[4] - cfm_copysign(mx, x);
}


//---------------FLOAT------------------//

float cfm_acosf(float x) {
 float x2, mx;
 uint32_t hi;
 float_bits bits;
 bits.f = x;
 bits.i = (bits.i & 0x80000000) ? bits.i & 0x7FFFFFFF : bits.i;
 hi = bits.f > 0.5f;
 bits.f = hi ? cfm_sqrtf((1.0f - bits.f) * 0.5f) : bits.f;
 mx = bits.f;
 x2 = mx * mx;
 mx = mx + (mx * x2) * (((FC[0] * x2 + FC[1]) * x2 + FC[2]) * x2 + FC[3]);
 mx = hi ? FC[4] - (mx + mx) : mx;
 return FC[4] - cfm_copysignf(mx, x);
}

