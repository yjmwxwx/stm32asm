#if !defined HAVE_SORTPTR_H__
#define      HAVE_SORTPTR_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

#include "sort/minmaxmed23.h"

#include "aux0/swap.h"

// pointer sort routines


template  <typename Type>
bool is_ptr_sorted(/*const Type *f,*/ ulong n, Type const*const*x)
// Return whether the sequence *x[0], *x[1], ..., *x[n-1] is ascending.
{
    for (ulong k=1; k<n; ++k)  if ( *x[k-1] > *x[k] )  return false;
    return  true;
}
// -------------------------


template <typename Type>
void ptr_selection_sort(/*const Type *f,*/ ulong n, const Type **x)
// Sort x[] so that the sequence *x[0], *x[1], ..., *x[n-1] is ascending.
// Algorithm is O(n*n), use for short arrays only.
{
    for (ulong i=0; i<n; ++i)
    {
        Type v = *x[i];
        ulong m = i;  // position-ptr of minimum
        ulong j = n;
        while ( --j > i )  // search (index of) minimum
        {
            if ( *x[j] < v )
            {
                m = j;
                v = *x[m];
            }
        }
        swap2(x[i], x[m]);
    }
}
// -------------------------


template <typename Type>
ulong ptr_partition(/*const Type *f,*/ ulong n, const Type **x)
// rearrange index array, so that for some index p
// max(f[x[0]], ..., f[x[p]]) <= min(f[x[p+1]], ..., f[x[n-1]]).
{
    // Avoid worst case with already sorted input:
    const Type v = median3(*x[0], *x[n/2], *x[n-1]);

    ulong i = 0UL - 1;
    ulong j = n;
    while ( 1 )
    {
        do  ++i;
        while ( *x[i] < v );

        do  --j;
        while ( *x[j] > v );

        if ( i < j )  swap2(x[i], x[j]);
        else          return j;
    }
}
// -------------------------


template <typename Type>
void ptr_quick_sort(/*const Type *f,*/ ulong n, const Type **x)
// Sort x[] so that the sequence *x[0], *x[1], ..., *x[n-1] is ascending.
{
 start:
    if ( n<8 )  // parameter: threshold for nonrecursive algorithm
    {
        ptr_selection_sort(n, x);
        return;
    }

    ulong p = ptr_partition(n, x);
    ulong ln = p + 1;
    ulong rn = n - ln;

    if ( ln > rn )  // recursion for shorter sub-array
    {
        ptr_quick_sort(rn, x+ln);  // f[x[ln]] ... f[x[n-1]]  right
        n = ln;
    }
    else
    {
        ptr_quick_sort(ln, x);  // f[x[0]]  ... f[x[ln-1]]  left
        n = rn;
        x += ln;
    }

    goto start;
}
// -------------------------


#endif  // !defined HAVE_SORTPTR_H__
