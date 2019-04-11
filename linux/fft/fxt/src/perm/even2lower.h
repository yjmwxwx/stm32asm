#if !defined  HAVE_EVEN2LOWER_H__
#define       HAVE_EVEN2LOWER_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "aux0/swap.h"
#include "fxttypes.h"


template <typename Type>
inline void even2lower(Type *f, ulong n)
// With the input (comma at middle of array):
//   [e0 o0 e1 o1 e2 o3 ..., E0 O0 E1 O1 E2 O2 ... ]
// obtain:
//   [e0 E0 e1 E1 e2 E3 ..., o0 O0 o1 O1 o2 O2 ... ]
// Self-inverse.
// n must be even.
{
    ulong nh = n/2;
    for (ulong k=1; k<nh; k+=2)  swap2(f[k], f[nh-1+k]);
}
// -------------------------


template <typename Type>
inline void even2lower_rev(Type *f, ulong n)
// Similar to even2lower() but the order of the swapped elements is reversed.
// Self-inverse.
// n must be even.
{
    ulong nh = n/2;
    for (ulong k=1, j=n-2;  k<nh;  k+=2, j-=2)  swap2(f[k], f[j]);
}
// -------------------------

template <typename Type>
inline void odd2lower(Type *f, ulong n)
// With the input (comma at middle of array):
//   [e0 o0 e1 o1 e2 o3 ..., E0 O0 E1 O1 E2 O2 ... ]
// obtain:
//   [O0 o0 O1 o1 O2 o3 ..., E0 e0 E1 e1 E2 e2 ... ]
// Self-inverse.
// n must be even.
{
    ulong nh = n/2;
    for (ulong k=0; k<nh; k+=2)  swap2(f[k], f[nh+1+k]);
}
// -------------------------


#endif  // !defined HAVE_EVEN2LOWER_H__
