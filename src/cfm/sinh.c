#include "cfm/math.h"
#include <stdint.h>

/*
 hyperbolic sine
*/
double cfm_sinh(double x) {
	double exp = cfm_exp(x);
	return (exp - (1.0 / exp)) * 0.5;
}

float cfm_sinhf(float x) {
	float exp = cfm_expf(x);
	return (exp - (1.0f / exp)) * 0.5f;
}

