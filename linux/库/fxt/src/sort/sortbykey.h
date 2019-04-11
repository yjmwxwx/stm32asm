#if !defined  HAVE_SORTBYKEY_H__
#define       HAVE_SORTBYKEY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


//#include "sort/sort.h"
#include "sort/sortidx.h"
#include "perm/permapply.h"
//#include "fxtalloca.h"
#include "fxttypes.h"

template <typename Type1, typename Type2>
void sort_by_key(Type1 *f, ulong n, Type2 *key, ulong *tmp=0, bool skq=true)
// Sort f[] according to key[] in ascending order:
//   f[k] precedes f[j] if key[k]<key[j].
// If skq is true then key[] is also sorted.
//
// Example:
// Input: (elements of f[] as bit strings):
//    f[]  key[]
//    ...   0
//    ..1   1
//    .1.   1
//    .11   3
//    1..   1
//    1.1   3
//    11.   3
//    111   7
// After sort_by_key(f, n, key, 1):
//    ...   0
//    1..   1
//    .1.   1
//    ..1   1
//    .11   3
//    1.1   3
//    11.   3
//    111   7
{
//    ALLOCA(ulong, x, n);
    ulong *x = tmp;
    if ( 0==tmp )  x = new ulong[n];

    for (ulong k=0; k<n; ++k)  x[k] = k;
    idx_quick_sort(key, n, x);

    apply_inverse_permutation(x, f, n);

//    if ( skq )  quick_sort(key, n);
    if ( skq )  apply_inverse_permutation(x, key, n);

    if ( 0==tmp )  delete [] x;
}
// -------------------------


#endif  // !defined HAVE_SORTBYKEY_H__
