// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "realfft/realfft.h"

#include "bits/bit2pow.h"  // ld()
#include "fxttypes.h"  // ulong

#include "aux1/copy.h"


#define  REAL_COMPLEX_FFT(x, ldn)   fht_real_complex_fft(x, ldn)
#define  REAL_COMPLEX_FFT0(x, ldn)  fht_real_complex_fft0(x, ldn)

#define  COMPLEX_REAL_FFT(x, ldn)   fht_complex_real_fft(x, ldn)


void
skip_real_complex_fft(double *f, ulong n, ulong d, double *w)
// Compute real to complex FFT of the n elements
// [0],[d],[2d],[3d],...,[(n-1)*d]
{
    skip_copy(f, w, n, d);

    ulong ldn = ld(n);
    REAL_COMPLEX_FFT(w, ldn);

    skip_copy_back(w, f, n, d);
}
// -------------------------


void
skip_real_complex_fft0(double *f, ulong n, ulong d, double *w)
// Compute real to complex FFT of the n elements
// [0],[d],[2d],[3d],...,[(n-1)*d]
// where the upper half are known to be zero.
{
    ulong nh = (n>>1);
    skip_copy(f, w, nh, d);
    null(w+nh, nh);

    ulong ldn = ld(n);
    REAL_COMPLEX_FFT0(w, ldn);

    skip_copy_back(w, f, n, d);
}
// -------------------------


void
skip_complex_real_fft(double *f, ulong n, ulong d, double *w)
// Compute complex to real FFT of the n elements
// [0],[d],[2d],[3d],...,[(n-1)*d]
{
    skip_copy(f, w, n, d);

    ulong ldn = ld(n);
    COMPLEX_REAL_FFT(w, ldn);

    skip_copy_back(w, f, n, d);
}
// -------------------------

