/*
 both sine and cosine function is calculated using Horner's
 Method Polynomial (4 degree)
 
 sin(x) = c0 * x + c1 * x² + c2 * x³ ...
 cos(y) = s0 * y + s1 * x² + s2 * y³ ...
 
 it uses arm neon vector "vn.d2" and "vn.s2" which is equivalent to
 "float64x2_t" and "float32x2_t" in <arm_neon.h> to calculate addition
 and multiplication at the same time. And also, it takes advantage multiply
 accumulate instruction "fmla" to perform mul and add with less cpu cycle
*/

/*
 we need to recreate each calculation to avoid any x adjustment
 and make it much faster
*/
__asm__(
 "__neon_sincos1: \n"
 "fmov x2, d0 \n"
 "mov v0.d[0], x2 \n"
 "mov v0.d[1], x2 \n"

 "ldr x2, =0x3f9d19eef248f963 \n"
 "mov v1.d[0], x2 \n"
 "mov v1.d[1], x2 \n"

 "ldr x2, =0xbfc9f0f3ba1b7e58 \n"
 "mov v2.d[0], x2 \n"
 "ldr x2, =0x3f98ae4df2e283d6 \n"
 "mov v2.d[1], x2 \n"

 "ldr x2, =0x3f9389eda55177d9 \n"
 "mov v3.d[0], x2 \n"
 "ldr x2, =0xbfe07cc1c8f1193c \n"
 "mov v3.d[1], x2 \n"
 
 "ldr x2, =0x3fefe2af1f0f0184 \n"
 "mov v4.d[0], x2 \n"
 "ldr x2, =0x3f6a614510557d15 \n"
 "mov v4.d[1], x2 \n"

 "ldr x2, =0x3ea4ee3a8c5dff92 \n"
 "mov v5.d[0], x2 \n"
 "ldr x2, =0x3fefff1e163c6c83 \n"
 "mov v5.d[1], x2 \n"

 "fmla v2.2d, v1.2d, v0.2d \n"
 "fmla v3.2d, v0.2d, v2.2d \n"
 "fmla v4.2d, v0.2d, v3.2d \n"
 "fmla v5.2d, v0.2d, v4.2d \n"
 
 "mov d0, v5.d[0] \n"
 "str d0, [x0] \n"

 "mov d0, v5.d[1] \n"
 "str d0, [x1] \n"

 "ret \n"
);

__asm__(
 "__neon_sincos2: \n"
 "fmov x2, d0 \n"
 "mov v0.d[0], x2 \n"
 "mov v0.d[1], x2 \n"

 "ldr x2, =0x3f9d19eef248f963 \n"
 "mov v1.d[0], x2 \n"
 "ldr x2, =0xbf9d19eef248f963 \n"
 "mov v1.d[1], x2 \n"

 "ldr x2, =0xbfc3c5603d62dd63 \n"
 "mov v2.d[0], x2 \n"
 "ldr x2, =0x3fd8660edaed561a \n"
 "mov v2.d[1], x2 \n"

 "ldr x2, =0xbfcaa25608d54a49 \n"
 "mov v3.d[0], x2 \n"
 "ldr x2, =0xbff6514f100ece2f \n"
 "mov v3.d[1], x2 \n"
 
 "ldr x2, =0x3ff5c143d339a1fd \n"
 "mov v4.d[0], x2 \n"
 "ldr x2, =0x3ff0118b96718967 \n"
 "mov v4.d[1], x2 \n"

 "ldr x2, =0xbfc93211370d4ad0 \n"
 "mov v5.d[0], x2 \n"
 "ldr x2, =0x3fe1e742ce92d617 \n"
 "mov v5.d[1], x2 \n"

 "fmla v2.2d, v1.2d, v0.2d \n"
 "fmla v3.2d, v0.2d, v2.2d \n"
 "fmla v4.2d, v0.2d, v3.2d \n"
 "fmla v5.2d, v0.2d, v4.2d \n"
 
 "mov d0, v5.d[0] \n"
 "str d0, [x0] \n"

 "mov d0, v5.d[1] \n"
 "str d0, [x1] \n"

 "ret \n"
);

