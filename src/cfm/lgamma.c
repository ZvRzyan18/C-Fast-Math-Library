#include "cfm/math.h"
#include "cfm/float_bits.h"
#include <stdint.h>

//https://www.rskey.org/CMS/the-library/?view=article&id=11
//https://compbio.mit.edu/dlcoal/pub/dlcoal/src/spidir/gamma.cpp
//Lanczos approximation to the gamma function


static const double DC[10] = {
  1.0000000001900150e-00,
  7.6180091729471460e+01,
 -8.6505320329416770e+01,
  2.4014098240830910e+01,
 -1.2317395724501550e-00,
  1.2086509738661790e-03, 
 -5.3952393849530000e-06,

  2.5066282746310002e-00,//7 sqrt(tau)
  3.1415926535897932e-00,//8 pi
  2.5066282746310005e-00,
};


static const float FC[10] = {
  1.00000000e-00f,
  7.61800917e+01f,
 -8.65053203e+01f,
  2.40140982e+01f,
 -1.23173957e-00f,
  1.20865097e-03f, 
 -5.39523938e-06f,

  2.50662827e-00f,//7 sqrt(tau)
  3.14159265e-00f,//8 pi
  2.50662827e-00f,
};


//TODO : unhandled negative x

//lgamma(x) = log(tgamma(x))
//---------------DOUBLE------------------//

double cfm_lgamma(double x) {
 double mx, mx1, mx2, x_1, x_2, x_3, x_4, x_5, x_6;
 mx = x - 1.0;
 mx2 = mx + 5.5;
 
 x_1 = mx + 1.0;
 x_2 = mx + 2.0;
 x_3 = mx + 3.0;
 x_4 = mx + 4.0;
 x_5 = mx + 5.0;
 x_6 = mx + 6.0;
 
 mx1 = DC[0] + DC[1] / x_1 + DC[2] / x_2 + DC[3] / x_3 + DC[4] / x_4 + DC[5] / x_5 + DC[6] / x_6;
 mx1 = cfm_log(DC[9] * mx1);
 mx2 = -(mx2 - (mx + 0.5) * cfm_log(mx2));
 return mx2 + mx1;
}

//---------------FLOAT------------------//

float cfm_lgammaf(float x) {
 float mx, mx1, mx2, x_1, x_2, x_3, x_4, x_5, x_6;
 mx = x - 1.0f;
 mx2 = mx + 5.5f;
 
 x_1 = mx + 1.0f;
 x_2 = mx + 2.0f;
 x_3 = mx + 3.0f;
 x_4 = mx + 4.0f;
 x_5 = mx + 5.0f;
 x_6 = mx + 6.0f;
 
 mx1 = FC[0] + FC[1] / x_1 + FC[2] / x_2 + FC[3] / x_3 + FC[4] / x_4 + FC[5] / x_5 + FC[6] / x_6;
 mx1 = cfm_logf(FC[9] * mx1);
 mx2 = -(mx2 - (mx + 0.5) * cfm_logf(mx2));
 return mx2 + mx1;
}

