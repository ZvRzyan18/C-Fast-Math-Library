/*
 MIT License

 Copyright (c) 2025 ZvRzyan18

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#include "cfm/math.h"
#include <stdint.h>

double cfm_erfc(double x) {
	if(*(uint64_t*)&x & 0x8000000000000000) {
	 *(uint64_t*)&x &= 0x7FFFFFFFFFFFFFFF;
	 if(x > 6.0) {
	 	return 0.0;
	 } else if(x > 3.0) {
	 	//4 degree polynomial
		 return 1.0 + ((((-5.6661240466817337e-06 * x + 0.00010612495308988421) * x + -0.00073559717715316513) * x + 0.002235217400497739) * x + 0.99748835754092657);
	 } else {
	  //8 degree polynomial
	  return 1.0 + ((((((((-0.0018826328802207409 * x + 0.022942863637175744) * x + -0.1044889321532258) * x + 0.19053301792340754) * x + 0.011428811873537377) * x + -0.42475749819282593) * x + 0.0241542422137178) * x + 1.1246493414066161) * x + 9.0065873982291729e-05);
 	}
	}
	
	if(x > 6.0) {
		return 0.0;
	} else if(x > 3.0) {
		//4 degree polynomial
		 return 1.0 - ((((-5.6661240466817337e-06 * x + 0.00010612495308988421) * x + -0.00073559717715316513) * x + 0.002235217400497739) * x + 0.99748835754092657);
	} else {
	 //8 degree polynomial
	 return 1.0 - ((((((((-0.0018826328802207409 * x + 0.022942863637175744) * x + -0.1044889321532258) * x + 0.19053301792340754) * x + 0.011428811873537377) * x + -0.42475749819282593) * x + 0.0241542422137178) * x + 1.1246493414066161) * x + 9.0065873982291729e-05);
	}
	return 0.0;
}


float cfm_erfcf(float x) {
	if(*(uint32_t*)&x & 0x80000000) {
	 *(uint32_t*)&x &= 0x7FFFFFFF;
	 if(x > 6.0f) {
	 	return 0.0f;
	 } else if(x > 3.0f) {
	 	//4 degree polynomial
		 return 1.0f + ((((-5.666124e-06f * x + 0.000106f) * x + -0.000735f) * x + 0.002235f) * x + 0.997488f);
	 } else {
	  //8 degree polynomial
	  return 1.0f + ((((((((-0.001882f * x + 0.022942f) * x + -0.104488f) * x + 0.190533f) * x + 0.011428f) * x + -0.424757f) * x + 0.024154f) * x + 1.124649f) * x + 9.006587e-05f);
 	}
	}
	
	if(x > 6.0f) {
		return 0.0f;
	} else if(x > 3.0f) {
		//4 degree polynomial
		return 1.0f - ((((-5.666124e-06f * x + 0.000106f) * x + -0.000735f) * x + 0.002235f) * x + 0.997488f);
	} else {
	 //8 degree polynomial
	 return 1.0f - ((((((((-0.001882f * x + 0.022942f) * x + -0.104488f) * x + 0.190533f) * x + 0.011428f) * x + -0.424757f) * x + 0.024154f) * x + 1.124649f) * x + 9.006587e-05f);
 }
	return 0.0f;
}

