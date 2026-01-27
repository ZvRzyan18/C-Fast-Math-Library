#include "cfm/math.h"
#include "cfm/float_bits.h"
#include <stdint.h>

//---------------DOUBLE------------------//

double cfm_frexp(double x, int* _exp) {
 double_bits bits, mantissa;
 bits.f = x;
 *_exp = (((int64_t)(bits.i & 0x7FFFFFFFFFFFFFFF) >> 52)-1023) + 1;
 mantissa.i = 4607182418800017408U | (bits.i & 0x000FFFFFFFFFFFFF);
 return mantissa.f * 0.5;
}

//---------------FLOAT------------------//

float cfm_frexpf(float x, int* _exp) {
 float_bits bits, mantissa;
 bits.f = x;
 *_exp = (((int32_t)(bits.i & 0x7FFFFFFF) >> 23)-127) + 1;
 mantissa.i = 1065353216U | ((*(uint32_t*)&x) & 0x007FFFFF);
 return mantissa.f * 0.5f;
}

