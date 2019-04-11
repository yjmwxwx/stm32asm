#if !defined  HAVE_WORDGRAY_H__
#define       HAVE_WORDGRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

//<<
// Word-wise Gray code and reversed Gray code.
// cf. bits/graycode.h and bits/graypower.h
//>>

template <typename Type>
void word_gray(Type *f, ulong n)
{
    for (ulong k=0;  k<n-1;  ++k)  f[k] ^= f[k+1];
}
// -------------------------

template <typename Type>
void inverse_word_gray(Type *f, ulong n)
{
#if 1
    ulong x = 0,  k = n;
    while ( k-- )  { x ^= f[k];  f[k] = x; }
#else
    for (ulong s=1; s<n; s*=2)
    {
        // word_gray ** s:
        for (ulong k=0, j=k+s;  j<n;  ++k, ++j)  f[k] ^= f[j];
    }
#endif
}
// -------------------------

template <typename Type>
void word_gray_pow(Type *f, ulong n, ulong x)
// result is identical to
//   for (ulong k=0; k<x; ++k)  word_gray(f, n);
// Work <= n/2
{
    for (ulong s=1; s<n; s*=2)
    {
        if ( x & 1 )
        {
            // word_gray ** s:
            for (ulong k=0, j=k+s;  j<n;  ++k, ++j)  f[k] ^= f[j];
        }
        x >>= 1;
    }
}
// -------------------------


template <typename Type>
void word_rev_gray(Type *f, ulong n)
{
    for (ulong k=n-1; 0!=k; --k)  f[k] ^= f[k-1];
}
// -------------------------

template <typename Type>
void inverse_word_rev_gray(Type *f, ulong n)
{
#if 1
    ulong x = 0;
    for (ulong k=0;  k<n; ++k)  { x ^= f[k];  f[k] = x; }
#else
    for (ulong s=1; s<n; s*=2)
    {
        // word_rev_gray ** s:
        for (ulong k=n-1, j=k-s;  k>=s;  --k, --j)  f[k] ^= f[j];
    }
#endif
}
// -------------------------

template <typename Type>
void word_rev_gray_pow(Type *f, ulong n, ulong x)
// result is identical to
//   for (ulong k=0; k<x; ++k)  word_rev_gray(f, n);
// work <= n/2
{
    x &= (n-1);  // modulo n
    for (ulong s=1; s<n; s*=2)
    {
        if ( x & 1)
        {
            // word_rev_gray ** s:
            for (ulong k=n-1, j=k-s;  k>=s;  --k, --j)  f[k] ^= f[j];
        }
        x >>= 1;
    }
}
// -------------------------



#endif  // !defined HAVE_WORDGRAY_H__
