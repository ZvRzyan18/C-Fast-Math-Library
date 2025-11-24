#include "cfm/math.h"
#include <stdint.h>

double cfm_ldexp(double x, int _exp) {
	uint64_t out = (uint64_t)(_exp + 1023) << 52;
	return (*(double*)&out) * x;
}


float cfm_ldexpf(float x, int _exp) {
	uint32_t out = (_exp + 127) << 23;
	return (*(float*)&out) * x;
}

