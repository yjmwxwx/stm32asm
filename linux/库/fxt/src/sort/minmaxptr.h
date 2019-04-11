#if !defined HAVE_MINMAXPTR_H__
#define      HAVE_MINMAXPTR_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


template <typename Type>
Type ptr_min(/*const Type *f,*/ ulong n, Type const*const*x)
// Return minimum (value) of array elements
//   {*x[0], *x[1], ..., *x[n-1]}
{
    Type v = *x[0];
    while ( n-- )  { if ( *x[n]<v )  v = *x[n]; }
    return  v;
}
// -------------------------

template <typename Type>
Type ptr_max(/*const Type *f,*/ ulong n, Type const*const*x)
// Return maximum (value) of array elements
//   {*x[0], *x[1], ..., *x[n-1]}
{
    Type v = *x[0];
    while ( n-- )  { if ( *x[n]>v )  v = *x[n]; }
    return v;
}
// -------------------------

template  <typename Type>
bool is_ptr_partitioned(/*const Type *f,*/ ulong n, Type const*const*x, ulong k)
{
    ++k;
    Type lmax = ptr_max(k,   x);
    Type rmin = ptr_min(n-k, x+k);

    return  ( lmax<=rmin );
}
// -------------------------


#endif  // !defined HAVE_MINMAXPTR_H__
