// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "convolution/weightedconvolution.h"

#include "bits/bit2pow.h"  // ld()

#include "fxttypes.h"  // ulong
#include "complextype.h"  // Complex


void
row_weighted_auto_convolutions(double *fr, double *fi, ulong nr, ulong nc, double v)
//
// (complex, weighted) convolution of the rows of the
// nr x nc matrix (nr rows, nc columns)
//
// v!=0.0 chooses alternative normalization
{
    const ulong ldc = ld(nc);

    const double inr = 1.0 / (double)nr;
    double *pr = fr, *pi = fi;
    for (ulong k=0; k<nr; ++k)
    {
//        double w = (double)k / (double)nr;
        double w = (double)k * inr;
        weighted_complex_auto_convolution(pr, pi, ldc, w, v);
        pr += nc;
        pi += nc;
    }
}
// -------------------------


void
row_weighted_auto_convolutions(Complex *f, ulong nr, ulong nc, double v)
//
// (complex, weighted) convolution of the rows of the
// nr x nc matrix (nr rows, nc columns)
//
// v!=0.0 chooses alternative normalization
{
    const ulong ldc = ld(nc);

    const double inr = 1.0 / (double)nr;
    Complex *p = f;
    for (ulong k=0; k<nr; ++k)
    {
//        double w = (double)k / (double)nr;
        double w = (double)k * inr;
        weighted_complex_auto_convolution(p, ldc, w, v);
        p += nc;
    }
}
// -------------------------

