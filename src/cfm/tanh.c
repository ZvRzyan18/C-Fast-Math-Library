#include "cfm/math.h"
#include <stdint.h>

/*
 hyperbolic tangent
*/
double cfm_tanh(double x) {
	double exp = cfm_exp(x);
	return (exp - (1.0 / exp)) / (exp + (1.0 / exp));
}


float cfm_tanhf(float x) {
	float exp = cfm_expf(x);
	return (exp - (1.0f / exp)) / (exp + (1.0f / exp));
}

