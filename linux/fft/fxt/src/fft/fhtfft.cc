// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fht/fht-default.h"
#include "fft/fft.h"
#include "aux0/sumdiff.h"
#include "fxttypes.h"  // ulong


#define  FHT_FFT_VERSION  0  // 0 or 1, doesn't matter

void
fht_fft(double *fr, double *fi, ulong ldn, int is)
// FFT based on FHT
// ldn := base-2 logarithm of the array length
// is := sign of the transform (+1 or -1)
{
#if  ( FHT_FFT_VERSION==1 )
    fht_fft_conversion(fr, fi, ldn, is);
    fht(fr, ldn);
    fht(fi, ldn);
#else  // FHT_FFT_VERSION
// alternative version, else same as fht_fft():
    fht(fr, ldn);
    fht(fi, ldn);
    fht_fft_conversion(fr, fi, ldn, is);
#endif  // FHT_FFT_VERSION
}
// -------------------------


void
fht_fft0(double *fr, double *fi, ulong ldn, int is)
// FFT based on FHT
// version for zero padded data:
//   fr[k], fi[k] == 0 for k=n/2 ... n-1
// ldn := base-2 logarithm of the array length
// is := sign of the transform (+1 or -1)
{
    fht0(fr, ldn);
    fht0(fi, ldn);
    fht_fft_conversion(fr, fi, ldn, is);
}
// -------------------------


void
fht_fft_conversion(double *fr, double *fi, ulong ldn, int is)
// preprocessing to use two length-n FHTs
// to compute a length-n complex FFT
// or
// postprocessing to use two length-n FHTs
// to compute a length-n complex FFT
//
// Self-inverse.
//
// is := sign of the transform (+1 or -1)
// ldn := base-2 logarithm of the array length
{
    const ulong n = (1UL<<ldn);

    if ( is>0 )
    {
        for (ulong i=1, j=n-1;  i<j;  i++, j--)
        {
            double q, r, s, t;
            sumdiff(fr[i], fr[j], q, r);
            sumdiff(fi[i], fi[j], s, t);
            sumdiff05(q, t, fr[j], fr[i]);
            sumdiff05(s, r, fi[i], fi[j]);
        }
    }
    else  // r, t negated
    {
        for (ulong i=1, j=n-1;  i<j;  i++, j--)
        {
            double q, r, s, t;
            sumdiff(fr[j], fr[i], q, r);
            sumdiff(fi[j], fi[i], s, t);
            sumdiff05(q, t, fr[j], fr[i]);
            sumdiff05(s, r, fi[i], fi[j]);
        }
    }
}
// -------------------------
