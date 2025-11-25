#include "cfm/math.h"
#include <stdint.h>

/*
 scale the floating point base on its radix value
*/
//---------------DOUBLE------------------//

double cfm_scalb(double x, double _exp) {
	return x * cfm_exp2(_exp);
}

//---------------FLOAT------------------//

float cfm_scalbf(float x, float _exp) {
	return x * cfm_exp2f(_exp);
}

