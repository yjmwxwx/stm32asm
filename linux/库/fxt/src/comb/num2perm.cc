// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/fact2perm.h"
#include "comb/fact2num.h"

#include "fxtalloca.h"
#include "fxttypes.h"



void
num2perm_rfact(ulong x, ulong *f, ulong n)
// Create permutation number x according to (rising factorial) unrank.
{
    ALLOCA(ulong, fc, n-1);
    num2rfact(x, fc, n-1);
    rfact2perm(fc, n, f);
}
// -------------------------


ulong
perm2num_rfact(const ulong *f, ulong n)
// Inverse of num2perm_rfact()
{
    ALLOCA(ulong, fc, n-1);
    perm2rfact(f, n, fc);
    ulong x = rfact2num(fc, n-1);
    return x;
}
// -------------------------


void
num2perm_ffact(ulong x, ulong *f, ulong n)
// Create permutation number x according to (falling factorial) unrank.
{
    ALLOCA(ulong, fc, n-1);
    num2ffact(x, fc, n-1);
    ffact2perm(fc, n, f);
}
// -------------------------


ulong
perm2num_ffact(const ulong *f, ulong n)
// Inverse of num2perm_ffact()
{
    ALLOCA(ulong, fc, n-1);
    perm2ffact(f, n, fc);
    ulong x = ffact2num(fc, n-1);
    return x;
}
// -------------------------

//void
//num2perm(ulong x, ulong *f, ulong n)
//// Create permutation number x according to (factorial) unrank.
//{
//    num2perm_rfact(x, f, n);
//}
//// -------------------------
//
//
//ulong
//perm2num(const ulong *f, ulong n)
//// Inverse of num2perm()
//{
//    return perm2num_rfact(f, n);
//}
//// -------------------------


void
num2perm_swp(ulong x, ulong *f, ulong n)
// Create permutation number x according to (rising factorial) unrank by swaps.
{
    ALLOCA(ulong, fc, n-1);
    num2rfact(x, fc, n-1);
    rfact2perm_swp(fc, n, f);
}
// -------------------------


ulong
perm2num_swp(const ulong *f, ulong n)
// Inverse of num2perm_swp()
{
    ALLOCA(ulong, fc, n-1);
    perm2rfact_swp(f, n, fc);
    ulong x = rfact2num(fc, n-1);
    return x;
}
// -------------------------

ulong
permlex2num(const ulong *f, ulong n)
// The following function computes the rank of the given permutation
// corresponding to lexicographic order:
//   1, 2, ..., n-1, n   is index 0
//   1, 2, ..., n, n-1   is index 1
//   ...
//   n, n-1, ..., 2, 1   is index n! -1
//
// The actual values of the elements are immaterial, only the relative
// ordering of the values is used.
//
// f[] is the array of elements of length n.
//
// Note 1: complexity is n*n
// Note 2:  n!-1 must fit into a ulong ==> only good for _tiny_ n
//.
// Original code by Thad Smith III, Boulder, CO  8/31/91
{
    ulong idx = 0;
    for (ulong i=1; i<n; i++)
    {
        ulong x = f[i-1];
        for (ulong j=i; j<n; j++)  if ( x>f[j] )  ++idx;
        idx *= (n - i);
    }

    return idx;
}
// -------------------------
