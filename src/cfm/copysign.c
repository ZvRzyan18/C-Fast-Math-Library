#include "cfm/math.h"
#include "cfm/float_bits.h"
#include <stdint.h>

/*
 copy the sign bit of floating point
*/
//---------------DOUBLE------------------//

double cfm_copysign(double x, double sign) {
 double_bits bits_a, bits_b, out_bits;
 bits_a.f = x; bits_b.f = sign;
 out_bits.i = (bits_a.i & 0x7FFFFFFFFFFFFFFF) | (bits_b.i & 0x8000000000000000);
 return out_bits.f;
}

//---------------FLOAT------------------//

float cfm_copysignf(float x, float sign) {
 float_bits bits_a, bits_b, out_bits;
 bits_a.f = x; bits_b.f = sign;
 out_bits.i = (bits_a.i & 0x7FFFFFFF) | (bits_b.i & 0x80000000);
 return out_bits.f;
}

