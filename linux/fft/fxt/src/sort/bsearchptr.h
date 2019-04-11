#if !defined HAVE_BSEARCHPTR_H__
#define      HAVE_BSEARCHPTR_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

template <typename Type>
ulong ptr_bsearch(/*const Type *f,*/ ulong n, Type const*const*x, const Type v)
// Return index of ptr i to first element in f[] that is == v
// i.e. *x[i] == v, with i minimal.
// Return n if there is no such element
// x[] must be (ptr-)sorted in ascending order:
// *x[i] <= *x[i+i]
// Must have  n!=0
{
    ulong nlo=0, nhi=n-1;
    while ( nlo != nhi )
    {
        ulong t = (nhi+nlo)/2;

        if ( *x[t] < v )  nlo = t + 1;
        else              nhi = t;
    }

    if ( *x[nhi]==v )  return nhi;
    else               return n;
}
// -------------------------


template <typename Type>
ulong ptr_bsearch_geq(/*const Type *f,*/ ulong n, Type const*const*x, const Type v)
// Return index of ptr of first element in f[] that is >= v
// i.e. *x[i] >= v, with i minimal.
// Return n if there is no such element
// x[] must be (ptr-)sorted in ascending order:
// *x[i] <= *x[i+i]
// Must have  n!=0
{
    ulong nlo=0, nhi=n-1;
    while ( nlo != nhi )
    {
        ulong t = (nhi+nlo)/2;

        if ( x[t] < v )  nlo = t + 1;
        else             nhi = t;
    }

    if ( *x[nhi]>=v )  return nhi;
    else               return n;
}
// -------------------------


#endif  // !defined HAVE_BSEARCHPTR_H__
