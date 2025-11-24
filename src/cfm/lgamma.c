#include "cfm/math.h"
#include <stdint.h>

//https://www.rskey.org/CMS/the-library/?view=article&id=11
//https://compbio.mit.edu/dlcoal/pub/dlcoal/src/spidir/gamma.cpp
//Lanczos approximation to the gamma function


//TODO : unhandled negative x

//lgamma(x) = log(tgamma(x))

double cfm_lgamma(double x) {
 x = x - 1.0;
 double tmp = x + 5.5;
 return -(tmp - (x + 0.5) * cfm_log(tmp)) + cfm_log(2.5066282746310005 * ((1.000000000190015 + 76.18009172947146 / (x + 1.0) + -86.50532032941677 / (x + 2.0) + 24.01409824083091 / (x + 3.0) + -1.231739572450155 / (x + 4.0) + 1.208650973866179e-3 / (x + 5.0) + -5.395239384953e-6 / (x + 6.0))));
}


float cfm_lgammaf(float x) {
 x = x - 1.0f;
 double tmp = x + 5.5f;
 return -(tmp - (x + 0.5f) * cfm_logf(tmp)) + cfm_logf(2.506628f * ((1.000000f + 76.180091f / (x + 1.0f) + -86.505320f / (x + 2.0f) + 24.014098f / (x + 3.0f) + -1.231739f / (x + 4.0f) + 1.208650e-3f / (x + 5.0f) + -5.395239e-6f / (x + 6.0f))));
}

