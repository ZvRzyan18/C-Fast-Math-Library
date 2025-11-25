#include "cfm/math.h"
#include "cfm/float_bits.h"
#include <stdint.h>

//atan(y, x) = atan(y/x)

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
 
  angle = atan2(y, x)
*/

static const double DC[7] = {
 -1.8845002614985722e-02,
  7.0003356460380181e-02,
 -1.3122924564035410e-01,
  1.9875912337381560e-01,
 -3.3331170075737049e-01,
  1.5707963267948965e-00,
  3.1415926535897932e-00,
};


static const float FC[7] = {
 -1.88450026e-02f,
  7.00033564e-02f,
 -1.31229245e-01f,
  1.98759123e-01f,
 -3.33311700e-01f,
  1.57079632e-00f,
  3.14159265e-00f,
};

//---------------DOUBLE------------------//

double cfm_atan2(double y, double x) {
 double ratio, mx, x2;
 uint32_t both_lo, y_hi_x_lo;
 double_bits bits;
 uint32_t hi;
 
 both_lo = (y < 0.0 && x < 0.0);
 y_hi_x_lo = (y > 0.0 && x < 0.0);
 ratio = y / x;
 
 bits.f = ratio;
 bits.i = bits.i & 0x8000000000000000 ? bits.i & 0x7FFFFFFFFFFFFFFF : bits.i;
 hi = (bits.i >> 52) >= 1023;
 bits.f = hi ? 1.0 / bits.f : bits.f;
 mx = bits.f;
 x2 = mx * mx;
 mx = mx + (mx * x2) * ((((DC[0] * x2 + DC[1]) * x2 + DC[2]) * x2 + DC[3]) * x2 + DC[4]);
 mx = hi ? DC[5] - mx : mx;
 mx = cfm_copysign(mx, ratio);
 
 mx = both_lo ? mx - DC[6] : mx;
 return !both_lo && y_hi_x_lo ? mx + DC[6] : mx;
}

//---------------FLOAT------------------//

float cfm_atan2f(float y, float x) {
 float ratio, mx, x2;
 uint32_t both_lo, y_hi_x_lo;
 float_bits bits;
 uint32_t hi;
 
 both_lo = (y < 0.0f && x < 0.0f);
 y_hi_x_lo = (y > 0.0f && x < 0.0f);
 ratio = y / x;
 
 bits.f = ratio;
 bits.i = bits.i & 0x80000000 ? bits.i & 0x7FFFFFFF : bits.i;
 hi = (bits.i >> 23) >= 127;
 bits.f = hi ? 1.0f / bits.f : bits.f;
 mx = bits.f;
 x2 = mx * mx;
 mx = mx + (mx * x2) * ((((FC[0] * x2 + FC[1]) * x2 + FC[2]) * x2 + FC[3]) * x2 + FC[4]);
 mx = hi ? FC[5] - mx : mx;
 mx = cfm_copysignf(mx, ratio);
 
 mx = both_lo ? mx - FC[6] : mx;
 return !both_lo && y_hi_x_lo ? mx + FC[6] : mx;
}