__asm__(
 "__neon_sincos3: \n"
 "fmov x2, d0 \n"
 "mov v0.d[0], x2 \n"
 "mov v0.d[1], x2 \n"

 "ldr x2, =0xbf9d19eef248f962 \n"
 "mov v1.d[0], x2 \n"
 "ldr x2, =0xbf9d19eef248f964 \n"
 "mov v1.d[1], x2 \n"

 "ldr x2, =0x3fe1e9d1ec667684 \n"
 "mov v2.d[0], x2 \n"
 "ldr x2, =0x3fd550451c9105a1 \n"
 "mov v2.d[1], x2 \n"

 "ldr x2, =0xc00ce58a93fa0628 \n"
 "mov v3.d[0], x2 \n"
 "ldr x2, =0xbfee18d4415ddfbe \n"
 "mov v3.d[1], x2 \n"
 
 "ldr x2, =0x40214c374dbb4664 \n"
 "mov v4.d[0], x2 \n"
 "ldr x2, =0xbfdb7c06a497ec2d \n"
 "mov v4.d[1], x2 \n"

 "ldr x2, =0xc01870ed9a1956e0 \n"
 "mov v5.d[0], x2 \n"
 "ldr x2, =0x4000984d19f80c93 \n"
 "mov v5.d[1], x2 \n"

 "fmla v2.2d, v1.2d, v0.2d \n"
 "fmla v3.2d, v0.2d, v2.2d \n"
 "fmla v4.2d, v0.2d, v3.2d \n"
 "fmla v5.2d, v0.2d, v4.2d \n"
 
 "mov d0, v5.d[0] \n"
 "str d0, [x0] \n"

 "mov d0, v5.d[1] \n"
 "str d0, [x1] \n"

 "ret \n"
);

__asm__(
 "__neon_sincos4: \n"
 "fmov x2, d0 \n"
 "mov v0.d[0], x2 \n"
 "mov v0.d[1], x2 \n"

 "ldr x2, =0xbf9d19eef248f965 \n"
 "mov v1.d[0], x2 \n"
 "ldr x2, =0x3f9d19eef248f961 \n"
 "mov v1.d[1], x2 \n"

 "ldr x2, =0x3fe05eed0d384e48 \n"
 "mov v2.d[0], x2 \n"
 "ldr x2, =0xbfe7a09c6b5641fb \n"
 "mov v2.d[1], x2 \n"

 "ldr x2, =0xc00771dee0721f6e \n"
 "mov v3.d[0], x2 \n"
 "ldr x2, =0x401aaede7f914010 \n"
 "mov v3.d[1], x2 \n"
 
 "ldr x2, =0x4015b95d8d466d03 \n"
 "mov v4.d[0], x2 \n"
 "ldr x2, =0xc03894b155019665 \n"
 "mov v4.d[1], x2 \n"

 "ldr x2, =0xbff09152c09be2a2 \n"
 "mov v5.d[0], x2 \n"
 "ldr x2, =0x403ef373a453220c \n"
 "mov v5.d[1], x2 \n"

 "fmla v2.2d, v1.2d, v0.2d \n"
 "fmla v3.2d, v0.2d, v2.2d \n"
 "fmla v4.2d, v0.2d, v3.2d \n"
 "fmla v5.2d, v0.2d, v4.2d \n"
 
 "mov d0, v5.d[0] \n"
 "str d0, [x0] \n"

 "mov d0, v5.d[1] \n"
 "str d0, [x1] \n"

 "ret \n"
);

