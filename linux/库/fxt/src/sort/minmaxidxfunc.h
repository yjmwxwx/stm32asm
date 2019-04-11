#if !defined HAVE_MINMAXIDXFUNC_H__
#define      HAVE_MINMAXIDXFUNC_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


template <typename Type>
Type idx_min(const Type *f, ulong n, const ulong *x,
             int (*cmp)(const Type &, const Type &))
// Return minimum (value) of array elements
//   {f[x[0]], f[x[1]], ..., f[x[n-1]]}
// with respect to comparison function cmp()
{
    Type v = f[x[0]];
    while ( n-- )  { if ( cmp(f[x[n]], v) < 0 )  v = f[x[n]]; }
    return  v;
}
// -------------------------

template <typename Type>
Type idx_max(const Type *f, ulong n, const ulong *x,
             int (*cmp)(const Type &, const Type &))
// Return maximum (value) of array elements
//   {f[x[0]], f[x[1]], ..., f[x[n-1]]}
// with respect to comparison function cmp()
{
    Type v = f[x[0]];
    while ( n-- )  { if ( cmp(f[x[n]], v) > 0 )  v = f[x[n]]; }
    return v;
}
// -------------------------

template  <typename Type>
bool is_idx_partitioned(const Type *f, ulong n, const ulong *x, ulong k,
                        int (*cmp)(const Type &, const Type &))
{
    ++k;
    Type lmax = idx_max(f,   k,   x,   cmp);
    Type rmin = idx_min(f,   n-k, x+k, cmp);
    return  ( cmp(lmax, rmin) <= 0 );
}
// -------------------------


#endif  // !defined HAVE_MINMAXIDXFUNC_H__
