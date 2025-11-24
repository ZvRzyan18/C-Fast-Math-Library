#include "cfm/math.h"
#include <stdint.h>

/*
 lower number subtraction
*/
double cfm_fdim(double x, double y) {
	return y >= x ? 0.0 : x - y;
}

float cfm_fdimf(float x, float y) {
	return y >= x ? 0.0f : x - y;
}

