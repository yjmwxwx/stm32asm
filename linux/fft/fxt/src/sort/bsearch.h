#if !defined HAVE_BSEARCH_H__
#define      HAVE_BSEARCH_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


template <typename Type>
ulong bsearch(const Type *f, ulong n, const Type v)
// Return index of first element in f[] that equals v
// Return n if there is no such element.
// f[] must be sorted in ascending order.
// Must have  n!=0
{
    ulong nlo=0, nhi=n-1;
    while ( nlo != nhi )
    {
        ulong t = (nhi+nlo)/2;

        if ( f[t] < v )  nlo = t + 1;
        else             nhi = t;
    }

    if ( f[nhi]==v )  return nhi;
    else              return n;
}
// -------------------------


template <typename Type>
ulong bsearch_geq(const Type *f, ulong n, const Type v)
// Return index of first element in f[] that is >= v
// Return n if there is no such element.
// f[] must be sorted in ascending order.
// Must have  n!=0
{
    ulong nlo=0, nhi=n-1;
    while ( nlo != nhi )
    {
        ulong t = (nhi+nlo)/2;

        if ( f[t] < v )  nlo = t + 1;
        else             nhi = t;
    }

    if ( f[nhi]>=v )  return nhi;
    else              return n;
}
// -------------------------


template <typename Type>
ulong bsearch_leq(const Type *f, ulong n, const Type v)
// Return index of first element in f[] that is <= v
// Return n (word with all bits set) if there is no such element.
// f[] must be sorted in ascending order.
// Must have  n!=0
{
    ulong nlo=0, nhi=n-1;
    while ( nlo != nhi )
    {
        ulong t = (nhi+nlo)/2;

        if ( f[t] > v )  nlo = t + 1;
        else             nhi = t;
    }

    if ( f[nhi]<=v )  return nhi;
    else              return n;
}
// -------------------------


#endif  // !defined HAVE_BSEARCH_H__
