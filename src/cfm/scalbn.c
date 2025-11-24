#include "cfm/math.h"
#include <stdint.h>

#if defined(__aarch64__)

__asm__ (
 ".type cfm_scalbn, @function \n"

 ".global cfm_scalbn \n"
 "cfm_scalbn: \n"
 //expoment
 "fmov x4, d0 \n"
 "ldr x3, =0x7FFFFFFFFFFFFFFF \n"
 "and x4, x4, x3 \n"
 "lsr x4, x4, #52 \n"
 "sxtw x3, w0 \n"
 "add x4, x4, x3 \n"
 "lsl x4, x4, #52 \n"
 
 //mantissa
 "fmov x5, d0 \n"
 "ldr x3, =0x000FFFFFFFFFFFFF \n"
 "and x5, x5, x3 \n"
 
 //sign bit
 "fmov x6, d0 \n"
 "ldr x3, =0x8000000000000000 \n"
 "and x6, x6, x3 \n"
 "lsl x6, x6, #63 \n"
 "orr x4, x4, x5 \n"
 "orr x4, x4, x6 \n"
 "fmov d0, x4 \n"
 "ret \n"
);


__asm__ (
 ".type cfm_scalbnf, @function \n"

 ".global cfm_scalbnf \n"
 "cfm_scalbnf: \n"
 //expoment
 "fmov w4, s0 \n"
 "ldr w3, =0x7FFFFFFF \n"
 "and w4, w4, w3 \n"
 "lsr w4, w4, #23 \n"
 "add w4, w4, w0 \n"
 "lsl w4, w4, #23 \n"
 
 //mantissa
 "fmov w5, s0 \n"
 "ldr w3, =0x007FFFFF \n"
 "and w5, w5, w3 \n"
 
 //sign bit
 "fmov w6, s0 \n"
 "ldr w3, =0x80000000 \n"
 "and w6, w6, w3 \n"
 "lsl w6, w6, #31 \n"
 "orr w4, w4, w5 \n"
 "orr w4, w4, w6 \n"
 "fmov s0, w4 \n"
 "ret \n"
);

#else

double cfm_scalbn(double x, int _exp) {
 uint64_t exponent = ((((*(int64_t*)&x) & 0x7FFFFFFFFFFFFFFF) >> 52) + _exp) << 52;
 uint64_t mantissa = ((*(uint64_t*)&x) & 0x000FFFFFFFFFFFFF);
 uint64_t sign_bit = ((*(uint64_t*)&x) & 0x8000000000000000) << 63;
 uint64_t value = sign_bit | exponent | mantissa;
 return *(double*)&value;
}

float cfm_scalbnf(float x, int _exp) {
 uint32_t exponent = ((((*(int32_t*)&x) & 0x7FFFFFFF) >> 23) + _exp) << 23;
 uint32_t mantissa = ((*(uint32_t*)&x) & 0x007FFFFF);
 uint64_t sign_bit = ((*(uint32_t*)&x) & 0x80000000) << 31;
 uint32_t value = sign_bit | exponent | mantissa;
 return *(float*)&value;
}

#endif