/*
 negative value
*/
__asm__(
 "__neon_sincos5: \n"
 "fmov x2, d0 \n"
 "mov v0.d[0], x2 \n"
 "mov v0.d[1], x2 \n"

 "ldr x2, =0x3f9d19eef248f963 \n"
 "mov v1.d[0], x2 \n"
 "mov v1.d[1], x2 \n"

 "ldr x2, =0xbfc9f0f3ba1b7e58 \n"
 "mov v2.d[0], x2 \n"
 "ldr x2, =0x3f98ae4df2e283d6 \n"
 "mov v2.d[1], x2 \n"

 "ldr x2, =0x3f9389eda55177d9 \n"
 "mov v3.d[0], x2 \n"
 "ldr x2, =0xbfe07cc1c8f1193c \n"
 "mov v3.d[1], x2 \n"
 
 "ldr x2, =0x3fefe2af1f0f0184 \n"
 "mov v4.d[0], x2 \n"
 "ldr x2, =0x3f6a614510557d15 \n"
 "mov v4.d[1], x2 \n"

 "ldr x2, =0x3ea4ee3a8c5dff92 \n"
 "mov v5.d[0], x2 \n"
 "ldr x2, =0x3fefff1e163c6c83 \n"
 "mov v5.d[1], x2 \n"

 "fmla v2.2d, v1.2d, v0.2d \n"
 "fmla v3.2d, v0.2d, v2.2d \n"
 "fmla v4.2d, v0.2d, v3.2d \n"
 "fmla v5.2d, v0.2d, v4.2d \n"
 
 "mov d0, v5.d[0] \n"
 "fneg d0, d0 \n"
 "str d0, [x0] \n"

 "mov d0, v5.d[1] \n"
 "str d0, [x1] \n"

 "ret \n"
);

__asm__(
 "__neon_sincos6: \n"
 "fmov x2, d0 \n"
 "mov v0.d[0], x2 \n"
 "mov v0.d[1], x2 \n"

 "ldr x2, =0x3f9d19eef248f963 \n"
 "mov v1.d[0], x2 \n"
 "ldr x2, =0xbf9d19eef248f963 \n"
 "mov v1.d[1], x2 \n"

 "ldr x2, =0xbfc3c5603d62dd63 \n"
 "mov v2.d[0], x2 \n"
 "ldr x2, =0x3fd8660edaed561a \n"
 "mov v2.d[1], x2 \n"

 "ldr x2, =0xbfcaa25608d54a49 \n"
 "mov v3.d[0], x2 \n"
 "ldr x2, =0xbff6514f100ece2f \n"
 "mov v3.d[1], x2 \n"
 
 "ldr x2, =0x3ff5c143d339a1fd \n"
 "mov v4.d[0], x2 \n"
 "ldr x2, =0x3ff0118b96718967 \n"
 "mov v4.d[1], x2 \n"

 "ldr x2, =0xbfc93211370d4ad0 \n"
 "mov v5.d[0], x2 \n"
 "ldr x2, =0x3fe1e742ce92d617 \n"
 "mov v5.d[1], x2 \n"

 "fmla v2.2d, v1.2d, v0.2d \n"
 "fmla v3.2d, v0.2d, v2.2d \n"
 "fmla v4.2d, v0.2d, v3.2d \n"
 "fmla v5.2d, v0.2d, v4.2d \n"
 
 "mov d0, v5.d[0] \n"
 "fneg d0, d0 \n"
 "str d0, [x0] \n"

 "mov d0, v5.d[1] \n"
 "str d0, [x1] \n"

 "ret \n"
);

__asm__(
 "__neon_sincos7: \n"
 "fmov x2, d0 \n"
 "mov v0.d[0], x2 \n"
 "mov v0.d[1], x2 \n"

 "ldr x2, =0xbf9d19eef248f962 \n"
 "mov v1.d[0], x2 \n"
 "ldr x2, =0xbf9d19eef248f964 \n"
 "mov v1.d[1], x2 \n"

 "ldr x2, =0x3fe1e9d1ec667684 \n"
 "mov v2.d[0], x2 \n"
 "ldr x2, =0x3fd550451c9105a1 \n"
 "mov v2.d[1], x2 \n"

 "ldr x2, =0xc00ce58a93fa0628 \n"
 "mov v3.d[0], x2 \n"
 "ldr x2, =0xbfee18d4415ddfbe \n"
 "mov v3.d[1], x2 \n"
 
 "ldr x2, =0x40214c374dbb4664 \n"
 "mov v4.d[0], x2 \n"
 "ldr x2, =0xbfdb7c06a497ec2d \n"
 "mov v4.d[1], x2 \n"

 "ldr x2, =0xc01870ed9a1956e0 \n"
 "mov v5.d[0], x2 \n"
 "ldr x2, =0x4000984d19f80c93 \n"
 "mov v5.d[1], x2 \n"

 "fmla v2.2d, v1.2d, v0.2d \n"
 "fmla v3.2d, v0.2d, v2.2d \n"
 "fmla v4.2d, v0.2d, v3.2d \n"
 "fmla v5.2d, v0.2d, v4.2d \n"
 
 "mov d0, v5.d[0] \n"
 "fneg d0, d0 \n"
 "str d0, [x0] \n"

 "mov d0, v5.d[1] \n"
 "str d0, [x1] \n"

 "ret \n"
);

