#include "cfm/math.h"
#include <stdint.h>

//extract float and double exponent and return it as float/double

double cfm_logb(double x) {
	return (double)(((((*(int64_t*)&x) & 0x7FFFFFFFFFFFFFFF) >> 52)-1023));
}


float cfm_logbf(float x) {
	return (float)(((((*(int32_t*)&x) & 0x7FFFFFFF) >> 23)-127));
}


