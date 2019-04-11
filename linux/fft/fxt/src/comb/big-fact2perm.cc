// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "ds/left-right-array.h"

#include "fxttypes.h"


void
perm2ffact(const ulong *x, ulong n, ulong *fc, left_right_array &LR)
// Convert permutation in x[0,...,n-1] into
//   the (n-1) digit factorial representation in fc[0,...,n-2].
// We have: fc[0]<n, fc[1]<n-1, ..., fc[n-2]<2 (falling radices)
// This is the so-called "Lehmer code" of a permutation.
{
    LR.set_all();
    for (ulong k=0; k<n-1; ++k)
    {
        // i :=  number of Set positions Left of x[k], Excluding x[k].
        ulong i = LR.num_SLE( x[k] );
        LR.get_set_idx_chg( i );
        fc[k] = i;
    }
}
// -------------------------

void
ffact2perm(const ulong *fc, ulong n, ulong *x, left_right_array &LR)
// Inverse of perm2ffact():
// Convert the (n-1) digit factorial representation in fc[0,...,n-2].
// into permutation in x[0,...,n-1]
// Must have: fc[0]<n, fc[1]<n-1, ..., fc[n-2]<2 (falling radices)
{
    LR.free_all();
    for (ulong k=0; k<n-1; ++k)
    {
        ulong i = LR.get_free_idx_chg( fc[k] );
        x[k] = i;
    }
    ulong i = LR.get_free_idx_chg( 0 );
    x[n-1] = i;
}
// -------------------------

void
ffact2invperm(const ulong *fc, ulong n, ulong *x, left_right_array &LR)
// Convert the (n-1) digit factorial representation in fc[0,...,n-2]
// into permutation in x[0,...,n-1] such that
// the permutation is the inverse of the one computed via ffact2perm().
// Must have: fc[0]<n, fc[1]<n-1, ..., fc[n-2]<2 (falling radices)
{
    LR.free_all();
    for (ulong k=0; k<n-1; ++k)
    {
        ulong i = LR.get_free_idx_chg( fc[k] );
        x[i] = k;
    }
    ulong i = LR.get_free_idx_chg( 0 );
    x[i] = n-1;
}
// -------------------------


void
perm2rfact(const ulong *x, ulong n, ulong *fc, left_right_array &LR)
// Convert permutation in x[0,...,n-1] into
//   the (n-1) digit factorial representation in fc[0,...,n-2].
// We have: fc[0]<2, fc[1]<3, ..., fc[n-2]<n (rising radices)
{
    LR.set_all();
    for (ulong k=0, r=n-1;  k<n-1;  ++k, --r)  //  r == n-1-k;
    {
        // i :=  number of Set positions Left of x[r], Excluding x[r].
        ulong i = LR.num_SLE( x[r] );
        LR.get_set_idx_chg( i );
        fc[r-1] = r - i;
    }
}
// -------------------------

void
rfact2perm(const ulong *fc, ulong n, ulong *x, left_right_array &LR)
// Inverse of perm2rfact():
// Convert the (n-1) digit factorial representation in fc[0,...,n-2].
//  into permutation in x[0,...,n-1]
// Must have: fc[0]<2, fc[1]<3, ..., fc[n-2]<n (rising radices)
{
    LR.free_all();
    for (ulong k=0; k<n-1; ++k)
    {
        ulong i = LR.get_free_idx_chg( fc[n-2-k] );
        x[n-1-k] = n-1-i;
    }
    ulong i = LR.get_free_idx_chg( 0 );
    x[0] = n-1-i;
}
// -------------------------


void
rfact2invperm(const ulong *fc, ulong n, ulong *x, left_right_array &LR)
// Convert the (n-1) digit factorial representation in fc[0,...,n-2].
//  into permutation in x[0,...,n-1] such that
// the permutation is the inverse of the one computed via rfact2perm().
// Must have: fc[0]<2, fc[1]<3, ..., fc[n-2]<n (rising radices)
{
    LR.free_all();
    for (ulong k=0; k<n-1; ++k)
    {
        ulong i = LR.get_free_idx_chg( fc[n-2-k] );
        x[n-1-i] = n-1-k;
    }
    ulong i = LR.get_free_idx_chg( 0 );
    x[n-1-i] = 0;
}
// -------------------------

