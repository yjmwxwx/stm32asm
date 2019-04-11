#if !defined  HAVE_HEAPSORT_H__
#define       HAVE_HEAPSORT_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "ds/heap.h"

#include "aux0/swap.h"


template <typename Type>
void heap_sort(Type *x, ulong n)
// Sort x[] into ascending order.
{
    build_heap(x, n);
    Type *p = x - 1;
    for (ulong k=n; k>1; --k)
    {
        swap2(p[1], p[k]);  // move largest to end of array
        --n;                // remaining array has one element less
        heapify(p, n, 1);   // restore heap-property
    }
}
// -------------------------


template <typename Type>
void heap_sort_descending(Type *x, ulong n)
// Sort x[] into descending order.
{
    build_heap(x, n);
    Type *p = x - 1;
    for (ulong k=n; k>1; --k)
    {
        ++p;  --n;         // remaining array has one element less
        heapify(p, n, 1);  // restore heap-property
    }
}
// -------------------------


#endif  // !defined HAVE_HEAPSORT_H__
