#include "cfm/math.h"
#include "cfm/float_bits.h"
#include <stdint.h>

/*
 return infinity value 
*/
//---------------DOUBLE------------------//

double cfm_inf() {
	double_bits bits;
	bits.i = 0x7FF0000000000000;
 return bits.f;
}

//---------------FLOAT------------------//

float cfm_inff() {
 float_bits bits;
 bits.i = 0x7F800000;
 return bits.f;
}

