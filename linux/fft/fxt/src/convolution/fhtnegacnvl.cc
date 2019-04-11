// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "convolution/weightedconvolution.h"
#include "fht/fht-default.h"
#include "fht/hartleyshift.h"  // hartley_shift_05()
#include "convolution/fhtmulsqr.h"  // fht_mul(), fht_sqr()
#include "restrict.h"
#include "fxttypes.h"  // ulong


void
fht_negacyclic_auto_convolution(double *f, ulong ldn, double v/*=0.0*/)
// Negacyclic (real) self-convolution using FHT.
// ldn := base-2 logarithm of the array length.
// v!=0.0 chooses alternative normalization.
{
    if ( ldn==0 ) { f[0] *= f[0];  return; }

    const ulong n = (1UL<<ldn);
    hartley_shift_05(f, n);
    fht(f, ldn);

    if ( v==0.0 )  v = 1.0/(double)n;
    v *= 0.5;

    for (ulong i=0, j=n-1;  i<j;  ++i, --j)  fht_sqr(f[i], f[j], v);

    fht(f, ldn);
    hartley_shift_05(f, n);
}
// -------------------------

void
fht_negacyclic_convolution(double * restrict f, double * restrict g, ulong ldn)
// Negacyclic (real) convolution using FHT.
// ldn := base-2 logarithm of the array length.
{
    if ( ldn==0 )  { g[0] *= f[0];  return; }

    const ulong n = (1UL<<ldn);
    hartley_shift_05(f, n);
    fht(f, ldn);
    hartley_shift_05(g, n);
    fht(g, ldn);

    const double v = 0.5/(double)n;
    for (ulong i=0, j=n-1;  i<j;  ++i, --j)  fht_mul(f[i], f[j], g[i], g[j], v);

    fht(g, ldn);
    hartley_shift_05(g, n);
}
// -------------------------
