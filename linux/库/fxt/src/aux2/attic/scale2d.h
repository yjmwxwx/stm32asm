#if !defined HAVE_SCALE2D_H__
#define      HAVE_SCALE2D_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "aux1/scale.h"
#include "sort/minmax.h"

#include <cmath> // log()


template <typename Type>
void linear_scale(Type **f, ulong nr, ulong nc,
                  Type nmi, Type nma)   // new min, max
// linear scale so that
//   new_min==nmi,  ne_max==nma
{
    Type mi, ma;
    min_max((const Type **)f, nr, nc, &mi, &ma);
    for (ulong r=0; r<nr; ++r)  linear_scale(f[r], nc, mi, ma, nmi, nma);
}
// -------------------------

template <typename Type>
void linear_scale(Type **f, ulong nr, ulong nc,
                  Type mi, Type ma,     // old min, max
                  Type nmi, Type nma)   // new min, max
// linear scale so that
//   new_min==nmi,  ne_max==nma
// supply (or pretend) old min and max
{
    for (ulong r=0; r<nr; ++r)  linear_scale(f[r], nc, mi, ma, nmi, nma);
}
// -------------------------


template <typename Type>
void log_scale(Type **f, ulong nr, ulong nc,
               double xi, double xa, Type nma)
{
    Type mi, ma;
    min_max((const Type **)f, nr, nc, &mi, &ma);

    double ei = exp(xi), ea = exp(xa);
    linear_scale(f, nr, nc, mi, ma, ei, ea);

    for (ulong r=0; r<nr; ++r)
    {
        Type *p = f[r];
        ulong c = nc;
        while ( c-- )  p[c] = (Type)log((double)p[c]);
    }

    linear_scale(f, nr, nc, xi, xa, 0.0, nma);
}
// -------------------------


#endif // !defined HAVE_SCALE2D_H__
