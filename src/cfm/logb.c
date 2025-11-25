#include "cfm/math.h"
#include "cfm/float_bits.h"
#include <stdint.h>

//extract float and double exponent 
//and return it as float/double

//---------------DOUBLE------------------//

double cfm_logb(double x) {
	double_bits bits;
	bits.f = x; //convert to signed value first before subtraction
	return (double)(( (int64_t) ((bits.i & 0x7FFFFFFFFFFFFFFF) >> 52) - 1023));
}

//---------------FLOAT------------------//

float cfm_logbf(float x) {
	float_bits bits;
	bits.f = x; //convert to signed value first before subtraction
	return (float)(( (int32_t) ((bits.i & 0x7FFFFFFF) >> 23) - 127));
}


