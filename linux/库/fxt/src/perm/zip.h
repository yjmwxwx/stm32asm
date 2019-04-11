#if !defined HAVE_ZIP_H__
#define      HAVE_ZIP_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "perm/revbinpermute.h"
#include "bits/bitrotate.h"
#include "restrict.h"

// perm/zip.cc:
void zip(double *f, ulong n);
void unzip(double *f, ulong n);


template <typename Type>
void zip(const Type * restrict f, Type * restrict g, ulong n)
// zip-permutation:
//   lower half --> even indices
//   upper half --> odd indices
// n must be even.
//.
// Same as transposing the array as 2 x n/2 - matrix.
{
    ulong nh = n/2;
    for (ulong k=0,  k2=0;  k<nh;  ++k, k2+=2)  g[k2] = f[k];
    for (ulong k=nh, k2=1;  k<n;   ++k, k2+=2)  g[k2] = f[k];
}
// -------------------------


template <typename Type>
void zip(Type *f, ulong n)
// zip-permutation, in-place version.
// n must be a power of 2.
//.
// Useful to combine real/imag part into a complex array.
{
    ulong nh = n/2;
    revbin_permute(f, nh);  revbin_permute(f+nh, nh);
    revbin_permute(f, n);
}
// -------------------------


template <typename Type>
void unzip(const Type * restrict f, Type * restrict g, ulong n)
// unzip-permutation:
//   even indices --> lower half
//    odd indices --> upper half
// n must be even.
// Inverse of zip().
//.
// Same as transposing the array as n/2 x 2 - matrix
{
    ulong nh = n/2;
    for (ulong k=0,  k2=0;   k<nh;  ++k, k2+=2)  g[k] = f[k2];
    for (ulong k=nh, k2=1;   k<n;   ++k, k2+=2)  g[k] = f[k2];
}
// -------------------------


template <typename Type>
void unzip(Type *f, ulong n)
// unzip-permutation, in-place version.
// n must be a power of 2
//.
// Useful to separate a complex array into real/imag part
{
    ulong nh = n/2;
    revbin_permute(f, n);
    revbin_permute(f, nh);  revbin_permute(f+nh, nh);
}
// -------------------------


#endif  // !defined HAVE_ZIP_H__
