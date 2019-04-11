#if !defined HAVE_COMP2COMB_H__
#define      HAVE_COMP2COMB_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "perm/reverse.h"
#include "fxttypes.h"

//: Conversion between combinations and compositions


inline void comp2comb_nk(ulong n, ulong k, ulong &N, ulong &K)
// A composition P(n,k) of n into (at most) k parts corresponds to
// a combination B(N,K) of K=n parts from N=n+k-1 elements:
//   P(n, k)  <-->  B(N, K) == B(n+k-1, n)
{
    N = n + k - 1;
    K = n;
}
// -------------------------

inline void comb2comp_nk(ulong N, ulong K, ulong &n, ulong &k)
// A combination B(N,K) of K elements out of N
// corresponds to a composition P(n,k) of n into (at most) k parts
// where k=N-K+1 and n=K:
//   B(N, K)  <-->  P(n, k) == P(K, N-K+1)
{
    n = K;
    k = N - K + 1;
}
// -------------------------


inline void comp2comb(const ulong *p, ulong k, ulong *b)
// Convert composition P(*, k) in p[] to combination in b[]
{
    for (ulong j=0, i=0, z=0; j<k; ++j)
    {
        ulong pj = p[j];
        for (ulong w=0; w<pj; ++w)   b[i++] = z++;
        ++z;
    }
}
// -------------------------

inline void comb2comp(const ulong *b, ulong N, ulong K, ulong *p)
// Convert combination B(N, K) in b[] to composition P(*,k) in p[]
// Must have: K>=1
{
    ulong k = N-K+1;
    for (ulong z=0; z<k; ++z)  p[z] = 0;
    --k;
    ulong c1 = N;
    while ( K-- )
    {
        ulong c0 = b[K];
        ulong d = c1 - c0;
        k -= (d-1);
        ++p[k];
        c1 = c0;
    }
}
// -------------------------


inline void reverse_combination(ulong *b, ulong N, ulong K)
// Reverse order and complement values in combination b[]
// Equivalent to order reversal of the corresponding composition:
//   B <--> P  ==>  reverse_combination(B) <--> reverse(P)
{
    for (ulong z=0; z<K; ++z)  b[z] = N-1-b[z];
    reverse(b, K);
}
// -------------------------


#endif  // !defined HAVE_COMP2COMB_H__
