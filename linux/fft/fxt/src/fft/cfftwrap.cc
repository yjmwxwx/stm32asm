// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fft/fft.h"
#include "perm/zip.h"

#include "fxttypes.h"  // ulong
#include "complextype.h"  // Complex


void
complex_to_real_imag(Complex *c, ulong n)
// Transform complex data into two seperate fields
// with real and imag data (in-place)
// n := array length
{
    unzip((double *)c, 2*n);  // jjcast
}
// -------------------------


void
real_imag_to_complex(double *fr/*, double *fi*/, ulong n)
// Transform two seperate fields with real and imag
// data into complex data (in-place)
// n := array length(s)
// Must have: imaginary parts must start at  (fr + n).
// That is, the data must lie in contiguous memory.
{
    zip(fr, 2*n);
}
// -------------------------


void
complex_fft(Complex *c, ulong ldn, int is)
// FFT wrapper to use the routines that use the data
// in the real/imag form for type complex data
// ldn := base-2 logarithm of the array length
// is := sign of the transform (+1 or -1)
// NOTE: dprecated, prefer routine that uses type Complex.
{
    const ulong n = (1UL<<ldn);
    double *fr = (double *)c;  // jjcast
    double *fi = fr + n;
    complex_to_real_imag(c, n);
    fht_fft(fr, fi, ldn, is);
    real_imag_to_complex(fr, n);
}
// -------------------------


void
real_imag_fft(double *fr/*, double *fi*/, ulong ldn, int is)
// FFT wrapper to use the routines that use the data
// in the complex form for data in real/imag form
// ldn := base-2 logarithm of the array length
// is := sign of the transform (+1 or -1)
// Must have: imaginary parts must start at  (fr + n).
// That is, the data must lie in contiguous memory.
{
    const ulong n  = (1UL<<ldn);
    real_imag_to_complex(fr, n);
    Complex *c = (Complex *)fr;  // jjcast
    //  here goes your type Complex FFT:
    fht_fft(c, ldn, is);
    complex_to_real_imag(c, n);
}
// -------------------------

