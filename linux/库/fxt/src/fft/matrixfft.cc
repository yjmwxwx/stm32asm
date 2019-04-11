// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fft/matrixfft.h"
#include "aux0/ldn2rc.h"

#include "aux2/transpose2.h"
#include "bits/bit2pow.h"

#include "fxttypes.h"  // ulong
#include "complextype.h"  // Complex


void
matrix_fft(double *fr, double *fi, ulong ldn, int is)
// Matrix (aka four-step) FFT.
// Useful for arrays larger than 2nd-level cache.
{
    ulong nr, nc;
    ldn2rc(ldn, nr, nc);
    column_ffts(fr, fi, nr, nc, is, 0, 0, 0);
    row_weighted_ffts(fr, fi, nr, nc, is);
    transpose2(fr, nr, nc);
    transpose2(fi, nr, nc);
}
// -------------------------


void
matrix_fft0(double *fr, double *fi, ulong ldn, int is)
// Matrix (aka four-step) FFT.
// Useful for arrays larger than 2nd-level cache.
// Version for zero padded data.
{
    ulong nr, nc;
    ldn2rc(ldn, nr, nc);
    column_ffts(fr, fi, nr, nc, is, 1, 0, 0);
    row_weighted_ffts(fr, fi, nr, nc, is);
    transpose2(fr, nr, nc);
    transpose2(fi, nr, nc);
}
// -------------------------


void
matrix_fft(Complex *f, ulong ldn, int is)
// Matrix (aka four-step) FFT.
// Useful for arrays larger than 2nd-level cache.
{
    ulong nr, nc;
    ldn2rc(ldn, nr, nc);
    column_ffts(f, nr, nc, is, 0, 0);
    row_weighted_ffts(f, nr, nc, is);
    transpose2(f, nr, nc);
}
// -------------------------


void
matrix_fft0(Complex *f, ulong ldn, int is)
// Matrix (aka four-step) FFT.
// Useful for arrays larger than 2nd-level cache.
// Version for zero padded data.
{
    ulong nr, nc;
    ldn2rc(ldn, nr, nc);
    column_ffts(f, nr, nc, is, 1, 0);
    row_weighted_ffts(f, nr, nc, is);
    transpose2(f, nr, nc);
}
// -------------------------
