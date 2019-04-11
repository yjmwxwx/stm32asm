#if !defined  HAVE_PERMRAND_PREF_H__
#define       HAVE_PERMRAND_PREF_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "aux0/swap.h"
#include "aux0/rand-idx.h"
#include "fxttypes.h"


template <typename Type>
void random_permute_pref(Type *f, ulong n, ulong m)
// Set the first m elements to a prefix of a random permutation.
// Same as: set the first m elements of f to a random permutation
// of a random selection of all n elements.
// Must have m<=n-1.
// Same as random_permute() if m>=n-1.
{
    if ( m>n-1 )  m = n-1;  // m>n-1 is not admissable
    for (ulong k=0, j=n;  k<m;  ++k, --j)
    {
        const ulong i = k + rand_idx(j);  // k<=i<n
        swap2(f[k], f[i]);
    }
}
// -------------------------


inline void random_pref_permutation(ulong *f, ulong n, ulong m)
// Create a length-m random permutation
// of a random selection of m form all n elements.
// Must have m<=n.
// Same as random_permutation() if m>=n-1.
{
    for (ulong k=0; k<n; ++k)  f[k] = k;
    random_permute_pref(f, n, m);
}
// -------------------------


#endif  // !defined HAVE_PERMRAND_PREF_H__
