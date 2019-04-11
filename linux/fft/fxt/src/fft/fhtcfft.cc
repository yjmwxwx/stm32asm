// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fht/fht-default.h"
#include "fft/fft.h"
#include "aux0/cmult.h"
#include "aux0/sumdiff.h"

#include "fxttypes.h"  // ulong
#include "complextype.h"  // Complex


#define  FHT_FFT_VERSION  0  // 0 or 1, doesn't matter

void
fht_fft(Complex *f, ulong ldn, int is)
// compute FFT using the Fast Hartley Transform
// ldn := base-2 logarithm of the array length
// is := sign of the transform (+1 or -1)
{
#if  ( FHT_FFT_VERSION==1 )
    fht_fft_conversion(f, ldn, is);
    fht(f, ldn);
#else  // FHT_FFT_VERSION
// alternative version, else same as fht_fft():
    fht(f, ldn);
    fht_fft_conversion(f, ldn, is);
#endif  // FHT_FFT_VERSION
}
// -------------------------


void
fht_fft0(Complex *f, ulong ldn, int is)
// compute FFT using the Fast Hartley Transform
// ldn := base-2 logarithm of the array length
// is := sign of the transform (+1 or -1)
// version for zero padded data:
//   f[k] == 0 for k=n/2 ... n-1
{
    fht0(f, ldn);
    fht_fft_conversion(f, ldn, is);
}
// -------------------------


void
fht_fft_conversion(Complex *f, ulong ldn, int is)
// preprocessing to use one length-n complex FHT
// to compute a length-n complex FFT
// or
// postprocessing to use one length-n complex FHT
// to compute a length-n complex FFT
//
// Self-inverse.
//
// is := sign of the transform (+1 or -1)
// ldn := base-2 logarithm of the array length
{
    const ulong n = (1UL<<ldn);
    double *fr = (double *)f;  // jjcast
    double *fi = fr + 1;
    if ( is>0 )
    {
        for (ulong i2=2, j2=2*(n-1);  i2<j2;  i2+=2, j2-=2)
        {
            double q, r, s, t;
            sumdiff(fr[i2], fr[j2], q, r);
            sumdiff(fi[i2], fi[j2], s, t);
            sumdiff05(q, t, fr[j2], fr[i2]);
            sumdiff05(s, r, fi[i2], fi[j2]);
        }
    }
    else  // r,t negated
    {
        for (ulong i2=2, j2=2*(n-1);  i2<j2;  i2+=2, j2-=2)
        {
            double q, r, s, t;
            sumdiff(fr[j2], fr[i2], q, r);
            sumdiff(fi[j2], fi[i2], s, t);
            sumdiff05(q, t, fr[j2], fr[i2]);
            sumdiff05(s, r, fi[i2], fi[j2]);
        }
    }
}
// -------------------------

