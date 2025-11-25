#include "cfm/math.h"
#include "cfm/float_bits.h"
#include <stdint.h>

/*
 sine
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
*/
/*
 sin(x) = cos(pi_half - x)
*/

static const double DC[9] = {
 -2.4429308463105237e-08,
  2.7548796448694666e-06,
 -1.9841222142485878e-04,
  8.3333332398349402e-03,
 -1.6666666666373373e-01, //4

  0.1591549430918950e-00, //5 inv tau
  0.6366197723675810e-00, //6 inv pio2
  1.5707963267948965e-00, //7 pio2
  6.2831853071795862e-00, //8 tau
};

static const float FC[9] = {
 -2.44293084e-08f,
  2.75487964e-06f,
 -1.98412221e-04f,
  8.33333323e-03f,
 -1.66666666e-01f, //4

  0.15915494e-00f, //5 inv tau
  0.63661977e-00f, //6 inv pio2
  1.57079632e-00f, //7 pio2
  6.28318530e-00f, //8 tau
};

//---------------DOUBLE------------------//

double cfm_sin(double x) {
 double mx, mx_s, x2_s, out_s, a;
 uint32_t flip_s, q;
 uint64_t sign_s;
 double_bits bits;
 
 bits.f = x;
 sign_s = bits.i & 0x8000000000000000;
 bits.i = sign_s ? bits.i & 0x7FFFFFFFFFFFFFFF : bits.i;
 a = bits.f;
 
 //remainder
 a = a - (double)(uint64_t)(a * DC[5]) * DC[8];
 q = (uint32_t)(a * DC[6]);
 mx = a;
 mx = mx - (DC[7] * (double)q);
 mx_s = mx;
 
 flip_s = (q == 1 || q == 3);
 sign_s = sign_s ^ ((uint64_t)(q == 2 || q == 3) << 63);
 mx_s = flip_s ? (DC[7] - mx_s) : mx_s;
 x2_s = mx_s * mx_s;
 out_s = ((((DC[0] * x2_s + DC[1]) * x2_s + DC[2]) * x2_s + DC[3]) * x2_s + DC[4]);
 out_s = out_s * (x2_s * mx_s) + mx_s;

 bits.f = out_s;
 bits.i |= sign_s;
 return bits.f;
}


//---------------FLOAT------------------//

float cfm_sinf(float x) {
 float mx, mx_s, x2_s, out_s, a;
 uint32_t sign_s, flip_s, q;
 float_bits bits;
 
 bits.f = x;
 sign_s = bits.i & 0x80000000;
 bits.i = sign_s ? bits.i & 0x7FFFFFFF : bits.i;
 a = bits.f;
 
 //remainder
 a = a - (float)(uint32_t)(a * FC[5]) * FC[8];
 q = (uint32_t)(a * FC[6]);
 mx = a;
 mx = mx - (FC[7] * (float)q);
 mx_s = mx;
 
 flip_s = (q == 1 || q == 3);
 sign_s = sign_s ^ ((uint32_t)(q == 2 || q == 3) << 31);
 mx_s = flip_s ? (FC[7] - mx_s) : mx_s;
 x2_s = mx_s * mx_s;

 out_s = ((((FC[0] * x2_s + FC[1]) * x2_s + FC[2]) * x2_s + FC[3]) * x2_s + FC[4]);
 out_s = out_s * (x2_s * mx_s) + mx_s;

 bits.f = out_s;
 bits.i |= sign_s;
 return bits.f;
}