__asm__(
 "__neon_sincos8: \n"
 "fmov x2, d0 \n"
 "mov v0.d[0], x2 \n"
 "mov v0.d[1], x2 \n"

 "ldr x2, =0xbf9d19eef248f965 \n"
 "mov v1.d[0], x2 \n"
 "ldr x2, =0x3f9d19eef248f961 \n"
 "mov v1.d[1], x2 \n"

 "ldr x2, =0x3fe05eed0d384e48 \n"
 "mov v2.d[0], x2 \n"
 "ldr x2, =0xbfe7a09c6b5641fb \n"
 "mov v2.d[1], x2 \n"

 "ldr x2, =0xc00771dee0721f6e \n"
 "mov v3.d[0], x2 \n"
 "ldr x2, =0x401aaede7f914010 \n"
 "mov v3.d[1], x2 \n"
 
 "ldr x2, =0x4015b95d8d466d03 \n"
 "mov v4.d[0], x2 \n"
 "ldr x2, =0xc03894b155019665 \n"
 "mov v4.d[1], x2 \n"

 "ldr x2, =0xbff09152c09be2a2 \n"
 "mov v5.d[0], x2 \n"
 "ldr x2, =0x403ef373a453220c \n"
 "mov v5.d[1], x2 \n"

 "fmla v2.2d, v1.2d, v0.2d \n"
 "fmla v3.2d, v0.2d, v2.2d \n"
 "fmla v4.2d, v0.2d, v3.2d \n"
 "fmla v5.2d, v0.2d, v4.2d \n"
 
 "mov d0, v5.d[0] \n"
 "fneg d0, d0 \n"
 "str d0, [x0] \n"

 "mov d0, v5.d[1] \n"
 "str d0, [x1] \n"

 "ret \n"
);

extern void __neon_sincos1(double x, double *_s, double *_c);
extern void __neon_sincos2(double x, double *_s, double *_c);
extern void __neon_sincos3(double x, double *_s, double *_c);
extern void __neon_sincos4(double x, double *_s, double *_c);
extern void __neon_sincos5(double x, double *_s, double *_c);
extern void __neon_sincos6(double x, double *_s, double *_c);
extern void __neon_sincos7(double x, double *_s, double *_c);
extern void __neon_sincos8(double x, double *_s, double *_c);


__asm__(
 "__neon_sincosf1: \n"
 "fmov w2, s0 \n"
 "mov v0.s[0], w2 \n"
 "mov v0.s[1], w2 \n"

 "ldr w2, =0x3ce8cf62 \n"
 "mov v1.s[0], w2 \n"
 "mov v1.s[1], w2 \n"

 "ldr w2, =0xbe4f8799 \n"
 "mov v2.s[0], w2 \n"
 "ldr w2, =0x3cc57265 \n"
 "mov v2.s[1], w2 \n"

 "ldr w2, =0x3c9c4f56 \n"
 "mov v3.s[0], w2 \n"
 "ldr w2, =0xbf03e60e \n"
 "mov v3.s[1], w2 \n"
 
 "ldr w2, =0x3f7f1577 \n"
 "mov v4.s[0], w2 \n"
 "ldr w2, =0x3b5309fe \n"
 "mov v4.s[1], w2 \n"

 "ldr w2, =0x35210fb0 \n"
 "mov v5.s[0], w2 \n"
 "ldr w2, =0x3f7ff8ef \n"
 "mov v5.s[1], w2 \n"

 "fmla v2.2s, v1.2s, v0.2s \n"
 "fmla v3.2s, v0.2s, v2.2s \n"
 "fmla v4.2s, v0.2s, v3.2s \n"
 "fmla v5.2s, v0.2s, v4.2s \n"
 
 "mov w2, v5.s[0] \n"
 "str w2, [x0] \n"

 "mov w2, v5.s[1] \n"
 "str w2, [x1] \n"
 
 "ret \n"
);

