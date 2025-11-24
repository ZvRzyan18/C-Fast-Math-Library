#include "cfm/math.h"
#include <stdint.h>

/*
 hyperbolic arc sine
*/
double cfm_asinh(double x) {
	return cfm_log(x + cfm_sqrt(x * x + 1.0));
}


float cfm_asinhf(float x) {
	return cfm_logf(x + cfm_sqrtf(x * x + 1.0f));
}

