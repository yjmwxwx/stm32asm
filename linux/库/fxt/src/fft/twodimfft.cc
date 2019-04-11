// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/bit2pow.h"  // ld()
#include "fft/fft-default.h"
#include "fxttypes.h"  // ulong


//#define FFT(re, im, ldn, is)  fht_fft(re, im, ldn, is)
#define FFT(re, im, ldn, is)  fft(re, im, ldn, is)


void
twodim_fft(double *fr, double *fi, ulong nr, ulong nc, int is)
{
    ulong n = nr * nc;

    // fft over rows:
    ulong ldc = ld(nc);
    for (ulong k=0; k<n; k+=nc)  FFT(fr+k, fi+k, ldc, is);

    // fft over columns:
    double *wr = new double[2*nr];
    double *wi = wr + nr;
    for (ulong k=0; k<nc; k++)  skip_fft(fr+k, fi+k, nr, nc, wr, wi, is);
    delete [] wr;
}
// -------------------------
