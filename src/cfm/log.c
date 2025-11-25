#include "cfm/math.h"
#include "cfm/float_bits.h"
#include <stdint.h>

//ln(x) = log2(x) * ln2

/*
 logarithm base e or
 natural logarithm
*/

/*

 
                                        ______
                                    __ -
  logarithmic growth ->         __ -
                            _ -
                           /
                          -
                         /
    udefined negatives  |
      -------|-------|--}* -> point exactly to one
                       /
                       | -> below 1.0 are negatives
                       /
   
-> gradually goes to zero with negative sign


  ln(x) = log2(x) / log2(e)
 
*/
static const double DC[6] = {
 -8.1615808498122383e-02,
  6.4514236358772082e-01,
 -2.1206751311142674e-00,
  4.0700907918522014e-00,
 -2.5128546239033371e-00,
  0.6931471805599452e-00,
};

static const double FC[6] = {
 -8.16158084e-02f,
  6.45142363e-01f,
 -2.12067513e-00f,
  4.07009079e-00f,
 -2.51285462e-00f,
  0.69314718e-00f,
};


//---------------DOUBLE------------------//

double cfm_log(double x) {
 double_bits bits, mantissa;
 double mx;
 int64_t hi;
 uint32_t lo;
 
 bits.f = x;
 lo = (bits.i >> 52) < 1023;
 bits.f = lo ? 1.0 / bits.f : bits.f;
 mantissa.i = 4607182418800017408U | (bits.i & 0x000FFFFFFFFFFFFF);
 hi = ((int64_t)(bits.i >> 52) - 1023);
 mx = mantissa.f;
 mx = ((((DC[0] * mx + DC[1]) * mx + DC[2]) * mx + DC[3]) * mx + DC[4]);
 mx = ((double)hi + mx) * DC[5];
 return lo ? -mx : mx;
}

//---------------FLOAT------------------//

float cfm_logf(float x) {
 float_bits bits, mantissa;
 float mx;
 int32_t hi;
 uint32_t lo;
 
 bits.f = x;
 lo = (bits.i >> 23) < 127;
 bits.f = lo ? 1.0f / bits.f : bits.f;
 mantissa.i = 1065353216U | (bits.i & 0x007FFFFF);
 hi = ((int64_t)(bits.i >> 23) - 127);
 mx = mantissa.f;
 mx = ((((FC[0] * mx + FC[1]) * mx + FC[2]) * mx + FC[3]) * mx + FC[4]);
 mx = ((float)hi + mx) * FC[5];
 return lo ? -mx : mx;
}

