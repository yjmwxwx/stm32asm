#if !defined  HAVE_MINMAXIDX_H__
#define       HAVE_MINMAXIDX_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


template <typename Type>
Type idx_min(const Type *f, ulong n, const ulong *x)
// Return minimum (value) of array elements
//   {f[x[0]], f[x[1]], ..., f[x[n-1]]}
{
    Type v = f[x[0]];
    while ( n-- )  { if ( f[x[n]]<v )  v = f[x[n]]; }
    return  v;
}
// -------------------------

template <typename Type>
Type idx_max(const Type *f, ulong n, const ulong *x)
// Return maximum (value) of array elements
//   {f[x[0]], f[x[1]], ..., f[x[n-1]]}
{
    Type v = f[x[0]];
    while ( n-- )  { if ( f[x[n]]>v )  v = f[x[n]]; }
    return v;
}
// -------------------------

template  <typename Type>
bool is_idx_partitioned(const Type *f, ulong n, const ulong *x, ulong k)
{
    ++k;
    Type lmax = idx_max(f,   k,   x);
    Type rmin = idx_min(f,   n-k, x+k);
    return  ( lmax<=rmin );
}
// -------------------------


#endif  // !defined HAVE_MINMAXIDX_H__
