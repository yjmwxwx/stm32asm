// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fft/fft-default.h"  // needs fft
#include "aux1/arith1.h"  // multiply_val()
#include "fxttypes.h"  // ulong

#include <cmath>  // sqrt()



static const int is = +1;  // sign of the (forward-) transform

static inline double inv_sqrt(ulong n)
{
    return 1.0/sqrt((double)(n));
}
// -------------------------

void
harmonic_wavelet(double *fr, double *fi, ulong ldn)
// Harmonic wavelet transform.
// Cf. David E. Newland: "Harmonic Wavelet Analysis",
//   Proceedings R. Soc. Lond. A,: Mathematical and Physical Sciences,
//   vol.443, no.1917, pp.203-225, (1993).
{
    ulong n = (1UL<<ldn);
    if ( n<4 )  return;

    fft(fr, fi, ldn, +is);
    multiply_val(fr, n, inv_sqrt(n));
    multiply_val(fi, n, inv_sqrt(n));

    for (ulong ldm=1; ldm<=ldn-1; ++ldm)
    {
        ulong m = (1UL<<ldm);  // m=2, 4, 8, ..., n/2

        fft(fr+m, fi+m, ldm, +is);
        multiply_val(fr+m, m, inv_sqrt(m));
        multiply_val(fi+m, m, inv_sqrt(m));
    }

    for (ulong k=n/2+1; k<n; ++k)  fi[k] = -fi[k];
}
// -------------------------


void
inverse_harmonic_wavelet(double *fr, double *fi, ulong ldn)
// Inverse of harmonic_wavelet()
{
    ulong n = (1UL<<ldn);
    if ( n<4 )  return;

    for (ulong k=n/2+1; k<n; ++k)  fi[k] = -fi[k];

    for (ulong ldm=ldn-1; ldm>=1; --ldm)
    {
        ulong m = (1UL<<ldm);  // m=n/2, n/4, ..., 4, 2
        fft(fr+m, fi+m, ldm, -is);
        multiply_val(fr+m, m, inv_sqrt(m));
        multiply_val(fi+m, m, inv_sqrt(m));
    }

    fft(fr, fi, ldn, -is);
    multiply_val(fr, n, inv_sqrt(n));
    multiply_val(fi, n, inv_sqrt(n));
}
// -------------------------