__asm__(
 "__neon_sincosf2: \n"
 "fmov w2, s0 \n"
 "mov v0.s[0], w2 \n"
 "mov v0.s[1], w2 \n"

 "ldr w2, =0x3ce8cf62  \n"
 "mov v1.s[0], w2 \n"
 "ldr w2, =0xbce8cf77 \n"
 "mov v1.s[1], w2 \n"

 "ldr w2, =0xbe1e2b00 \n"
 "mov v2.s[0], w2 \n"
 "ldr w2, =0x3ec33077 \n"
 "mov v2.s[1], w2 \n"

 "ldr w2, =0xbe5512b0 \n"
 "mov v3.s[0], w2 \n"
 "ldr w2, =0xbfb28a78 \n"
 "mov v3.s[1], w2 \n"
 
 "ldr w2, =0x3fae0a1e \n"
 "mov v4.s[0], w2 \n"
 "ldr w2, =0x3f808c5d \n"
 "mov v4.s[1], w2 \n"

 "ldr w2, =0xbe499088 \n"
 "mov v5.s[0], w2 \n"
 "ldr w2, =0x3f0f3a16 \n"
 "mov v5.s[1], w2 \n"

 "fmla v2.2s, v1.2s, v0.2s \n"
 "fmla v3.2s, v0.2s, v2.2s \n"
 "fmla v4.2s, v0.2s, v3.2s \n"
 "fmla v5.2s, v0.2s, v4.2s \n"
 
 "mov w2, v5.s[0] \n"
 "str w2, [x0] \n"

 "mov w2, v5.s[1] \n"
 "str w2, [x1] \n"
 
 "ret \n"
);


__asm__(
 "__neon_sincosf3: \n"
 "fmov w2, s0 \n"
 "mov v0.s[0], w2 \n"
 "mov v0.s[1], w2 \n"

 "ldr w2, =0xbce8cf62 \n"
 "mov v1.s[0], w2 \n"
 "ldr w2, =0xbce8cf77 \n"
 "mov v1.s[1], w2 \n"

 "ldr w2, =0x3f0f4e8e \n"
 "mov v2.s[0], w2 \n"
 "ldr w2, =0x3eaa8229 \n"
 "mov v2.s[1], w2 \n"

 "ldr w2, =0xc0672c55 \n"
 "mov v3.s[0], w2 \n"
 "ldr w2, =0xbf70c6a2 \n"
 "mov v3.s[1], w2 \n"
 
 "ldr w2, =0x410a61ba \n"
 "mov v4.s[0], w2 \n"
 "ldr w2, =0xbedbe035 \n"
 "mov v4.s[1], w2 \n"

 "ldr w2, =0xc0c3876d \n"
 "mov v5.s[0], w2 \n"
 "ldr w2, =0x4004c269 \n"
 "mov v5.s[1], w2 \n"

 "fmla v2.2s, v1.2s, v0.2s \n"
 "fmla v3.2s, v0.2s, v2.2s \n"
 "fmla v4.2s, v0.2s, v3.2s \n"
 "fmla v5.2s, v0.2s, v4.2s \n"
 
 "mov w2, v5.s[0] \n"
 "str w2, [x0] \n"

 "mov w2, v5.s[1] \n"
 "str w2, [x1] \n"
 
 "ret \n"
);

