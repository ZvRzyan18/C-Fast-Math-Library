#include "cfm/math.h"
#include "cfm/float_bits.h"
#include <stdint.h>

/*
 tangent
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
 
  y = sin(angle)
  x = cos(angle)
  y/x = tan(angle)
*/

static const double DC[14] = {
 -2.4429308463105237e-08,
  2.7548796448694666e-06,
 -1.9841222142485878e-04,
  8.3333332398349402e-03,
 -1.6666666666373373e-01, //4

  1.4837952430518087e-07,
 -8.6715056458098863e-06,
  2.6041160896346602e-04,
 -3.1249990095943724e-03,
  6.2499999689599175e-03, //9

  0.1591549430918950e-00, //10 inv tau
  0.6366197723675810e-00, //11 inv pio2
  1.5707963267948965e-00, //12 pio2
  6.2831853071795862e-00, //13 tau
};


static const float FC[14] = {
 -2.44293084e-08f,
  2.75487964e-06f,
 -1.98412221e-04f,
  8.33333323e-03f,
 -1.66666666e-01f, //4

  1.48379524e-07f,
 -8.67150564e-06f,
  2.60411608e-04f,
 -3.12499900e-03f,
  6.24999996e-03f, //9

  0.15915494e-00f, //10 inv tau
  0.63661977e-00f, //11 inv pio2
  1.57079632e-00f, //12 pio2
  6.28318530e-00f, //13 tau
};


//---------------DOUBLE------------------//

double cfm_tan(double x) {
 double mx, mx_s, mx_c, x2_c, x2_s, out_s, out_c, a;
 uint32_t flip, q;
 uint64_t sign;
 double_bits bits;
 
 bits.f = x;
 bits.i = bits.i & 0x7FFFFFFFFFFFFFFF;
 a = bits.f;
 
 //remainder
 a = a - (double)(uint64_t)(a * DC[10]) * DC[13];
 
 q = (uint32_t)(a * DC[11]);
 mx = a;
 mx = mx - (DC[12] * (double)q);
 
 //hoping that this is pipeline optimized 
 //execution
 
 flip = (q == 1 || q == 3);

 mx = flip ? (DC[12] - mx) : mx;

 mx_c = mx;
 mx_s = mx;

 sign = (uint64_t)(flip) << 63;

 x2_s = mx_s * mx_s;
 x2_c = mx_c * mx_c;

 out_s = ((((DC[0] * x2_s + DC[1]) * x2_s + DC[2]) * x2_s + DC[3]) * x2_s + DC[4]);
 out_c = ((((DC[5] * x2_c + DC[6]) * x2_c + DC[7]) * x2_c + DC[8]) * x2_c + DC[9]);
 
 out_s = out_s * (x2_s * mx_s) + mx_s;
 out_c = out_c * 160.0;

 bits.f = out_s/out_c;
 bits.i |= sign;
 return bits.f;
}

//---------------FLOAT------------------//

float cfm_tanf(float x) {
 float mx, mx_s, mx_c, x2_c, x2_s, out_s, out_c, a;
 uint32_t flip, q;
 uint32_t sign;
 float_bits bits;
 
 bits.f = x;
 bits.i = bits.i & 0x7FFFFFFF;
 a = bits.f;
 
 //remainder
 a = a - (float)(uint32_t)(a * DC[10]) * DC[13];
 
 q = (uint32_t)(a * DC[11]);
 mx = a;
 mx = mx - (FC[12] * (float)q);
 
 //hoping that this is pipeline optimized 
 //execution
 
 flip = (q == 1 || q == 3);

 mx = flip ? (FC[12] - mx) : mx;

 mx_c = mx;
 mx_s = mx;

 sign = (uint32_t)(flip) << 31;

 x2_s = mx_s * mx_s;
 x2_c = mx_c * mx_c;

 out_s = ((((FC[0] * x2_s + FC[1]) * x2_s + FC[2]) * x2_s + FC[3]) * x2_s + FC[4]);
 out_c = ((((FC[5] * x2_c + FC[6]) * x2_c + FC[7]) * x2_c + FC[8]) * x2_c + FC[9]);
 
 out_s = out_s * (x2_s * mx_s) + mx_s;
 out_c = out_c * 160.0f;

 bits.f = out_s/out_c;
 bits.i |= sign;
 return bits.f;
}

