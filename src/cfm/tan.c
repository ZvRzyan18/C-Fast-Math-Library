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
 uint32_t flip_s, flip_c, q;
 uint64_t sign_s, sign_c;
 double_bits bits;
 
 bits.f = x;
 sign_s = bits.i & 0x8000000000000000;
 bits.i = sign_s ? bits.i & 0x7FFFFFFFFFFFFFFF : bits.i;
 a = bits.f;
 
 //remainder
 a = a - (double)(uint64_t)(a * DC[10]) * DC[13];
 
 q = (uint32_t)(a * DC[11]);
 mx = a;
 mx = mx - (DC[12] * (double)q);
 
 //hoping that this is pipeline optimized 
 //execution
 mx_c = mx;
 mx_s = mx;
 
 flip_s = (q == 1 || q == 3);
 flip_c = (q == 1 || q == 3);
 sign_c = (uint64_t)(q == 1 || q == 2) << 63;

 sign_s = sign_s ^ ((uint64_t)(q == 2 || q == 3) << 63);

 mx_s = flip_s ? (DC[12] - mx_s) : mx_s;
 mx_c = flip_c ? (mx_c - DC[12]) : mx_c;

 x2_s = mx_s * mx_s;
 x2_c = mx_c * mx_c;

 out_s = ((((DC[0] * x2_s + DC[1]) * x2_s + DC[2]) * x2_s + DC[3]) * x2_s + DC[4]);
 out_c = ((((DC[5] * x2_c + DC[6]) * x2_c + DC[7]) * x2_c + DC[8]) * x2_c + DC[9]);
 
 out_s = out_s * (x2_s * mx_s) + mx_s;
 out_c = out_c * 160.0;

 bits.f = out_s;
 bits.i |= sign_s;
 out_s = bits.f;

 bits.f = out_c;
 bits.i |= sign_c;
 out_c = bits.f;
 
 return out_s/out_c;
}

//---------------FLOAT------------------//

float cfm_tanf(float x) {
 float mx, mx_s, mx_c, x2_c, x2_s, out_s, out_c, a;
 uint32_t sign_s, sign_c, flip_s, flip_c, q;
 float_bits bits;
 
 bits.f = x;
 sign_s = bits.i & 0x80000000;
 bits.i = sign_s ? bits.i & 0x7FFFFFFF : bits.i;
 a = bits.f;
 
 //remainder
 a = a - (float)(uint32_t)(a * FC[10]) * FC[13];
 
 q = (uint32_t)(a * FC[11]);
 mx = a;
 mx = mx - (FC[12] * (float)q);
 
 //hoping that this is pipeline optimized 
 //execution
 mx_c = mx;
 mx_s = mx;
 
 flip_s = (q == 1 || q == 3);
 flip_c = (q == 1 || q == 3);
 sign_c = (uint64_t)(q == 1 || q == 2) << 31;

 sign_s = sign_s ^ ((q == 2 || q == 3) << 31);

 mx_s = flip_s ? (FC[12] - mx_s) : mx_s;
 mx_c = flip_c ? (mx_c - FC[12]) : mx_c;

 x2_s = mx_s * mx_s;
 x2_c = mx_c * mx_c;

 out_s = ((((FC[0] * x2_s + FC[1]) * x2_s + FC[2]) * x2_s + FC[3]) * x2_s + FC[4]);
 out_c = ((((FC[5] * x2_c + FC[6]) * x2_c + FC[7]) * x2_c + FC[8]) * x2_c + FC[9]);
 
 out_s = out_s * (x2_s * mx_s) + mx_s;
 out_c = out_c * 160.0f;

 bits.f = out_s;
 bits.i |= sign_s;
 out_s = bits.f;

 bits.f = out_c;
 bits.i |= sign_c;
 out_c = bits.f;
 
 return out_s/out_c;
}

