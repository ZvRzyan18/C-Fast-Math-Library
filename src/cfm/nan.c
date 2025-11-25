#include "cfm/math.h"
#include "cfm/float_bits.h"
#include <stdint.h>

/*
 return nan value
*/
//---------------DOUBLE------------------//

double cfm_nan() {
	double_bits bits;
	bits.i = 0x7FF0000000000001;
 return bits.f;
}

//---------------FLOAT------------------//

float cfm_nanf() {
 float_bits bits;
 bits.i = 0x7F800001;
 return bits.f;
}

