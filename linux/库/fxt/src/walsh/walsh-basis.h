#if !defined  HAVE_WALSH_BASIS_H__
#define       HAVE_WALSH_BASIS_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "bits/parity.h"
#include "bits/graycode.h"
#include "bits/grsnegative.h"
//#include "bits/revgraycode.h"
#include "bits/revbin.h"  // revbin()
#include "bits/bit2pow.h"  // ld()
#include "fxttypes.h"  // ulong


template <typename Type>
void walsh_wak_basis(Type *f, ulong n, ulong k)
// Compute the k-th basis function for
// the Walsh-Kronecker transform (wak-functions).
{
    for (ulong i=0; i<n; ++i)
    {
        ulong x = i & k;
        x = parity(x);
        f[i] = ( 0==x ? +1 : -1 );
    }
}
// -------------------------

template <typename Type>
void walsh_pal_basis(Type *f, ulong n, ulong k)
// Compute the k-th basis function for
// the Walsh-Paley transform (pal-functions).
{
    k = revbin(k, ld(n));
    for (ulong i=0; i<n; ++i)
    {
        ulong x = i & k;
        x = parity(x);
        f[i] = ( 0==x ? +1 : -1 );
    }
}
// -------------------------


template <typename Type>
void walsh_wal_basis(Type *f, ulong n, ulong k)
// Compute the k-th basis function for
// the Walsh-Kaczmarz transform (wal-functions).
{
    k = revbin(k, ld(n)+1);
    k = gray_code(k);
//    // =^=
//    k = revbin(k, ld(n));
//    k = rev_gray_code(k);
    for (ulong i=0; i<n; ++i)
    {
        ulong x = i & k;
        x = parity(x);
        f[i] = ( 0==x ? +1 : -1 );
    }
}
// -------------------------

template <typename Type>
void walsh_wal_rev_basis(Type *f, ulong n, ulong k)
// Compute the k-th basis function for the transform walsh_wal_rev()
{
    k = revbin(k, ld(n));
    k = gray_code(k);
    // =^=
//    k = rev_gray_code(k);
//    k = revbin(k, ld(n));
    for (ulong i=0; i<n; ++i)
    {
        ulong x = i & k;
        x = parity(x);
        f[i] = ( 0==x ? +1 : -1 );
    }
}
// -------------------------

template <typename Type>
void walsh_q1_basis(Type *f, ulong n, ulong k)
// Compute the k-th basis function for the transform walsh_q1()
{
    ulong qk = (grs_negative_q(k) ? 1 : 0);
    k = gray_code(k);
    k = revbin(k, ld(n));
    for (ulong i=0; i<n; ++i)
    {
        ulong x = i & k;
        x = parity(x);
        ulong qi = (grs_negative_q(i) ? 1 : 0);
        x ^= (qk ^ qi);
        f[i] = ( 0==x ? +1 : -1 );
    }
}
// -------------------------

template <typename Type>
void walsh_q2_basis(Type *f, ulong n, ulong k)
// Compute the k-th basis function for the transform walsh_q2()
{
    ulong qk = (grs_negative_q(k) ? 1 : 0);
    k = revbin(k, ld(n));
    k = gray_code(k);
    for (ulong i=0; i<n; ++i)
    {
        ulong x = i & k;
        x = parity(x);
        ulong qi = (grs_negative_q(i) ? 1 : 0);
        x ^= (qk ^ qi);
        f[i] = ( 0==x ? +1 : -1 );
    }
}
// -------------------------


#endif  // !defined HAVE_WALSH_BASIS_H__
