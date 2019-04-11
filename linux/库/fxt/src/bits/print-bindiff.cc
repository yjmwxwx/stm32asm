// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

//#include "bits/print-bin.h"

#include "bits/revbin.h"
#include "bits/bitsperlong.h"

#include "fxttypes.h"
#include "fxtio.h"


static const char n01pm[] = {'.', '1', '+', '-'};

void
print_bin_diff(const char*bla,
               unsigned long long x1,  // ==old
               unsigned long long x2,  // ==new
               ulong pd/*=0*/,
               const char *c01pm/*=".1+-"*/)
// Binary print difference between two values x1 and x2:
// Bits that agree between x1 and x2 are printed as
//    c01pm[0]=='.' for zero and c01pm[1]='1' for one
// Bits that differ between x1 and x2 are printed as
//    c01pm[2]=='+' if set in x2 (i.e. bit was added)
//    c01pm[3]=='-' if set in x1 (i.e. bit was removed)
//
// Example:
//         x1==1..11.111
//         x2==1.111...1
//         eq==11.111..1
//   output = "1.+11.--1"
{
    cout << bla;

    if ( 0==pd )  pd = BITS_PER_LONG;
    unsigned long long m = 1ULL << (BITS_PER_LONG_LONG-1);
    m >>= (BITS_PER_LONG_LONG-pd);

    const char *d = ( 0==c01pm ?  n01pm : c01pm );

    unsigned long long eq = x1 ^ (~x2);  // bits that agree between x1 and x2
    for (  ; 0!=m; m>>=1)
    {
        if ( m&eq )  cout << d[ 0!=(x1 & m) ];
        else
        {
            if ( x2&m )  cout << d[2];
            else         cout << d[3];
        }
    }
}
// -------------------------

void
print_bin_vec_diff(const char*bla,
                   unsigned long long x1,
                   unsigned long long x2,
                   ulong pd/*=0*/,
                   const char *c01pm/*=".1+-"*/)
{
    x1 = revbin(x1, pd);
    x2 = revbin(x2, pd);
    print_bin_diff(bla, x1, x2, pd, c01pm);
}
// -------------------------
