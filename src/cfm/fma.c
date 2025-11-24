#include "cfm/math.h"

// TODO : implement cpu specific instruction
#if defined(__aarch64__)

__asm__ (
 ".type cfm_fma, @function \n"

 ".global cfm_fma \n"
 "cfm_fma: \n"
 "fmadd d0, d0, d1, d2 \n"
 "ret \n"
);

__asm__ (
 ".type cfm_fmaf, @function \n"

 ".global cfm_fmaf \n"
 "cfm_fmaf: \n"
 "fmadd s0, s0, s1, s2 \n"
 "ret \n"
);

#else 

double cfm_fma(double x, double y, double z) {
 return x * y + z;
}

float cfm_fmaf(float x, float y, float z) {
 return x * y + z;
}

#endif

