#include "cfm/math.h"
#include <stdint.h>

/*
 only allowed to subtract a number into a much smaller ones
 otherwise, return zero
*/
//---------------DOUBLE------------------//

double cfm_fdim(double x, double y) {
	return y >= x ? 0.0 : x - y;
}

//---------------FLOAT------------------//

float cfm_fdimf(float x, float y) {
	return y >= x ? 0.0f : x - y;
}

