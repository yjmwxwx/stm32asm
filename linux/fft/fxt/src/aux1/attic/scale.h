#if !defined HAVE_SCALE_H__
#define      HAVE_SCALE_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "sort/minmax.h"

#include <cmath>  // log()


template <typename Type>
void linear_scale(Type *f, ulong n,
                  Type mi, Type ma,     // old min, max
                  Type nmi, Type nma)   // new min, max
// linear scale so that
//   new_min==nmi,  ne_max==nma
// supply (or pretend) old min and max
{
    const double v = 0.0 + (nma-nmi)/(ma-mi);
    const double d = 0.0 + nmi - v*mi;
    while ( n-- )
    {
        f[n] = v*f[n] + d;  // == nmi + v * (f[n]-mi);
    }
}
// -------------------------


template <typename Type>
void linear_scale(Type *f, ulong n,
                  Type nmi, Type nma)   // new min, max
// linear scale so that
//   new_min==nmi,  ne_max==nma
{
    Type mi,ma;
    min_max(f, n, &mi, &ma);
    linear_scale(f, n, mi, ma, nmi, nma);
}
// -------------------------


template <typename Type>
void log_scale(Type *f, ulong n,
               double xi, double xa,
               Type nma)
{
    Type mi, ma;
    min_max(f, n, &mi, &ma);

    double ei = exp(xi), ea = exp(xa);
    linear_scale(f, n, mi, ma, ei, ea);

    ulong t = n;
    while ( t-- )  f[t] = (Type)log( (double)f[t] );

    linear_scale(f, n, xi, xa, 0.0, nma);
}
// -------------------------


#endif // !defined HAVE_SCALE_H__
