#if !defined HAVE_ZIPREV_H__
#define      HAVE_ZIPREV_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "perm/reverse.h"
#include "perm/revbinpermute.h"
#include "restrict.h"

template <typename Type>
void zip_rev(const Type * restrict x, Type * restrict y, ulong n)
// reordering needed for fht based inverse dct
// n must be even
{
    const ulong nh = n/2;
//    for (ulong k=0, k2=0;  k<nh;  k++, k2+=2)
//    {
//        y[k2] = x[k];
//        y[n-1-k2] = x[nh+k];
//    }
    // =^=
    for (ulong k=0, k2=0;     k<nh;  k++, k2+=2)  y[k2] = x[k];
    for (ulong k=nh, k2=n-1;  k<n;   k++, k2-=2)  y[k2] = x[k];
}
// -------------------------


template <typename Type>
void zip_rev(Type *x, ulong n)
// in-place version
// n must be a power of 2
{
    const ulong nh = n/2;
    reverse(x+nh, nh);
    revbin_permute(x, nh); revbin_permute(x+nh, nh);
    revbin_permute(x, n);
}
// -------------------------


template <typename Type>
void unzip_rev(const Type * restrict x, Type * restrict y, ulong n)
// reordering needed for fht based dct
// n must be even
{
    const ulong nh = n/2;
//    for (ulong k=0, k2=0;  k<nh;  k++, k2+=2)
//    {
//        y[k] = x[k2];
//        y[nh+k] = x[n-1-k2];
//    }
    // =^=
    for (ulong k=0, k2=0;     k<nh;  k++, k2+=2)  y[k] = x[k2];
    for (ulong k=nh, k2=n-1;  k<n;   k++, k2-=2)  y[k] = x[k2];
}
// -------------------------


template <typename Type>
void unzip_rev(Type *x, ulong n)
// in-place version
// n must be a power of 2
{
    const ulong nh = n/2;
    revbin_permute(x, n);
    revbin_permute(x, nh); revbin_permute(x+nh, nh);
    reverse(x+nh, nh);
}
// -------------------------



#endif  // !defined HAVE_ZIPREV_H__
