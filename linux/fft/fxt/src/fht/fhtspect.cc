// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fht/fht-default.h"
#include "fxttypes.h"  // ulong

#include <cmath>


void
fht_spectrum(double *f, ulong ldn, int phasesq/*=0*/)
//
// Compute power spectrum using FHT
// ldn := base-2 logarithm of the array length
//
// phasesq != 0  requests computation of phases
// phase[i] is in f[n-i]  (i=1...n/2-1)
// phase[0] == 0,  phase[n/2] == 0
//
// output is not normalized
{
    fht(f, ldn);

    const ulong n  = (1UL<<ldn);

    if ( phasesq )
    {
        for (ulong i=1, j=n-1;  i<j;  i++, j--)
        {
            double a = f[i] + f[j];
            double b = f[i] - f[j];
            f[i] = sqrt(a*a+b*b)*0.5;
            f[j] = atan2(b, a);
        }
    }
    else
    {
        for (ulong i=1, j=n-1;  i<j;  i++, j--)
        {
            double a = f[i] + f[j];
            double b = f[i] - f[j];
            f[i] = sqrt(a*a+b*b)*0.5;
            f[j] = 0.0;
        }
    }

    f[0]  = fabs(f[0]);   // DC part

    const ulong nh = n/2;
    if ( nh!=0 )  f[nh] = fabs(f[nh]);  // nyquist freq
}
// -------------------------
