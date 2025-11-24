#include "cfm/math.h"
#include <stdint.h>

//extract float and double exponent and return it as integer
int cfm_ilogb(double x) {
	return (int)(((((*(int64_t*)&x) & 0x7FFFFFFFFFFFFFFF) >> 52)-1023));
}

int cfm_ilogbf(float x) {
	return (int)(((((*(int32_t*)&x) & 0x7FFFFFFF) >> 23)-127));
}

