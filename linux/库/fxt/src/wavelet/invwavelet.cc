// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "wavelet/wavelet.h"  // inverse_wavelet_step()
#include "wavelet/waveletfilter.h"

#include "aux1/copy.h"  // null(), acopy()

#include "fxttypes.h"
#include "fxtalloca.h"


void
inverse_wavelet(double *f, ulong ldn, const wavelet_filter &wf, ulong minm/*=2*/)
// Inverse wavelet transform
{
    ulong n = (1UL<<ldn);
    ALLOCA(double, t, n);
    for (ulong m=minm; m<=n; m<<=1)  inverse_wavelet_step(f, m, wf, t);
}
// -------------------------


void
inverse_wavelet_step(double *f, ulong n, const wavelet_filter &wf, double *t)
{
    const ulong nh = (n>>1);
    const ulong m = n-1;  // mask to compute modulo n (n is a power of 2)
    null(t, n);  // t[] := [0,0,...,0]
    for (ulong i=0, j=0;  i<n;  i+=2, ++j)
    {
        const double x = f[j],  y = f[nh+j];
        for (ulong k=0;  k<wf.n_;  ++k)
        {
            ulong w = (i+k) & m;
            t[w] += (wf.h_[k] * x);
            t[w] += (wf.g_[k] * y);
        }
    }
    acopy(t, f, n);  // f[] := t[]
}
// -------------------------

