#if !defined  HAVE_MINMAXFUNC_H__
#define       HAVE_MINMAXFUNC_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

template <typename Type>
Type min(const Type *f, ulong n, int (*cmp)(const Type &, const Type &))
// Return minimum (value) of array elements
// wrt. to comparison function
{
    Type v = f[0];
    while ( n-- )  { if ( cmp(f[n], v) < 0 )  v = f[n]; }
    return  v;
}
// -------------------------

template <typename Type>
Type max(const Type *f, ulong n, int (*cmp)(const Type &, const Type &))
// Return maximum (value) of array elements
// wrt. to comparison function
{
    Type v = f[0];
    while ( n-- )  { if ( cmp(f[n], v) > 0 )  v = f[n]; }
    return v;
}
// -------------------------

template  <typename Type>
bool is_partitioned(const Type *f, ulong n, ulong k, int (*cmp)(const Type &, const Type &))
{
    ++k;
    Type lmax = max(f,   k,   cmp);
    Type rmin = min(f+k, n-k, cmp);
    return  ( cmp(lmax, rmin) <= 0 );
}
// -------------------------


#endif  // !defined HAVE_MINMAXFUNC_H__
