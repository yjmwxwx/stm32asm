#if !defined  HAVE_BITMAT_INLINE_H__
#define       HAVE_BITMAT_INLINE_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "bits/parity.h"
#include "bits/bitrotate.h"

inline ulong bitmat_get(const ulong *M, ulong r, ulong c)
// Return entry M[r,c]
{
    return  (M[r]>>c) & 1UL;
}
// -------------------------

inline void bitmat_set(ulong *M, ulong r, ulong c, ulong v)
// Set M[r,c] = v
{
#if 0  // with branch:
    const ulong x = 1UL << c;
    if ( v )  M[r] |=  x;
    else      M[r] &= ~x;
#else  // branchless:
    const ulong Mr = M[r];
    const ulong m = (1UL << c);    // only bit c
    v <<= c;
    const ulong x = (Mr & m) ^ v;  // one bit if change, else zero
    M[r] = Mr ^ x;
#endif
}
// -------------------------



inline void bitmat_copy(const ulong *M1, ulong n, ulong *M2)
// M2 = M1 (for binary matrices)
{
    for (ulong k=0; k<n; ++k)  M2[k] = M1[k];
}
// -------------------------

inline void bitmat_unit(ulong *M, ulong n)
// M = unity
{
    for (ulong k=0, b=1UL;  k<n;  ++k, b<<=1)  M[k] = b;
}
// -------------------------


inline bool bitmat_is_unit(const ulong *M, ulong n)
// Return whether M equals unity.
{
    for (ulong k=0, b=1UL;  k<n;  ++k, b<<=1)
    {
        if ( M[k] != b )  return  false;
    }
    return  true;
}
// -------------------------

inline bool bitmat_is_zero(const ulong *M, ulong n)
// Return whether M equals 0.
{
    ulong t = 0;
    for (ulong k=0;  k<n;  ++k)  t |= M[k];
    return  ( 0==t );
}
// -------------------------


inline void bitmat_add_unit(ulong *M, ulong n)
// M += unity
{
    for (ulong k=0, b=1UL;  k<n;  ++k, b<<=1)  M[k] ^= b;
}
// -------------------------


inline ulong bitmat_trace(const ulong *M, ulong n)
// Return the trace of M.
{
    ulong t = 0;
    for (ulong i=0; i<n; ++i)  t ^= (M[i] >> i);
    return  t & 1UL;
}
// -------------------------

inline bool bitmat_eq(const ulong *M1, const ulong *M2, ulong n)
// Return whether M1 equals M2.
{
    for (ulong i=0; i<n; ++i)  if ( M1[i] ^ M2[i] )  return false;
    return  true;
}
// -------------------------


inline ulong bitmat_mult_Mv(const ulong *M, ulong n, ulong v)
// Return M*v where
// M is a binary (n x n) matrix, v is a binary vector.
{
    ulong p = 0;
    for (ulong j=0; j<n; ++j)
    {
        ulong t = parity( M[j] & v );
        p |= (t<<j);
    }
    return p;
}
// -------------------------


inline ulong bitmat_mult_vM(const ulong *M, ulong n, ulong v)
// Return v*M where
// M is a binary (n x n) matrix, v is a binary vector.
{
    ulong p = 0;
    for (ulong j=0; j<n; ++j)
    {
        if ( v&1 )  p ^= M[j];
        v >>= 1;
    }
    return p;
}
// -------------------------


inline void bitmat_companion(ulong p, ulong n, ulong *M)
// Create companion matrix for the binary polynomial
// p(x) = x^n + \sum_{i=0}^{n-1}{c_i*x^i}
{
    ulong h = 1UL << (n-1);
    ulong r = 0;
    if ( p & 1UL )  r |= h;
    M[0] = r;
    ulong d = 1UL;
    for (ulong i=1; i<n; ++i)
    {
        r = d;
        d <<= 1;
        p >>= 1;
        if ( p & 1UL )  r |= h;
        M[i] = r;
    }
}
// -------------------------


inline void bitmat_circulant(ulong v, ulong n, ulong *M)
// Create circulant matrix with rows that are cyclic shifts of v.
{
    for (ulong j=0; j<n; ++j)
    {
        M[j] = v;
        v = bit_rotate_left(v, 1, n);
    }
}
// -------------------------


#endif  // !defined HAVE_BITMAT_INLINE_H__
