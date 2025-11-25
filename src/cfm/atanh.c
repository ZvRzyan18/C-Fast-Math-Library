#include "cfm/math.h"
#include <stdint.h>

/*
 hyperbolic arc tangent
*/
//---------------DOUBLE------------------//

double cfm_atanh(double x) {
	return 0.5 * cfm_log((1.0 + x) / (1.0 - x));
}

//---------------FLOAT------------------//

float cfm_atanhf(float x) {
	return 0.5f * cfm_logf((1.0f + x) / (1.0f - x));
}

