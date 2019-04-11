#if !defined  HAVE_PERMRAND_PARITY_H__
#define       HAVE_PERMRAND_PARITY_H__
// This file is part of the FXT library.
// Copyright (C) 2010 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "aux0/swap.h"
#include "aux0/rand-idx.h"
#include "fxttypes.h"


template <typename Type>
void random_permute_parity(Type *f, ulong n, bool par)
// Randomly permute the elements of f, such that the
// parity of the permutation equals par.
// I.e. the minimal number of transpositions of the
//  permutation is even if par==0, else odd.
// Note: with n<=1 there is no odd permutation.
{
    if ( (par==1) && (n<2) )  return;  // not admissable

    bool pr = 0;  // identity has even parity
#if 0
    for (ulong k=n; k>1; --k)
    {
        const ulong i = rand_idx(k);
        swap2(f[k-1], f[i]);
        pr ^= ( k-1 != i );   // parity changes with swap
    }

#else

    for (ulong k=1; k<n; ++k)
    {
        const ulong i = rand_idx(k+1);
        swap2(f[k], f[i]);
        pr ^= ( k != i );   // parity changes with swap
    }
#endif

    if ( par!=pr )  swap2(f[0], f[1]);  // need to change parity
}
// -------------------------


inline void random_parity_permutation(ulong *f, ulong n, bool par)
// Create a random permutation.
{
    for (ulong k=0; k<n; ++k)  f[k] = k;
    random_permute_parity(f, n, par);
}
// -------------------------



#endif  // !defined HAVE_PERMRAND_PARITY_H__
