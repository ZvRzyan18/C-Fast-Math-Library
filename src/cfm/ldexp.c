#include "cfm/math.h"
#include "cfm/float_bits.h"
#include <stdint.h>

//---------------DOUBLE------------------//

double cfm_ldexp(double x, int _exp) {
	double_bits bits;
	bits.i = (uint64_t)(_exp + 1023) << 52;
	return bits.f * x;
}

//---------------FLOAT------------------//

float cfm_ldexpf(float x, int _exp) {
	float_bits bits;
	bits.i = (_exp + 127) << 23;
	return bits.f * x;
}

