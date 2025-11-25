#include "cfm/math.h"
#include "cfm/float_bits.h"
#include <stdint.h>

//pow(x, y) = exp2(y * log2(x))
// its preferable to use exp2 and log2 since they have no loss, unlike exp and log

//implemented using inlined functions of exp2 and log2
static const double DC[10] = {
  1.3697664475809267e-02,
  5.1690358205939469e-02,
  2.4163844572498163e-01,
  6.9296612266139567e-01,
  1.0000037044659370e-00,

 -8.1615808498122383e-02,
  6.4514236358772082e-01,
 -2.1206751311142674e-00,
  4.0700907918522014e-00,
 -2.5128546239033371e-00,
};


static const float FC[10] = {
  1.36976644e-02f,
  5.16903582e-02f,
  2.41638445e-01f,
  6.92966122e-01f,
  1.00000370e-00f,

 -8.16158084e-02f,
  6.45142363e-01f,
 -2.12067513e-00f,
  4.07009079e-00f,
 -2.51285462e-00f,
};

//---------------DOUBLE------------------//

double cfm_pow(double x, double y) {
 double_bits bits, mantissa;
 double mx, frac;
 int64_t hi, whole;
 uint32_t lo, sign;
 
 bits.f = x;
 lo = (bits.i >> 52) < 1023;
 bits.f = lo ? 1.0 / bits.f : bits.f;
 mantissa.i = 4607182418800017408U | (bits.i & 0x000FFFFFFFFFFFFF);
 hi = ((int64_t)(bits.i >> 52) - 1023);
 mx = mantissa.f;
 mx = ((((DC[5] * mx + DC[6]) * mx + DC[7]) * mx + DC[8]) * mx + DC[9]);
 mx = ((double)hi + mx) * y;
 mx = lo ? -mx : mx;
 
 bits.f = mx;
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

float cfm_powf(float x, float y) {
 float_bits bits, mantissa;
 float mx, frac;
 int32_t hi, whole;
 uint32_t lo, sign;
 
 bits.f = x;
 lo = (bits.i >> 23) < 127;
 bits.f = lo ? 1.0f / bits.f : bits.f;
 mantissa.i = 1065353216U | (bits.i & 0x007FFFFF);
 hi = ((int64_t)(bits.i >> 23) - 127);
 mx = mantissa.f;
 mx = ((((FC[5] * mx + FC[6]) * mx + FC[7]) * mx + FC[8]) * mx + FC[9]);
 mx = ((float)hi + mx) * y;
 mx = lo ? -mx : mx;
 
 bits.f = mx;
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

