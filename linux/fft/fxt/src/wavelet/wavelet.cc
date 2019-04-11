// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "wavelet/wavelet.h"  // wavelet_step()
#include "wavelet/waveletfilter.h"

#include "aux1/copy.h"  // acopy()

#include "fxtalloca.h"
#include "fxttypes.h"


void
wavelet(double *f, ulong ldn, const wavelet_filter &wf, ulong minm/*=2*/)
// Wavelet transform
{
    ulong n = (1UL<<ldn);
    ALLOCA(double, t, n);
    for (ulong m=n; m>=minm; m>>=1)  wavelet_step(f, m, wf, t);
}
// -------------------------


void
wavelet_step(double *f, ulong n, const wavelet_filter &wf, double *t)
{
    const ulong nh = (n>>1);
    const ulong m = n-1;  // mask to compute modulo n (n is a power of 2)
    for (ulong i=0, j=0;  i<n;  i+=2, ++j)  // i \in [0,2,4,..,n-2];  j \in [0,1,2,..,n/2-1]
    {
        double s = 0.0,  d = 0.0;
        for (ulong k=0; k<wf.n_; ++k)
        {
            ulong w = (i+k) & m;
            s += (wf.h_[k] * f[w]);
            d += (wf.g_[k] * f[w]);
        }
        t[j] = s;
        t[nh+j] = d;
    }
    acopy(t, f, n);  // f[] := t[]
}
// -------------------------
