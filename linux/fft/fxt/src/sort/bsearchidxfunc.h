#if !defined HAVE_BSEARCHIDXFUNC_H__
#define      HAVE_BSEARCHIDXFUNC_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

template <typename Type>
ulong idx_bsearch(const Type *f, ulong n, const ulong *x, const Type v,
                  int (*cmp)(const Type &, const Type &))
// Return index-ptr i of first element in f[] that is == v
// i.e. f[x[i]] == v, with i minimal.
// Return n if there is no such element
// f[x[]] must be (index-)sorted in ascending order:
// f[x[i]] <= f[x[i+i]]
// Must have  n!=0
{
    ulong nlo=0, nhi=n-1;
    while ( nlo != nhi )
    {
        ulong t = (nhi+nlo)/2;

//        if ( f[x[t]] < v )  nlo = t + 1;
        if ( cmp(f[x[t]], v) < 0 )  nlo = t + 1;
        else                        nhi = t;
    }

//    if ( f[x[nhi]]==v )  return nhi;
    if ( cmp(f[x[nhi]], v)==0 )  return nhi;
    else                         return n;
}
// -------------------------


template <typename Type>
ulong idx_bsearch_geq(const Type *f, ulong n, const ulong *x, const Type v,
                      int (*cmp)(const Type &, const Type &))
// Return index-ptr of first element in f[] that is >= v
// i.e. f[x[i]] >= v, with i minimal.
// Return n if there is no such element
// f[x[]] must be (index-)sorted in ascending order:
// f[x[i]] <= f[x[i+i]]
// Must have  n!=0
{
    ulong nlo=0, nhi=n-1;
    while ( nlo != nhi )
    {
        ulong t = (nhi+nlo)/2;
//        if ( f[x[t]] < v )  nlo = t + 1;
        if ( cmp(f[x[t]], v)<0 )  nlo = t + 1;
        else                      nhi = t;
    }

//    if ( f[x[nhi]]>=v )  return nhi;
    if ( cmp(f[x[nhi]], v)>=0 )  return nhi;
    else                         return n;
}
// -------------------------


#endif  // !defined HAVE_BSEARCHIDXFUNC_H__
