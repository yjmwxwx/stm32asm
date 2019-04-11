// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "realfft/realfft.h"
#include "aux0/cmult.h"
#include "aux0/sumdiff.h"
#include "fxttypes.h"  // ulong


void
fft_correlation(double *f, double *g, ulong ldn)
// Cyclic correlation of f[], g[], both real-valued sequences.
// Result is written to g[].
// ldn := base-2 logarithm of the array length
// n = 2**ldn  must be >=2
{
    const ulong n=(1UL<<ldn);
    const ulong nh=(n>>1);

    fht_real_complex_fft(f, ldn);  // real, imag part in lower, upper half
    fht_real_complex_fft(g, ldn);

    const double v = 1.0/(double)n;
    g[0]  *= f[0] * v;
//    if ( nh>0 )
    {
        g[nh] *= f[nh] * v;
        for (ulong i=1, j=n-1;  i<nh;  ++i, --j)  // real at index i, imag at index j
        {
            cmult_n(f[i], -f[j], g[i], g[j], v);
        }
    }

    fht_complex_real_fft(g, ldn);
}
// -------------------------


void
fft_auto_correlation(double *f, ulong ldn)
// Cyclic self-correlation of f[], a real-valued sequence.
// ldn := base-2 logarithm of the array length
// n = 2**ldn  must be >=2
{
    const ulong n=(1UL<<ldn);
    const ulong nh=(n>>1);

    fht_real_complex_fft(f, ldn);

    const double v = 1.0/(double)n;
    f[0]  *= f[0] * v;
//    if ( nh>0 )
    {
        f[nh] *= f[nh] * v;
        for (ulong i=1, j=n-1;  i<nh;  ++i, --j)
        {
            f[i] = (f[i]*f[i] + f[j]*f[j]) * v;
            f[j] = 0;
        }
    }

    fht_complex_real_fft(f, ldn);
}
// -------------------------


void
fft_correlation0(double *f, double *g, ulong ldn)
// Linear correlation of f[], g[], two real-valued sequences.
// Result is written to g[].
// Version for zero padded data:
//   f[k], g[k] == 0 for k=n/2 ... n-1
// ldn := base-2 logarithm of the array length
// n = 2**ldn  must be >=2
{
    const ulong n=(1UL<<ldn);
    const ulong nh=(n>>1);

    fht_real_complex_fft0(f, ldn);
    fht_real_complex_fft0(g, ldn);

    const double v = 1.0/(double)n;
    g[0]  *= f[0] * v;
//    if ( nh>0 )
    {
        g[nh] *= f[nh] * v;
        for (ulong i=1, j=n-1;  i<nh;  ++i, --j)
        {
            cmult_n(f[i], -f[j], g[i], g[j], v);
        }
    }

    fht_complex_real_fft(g, ldn);
}
// -------------------------


void
fft_auto_correlation0(double *f, ulong ldn)
// Linear self-correlation of f[], a real-valued sequence.
// Version for zero padded data:
//   f[k] == 0 for k=n/2 ... n-1
// ldn := base-2 logarithm of the array length
// n = 2**ldn  must be >=2
{
    const ulong n=(1UL<<ldn);
    const ulong nh=(n>>1);

    fht_real_complex_fft0(f, ldn);

    const double v = 1.0/(double)n;
    f[0]  *= f[0] * v;
//    if ( nh>0 )
    {
        f[nh] *= f[nh] * v;
        for (ulong i=1, j=n-1;  i<nh;  ++i, --j)
        {
            f[i] = (f[i]*f[i] + f[j]*f[j]) * v;
            f[j] = 0;
        }
    }

    fht_complex_real_fft(f, ldn);
}
// -------------------------
