#include "cfm/math.h"
#include <stdint.h>

/*
 hyperbolic cosine
*/
//---------------DOUBLE------------------//

double cfm_cosh(double x) {
	double exp = cfm_exp(x);
	return (exp + (1.0 / exp)) * 0.5;
}

//---------------FLOAT------------------//

float cfm_coshf(float x) {
	float exp = cfm_expf(x);
	return (exp + (1.0f / exp)) * 0.5f;
}