__asm__(
 "__neon_sincosf4: \n"
 "fmov w2, s0 \n"
 "mov v0.s[0], w2 \n"
 "mov v0.s[1], w2 \n"

 "ldr w2, =0xbce8cf62 \n"
 "mov v1.s[0], w2 \n"
 "ldr w2, =0x3ce8cf77 \n"
 "mov v1.s[1], w2 \n"

 "ldr w2, =0x3f02f768 \n"
 "mov v2.s[0], w2 \n"
 "ldr w2, =0xbf3d04e3 \n"
 "mov v2.s[1], w2 \n"

 "ldr w2, =0xc03b8ef7 \n"
 "mov v3.s[0], w2 \n"
 "ldr w2, =0x40d576f4 \n"
 "mov v3.s[1], w2 \n"
 
 "ldr w2, =0x40adcaec \n"
 "mov v4.s[0], w2 \n"
 "ldr w2, =0xc1c4a58a \n"
 "mov v4.s[1], w2 \n"

 "ldr w2, =0xbf848a96 \n"
 "mov v5.s[0], w2 \n"
 "ldr w2, =0x41f79b9d \n"
 "mov v5.s[1], w2 \n"

 "fmla v2.2s, v1.2s, v0.2s \n"
 "fmla v3.2s, v0.2s, v2.2s \n"
 "fmla v4.2s, v0.2s, v3.2s \n"
 "fmla v5.2s, v0.2s, v4.2s \n"
 
 "mov w2, v5.s[0] \n"
 "str w2, [x0] \n"

 "mov w2, v5.s[1] \n"
 "str w2, [x1] \n"
 
 "ret \n"
);

__asm__(
 "__neon_sincosf5: \n"
 "fmov w2, s0 \n"
 "mov v0.s[0], w2 \n"
 "mov v0.s[1], w2 \n"

 "ldr w2, =0x3ce8cf62 \n"
 "mov v1.s[0], w2 \n"
 "mov v1.s[1], w2 \n"

 "ldr w2, =0xbe4f8799 \n"
 "mov v2.s[0], w2 \n"
 "ldr w2, =0x3cc57265 \n"
 "mov v2.s[1], w2 \n"

 "ldr w2, =0x3c9c4f56 \n"
 "mov v3.s[0], w2 \n"
 "ldr w2, =0xbf03e60e \n"
 "mov v3.s[1], w2 \n"
 
 "ldr w2, =0x3f7f1577 \n"
 "mov v4.s[0], w2 \n"
 "ldr w2, =0x3b5309fe \n"
 "mov v4.s[1], w2 \n"

 "ldr w2, =0x35210fb0 \n"
 "mov v5.s[0], w2 \n"
 "ldr w2, =0x3f7ff8ef \n"
 "mov v5.s[1], w2 \n"

 "fmla v2.2s, v1.2s, v0.2s \n"
 "fmla v3.2s, v0.2s, v2.2s \n"
 "fmla v4.2s, v0.2s, v3.2s \n"
 "fmla v5.2s, v0.2s, v4.2s \n"
 
 "mov w2, v5.s[0] \n"
 "fmov s0, w2 \n"
 "fneg s0, s0 \n"
 "str s0, [x0] \n"

 "mov w2, v5.s[1] \n"
 "str w2, [x1] \n"
 
 "ret \n"
);

__asm__(
 "__neon_sincosf6: \n"
 "fmov w2, s0 \n"
 "mov v0.s[0], w2 \n"
 "mov v0.s[1], w2 \n"

 "ldr w2, =0x3ce8cf62  \n"
 "mov v1.s[0], w2 \n"
 "ldr w2, =0xbce8cf77 \n"
 "mov v1.s[1], w2 \n"

 "ldr w2, =0xbe1e2b00 \n"
 "mov v2.s[0], w2 \n"
 "ldr w2, =0x3ec33077 \n"
 "mov v2.s[1], w2 \n"

 "ldr w2, =0xbe5512b0 \n"
 "mov v3.s[0], w2 \n"
 "ldr w2, =0xbfb28a78 \n"
 "mov v3.s[1], w2 \n"
 
 "ldr w2, =0x3fae0a1e \n"
 "mov v4.s[0], w2 \n"
 "ldr w2, =0x3f808c5d \n"
 "mov v4.s[1], w2 \n"

 "ldr w2, =0xbe499088 \n"
 "mov v5.s[0], w2 \n"
 "ldr w2, =0x3f0f3a16 \n"
 "mov v5.s[1], w2 \n"

 "fmla v2.2s, v1.2s, v0.2s \n"
 "fmla v3.2s, v0.2s, v2.2s \n"
 "fmla v4.2s, v0.2s, v3.2s \n"
 "fmla v5.2s, v0.2s, v4.2s \n"
 
 "mov w2, v5.s[0] \n"
 "fmov s0, w2 \n"
 "fneg s0, s0 \n"
 "str s0, [x0] \n"

 "mov w2, v5.s[1] \n"
 "str w2, [x1] \n"
 
 "ret \n"
);


