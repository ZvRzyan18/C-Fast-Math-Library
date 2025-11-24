#include "cfm/math.h"
#include <stdint.h>

double cfm_frexp(double x, int* _exp) {
	*_exp = ((((*(int64_t*)&x) & 0x7FFFFFFFFFFFFFFF) >> 52)-1023) + 1;
	uint64_t mantissa = 4607182418800017408U | ((*(uint64_t*)&x) & 0x000FFFFFFFFFFFFF);
	return *(double*)&mantissa * 0.5;
}


float cfm_frexpf(float x, int* _exp) {
	*_exp = ((((*(int32_t*)&x) & 0x7FFFFFFF) >> 23)-127) + 1;
	uint32_t mantissa = 1065353216U | ((*(uint32_t*)&x) & 0x007FFFFF);
	return *(float*)&mantissa * 0.5f;
}

