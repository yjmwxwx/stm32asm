#if !defined HAVE_SORTIDXFUNC_H__
#define      HAVE_SORTIDXFUNC_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

#include "sort/minmaxmed23func.h"

#include "aux0/swap.h"


template  <typename Type>
bool is_idx_sorted(const Type *f, ulong n, const ulong *x,
                   int (*cmp)(const Type &, const Type &))
// Return whether the sequence f[x[0]], f[x[1]], ... f[x[n-1]] is ascending
// with respect to comparison function cmp().
{
    for (ulong k=1; k<n; ++k)  if ( cmp(f[x[k-1]], f[x[k]]) > 0 )  return false;
    return  true;
}
// -------------------------


template <typename Type>
void idx_selection_sort(const Type *f, ulong n, ulong *x,
                        int (*cmp)(const Type &, const Type &))
// Sort x[] so that the sequence f[x[0]], f[x[1]], ... f[x[n-1]]
// is ascending with respect to comparison function cmp().
// Algorithm is O(n*n), use for short arrays only.
{
    for (ulong i=0; i<n; ++i)
    {
        Type v = f[x[i]];
        ulong m = i;  // position-ptr of minimum
        ulong j = n;
        while ( --j > i )  // search (index of) minimum
        {
//            if ( f[x[j]] < v )
            if ( cmp(f[x[j]], v) < 0 )
            {
                m = j;
                v = f[x[m]];
            }
        }

        swap2(x[i], x[m]);
    }
}
// -------------------------


template <typename Type>
ulong idx_partition(const Type *f, ulong n, ulong *x,
                    int (*cmp)(const Type &, const Type &))
// Rearrange index array, so that for some index p
// max(f[x[0]] ... f[x[p]]) <= min(f[x[p+1]] ... f[x[n-1]])
// with respect to comparison function cmp().
{
    // Avoid worst case with already sorted input:
    const Type v = median3(f[x[0]], f[x[n/2]], f[x[n-1]], cmp);

    ulong i = -1UL;
    ulong j = n;
    while ( 1 )
    {
        do  ++i;
//        while ( f[x[i]] < v );
        while ( cmp(f[x[i]], v) < 0 );

        do  --j;
//        while ( f[x[i]] > v );
        while ( cmp(f[x[j]], v) > 0 );

        if ( i < j )  swap2(x[i], x[j]);
        else          return j;
    }
}
// -------------------------


template <typename Type>
void idx_quick_sort(const Type *f, ulong n, ulong *x,
                    int (*cmp)(const Type &, const Type &))
// Sort x[] so that the sequence f[x[0]], f[x[1]], ... f[x[n-1]]
// is ascending with respect to comparison function cmp().
{
 start:
    if ( n<8 )  // parameter: threshold for nonrecursive algorithm
    {
        idx_selection_sort(f, n, x, cmp);
        return;
    }

    ulong p = idx_partition(f, n, x, cmp);
    ulong ln = p + 1;
    ulong rn = n - ln;

    if ( ln > rn )  // recursion for shorter sub-array
    {
        idx_quick_sort(f, rn, x+ln, cmp);  // f[x[ln]] ... f[x[n-1]]  right
        n = ln;
    }
    else
    {
        idx_quick_sort(f, ln, x, cmp);  // f[x[0]]  ... f[x[ln-1]]  left
        n = rn;
        x += ln;
    }

    goto start;
}
// -------------------------


#endif  // !defined HAVE_SORTIDXFUNC_H__
