// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "convolution/realconvolution.h"
#include "realfft/realfft.h"
#include "aux0/cmult.h"
#include "fxttypes.h"  // ulong


void
fht_fft_auto_convolution(double *f, ulong ldn)
// (cyclic, real) self-convolution:  f[] :=  f[] (*) f[]
// ldn := base-2 logarithm of the array length
{
    fht_real_complex_fft(f, ldn);
    fft_auto_convolution_core1(f, ldn);
    fht_complex_real_fft(f, ldn);
}
// -------------------------


void
split_radix_fft_auto_convolution(double *f, ulong ldn)
// (cyclic, real) self-convolution:  f[] :=  f[] (*) f[]
// ldn := base-2 logarithm of the array length
{
    split_radix_real_complex_fft(f, ldn);
    fft_auto_convolution_core1(f, ldn);
    split_radix_complex_real_fft(f, ldn);
}
// -------------------------


void
fht_fft_auto_convolution0(double *f, ulong ldn)
// (linear, real) self-convolution:  f[] :=  f[] (*0) f[]
// ldn := base-2 logarithm of the array length
// input data must be zero padded: f[n/2] .. f[n-1] == 0
// n = 2**ldn  must be >=2
{
    fht_real_complex_fft0(f, ldn);
    fft_auto_convolution_core1(f, ldn);
    fht_complex_real_fft(f, ldn);
}
// -------------------------


void
split_radix_fft_auto_convolution0(double *f, ulong ldn)
// (linear, real) self-convolution:  f[] :=  f[] (*0) f[]
// ldn := base-2 logarithm of the array length
// input data must be zero padded: f[n/2] .. f[n-1] == 0
// n = 2**ldn  must be >=2
{
    split_radix_real_complex_fft0(f, ldn);
    fft_auto_convolution_core1(f, ldn);
    split_radix_complex_real_fft(f, ldn);
}
// -------------------------


void
fft_auto_convolution_core1(double *f, ulong ldn, double v/*=0.0*/)
// auxiliary routine for FFT based (real) self-convolutions
// supply a value for v for a normalization factor != 1/n
{
    const ulong n  = (1UL<<ldn);

    if ( v==0.0 )  v = 1.0/(double)n;

    f[0]  *= f[0] * v;

    const ulong nh = n/2;
    if ( nh>0 )
    {
        f[nh] *= f[nh] * v;

        for (ulong i=1, j=n-1;  i<j;  ++i, --j)
        {
            csqr_n(f[i], f[j], v);
        }
    }
}
// -------------------------


void
fft_auto_convolution_core2(double *f, ulong ldn, double v/*=0.0*/)
// auxiliary routine for FFT based (real) self-convolutions
// supply a value for v for a normalization factor != 1/n
{
    const ulong n  = (1UL<<ldn);

    if ( v==0.0 )  v = 1.0/(double)n;

    f[0]  *= f[0] * v;

    const ulong nh = n/2;
    if ( nh>0 )
    {
        f[nh] *= f[nh] * v;

        for (ulong i=1, j=nh+1;  i<nh;  ++i, ++j)
        {
            csqr_n(f[i], f[j], v);
        }
    }
}
// -------------------------
