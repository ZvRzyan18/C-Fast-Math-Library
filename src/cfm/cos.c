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
#include <stdlib.h>

double cfm_cos(double x) {
 if((*(uint64_t*)&x) & 0x8000000000000000)
  (*(uint64_t*)&x) &= 0x7FFFFFFFFFFFFFFF;
 
 if((*(uint64_t*)&x) > 0x401921fb54442d18)
  x = x - (int64_t)(x * 0.1591549) * 6.2831853;
  
 switch((int64_t)(x * 0.636619772367581382432888403855)) {
 	case 0:
  	return ((((0.028419240510851106 * x + 0.024102418851388162) * x + -0.51522912260478604) * x + 0.0032202099707060541) * x + 0.99989227622008092);
 	break;
 	case 1:
   return ((((-2.8419240510851105e-2 * x + 3.8122912768935326e-1) * x - 1.3948507907160879) * x + 1.0042835118007021) * x + 5.5948009821321672e-1);
 	break;
 	case 2:
   return ((((-2.8419240510851109e-2 * x + 3.3302428998657699e-1) * x - 9.4053089873249697e-1) * x - 4.2944494317606792e-1) * x + 2.0743658093284209);
 	break;
 	case 3:
   return ((((2.84192405108511e-2 * x - 7.3835583652731825e-1) * x + 6.6707706386951177) * x - 2.4580830872428483e+1) * x + 3.0950983305259838e+1);
  break;
 }
 return 0.0;
}



float cfm_cosf(float x) {
 if((*(uint32_t*)&x) & 0x80000000)
  (*(uint32_t*)&x) &= 0x7FFFFFFF;
 
 if((*(uint32_t*)&x) > 0x40c90fdb)
  x = x - (int64_t)(x * 0.1591549f) * 6.2831853f;
  
 switch((int64_t)(x * 0.6366197f)) {
 	case 0:
  	return ((((0.0284192f * x + 0.0241024f) * x + -0.5152291f) * x + 0.0032202f) * x + 0.9998922f);
 	break;
 	case 1:
   return ((((-2.8419240e-2f * x + 3.8122912e-1f) * x - 1.3948507f) * x + 1.0042835f) * x + 5.5948009e-1f);
 	break;
 	case 2:
   return ((((-2.8419240e-2f * x + 3.3302428e-1f) * x - 9.4053089e-1f) * x - 4.2944494e-1f) * x + 2.0743658f);
 	break;
 	case 3:
   return ((((2.8419240e-2f * x - 7.3835583e-1f) * x + 6.6707706f) * x - 2.4580830e+1f) * x + 3.0950983e+1f);
  break;
 }
 return 0.0f;
}

