#include "cfm/math.h"
#include "cfm/float_bits.h"
#include <stdint.h>

/*
 arc sine
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
 
  angle = asin(y)
*/

/*
 approxiamtion

 acos(x) = acos(x)/sqrt(1.0 - x), interval : [0, 1]

 asin(x) = PI/2 - acos(x)
*/

static const double DC[6] = {
 -0.1872986877659853e-01,
  0.7426234494007040e-01,
 -0.2121152405852734e-00,
  1.5707288189560218e-00,
  3.1415926535897930e-00,
  1.5707963267948965e-00,
};

static const float FC[6] = {
 -0.18729868e-01f,
  0.74262344e-01f,
 -0.21211524e-00f,
  1.57072881e-00f,
  3.14159265e-00f,
  1.57079632e-00f,
};

//---------------DOUBLE------------------//

double cfm_asin(double x) {
 double mx;
 double mx1;
 double out;
 mx = cfm_fabs(x);
 mx1 = (((DC[0] * mx + DC[1]) * mx + DC[2]) * mx + DC[3]);
 out = mx1 * cfm_sqrt(1.0 - mx);
 return DC[5] - ((x < 0.0) ? DC[4] - out : out);
}

//---------------FLOAT------------------//

float cfm_asinf(float x) {
 float mx;
 float mx1;
 float out;
 mx = cfm_fabsf(x);
 mx1 = (((FC[0] * mx + FC[1]) * mx + FC[2]) * mx + FC[3]);
 out = mx1 * cfm_sqrtf(1.0f - mx);
 return FC[5] - ((x < 0.0f) ? FC[4] - out : out);
}

