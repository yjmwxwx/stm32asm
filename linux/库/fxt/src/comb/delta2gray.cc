// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "bits/bitlow.h"
#include "fxttypes.h"



void
delta2gray(const unsigned char *d, ulong ldn, ulong *g, ulong g0/*=0*/)
// Fill into g[0..N-1] (N=2**ldn) the Gray path
//  corresponding to the delta sequence d[0..N-2].
{
    g[0] = g0;
    ulong n = 1UL << ldn;
    for (ulong k=0; k<n-1; ++k)  g[k+1] = g[k] ^ (1UL << d[k]);
}
// -------------------------

void
gray2delta(ulong ldn, const ulong *g, unsigned char *d)
// Inverse of delta2gray().
{
    ulong n = 1UL << ldn;
    for (ulong k=0; k<n-1; ++k)  d[k] = (unsigned char)lowest_one_idx( g[k+1] ^ g[k] );
}
// -------------------------
