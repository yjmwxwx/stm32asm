// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fht/fht-default.h"

#include "bits/bit2pow.h"  // ld()
#include "aux1/copy.h"
#include "fxttypes.h"  // ulong



void
skip_fht(double *f, ulong n, ulong d, double *w)
// Compute fast Hartley transform (FHT) of the n elements
//    [0], [d], [2d], [3d],..., [(n-1)*d]
{
    skip_copy(f, w, n, d);
    ulong ldn = ld(n);
    fht(w, ldn);
    skip_copy_back(w, f, n, d);
}
// -------------------------


void
skip_fht0(double *f, ulong n, ulong d, double *w)
// Compute fast Hartley transform (FHT) of the n elements
//   [0], [d], [2d], [3d],..., [(n-1)*d]
// where the second have are zero.
{
    ulong nh = (n>>1);
    skip_copy(f, w, nh, d);
    null(f+nh, nh);
    ulong ldn = ld(n);
    fht0(w, ldn);
    skip_copy_back(w, f, n, d);
}
// -------------------------
