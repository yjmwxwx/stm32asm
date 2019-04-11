// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include "bits/print-bin.h"

#include "bits/bitsperlong.h"
#include "comb/comb-print.h"  // print_deltaset_as_set()

#include "fxttypes.h"
#include "fxtio.h"
#include "fxtalloca.h"


//: Default is to print zeros as dots.
static const char n01[] = {'.', '1'};
//static const char n01[] = {'0', '1'};


void
print_bin(const char *bla, unsigned long long x, ulong pd/*=0*/, const char *c01/*=0*/)
// Print x to radix-2.
// pd: how many bits to print.
{
    cout << bla;

    if ( 0==pd )  pd = BITS_PER_LONG;
    unsigned long long m = 1ULL << (BITS_PER_LONG_LONG-1);
    m >>= (BITS_PER_LONG_LONG-pd);

    const char *d = ( 0==c01 ?  n01 : c01 );

    for (  ; 0!=m; m>>=1)  cout << d[ 0!=(x & m) ];
}
// -------------------------

void
print_bin_vec(const char *bla, unsigned long long x, ulong pd/*=0*/, const char *c01/*=0*/)
// Print x to radix-2, least significant bits first (as Vector).
// pd: how many bits to print.
{
    cout << bla;

    if ( 0==pd )  pd = BITS_PER_LONG;
    const char *d = ( 0==c01 ?  n01 : c01 );

    for (ulong j = 0; j<pd; ++j)
    {
        cout << d[ 0!=(x & 1) ];
        x >>= 1;
    }
}
// -------------------------


void
print_idx_seq(const char *bla, unsigned long long x, ulong off/*=0*/)
// Print x as index sequence:
//   x=....1..11  ==>  [0, 1, 4]
// With offsets off!=0 start index with off instead of zero.
{
    cout << bla;
    cout << "[";
    ulong j = 0;
    do
    {
        if ( x & 1UL )
        {
            cout << j + off;
            if ( x>1 )  cout << ", ";
        }
        ++j;
        x >>= 1;
    }
    while ( x );

    cout << "]";
}
// -------------------------
