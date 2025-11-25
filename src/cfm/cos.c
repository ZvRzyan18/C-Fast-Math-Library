#include "cfm/math.h"
#include "cfm/float_bits.h"
#include <stdint.h>

/*
 cosine
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
 
  x = cos(angle)
*/
/*
 sin(x) = cos(pi_half - x)
*/

static const double DC[9] = {
  1.4837952430518087e-07,
 -8.6715056458098863e-06,
  2.6041160896346602e-04,
 -3.1249990095943724e-03,
  6.2499999689599175e-03,

  0.1591549430918950e-00, //10 inv tau
  0.6366197723675810e-00, //11 inv pio2
  1.5707963267948965e-00, //12 pio2
  6.2831853071795862e-00, //13 tau
};


static const float FC[9] = {
  1.48379524e-07,
 -8.67150564e-06,
  2.60411608e-04,
 -3.12499900e-03,
  6.24999996e-03,

  0.15915494e-00, //10 inv tau
  0.63661977e-00, //11 inv pio2
  1.57079632e-00, //12 pio2
  6.28318530e-00, //13 tau
};

//---------------DOUBLE------------------//

double cfm_cos(double x) {
 double mx, mx_c, x2_c, out_c, a;
 uint32_t flip_c, q;
 uint64_t sign_c;
 double_bits bits;
 
 bits.f = x;
 bits.i = bits.i & 0x7FFFFFFFFFFFFFFF;
 a = bits.f;
 
 //remainder
 a = a - (double)(uint64_t)(a * DC[5]) * DC[8];
 q = (uint32_t)(a * DC[6]);
 mx = a;
 mx = mx - (DC[7] * (double)q);
 mx_c = mx;
 
 flip_c = (q == 1 || q == 3);
 sign_c = (uint64_t)(q == 1 || q == 2) << 63;
 mx_c = flip_c ? (mx_c - DC[7]) : mx_c;
 x2_c = mx_c * mx_c;
 out_c = ((((DC[0] * x2_c + DC[1]) * x2_c + DC[2]) * x2_c + DC[3]) * x2_c + DC[4]);
 out_c = out_c * 160.0;

 bits.f = out_c;
 bits.i |= sign_c;
 return bits.f;
}

//---------------FLOAT------------------//

float cfm_cosf(float x) {
 float mx, mx_c, x2_c, out_c, a;
 uint32_t sign_c, flip_c, q;
 float_bits bits;
 
 bits.f = x;
 bits.i = bits.i & 0x7FFFFFFF;
 a = bits.f;
 
 //remainder
 a = a - (float)(uint32_t)(a * FC[5]) * FC[8];
 q = (uint32_t)(a * FC[6]);
 mx = a;
 mx = mx - (FC[7] * (float)q);
 mx_c = mx;
 
 flip_c = (q == 1 || q == 3);
 sign_c = (q == 1 || q == 2) << 31;
 mx_c = flip_c ? (mx_c - FC[7]) : mx_c;
 x2_c = mx_c * mx_c;
 out_c = ((((FC[0] * x2_c + FC[1]) * x2_c + FC[2]) * x2_c + FC[3]) * x2_c + FC[4]);
 out_c = out_c * 160.0f;

 bits.f = out_c;
 bits.i |= sign_c;
 return bits.f;
}

