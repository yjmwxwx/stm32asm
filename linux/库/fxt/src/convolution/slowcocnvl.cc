// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/cmult.h"

#include "fxtalloca.h"
#include "fxttypes.h"
#include "complextype.h"

#include "aux1/copy.h"


void
slow_complex_convolution(const double *fr, const double *fi,
                         double *gr, double *gi, ulong n)
// (cyclic, complex) convolution:  (gr, gi)[] :=  (fr,fi)[] (*) (gr,gi)[]
// (use zero padded data for linear convolution)
{
    ALLOCA(double, hr, 2*n);
    double *hi = hr + n;

    long ns = (long)n;
    for (long tau=0; tau<ns; ++tau)
    {
        double sr = 0.0, si = 0.0;
        for (long k=0; k<ns; ++k)
        {
             long k2 = tau - k;
             if ( k2<0 )  k2 += ns;

             double ar = gr[k];
             double ai = gi[k];
             cmult(fr[k2], fi[k2], ar, ai);

             sr += ar;
             si += ai;
        }

        hr[tau] = sr;
        hi[tau] = si;
    }
    acopy(hr, gr, n);
    acopy(hi, gi, n);
}
// -------------------------


void
slow_complex_auto_convolution(double *fr, double *fi, ulong n)
// (cyclic, complex) self-convolution:  (fr,fi)[] := (fr,fi)[] (*) (fr,fi)[]
// (use zero padded data for linear convolution)
{
    slow_complex_convolution(fr, fi, fr, fi, n);
}
// -------------------------

