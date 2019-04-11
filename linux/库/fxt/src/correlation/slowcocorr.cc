// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/cmult.h"

#include "aux1/copy.h"

#include "fxtalloca.h"
#include "fxttypes.h"


void
slow_complex_correlation(const double *fr, const double *fi,
                         const double *gr, const double *gi,
                         double *hr, double *hi,
                         ulong n)
// (cyclic, complex) correlation:  (hr, hi)[] :=  (fr,fi)[] (c) (gr,gi)[]
// (use zero padded data for linear correlation)
{
    long ns = (long)n;
    for (long tau=0; tau<ns; ++tau)
    {
        double sr=0.0, si=0.0;
        for (long k=0; k<ns; ++k)
        {
             long k2 = k + tau;
             if ( k2>=ns )  k2 -= ns;

             double ar = gr[k];
             double ai = gi[k];

             cmult(fr[k2], fi[k2], ar, ai);

             sr += ar;
             si += ai;
        }
        hr[tau] = sr;
        hi[tau] = si;
    }
}
// -------------------------


void
slow_complex_correlation(const double *fr, const double *fi,
                         double *gr, double *gi, ulong n)
// (cyclic, complex) correlation:  (gr, gi)[] :=  (fr,fi)[] (c) (gr,gi)[]
// (use zero padded data for linear correlation)
{
    ALLOCA(double, hr, n);
    ALLOCA(double, hi, n);

    slow_complex_correlation(fr, fi, gr, gi, hr, hi, n);

    acopy(hr, gr, n);
    acopy(hi, gi, n);
}
// -------------------------


void
slow_complex_auto_correlation(double *fr, double *fi, ulong n)
// (cyclic, complex) self-correlation:  (gr, gi)[] :=  (fr,fi)[] (c) (fr,fi)[]
// (use zero padded data for linear correlation)
{
    slow_complex_correlation(fr, fi, fr, fi, n);
}
// -------------------------
