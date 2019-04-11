#if !defined HAVE_SORTIDX_H__
#define      HAVE_SORTIDX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

#include "sort/minmaxmed23.h"

#include "aux0/swap.h"


template  <typename Type>
bool is_idx_sorted(const Type *f, ulong n, const ulong *x)
// Return whether the sequence f[x[0]], f[x[1]], ... f[x[n-1]] ascending.
{
    for (ulong k=1; k<n; ++k)  if ( f[x[k-1]] > f[x[k]] )  return false;
    return  true;
}
// -------------------------


template <typename Type>
void idx_selection_sort(const Type *f, ulong n, ulong *x)
// Sort x[] so that the sequence f[x[0]], f[x[1]], ... f[x[n-1]] ascending.
// Algorithm is O(n*n), use for short arrays only.
{
    for (ulong i=0; i<n; ++i)
    {
        Type v = f[x[i]];
        ulong m = i;  // position-ptr of minimum
        ulong j = n;
        while ( --j > i )  // search (index of) minimum
        {
            if ( f[x[j]] < v )
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
ulong idx_partition(const Type *f, ulong n, ulong *x)
// rearrange index array, so that for some index p
// max(f[x[0]] ... f[x[p]]) <= min(f[x[p+1]] ... f[x[n-1]])
{
    // Avoid worst case with already sorted input:
    const Type v = median3(f[x[0]], f[x[n/2]], f[x[n-1]]);

    ulong i = 0UL - 1;
    ulong j = n;
    while ( 1 )
    {
        do  ++i;
        while ( f[x[i]] < v );

        do  --j;
        while ( f[x[j]] > v );

        if ( i < j )  swap2(x[i], x[j]);
        else          return j;
    }
}
// -------------------------


template <typename Type>
void idx_quick_sort(const Type *f, ulong n, ulong *x)
// Sort x[] so that the sequence f[x[0]], f[x[1]], ... f[x[n-1]] is ascending.
{
 start:
    if ( n<8 )  // parameter: threshold for nonrecursive algorithm
    {
        idx_selection_sort(f, n, x);
        return;
    }

    ulong p = idx_partition(f, n, x);
    ulong ln = p + 1;
    ulong rn = n - ln;

    if ( ln > rn )  // recursion for shorter sub-array
    {
        idx_quick_sort(f, rn, x+ln);  // f[x[ln]] ... f[x[n-1]]  right
        n = ln;
    }
    else
    {
        idx_quick_sort(f, ln, x);  // f[x[0]]  ... f[x[ln-1]]  left

        n = rn;
        x += ln;
    }

    goto start;
}
// -------------------------


#endif  // !defined HAVE_SORTIDX_H__
