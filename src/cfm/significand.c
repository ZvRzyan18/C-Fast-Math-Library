#include "cfm/math.h"
#include "cfm/float_bits.h"
#include <stdint.h>

/*
 convert mantissa into representable floating point value
*/
double cfm_significand(double x) {
	double_bits bits, out_bits;
	bits.f = x;
	out_bits.i = (4607182418800017408U | (bits.i & 0x000FFFFFFFFFFFFF)) | ((bits.i & 0x8000000000000000) ? 0x8000000000000000 : 0);
	return out_bits.f;
}

float cfm_significandf(float x) {
	float_bits bits, out_bits;
	bits.f = x;
	out_bits.i = (1065353216U | (bits.i & 0x007FFFFF)) | ((bits.i & 0x80000000) ? 0x80000000 : 0);
	return out_bits.f;
}

