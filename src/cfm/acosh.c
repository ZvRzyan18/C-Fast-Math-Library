#include "cfm/math.h"
#include <stdint.h>

/*
 hyperbolic arc cosine
*/
double cfm_acosh(double x) {
	return cfm_log(x + cfm_sqrt(x * x - 1.0));
}


float cfm_acoshf(float x) {
	return cfm_logf(x + cfm_sqrtf(x * x - 1.0f));
}

