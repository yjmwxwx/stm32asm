// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "mod/mod.h"
#include "ntt/ntt.h"

#include "fxttypes.h"
#include "fxtalloca.h"


#include "aux1/copy.h"


#define  SLOW_MOD_CONVOLUTION_VERSION  0  // 1 or 2

#if  ( SLOW_MOD_CONVOLUTION_VERSION==1 )

void
slow_mod_convolution(mod *f, mod *g, ulong n)  // version 1
// (cyclic) convolution:  g[] :=  f[] (*) g[]
// n := array length
//
// (use zero padded data for linear convolution)
//
{
    ALLOCA(mod, r, n);
    for (ulong tau=0; tau<n; ++tau)
    {
        mod t = mod::zero;
        for (ulong k=0; k<n; ++k)
        {
            ulong k2;

            if ( tau>=k )  k2 = tau - k;
            else           k2 = n + tau - k;

            t += (f[k2]*g[k]);
        }

        r[tau] = t;
    }
    acopy(r, g, n);
}
// -------------------------


#else  // ( SLOW_MOD_CONVOLUTION_VERSION==1 )


void
slow_mod_convolution(mod *f, mod *g, ulong n)  // version 2
// (cyclic) convolution:  g[] :=  f[] (*) g[]
// n := array length
//
// (use zero padded data for linear convolution)
//
{
    long ns = (long)n;
    ALLOCA(mod, r, n);
    for (long tau=0; tau<ns; ++tau)
    {
        mod s = mod::zero;
        for (long k=0; k<ns; ++k)
        {
             long k2 = tau - k;

             if ( k2<0 )  k2 += ns;

             s += (f[k]*g[k2]);
        }
        r[tau] = s;
    }
    acopy(r, g, n);
}
// -------------------------


#endif  // ( SLOW_MOD_CONVOLUTION_VERSION==1 )
