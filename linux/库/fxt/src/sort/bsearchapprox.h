#if !defined  HAVE_BSEARCHAPPROX_H__
#define       HAVE_BSEARCHAPPROX_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

#include "sort/bsearch.h"
#include "sort/bsearchfunc.h"


template <typename Type>
ulong bsearch_approx(const Type *f, ulong n, const Type v, Type da)
// Return index of first element x in f[] for which  |(x-v)| <= da
// Return n if there is no such element.
// f[] must be sorted in ascending order.
// da must be positive.
//
// Makes sense only with inexact types (float or double).
// Must have  n!=0
{
    ulong k = bsearch_geq(f, n, v-da);
    if ( k<n )  k = bsearch_leq(f+k, n-k, v+da);
    return k;
}
// -------------------------


template <typename Type>
ulong bsearch_approx(const Type *f, ulong n, const Type v, Type da,
                     int (*cmp)(const Type &, const Type &))
//
// Return index of first element x in f[] for which  |(x-v)| <= da
//    with respect to comparison function cmp().
// Return n if there is no such element.
// f[] must be sorted in ascending order.
// da must be positive.
//
// Makes sense only with inexact types (float or double).
// Must have  n!=0
{
    ulong k = bsearch_geq(f, n, v-da, cmp);
    if ( k<n )  k = bsearch_leq(f+k, n-k, v+da, cmp);
    return k;
}
// -------------------------


#endif  // !defined HAVE_BSEARCHAPPROX_H__
