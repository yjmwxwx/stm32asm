// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fft/fft.h"
#include "bits/bit2pow.h"  // ld()

#include "aux1/copy.h"

#include "fxttypes.h"  // ulong


#define  FFT(re, im, ldn, is)   fht_fft(re, im, ldn, is)
#define  FFT0(re, im, ldn, is)  fht_fft0(re, im, ldn, is)

void
skip_fft(double *fr, double *fi, ulong n, ulong d,
         double *wr, double *wi, int is)
// Compute FFT of the n elements
// fr, fi [0], [d], [2d], [3d], ..., [(n-1)*d]
{
    skip_copy(fr, wr, n, d);
    skip_copy(fi, wi, n, d);

    ulong ldn = ld(n);
    FFT(wr, wi, ldn, is);

    skip_copy_back(wr, fr, n, d);
    skip_copy_back(wi, fi, n, d);
}
// -------------------------


void
skip_fft0(double *fr, double *fi, ulong n, ulong d,
          double *wr, double *wi, int is)
// Compute FFT of the n elements
// fr, fi [0], [d], [2d], [3d], ..., [(n-1)*d]
// version for zero padded data:
//   fr[k], fi[k] == 0 for k=d*n/2 ... d*(n-1)
{
    ulong nh = (n>>1);
    skip_copy(fr, wr, nh, d);
    null(wr+nh, nh);
    skip_copy(fi, wi, nh, d);
    null(wi+nh, nh);

    ulong ldn = ld(n);
    FFT0(wr, wi, ldn, is);

    skip_copy_back(wr, fr, n, d);
    skip_copy_back(wi, fi, n, d);
}
// -------------------------
