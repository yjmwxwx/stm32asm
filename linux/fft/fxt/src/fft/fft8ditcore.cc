// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "complextype.h"  // Complex

#include <cmath>  // M_SQRT1_2

// swap (1 with 4) and (3 with 6) in all _output_ expressions f[.]


void
fft8_dit_core_p1(Complex *f)
// 8-point decimation in time FFT
// fixed isign = -1
// input data must be in revbin_permuted order
//.
// Cf. Nussbaumer p.148f
{
    Complex t1 = f[0] + f[1];
    Complex m3 = f[0] - f[1];

    Complex t4 = f[4] + f[5];
    Complex t3 = f[4] - f[5];

    Complex t5 = f[6] + f[7];
    Complex t6 = f[6] - f[7];

    Complex t2 = f[2] + f[3];
    Complex t7 = t1 + t2;
    Complex m2 = t1 - t2;
    Complex t8 = t4 + t5;

    f[0] = t7 + t8;
    f[4] = t7 - t8;
    Complex m4 = M_SQRT1_2 * (t3 - t6);

    // isign = +1:
    Complex m7 = Complex(0, -M_SQRT1_2) * (t3 + t6);
    Complex m5 = (t5 - t4) * Complex(0, 1);
    Complex m6 = (f[3] - f[2]) * Complex(0, 1);

//    // isign = -1:
//    Complex m7 = Complex(0, M_SQRT1_2) * (t3 + t6);
//    Complex m5 = (t4 - t5) * Complex(0, 1);
//    Complex m6 = (f[2] - f[3]) * Complex(0, 1);

#define s1 t1
#define s2 t2
#define s3 t3
#define s4 t4
    s1 = m3 + m4;
    s2 = m3 - m4;

    s3 = m6 + m7;
    s4 = m6 - m7;

    f[7] = s1 + s3;
    f[1] = s1 - s3;

    f[3] = s2 + s4;
    f[5] = s2 - s4;

    f[6] = m2 + m5;
    f[2] = m2 - m5;
#undef s1
#undef s2
#undef s3
#undef s4
}
// -------------------------


void
fft8_dit_core_m1(Complex *f)
// 8-point decimation in time FFT
// fixed isign = -1
// input data must be in revbin_permuted order
//.
// Cf. Nussbaumer p.148f
{
    Complex t1 = f[0] + f[1];
    Complex m3 = f[0] - f[1];

    Complex t4 = f[4] + f[5];
    Complex t3 = f[4] - f[5];

    Complex t5 = f[6] + f[7];
    Complex t6 = f[6] - f[7];

    Complex t2 = f[2] + f[3];
    Complex t7 = t1 + t2;
    Complex m2 = t1 - t2;
    Complex t8 = t4 + t5;

    f[0] = t7 + t8;
    f[4] = t7 - t8;
    Complex m4 = M_SQRT1_2 * (t3 - t6);

//    // isign = +1:
//    Complex m7 = Complex(0, -M_SQRT1_2) * (t3 + t6);
//    Complex m5 = (t5 - t4) * Complex(0, 1);
//    Complex m6 = (f[3] - f[2]) * Complex(0, 1);

    // isign = -1:
    Complex m7 = Complex(0, M_SQRT1_2) * (t3 + t6);
    Complex m5 = (t4 - t5) * Complex(0, 1);
    Complex m6 = (f[2] - f[3]) * Complex(0, 1);

#define s1 t1
#define s2 t2
#define s3 t3
#define s4 t4
    s1 = m3 + m4;
    s2 = m3 - m4;

    s3 = m6 + m7;
    s4 = m6 - m7;

    f[7] = s1 + s3;
    f[1] = s1 - s3;

    f[3] = s2 + s4;
    f[5] = s2 - s4;

    f[6] = m2 + m5;
    f[2] = m2 - m5;
#undef s1
#undef s2
#undef s3
#undef s4
}
// -------------------------


void
fft8_dit_core_p1(double *fr, double *fi)
// 8-point decimation in time FFT
// isign = +1
// input data must be in revbin_permuted order
//.
// Cf. Nussbaumer p.148f
{
    // INPUT_RE:
    double t1r = fr[0] + fr[1];
    double t2r = fr[2] + fr[3];
    double t7r = t1r + t2r;
    double t3r = fr[4] - fr[5];
    double t4r = fr[4] + fr[5];
    double t5r = fr[6] + fr[7];
    double t8r = t4r + t5r;
    double t6r = fr[6] - fr[7];

    double m0r = t7r + t8r;
    double m1r = t7r - t8r;
    double m2r = t1r - t2r;
    double m3r = fr[0] - fr[1];
    double m4r = M_SQRT1_2 * (t3r - t6r);

#define m5i t6r
#define m6i t7r
#define m7i t8r
    m7i = M_SQRT1_2 * (t3r + t6r);
    m5i = t5r - t4r;
    m6i = fr[3] - fr[2];

    // INPUT_IM:
    double t1i = fi[0] + fi[1];
    double t2i = fi[2] + fi[3];
    double t7i = t1i + t2i;
    double t3i = fi[4] - fi[5];
    double t4i = fi[4] + fi[5];
    double t5i = fi[6] + fi[7];
    double t8i = t4i + t5i;
    double t6i = fi[6] - fi[7];

    double m0i = t7i + t8i;
    double m1i = t7i - t8i;
    double m2i = t1i - t2i;
    double m3i = fi[0] - fi[1];
    double m4i = M_SQRT1_2 * (t3i - t6i);

#define m5r t6i
#define m6r t7i
#define m7r t8i
    m7r = M_SQRT1_2 * (t3i + t6i);
    m5r = t4i - t5i;
    m6r = fi[2] - fi[3];

#define s1r t1r
#define s2r t2r
#define s3r t3r
#define s4r t4r
    s1r = m3r + m4r;
    s2r = m3r - m4r;
    s3r = m6r + m7r;
    s4r = m6r - m7r;

    // OUTPUT_RE:
    fr[0] = m0r;
    fr[7] = s1r + s3r;
    fr[6] = m2r + m5r;
    fr[5] = s2r - s4r;
    fr[4] = m1r;
    fr[3] = s2r + s4r;
    fr[2] = m2r - m5r;
    fr[1] = s1r - s3r;

#define s1i t1r
#define s2i t2r
#define s3i t3r
#define s4i t4r
    s1i = m3i + m4i;
    s2i = m3i - m4i;
    s3i = m6i - m7i;
    s4i = m6i + m7i;

    // OUTPUT_IM:
    fi[0] = m0i;
    fi[7] = s1i + s3i;
    fi[6] = m2i + m5i;
    fi[5] = s2i - s4i;
    fi[4] = m1i;
    fi[3] = s2i + s4i;
    fi[2] = m2i - m5i;
    fi[1] = s1i - s3i;
}
// -------------------------

#undef s1r
#undef s2r
#undef s3r
#undef s4r

#undef s1i
#undef s2i
#undef s3i
#undef s4i

#undef m5r
#undef m6r
#undef m7r

#undef m5i
#undef m6i
#undef m7i