__asm__(
 "__neon_sincosf7: \n"
 "fmov w2, s0 \n"
 "mov v0.s[0], w2 \n"
 "mov v0.s[1], w2 \n"

 "ldr w2, =0xbce8cf62 \n"
 "mov v1.s[0], w2 \n"
 "ldr w2, =0xbce8cf77 \n"
 "mov v1.s[1], w2 \n"

 "ldr w2, =0x3f0f4e8e \n"
 "mov v2.s[0], w2 \n"
 "ldr w2, =0x3eaa8229 \n"
 "mov v2.s[1], w2 \n"

 "ldr w2, =0xc0672c55 \n"
 "mov v3.s[0], w2 \n"
 "ldr w2, =0xbf70c6a2 \n"
 "mov v3.s[1], w2 \n"
 
 "ldr w2, =0x410a61ba \n"
 "mov v4.s[0], w2 \n"
 "ldr w2, =0xbedbe035 \n"
 "mov v4.s[1], w2 \n"

 "ldr w2, =0xc0c3876d \n"
 "mov v5.s[0], w2 \n"
 "ldr w2, =0x4004c269 \n"
 "mov v5.s[1], w2 \n"

 "fmla v2.2s, v1.2s, v0.2s \n"
 "fmla v3.2s, v0.2s, v2.2s \n"
 "fmla v4.2s, v0.2s, v3.2s \n"
 "fmla v5.2s, v0.2s, v4.2s \n"
 
 "mov w2, v5.s[0] \n"
 "fmov s0, w2 \n"
 "fneg s0, s0 \n"
 "str s0, [x0] \n"

 "mov w2, v5.s[1] \n"
 "str w2, [x1] \n"
 
 "ret \n"
);

__asm__(
 "__neon_sincosf8: \n"
 "fmov w2, s0 \n"
 "mov v0.s[0], w2 \n"
 "mov v0.s[1], w2 \n"

 "ldr w2, =0xbce8cf62 \n"
 "mov v1.s[0], w2 \n"
 "ldr w2, =0x3ce8cf77 \n"
 "mov v1.s[1], w2 \n"

 "ldr w2, =0x3f02f768 \n"
 "mov v2.s[0], w2 \n"
 "ldr w2, =0xbf3d04e3 \n"
 "mov v2.s[1], w2 \n"

 "ldr w2, =0xc03b8ef7 \n"
 "mov v3.s[0], w2 \n"
 "ldr w2, =0x40d576f4 \n"
 "mov v3.s[1], w2 \n"
 
 "ldr w2, =0x40adcaec \n"
 "mov v4.s[0], w2 \n"
 "ldr w2, =0xc1c4a58a \n"
 "mov v4.s[1], w2 \n"

 "ldr w2, =0xbf848a96 \n"
 "mov v5.s[0], w2 \n"
 "ldr w2, =0x41f79b9d \n"
 "mov v5.s[1], w2 \n"

 "fmla v2.2s, v1.2s, v0.2s \n"
 "fmla v3.2s, v0.2s, v2.2s \n"
 "fmla v4.2s, v0.2s, v3.2s \n"
 "fmla v5.2s, v0.2s, v4.2s \n"
 
 "mov w2, v5.s[0] \n"
 "fmov s0, w2 \n"
 "fneg s0, s0 \n"
 "str s0, [x0] \n"

 "mov w2, v5.s[1] \n"
 "str w2, [x1] \n"
 
 "ret \n"
);

extern void __neon_sincosf1(float x, float *_s, float *_c);
extern void __neon_sincosf2(float x, float *_s, float *_c);
extern void __neon_sincosf3(float x, float *_s, float *_c);
extern void __neon_sincosf4(float x, float *_s, float *_c);
extern void __neon_sincosf5(float x, float *_s, float *_c);
extern void __neon_sincosf6(float x, float *_s, float *_c);
extern void __neon_sincosf7(float x, float *_s, float *_c);
extern void __neon_sincosf8(float x, float *_s, float *_c);


