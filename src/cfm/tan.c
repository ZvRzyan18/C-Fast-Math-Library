#include "cfm/math.h"
#include "cfm/float_bits.h"
#include <stdint.h>

/*
 tangent
          • (x, y) normalized value of circle
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
static const double DC[5] = {
  1.4837952430518087e-07,
 -8.6715056458098863e-06,
  2.6041160896346602e-04,
 -3.1249990095943724e-03,
  6.2499999689599175e-03,
};


static const float FC[5] = {
  1.48379524e-07,
 -8.67150564e-06,
  2.60411608e-04,
 -3.12499900e-03,
  6.24999996e-03,
};


//---------------DOUBLE------------------//

double cfm_tan(double x) {
  /*
   convert to fixed point of (65536 / TAU)
   and use intentional overflow so we dont have to
   use remainder operation.
  */
  uint16_t tx = (uint16_t)(cfm_fabs(x) * 10430.378350);
  int16_t ix = (int16_t)tx;
  uint8_t fp = (tx >= 0x3FFF) && (tx <= 0xBFFF);
  ix = fp ? 0x7FFF - ix : ix;

  double t = ((double)ix) * 0.0000958738;

  double x2 = t * t;
  double mx = ((((DC[0] * x2 + DC[1]) * x2 + DC[2]) * x2 + DC[3]) * x2 + DC[4]) * 0.160e+3;
  double mx1 = cfm_sqrt(1.0 - mx * mx);
  return (((x < 0.0) ^ (tx > 0x7FFF)) ? -mx1 : mx1) / (fp ? -mx : mx);
}

//---------------FLOAT------------------//

float cfm_tanf(float x) {
  /*
   convert to fixed point of (65536 / TAU)
   and use intentional overflow so we dont have to
   use remainder operation.
  */
  uint16_t tx = (uint16_t)(cfm_fabsf(x) * 10430.378350f);
  int16_t ix = (int16_t)tx;
  uint8_t fp = (tx >= 0x3FFF) && (tx <= 0xBFFF);
  ix = fp ? 0x7FFF - ix : ix;

  float t = ((float)ix) * 0.0000958738f;

  float x2 = t * t;
  float mx = ((((FC[0] * x2 + FC[1]) * x2 + FC[2]) * x2 + FC[3]) * x2 + FC[4]) * 0.160e+3f;
  float mx1 = cfm_sqrtf(1.0f - mx * mx);
  return (((x < 0.0f) ^ (tx > 0x7FFF)) ? -mx1 : mx1) / (fp ? -mx : mx);
}

