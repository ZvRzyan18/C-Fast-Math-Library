#include "cfm/math.h"
#include "cfm/float_bits.h"
#include <stdint.h>


/*
 arc tangent
          • (x, y) normalized value
         /|
        / |
       /  |
      /   |
     /__  |
    /   | |
   •-------
     ^
    angle
 
  angle = atan(y/x)
*/


/*
 # arc tangent
                     ________
 atan(x) = asin(x / √1 + x*x ) 

 • alternative (only works on positive x):
                     ________
 atan(x) = acos(1 / √1 + x*x )
*/

/*
 implementation
 
 for |x| <= 1.0
 
 atanPoly(x) = c0 * x + c1 * x² + c2 * x³....
 
 for |x| >= 1.0
 
 atan(x) pi_half - atanPoly(1.0 / x)
*/

static const double DC[6] = {
 -1.8845002614985722e-02,
  7.0003356460380181e-02,
 -1.3122924564035410e-01,
  1.9875912337381560e-01,
 -3.3331170075737049e-01,
  1.5707963267948965e-00,
};


static const float FC[6] = {
 -1.88450026e-02f,
  7.00033564e-02f,
 -1.31229245e-01f,
  1.98759123e-01f,
 -3.33311700e-01f,
  1.57079632e-00f,
};

//---------------DOUBLE------------------//

double cfm_atan(double x) {
 double x2, mx;
 double_bits bits;
 uint32_t hi;
 bits.f = x;
 bits.i = bits.i & 0x8000000000000000 ? bits.i & 0x7FFFFFFFFFFFFFFF : bits.i;
 hi = (bits.i >> 52) >= 1023;
 bits.f = hi ? 1.0 / bits.f : bits.f;
 mx = bits.f;
 x2 = mx * mx;
 mx = mx + (mx * x2) * ((((DC[0] * x2 + DC[1]) * x2 + DC[2]) * x2 + DC[3]) * x2 + DC[4]);
 mx = hi ? DC[5] - mx : mx;
 return cfm_copysign(mx, x);
}

//---------------FLOAT------------------//

float cfm_atanf(float x) {
 float x2, mx;
 float_bits bits;
 uint32_t hi;
 bits.f = x;
 bits.i = bits.i & 0x80000000 ? bits.i & 0x7FFFFFFF : bits.i;
 hi = (bits.i >> 23) >= 127;
 bits.f = hi ? 1.0f / bits.f : bits.f;
 mx = bits.f;
 x2 = mx * mx;
 mx = mx + (mx * x2) * ((((FC[0] * x2 + FC[1]) * x2 + FC[2]) * x2 + FC[3]) * x2 + FC[4]);
 mx = hi ? FC[5] - mx : mx;
 return cfm_copysignf(mx, x);
}


