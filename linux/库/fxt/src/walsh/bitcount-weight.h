#if !defined  HAVE_BITCOUNT_WEIGHT_H__
#define       HAVE_BITCOUNT_WEIGHT_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "bits/bitcount.h"

#include "fxttypes.h"

template <typename Type>
void bit_count_weight(Type *f, ulong ldn, Type w)
// Multiply f[i] by w**bitcount(i).
{
    ALLOCA(Type, pw, ldn+1);  // powers of w, tiny table
    pw[0] = (Type)1;
    for (ulong j=1; j<=ldn; ++j)  pw[j] = w * pw[j-1];
    const ulong n = (1UL<<ldn);
    for (ulong j=1; j<n; ++j)  f[j] *= pw[ bit_count(j) ];
}
// -------------------------

template <typename Type>
void rev_bit_count_weight(Type *f, ulong ldn, Type w)
// Multiply f[i] by w**bitcount(n-1-i).
{
    ALLOCA(Type, pw, ldn+1);  // powers of w, tiny table
    pw[0] = (Type)1;
    for (ulong j=1; j<=ldn; ++j)  pw[j] = w * pw[j-1];
    const ulong n = (1UL<<ldn);
    for (ulong j=0; j<n; ++j)  f[j] *= pw[ bit_count(n-1-j) ];
}
// -------------------------


#endif  // !defined HAVE_BITCOUNT_WEIGHT_H__
