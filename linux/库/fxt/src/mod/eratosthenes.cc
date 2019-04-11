// This file is part of the FXT library.
// Copyright (C) 2010, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "ds/bitarray.h"
#include "mod/isqrt.h"

#include "fxttypes.h"


bitarray *
make_prime_bitarray(ulong n, bitarray *B/*=0*/)
{
    if ( B && (n!=B->n_) )
    {
        delete B;
        B = 0;
    }

    if ( 0==B )  B = new bitarray( n );

    B->set_all();
    B->clear(0);
    B->clear(1);
    // ulong n = B->n_;
    ulong r = isqrt(n);
    ulong k = 0;
    while ( (k=B->next_set(k+1)) < n )
    {
        if ( k > r )  break;
        for (ulong j=k*k; j<n; j+=k )  B->clear(j);
    }

    return B;
}
// -------------------------

bitarray *
make_oddprime_bitarray(ulong n, bitarray *B/*=0*/)
// Sieve of Eratosthenes.
{
    if ( 0!=B )  delete B;
    B = new bitarray( n/2 );

    B->set_all();
    const ulong m = B->n_;

    B->clear(0);
    ulong r = isqrt(n);
    ulong i = 3;
    ulong ih = i/2;
    while ( i <= r )
    {
        if ( B->test( ih ) )
        {
            for (ulong kh=(i*i)/2;  kh<m;  kh+=i)  B->clear( kh );
        }
        ih = B->next_set( ih+1 );
        i = 2*ih + 1;
    }

    return B;
}
// -------------------------

