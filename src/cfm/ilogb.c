#include "cfm/math.h"
#include "cfm/float_bits.h"
#include <stdint.h>

//extract float and double exponent 
//and return it as signed integer
//---------------DOUBLE------------------//

int cfm_ilogb(double x) {
	double_bits bits;
	bits.f = x; //make sure its signed int before subtracting
	return ((int)((bits.i & 0x7FFFFFFFFFFFFFFF) >> 52) - 1023);
}

//---------------FLOAT------------------//

int cfm_ilogbf(float x) {
	float_bits bits;
	bits.f = x; //make sure its signed int before subtracting
	return ((int)((bits.i & 0x7FFFFFFF) >> 23) - 127);
}

