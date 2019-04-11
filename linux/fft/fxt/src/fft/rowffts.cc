// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fft/fft-default.h"
#include "bits/bit2pow.h"  // ld()

#include "fxttypes.h"  // ulong
#include "complextype.h"  // Complex


void
row_ffts(double *fr, double *fi, ulong nr, ulong nc, int is)
//
// nr x nc matrix (nr rows of length nc)
//
{
    ulong ldc = ld(nc);
    double *pr = fr,  *pi = fi;
    for (ulong k=0; k<nr; ++k)
    {
        fft(pr, pi, ldc, is);  // note: cache problem !

        pr += nc;
        pi += nc;
    }
}
// -------------------------


void
row_weighted_ffts(double *fr, double *fi, ulong nr, ulong nc, int is)
//
// nr x nc matrix (nr rows of length nc)
//
{
    ulong ldc = ld(nc);
    double *pr = fr,  *pi = fi;
    const double ph = (double)is / (double)nr;
    for (ulong k=0; k<nr; ++k)
    {
//        fourier_shift(pr, pi, nc, 1.0*is*k/nr);  // note: cache problem !
        fourier_shift(pr, pi, nc, (double)k*ph);  // note: cache problem !
        fft(pr, pi, ldc, is);  // note: cache problem !

        pr += nc;
        pi += nc;
    }
}
// -------------------------


void
row_ffts(Complex *f, ulong nr, ulong nc, int is)
//
// nr x nc matrix (nr rows of length nc)
//
{
    ulong ldc = ld(nc);
    Complex *p = f;
    for (ulong k=0; k<nr; ++k)
    {
        fft(p, ldc, is);
        p += nc;
    }
}
// -------------------------


void
row_weighted_ffts(Complex *f, ulong nr, ulong nc, int is)
//
// nr x nc matrix (nr rows of length nc)
//
{
    ulong ldc = ld(nc);
    const double ph = (double)is / (double)nr;
    Complex *p = f;
    for (ulong k=0; k<nr; ++k)
    {
//        fourier_shift(p, nc, 1.0*is*k/nr);
        fourier_shift(p, nc, (double)k*ph);
        fft(p, ldc, is);
        p += nc;
    }
}
// -------------------------

