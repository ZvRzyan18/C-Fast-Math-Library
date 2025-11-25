#include "cfm/math.h"
#include "cfm/float_bits.h"
#include <stdint.h>

/*
 error function
*/

static const double DC[14] = {
	-1.882632880220740e-03,
	 2.294286363717574e-02,
 -1.044889321532258e-01,
  1.905330179234075e-01,
  1.142881187353737e-02,
 -4.247574981928259e-01,
  2.415424221371780e-02,
  1.124649341406616e-00,
  9.006587398229172e-05,
  
 -5.666124046681733e-06,
  1.061249530898842e-04,
 -7.355971771531651e-04,
  2.235217400497739e-03,
  9.974883575409265e-01,
};

static const float FC[14] = {
	-1.88263288e-03f,
	 2.29428636e-02f,
 -1.04488932e-01f,
  1.90533017e-01f,
  1.14288118e-02f,
 -4.24757498e-01f,
  2.41542422e-02f,
  1.12464934e-00f,
  9.00658739e-05f,
  
 -5.66612404e-06f,
  1.06124953e-04f,
 -7.35597177e-04f,
  2.23521740e-03f,
  9.97488357e-01f,
};

//---------------DOUBLE------------------//

double cfm_erf(double x) {
 double_bits bits;
 uint64_t sign, gt_1, gt_2;
 double mx, mx1, out;
 
 bits.f = x;
 sign = bits.i & 0x8000000000000000;
 bits.i = sign ? bits.i & 0x7FFFFFFFFFFFFFFF : bits.i;
 mx = bits.f;
 mx1 = bits.f;
 
 mx1 = ((((((((DC[0] * mx1 + DC[1]) * mx1 + DC[2]) * mx1 + DC[3]) * mx1 + DC[4]) * mx1 + DC[5]) * mx1 + DC[6]) * mx1 + DC[7]) * mx1 + DC[8]);
 mx = ((((DC[9] * mx + DC[10]) * mx + DC[11]) * mx + DC[12]) * mx + DC[13]);
 gt_1 = bits.f > 6.0;
 gt_2 = bits.f > 3.0;
 
 out = gt_2 ? mx : mx1;
 out = gt_1 && !gt_2 ? 1.0 : out;
 
 bits.f = out;
 bits.i = bits.i | sign;
 return bits.f;
}

//---------------FLOAT------------------//

float cfm_erff(float x) {
 float_bits bits;
 uint32_t sign, gt_1, gt_2;
 float mx, mx1, out;
 
 bits.f = x;
 sign = bits.i & 0x80000000;
 bits.i = sign ? bits.i & 0x7FFFFFFF : bits.i;
 mx = bits.f;
 mx1 = bits.f;
 
 mx1 = ((((((((FC[0] * mx1 + FC[1]) * mx1 + FC[2]) * mx1 + FC[3]) * mx1 + FC[4]) * mx1 + FC[5]) * mx1 + FC[6]) * mx1 + FC[7]) * mx1 + FC[8]);
 mx = ((((FC[9] * mx + FC[10]) * mx + FC[11]) * mx + FC[12]) * mx + FC[13]);
 gt_1 = bits.f > 6.0f;
 gt_2 = bits.f > 3.0f;
 
 out = gt_2 ? mx : mx1;
 out = gt_1 && !gt_2 ? 1.0f : out;
 
 bits.f = out;
 bits.i = bits.i | sign;
 return bits.f;
}

