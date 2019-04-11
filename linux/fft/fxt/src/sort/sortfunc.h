#if !defined HAVE_SORTFUNC_H__
#define      HAVE_SORTFUNC_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

#include "sort/minmaxmed23func.h"

#include "aux0/swap.h"


template  <typename Type>
bool is_sorted(const Type *f, ulong n, int (*cmp)(const Type &, const Type &))
// Return whether the sequence f[0], f[1], ..., f[n-1]
// is sorted in ascending order with respect to comparison function cmp().
{
    for (ulong k=1; k<n; ++k)  if ( cmp(f[k-1], f[k]) > 0 )  return false;
    return  true;
}
// -------------------------


template <typename Type>
void selection_sort(Type *f, ulong n, int (*cmp)(const Type &, const Type &))
// Sort f[] (ascending order) with respect to comparison function cmp().
// Algorithm is O(n*n), use for short arrays only.
{
    for (ulong i=0; i<n; ++i)
    {
        Type v = f[i];
        ulong m = i;  // position of minimum
        ulong j = n;
        while ( --j > i )  // search (index of) minimum
        {
            if ( cmp(f[j], v) < 0 )
            {
                m = j;
                v = f[m];
            }
        }

        swap2(f[i], f[m]);
    }
}
// -------------------------


template <typename Type>
ulong partition(Type *f, ulong n, int (*cmp)(const Type &, const Type &))
// rearrange array, so that for some index p
// max(f[0] ... f[p]) <= min(f[p+1] ... f[n-1]).
// min(), max() taken with respect to comparison function cmp().
{
    // Avoid worst case with already sorted input:
    const Type v = median3(f[0], f[n/2], f[n-1], cmp);

    ulong i = 0UL - 1;
    ulong j = n;
    while ( 1 )
    {
        do  ++i;
        while ( cmp(f[i], v) < 0 );

        do  --j;
        while ( cmp(f[j], v) > 0 );

        if ( i < j )  swap2(f[i], f[j]);
        else          return j;
    }
}
// -------------------------


template <typename Type>
void quick_sort(Type *f, ulong n, int (*cmp)(const Type &, const Type &))
// Sort f[] (ascending order)
// with respect to comparison function cmp().
{
 start:
    if ( n<8 )  // parameter: threshold for nonrecursive algorithm
    {
        selection_sort(f, n, cmp);
        return;
    }

    ulong p = partition(f, n, cmp);
    ulong ln = p + 1;
    ulong rn = n - ln;

    if ( ln > rn )  // recursion for shorter sub-array
    {
        quick_sort(f+ln, rn, cmp);  // f[ln] ... f[n-1]   right
        n = ln;
    }
    else
    {
        quick_sort(f, ln, cmp);  // f[0]  ... f[ln-1]  left
        n = rn;
        f += ln;
    }

    goto start;
}
// -------------------------


#endif  // !defined HAVE_SORTFUNC_H__
