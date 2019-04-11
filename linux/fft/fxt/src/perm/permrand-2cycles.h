#if !defined  HAVE_PERMRAND_2CYCLES_H__
#define       HAVE_PERMRAND_2CYCLES_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "aux0/randf.h"
#include "sort/bsearch.h"

#include "fxttypes.h"


inline void init_harmonic(double *b, ulong n)
// Set  b[k] = sum( j=1, k+1, 1/j )
{
    double h = 1.0,   j = 1.0;
    for (ulong k=0; k<n; ++k)  { b[k]=h;  j+=1.0;  h+=1.0/j; }
}
// -------------------------


template <typename Type>
inline void random_permute_2cycles(Type *f, ulong n,
                                   double *tb=0, bool bi=false)
// Permute the n elements of f[] by a random permutation
//   consisting of exactly two cycles (must have n>=2).
// Set bi:=true to signal that the sums tb[k] = sum( j=1, k+1, 1/j )
//   have been precomputed (via init_harmonic()).
{
    if ( n<=2 )  return;

    double *b = tb;
    if ( tb==0 )  { b = new double[n];  bi=false; }
    if ( !bi )  init_harmonic(b, n);

    const double hn = b[n-2];
    const double t = rnd01() * hn;
    const ulong s = bsearch_geq(b, n-1, t) + 1;  // 1<s<n

    for (ulong k=1; k<s; ++k)
    {
        const ulong i = rand_idx(k);
        swap2(f[k], f[i]);
    }
    // skipping index s here
    for (ulong k=s+1; k<n; ++k)
    {
        const ulong i = rand_idx(k);
        swap2(f[k], f[i]);
    }

    if ( tb==0 )  delete [] b;
}
// -------------------------

template <typename Type>
inline void random_2cycles_permutation(Type *f, ulong n,
                                       double *tb=0, bool bi=false)
{
    for (ulong j=0; j<n; ++j)  f[j] = j;
    random_permute_2cycles(f, n, tb, bi);
}
// -------------------------


#endif  // !defined HAVE_PERMRAND_2CYCLES_H__
