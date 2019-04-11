// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "realfft/realfft.h"
#include "fxttypes.h"  // ulong

#include <cmath>


void
fft_spectrum(double *f, ulong ldn, int phasesq/*=0*/)
//
// Compute power spectrum using FFT
// ldn := base-2 logarithm of the array length
// phasesq != 0  requests computation of phases
// phase[i] is in f[n-i]  (i=1...n/2-1)
// phase[0] == 0,  phase[n/2] == 0
//
// output is not normalized
{
//    split_radix_real_complex_fft(f, ldn);  // sign of phases opposite wrt. fht_spectrum()
    fht_real_complex_fft(f, ldn);  // sign of phases same wrt. fht_spectrum()

    const ulong n=(1UL<<ldn);
    if ( phasesq )
    {
        for (ulong i=1, j=n-1;  i<j;  i++, j--)
        {
            double a = f[i],  b = f[j];
            f[i] = sqrt( a*a + b*b );
            f[j] = atan2(b, a);
        }
    }
    else
    {
        for (ulong i=1, j=n-1;  i<j;  i++, j--)
        {
            double a = f[i],  b = f[j];
            f[i] = sqrt( a*a + b*b );
//            f[j] = 0.0;
        }
    }

    f[0]  = fabs(f[0]);   // DC part

    const ulong nh = n/2;
    if ( nh!=0 )  f[nh] = fabs(f[nh]);  // nyquist freq
}
// -------------------------
