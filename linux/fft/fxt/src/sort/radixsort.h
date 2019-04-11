#if !defined  HAVE_RADIXSORT_H__
#define       HAVE_RADIXSORT_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "restrict.h"


// sort/radixsort.cc:
bool is_counting_sorted(const ulong *f, ulong n, ulong b0, ulong m);
void counting_sort_core(const ulong * restrict f, ulong n, ulong * restrict g, ulong b0, ulong m);
void radix_sort(ulong *f, ulong n);


#endif  // !defined HAVE_RADIXSORT_H__
