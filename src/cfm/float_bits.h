#ifndef CFM_FLOAT_BITS_H
#define CFM_FLOAT_BITS_H

#include <stdint.h>

/*
 type punning for both float and doubles
*/

//---------------DOUBLE------------------//

typedef union {
 double f;
 uint64_t i;
} double_bits;

//---------------FLOAT------------------//

typedef union {
 float f;
 uint32_t i;
} float_bits;


#endif
