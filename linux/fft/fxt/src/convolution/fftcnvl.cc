// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "realfft/realfft.h"
#include "convolution/realconvolution.h"
#include "aux0/cmult.h"
#include "aux0/sumdiff.h"
#include "restrict.h"
#include "fxttypes.h"  // ulong


void
fht_fft_convolution(double * restrict f, double * restrict g, ulong ldn)
// (cyclic, real) convolution:  g[] :=  f[] (*) g[]
// ldn := base-2 logarithm of the array length
{
    fht_real_complex_fft(f, ldn);
    fht_real_complex_fft(g, ldn);

    fft_convolution_core1(f, g, ldn);

    fht_complex_real_fft(g, ldn);
}
// -------------------------


void
split_radix_fft_convolution(double * restrict f, double * restrict g, ulong ldn)
// (cyclic, real) convolution:  g[] :=  f[] (*) g[]
// ldn := base-2 logarithm of the array length
// n = 2**ldn  must be >=2
{
//    if ( ldn==0 )  { g[0] *= f[0];  return; }

    split_radix_real_complex_fft(f, ldn);
    split_radix_real_complex_fft(g, ldn);

    fft_convolution_core1(f, g, ldn);

    split_radix_complex_real_fft(g, ldn);
}
// -------------------------


void
fht_fft_convolution0(double * restrict f, double * restrict g, ulong ldn)
// (linear, real) convolution:  g[] :=  f[] (*) g[]
// ldn := base-2 logarithm of the array length
// input data must be zero padded:
//   f[n/2] .. f[n-1] == 0 and g[n/2] .. g[n-1] == 0
// n = 2**ldn  must be >=2
{
    fht_real_complex_fft0(f, ldn);
    fht_real_complex_fft0(g, ldn);

    fft_convolution_core1(f, g, ldn);

    fht_complex_real_fft(g, ldn);
}
// -------------------------


void
split_radix_fft_convolution0(double * restrict f, double * restrict g, ulong ldn)
// (linear, real) convolution:  g[] :=  f[] (*) g[]
// ldn := base-2 logarithm of the array length
// input data must be zero padded:
//   f[n/2] .. f[n-1] == 0 and g[n/2] .. g[n-1] == 0
// n = 2**ldn  must be >=2
{
    split_radix_real_complex_fft0(f, ldn);
    split_radix_real_complex_fft0(g, ldn);

    fft_convolution_core1(f, g, ldn);

    split_radix_complex_real_fft(g, ldn);
}
// -------------------------



void
fft_convolution_core1(const double * restrict f, double * restrict g,
                      ulong ldn, double v/*=0.0*/)
// Auxiliary routine for FFT based convolutions.
// Supply a value for v for a normalization factor != 1/n
{
    const ulong n  = (1UL<<ldn);

    if ( v==0.0 )  v = 1.0/(double)n;

    g[0]  *= f[0] * v;
    const ulong nh = n/2;
    g[nh] *= f[nh] * v;

    for (ulong i=1, j=n-1;  i<j;  ++i, --j)
    {
        cmult_n(f[i], f[j], g[i], g[j], v);
    }
}
// -------------------------


void
fft_convolution_core2(const double * restrict f, double * restrict g,
                      ulong ldn, double v/*=0.0*/)
// Auxiliary routine for FFT based convolutions.
// Supply a value for v for a normalization factor != 1/n
{
    const ulong n  = (1UL<<ldn);

    if ( v==0.0 )  v = 1.0/(double)n;

    g[0]  *= f[0] * v;
    const ulong nh = n/2;
    g[nh] *= f[nh] * v;

    for (ulong i=1, j=nh+1;  i<nh;  ++i, ++j)
    {
        cmult_n(f[i], f[j], g[i], g[j], v);
    }
}
// -------------------------
