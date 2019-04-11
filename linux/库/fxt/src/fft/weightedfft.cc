// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fft/fft-default.h"
#include "fxttypes.h"  // ulong


void
weighted_fft(double *fr, double *fi, ulong ldn, int is, double w)
// Weighted FFT
{
    ulong n = (1UL<<ldn);
    fourier_shift(fr, fi, n, w);
    fft(fr, fi, ldn, is);
}
// -------------------------


void
weighted_inverse_fft(double *fr, double *fi, ulong ldn, int is, double w)
// Inverse of weighted_fft() iff signs of both w and is are changed
{
    ulong n = (1UL<<ldn);
    fft(fr, fi, ldn, is);
    fourier_shift(fr, fi, n, w);
}
// -------------------------

