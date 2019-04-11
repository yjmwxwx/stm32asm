// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fft/fft-default.h"
#include "aux0/cmult.h"
#include "aux0/sumdiff.h"

#include "restrict.h"

#include "fxttypes.h"  // ulong
#include "complextype.h"  // Complex


//#define  FFT(fr, fi, ldn, is)   fht_fft(fr, fi, ldn, is)
#define  FFT(fr, fi, ldn, is)   fft(fr, fi, ldn, is)

// tuning parameter:
#define  USE_SPLRX  0  // whether split-radix DIF/DIT FFTs are used (default=0)
#if ( USE_SPLRX==1 )
//#warning 'FYI: complex_(auto)_convolution() use split-radix FFTs'
#define  DIT_FFT_CORE  split_radix_fft_dit_core  // isign = -1
#define  DIF_FFT_CORE  split_radix_fft_dif_core  // isign = +1
#else
//#warning 'FYI: complex_(auto)_convolution() use radix-4 FFTs'
#define  DIT_FFT_CORE  fft_dit4_core_m1  // isign = -1
#define  DIF_FFT_CORE  fft_dif4_core_p1  // isign = +1
#endif


void
fft_complex_auto_convolution(Complex *f, ulong ldn,
                             double v/*=0.0*/)
// (complex, cyclic) self-convolution:  f[] :=  f[] (*) f[]
// Use zero padded data for linear convolution.
// ldn := base-2 logarithm of the array length.
// Supply a value for v if the normalization factor
//   shall differ from 1/n
{
    const ulong n = (1UL<<ldn);

    DIF_FFT_CORE(f, ldn);
    if ( v==0.0 )  v = 1.0/(double)n;
    for (ulong i=0; i<n; ++i)
    {
        Complex t = f[i];
        t *= t;
        f[i] = t * v;
    }
    DIT_FFT_CORE(f, ldn);
}
// -------------------------


void
fft_complex_convolution(Complex * restrict f, Complex * restrict g,
                        ulong ldn, double v/*=0.0*/)
// (complex, cyclic) convolution:  g[] :=  f[] (*) g[]
// Use zero padded data for usual convolution.
// ldn := base-2 logarithm of the array length.
// Supply a value for v if the normalization factor
//   shall differ from 1/n
{
    const ulong n = (1UL<<ldn);

    DIF_FFT_CORE(f, ldn);
    DIF_FFT_CORE(g, ldn);
    if ( v==0.0 )  v = 1.0/(double)n;
    for (ulong i=0; i<n; ++i)
    {
        Complex t = g[i] * f[i];
        g[i] = t * v;
    }
    DIT_FFT_CORE(g, ldn);
}
// -------------------------


void
fft_complex_auto_convolution(double * restrict fr, double * restrict fi,
                             ulong ldn, double v/*=0.0*/)
// (complex, cyclic) self-convolution:
//   (fr, fi)[] :=  (fr, fi)[] (*) (fr, fi)[]
// Use zero padded data for linear convolution.
// ldn := base-2 logarithm of the array length.
// Supply a value for v if the normalization factor
//   shall differ from 1/n
{
    const int is = 1;
    const ulong n = (1UL<<ldn);

    FFT(fr, fi, ldn, is);

    if ( v==0.0 )  v = 1.0/(double)n;
    for (ulong k=0; k<n; ++k)
    {
        double tr = fr[k];
        double ti = fi[k];
        csqr(tr, ti);
        fr[k] = tr * v;
        fi[k] = ti * v;
    }

    FFT(fr, fi, ldn, -is);
}
// -------------------------


void
fft_complex_convolution(double * restrict fr, double * restrict fi,
                        double * restrict gr, double * restrict gi,
                        ulong ldn, double v/*=0.0*/)
// (complex, cyclic) convolution:
//   (gr, gi)[] :=  (fr, fi)[] (*) (gr, gi)[]
// Use zero padded data for usual convolution.
// ldn := base-2 logarithm of the array length.
// Supply a value for v if the normalization factor
//   shall differ from 1/n
{
    const int is = 1;
    const ulong n = (1UL<<ldn);

    FFT(fr, fi, ldn, is);
    FFT(gr, gi, ldn, is);

    if ( v==0.0 )  v = 1.0/(double)n;
    for (ulong k=0; k<n; ++k)
    {
        double tr = fr[k];
        double ti = fi[k];
        cmult(gr[k], gi[k], tr, ti);
        gr[k] = tr * v;
        gi[k] = ti * v;

        cmult(fr[k], fi[k], gr[k], gi[k]);
    }

    FFT(gr, gi, ldn, -is);
}
// -------------------------
