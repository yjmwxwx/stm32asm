// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fft/fft-default.h"
#include "aux0/cmult.h"
#include "aux0/sumdiff.h"
#include "restrict.h"
#include "fxttypes.h"  // ulong
//#include "complextype.h"


//#define  FFT(fr, fi, ldn, is)   fht_fft(fr, fi, ldn, is)
#define  FFT(fr, fi, ldn, is)   fft(fr, fi, ldn, is)

void
fft_complex_auto_correlation(double * restrict fr, double * restrict fi, ulong ldn)
//
// Complex (cyclic) self-correlation
// (use zero padded data for linear correlation)
//
// ldn := base-2 logarithm of the array length
//
{
    const int is = 1;
    const ulong n = (1UL<<ldn);

    FFT(fr, fi, ldn, +is);

    csqr(fr[0],  fi[0]);
    const ulong nh = (n>>1);
    csqr(fr[nh], fi[nh]);
    double v = 1.0/(double)n;
    for (ulong k=1, j=n-1;  k<j;  k++, j--)
    {
        double r1 = fr[k];
        double i1 = fi[k];
        double r2 = fr[j];
        double i2 = fi[j];
        cmult(r1, i1, r2, i2, fr[k], fi[k]);
        fr[j] = fr[k] * v;
        fi[j] = fi[k] * v;
    }

    FFT(fr, fi, ldn, -is);
}
// -------------------------



void
fft_complex_correlation(double * restrict fr, double * restrict fi,
                        double * restrict gr, double * restrict gi,
                        ulong ldn)
//
// Complex (cyclic) correlation of fr, fi with gr, gi
// (use zero padded data for linear convolution)
//
// ldn := base-2 logarithm of the array length
//
// Result in gr, gi
//
{
    const int is = 1;

    FFT(fr, fi, ldn, -is);
    FFT(gr, gi, ldn, +is);

    const ulong n = (1UL<<ldn);
    double v = 1.0/(double)n;
    for (ulong k=0; k<n; ++k)
    {
        double tr = fr[k];
        double ti = fi[k];
        cmult(gr[k], gi[k], tr, ti);
        gr[k] = tr * v;
        gi[k] = ti * v;
    }

    FFT(gr, gi, ldn, -is);
}
// -------------------------

